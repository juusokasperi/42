import socket
import time
import re

class Colours:
    HEADER = "\033[95m"     # [TEST]
    CYAN = "\033[96m"       # [MSG]
    BLUE = "\033[94m"       # [RESPONSE]
    GREEN = "\033[92m"      # [PASS]
    RED = "\033[91m"        # [FAIL]
    RESET = "\033[0m"

def log_test(msg):
    print(f"\n{Colours.HEADER}[TEST]{Colours.RESET} {msg}")

def log_msg(msg):
    print(f"{Colours.CYAN}[MSG]{Colours.RESET} {msg}")

def log_response(msg):
    print(f"{Colours.BLUE}[RESPONSE]{Colours.RESET} {msg}")

def log_pass(msg="Test passed"):
    print(f"{Colours.GREEN}[PASS]{Colours.RESET} {msg}")

def log_fail(msg="Test failed"):
    print(f"{Colours.RED}[FAIL]{Colours.RESET} {msg}")


class IRCClient:
    def __init__(self, server, port, password=None):
        self.server = server
        self.port = port
        self.password = password
        self.sock = None
        self.log = []

    def connect(self):
        self.sock = socket.create_connection((self.server, self.port))
        self.sock.settimeout(2)
        
        if self.password:
            self.send(f"PASS {self.password}")
    def send(self, message):
        self.sock.sendall((message + "\r\n").encode())
        self.log.append(("SEND", message))
        
    def send_raw(self, data):
        self.sock.sendall(data.encode())
        self.log.append(("SEND", data))
    
    def recv(self):
        try:
            data = self.sock.recv(4096).decode()
        except socket.timeout:
            return ""
        lines = data.split("\r\n")
        for line in lines:
            if line:
                self.log.append(("RECV", line))
        return data

    def close(self):
        if self.sock:
            self.sock.close()
            self.sock = None

    def get_log(self):
        return self.log

    def clear_log(self):
        self.log = []
        
    def wait_for(self, pattern, timeout=0.5):
        """Wait and check received lines for a regex pattern"""
        start_pos = len(self.log) 
        end_time = time.time() + timeout
        while time.time() < end_time:
            self.recv()
            for t, line in self.log[start_pos:]:
                if t == "RECV" and re.search(pattern, line):
                    return line
            time.sleep(0.2)
        return None
    
    def collect_expected_responses(self, patterns, timeout=1.0):
        results = {pat: None for pat in patterns}
        deadline = time.time() + timeout
        start_pos = len(self.log)  # Start checking from here
        while time.time() < deadline and any(val is None for val in results.values()):
            self.recv()
            for t, line in self.log[start_pos:]:
                if t != "RECV":
                    continue
                for pat in results:
                    if results[pat] is None and re.search(pat, line):
                        results[pat] = line
            time.sleep(0.05)
        return results
    
# Function for creating clients

def make_client(nickname, server="localhost", port=6667, password="mypassword"):
    client = IRCClient(server, port, password)
    client.connect()
    client.send(f"NICK {nickname}")
    client.nick = nickname
    return client

# --- Test categories ---

class TestConnection:
    def __init__(self, server="localhost", port=6667, password="mypassword"):
        self.server = server
        self.port = port
        self.password = password

    def test_connection_without_password(self):
        log_test("Connection - No password provided")
        client = IRCClient(self.server, self.port)
        client.connect()
        client.send("NICK NoPass")
        client.send("USER test 0 * :Test User")
        
        response = client.wait_for(r":.* 464 .*")  # ERR_PASSWDMISMATCH
        log_response(response)
        assert response, log_fail("No password error received")
        log_pass("Connection correctly rejected without password")
        client.close()

    def test_wrong_password(self):
        log_test("Connection - Wrong password")
        client = IRCClient(self.server, self.port, "wrongpass")
        client.connect()
        client.send("NICK WrongPass")
        client.send("USER test 0 * :Test User")
        
        response = client.wait_for(r":.* 464 .*")  # ERR_PASSWDMISMATCH
        log_response(response)
        assert response, log_fail("Wrong password not rejected")
        log_pass("Wrong password correctly rejected")
        client.close()

class TestRegistration:
    def __init__(self, client):
        self.client = client

    def test_registration_order_nick_first(self):
        log_test("Registration - NICK before USER")
        client = IRCClient("localhost", 6667, "mypassword")
        client.connect()
        client.send("NICK Order1")
        client.send("USER order 0 * :Order Test")
        
        response = client.wait_for(r":.* 001 .*")
        log_response(response)
        assert response, log_fail("Registration failed with NICK first")
        log_pass("NICK->USER registration order works")
        client.close()

    def test_registration_order_user_first(self):
        log_test("Registration - USER before NICK")
        client = IRCClient("localhost", 6667, "mypassword")
        client.connect()
        client.send("USER order 0 * :Order Test")
        client.send("NICK Order2")
        
        response = client.wait_for(r":.* 001 .*")
        log_response(response)
        assert response, log_fail("Registration failed with USER first")
        log_pass("USER->NICK registration order works")
        client.close()

    def test_commands_before_registration(self):
        log_test("Commands before registration")
        client = IRCClient("localhost", 6667, "mypassword")
        client.connect()
        
        # Try commands before registering
        commands = ["JOIN #test", "PRIVMSG #test :hello", "MODE #test +t"]
        for cmd in commands:
            client.send(cmd)
            log_msg(cmd)
            response = client.wait_for(r":.* 451 .*")  # ERR_NOTREGISTERED
            log_response(response)
            assert response, log_fail(f"No ERR_NOTREGISTERED for {cmd}")
        
        log_pass("Commands before registration correctly rejected")
        client.close()

class TestUser:
    def __init__(self, client):
        self.client = client

    def test_user_sanitization_cases(self):
        log_test("USER - Sanitization of invalid usernames and realnames")

        test_cases = {
            # Format: (command to send, expected numeric reply, description)
            "USER": ("461", "Missing parameters"),
            "USER user 0 * :Real\nName": ("001", "Valid username and sanitized realname"),
            "USER inv user 0 * :Real": ("461", "Too many words in username param"),
            "USER tester\n3 0 * :Realme": ("001", "Valid sanitized username and realname"),
            "USER tester 0 * :": ("461", "Empty realname")
        }

        for cmd, (expected_reply, description) in test_cases.items():
            client = IRCClient("localhost", 6667, "mypassword")
            client.connect()
            client.clear_log()
            
            client.send("NICK Nicky")
            client.send(cmd)
            log_msg(f"{cmd}")
            
            if expected_reply == "001":
                response = client.wait_for(r":.* 001 .*")
                log_response(response)
                assert response, log_fail(f"Did not receive 001 welcome for: {cmd}")
                log_pass(f"{description}")
                
            else:
                pattern = fr":.* {expected_reply} .*"
                err = client.wait_for(pattern)
                log_response(err)
                assert err, log_fail(f"Expected {expected_reply} for: {cmd}")
                log_pass(f"{description} - got {expected_reply}")
        client.close()

    def test_user_reregistration(self):
        log_test("USER - Re-registration")
        self.client.clear_log()
        msg = "USER another 0 * :Another name"
        self.client.send(msg)
        log_msg(msg)
        response = self.client.wait_for(r":.* 462 .* USER :You may not reregister")
        log_response(response)
        assert response, log_fail("Did not receive ERR_ALREADYREGISTRED")
        log_pass("Re-registration blocked (ERR_ALREADYREGISTRED)")

class TestNick:
    def __init__(self, client):
        self.client = client

    def test_nick_changes(self):
        log_test("NICK - Nick changes")
        self.client.clear_log()

        # Change to a series of valid nicknames
        nick_changes = ["Alias", "nick-two", "Nope3", "Nicky[]", ":withcolon", "Nicky"]
        
        for new_nick in nick_changes:
            self.client.clear_log()
            msg = f"NICK {new_nick}"
            self.client.send(msg)
            log_msg(msg)

            response = self.client.wait_for(r".*") or ""
            log_response(response)
            if (
                re.search(rf":\S+ NICK :{re.escape(new_nick)}", response) or
                " 432 " in response
                ):
                log_pass(f"NICK change to '{new_nick}' accepted or properly rejected")
                if "NICK" in response and " :" in response:
                    self.client.nick = new_nick
                else:
                    assert False, log_fail(f"Unexpected response for NICK '{new_nick}': {response.strip()}")

    def test_duplicate_nick(self, nick):
        log_test(f"NICK - Duplicate")
        otherNick = "Wannabe"
        other = make_client(f"{otherNick}")
        other.send("USER Nameless whatever * :real wannabe")
        other.wait_for(r":.* 001 ")

        self.client.clear_log()
        msg = f"NICK {otherNick}"
        self.client.send(msg)
        log_msg(msg)

        pattern = fr":.* 433 {nick} {otherNick} :Nickname is already in use"
        response = self.client.wait_for(pattern)
        log_response(response)
        assert response, log_fail(f"Did not receive ERR_NICKNAMEINUSE for nick {nick}")
        log_pass(f"Nickname' {nick}' correctly rejected as duplicate with ERR_NICKNAMEINUSE")
        other.close()

    def test_invalid_nick(self):
        log_test("NICK - Invalid nick")
        invalid_cases = [
            "12me",
             "_myname",
            "!invalid",
            "veryveryveryverylongname",
            ":space jam"
        ]
        for nick in invalid_cases:
            self.client.clear_log()
            msg = f"NICK {nick}"
            self.client.send(msg)
            log_msg(msg)
            pattern = fr":.* 432 {self.client.nick} .* :Erroneous nickname"
            response = self.client.wait_for(pattern)
            log_response(response)
            assert response, log_fail("Did not receive ERR_ERRONEOUSNICKNAME")
            log_pass(f"Received correct error ERR_ERRONEOUSNICKNAME")
            
    def test_nick_without_parameter(self):
        log_test("NICK - without parameter")
        self.client.clear_log()
        msg = "NICK"
        self.client.send(msg)
        log_msg(msg)
        response = self.client.wait_for(f":.* 431 {self.client.nick} :No nickname given")
        log_response(response)
        assert response, log_fail("Did not receive ERR_NONICKNAMEGIVEN")
        log_pass("Received correct error ERR_NONICKNAMEGIVEN")

class TestMessageBuffering:
    def __init__(self, client):
        self.client = client
    
    def test_partial_message(self, part1, part2):
        log_test("Partial message buffering")

        self.client.clear_log()
        self.client.send_raw(part1)  # No newline
        log_msg(part1)
        self.client.send_raw(part2)  # Still no newline
        log_msg(part2)

        # Now send newline to complete both messages
        self.client.send_raw("\r\n")
        log_msg("\r\n")
        response = self.client.wait_for(r".* 432 .*")
        log_response(response)
        assert response, log_fail("Did not receive error after completing message")
        log_pass("Server waited until newline before processing")

    def test_multiple_commands_in_one_message(self, command1, command2):
        log_test("Multiple commands in one buffer")

        self.client.clear_log()
        raw_msg = f"{command1} {command2}\r\n"
        self.client.send_raw(raw_msg)
        log_msg(raw_msg)
        response1 = self.client.wait_for(r".* 432 .*")
        log_response(response1)
        assert response1, log_fail("Did not receive error from combined command")
        log_pass("Server processed multiple commands in one message")

    def test_character_by_character_message(self):
        log_test("Character-by-character message assembly")
        
        command = "NICK invalid_nick_123456789"  # Too long nickname
        self.client.clear_log()
        
        # Send each character individually
        for char in command:
            self.client.send_raw(char)
            log_msg(f"Sent char: '{char}'")
            time.sleep(0.01)  # Small delay between characters
        
        # Complete with CRLF
        self.client.send_raw("\r\n")
        log_msg("\\r\\n")
        
        response = self.client.wait_for(r".* 432 .*")
        log_response(response)
        assert response, log_fail("Server didn't process character-by-character message")
        log_pass("Server correctly buffered character-by-character input")

    def test_mixed_line_endings(self):
        log_test("Mixed line endings buffering")
        
        test_cases = [
            ("NICK 1bad", "\r\n"),      # Standard CRLF
            ("NICK _bad", "\n"),        # LF only
            ("NICK !test3", "\r"),      # CR only (should not complete)
            ("", "\n"),                 # Complete the CR-only line
        ]
        
        self.client.clear_log()
        
        for command, ending in test_cases:
            full_msg = command + ending
            self.client.send_raw(full_msg)
            log_msg(f"{repr(full_msg)}")
            time.sleep(0.1)
            if ending == "\r":
                continue
            # Should get responses for properly terminated messages
            response = self.client.wait_for(r".* (432|433) .*")
            log_response(response)
            assert response, log_fail("Server didn't handle line ending correctly")
            log_pass("Server handled line ending appropriately")

    def test_very_long_partial_messages(self):
        log_test("Very long partial message buffering")
        
        # Create a long message in parts
        prefix = "PRIVMSG #test :"
        long_text = "A" * 200
        suffix = " END"
        
        self.client.clear_log()
        
        # Send in three parts
        parts = [prefix, long_text, suffix]
        for i, part in enumerate(parts):
            self.client.send_raw(part)
            log_msg(f"Part {i+1}: {part[:20]}...")
            time.sleep(0.05)
        
        # Complete the message
        self.client.send_raw("\r\n")
        log_msg("\\r\\n")
        
        # Should process the complete long message
        response = self.client.wait_for(r".*")
        log_response(response)  
        log_pass("Server buffered very long partial message correctly")

    def test_ping_pong(self):
        log_test("PING/PONG handling")

        self.client.clear_log()
        msg = "PING 12345"
        self.client.send(msg)
        log_msg(msg)
        response = self.client.wait_for(r".*PONG.*12345.*")
        log_response(response)
        assert response, log_fail("PONG not received")
        log_pass("Server replied to PING with correct PONG")

class TestPrivmsg:
    def __init__(self, c1, c2, c3):
        self.c1 = c1
        self.c2 = c2
        self.c3 = c3

    def test_privmsg_user(self):
        log_test("PRIVMSG between two users")

        self.c2.clear_log()
        msg = "Hello from c1 to c2!"
        privmsg = f"PRIVMSG {self.c2.nick} :{msg}"
        self.c1.send(privmsg)
        log_msg(privmsg)
        expected_pattern = fr":{self.c1.nick} PRIVMSG {self.c2.nick} :{re.escape(msg)}"
        response = self.c2.wait_for(expected_pattern)
        log_response(response)
        assert response, log_fail("PRIVMSG to user not received")
        log_pass("PRIVMSG to user delivered correctly")
        
    def test_privmsg_multiple_targets(self):
        log_test("PRIVMSG to multiple user targets")

        self.c2.clear_log()
        self.c3.clear_log()
        msg = "Hello to both!"
        privmsg = f"PRIVMSG {self.c2.nick},{self.c3.nick} :{msg}"
        self.c1.send(privmsg)
        log_msg(privmsg)
        
        pattern_c2 = fr":{self.c1.nick} PRIVMSG {self.c2.nick} :{re.escape(msg)}"
        response_c2 = self.c2.wait_for(pattern_c2)
        log_response(response_c2)
        
        pattern_c3 = fr":{self.c1.nick} PRIVMSG {self.c3.nick} :{re.escape(msg)}"
        response_c3 = self.c3.wait_for(pattern_c3)
        log_response(response_c3)

        assert response_c2, log_fail("PRIVMSG to first user not received")
        assert response_c3, log_fail("PRIVMSG to second user not received")
        log_pass("PRIVMSG to multiple users delivered correctly")

    def test_privmsg_channel(self):
        log_test("PRIVMSG to a channel")

        channel = "#msg_channel"
        self.c1.send(f"JOIN {channel}")
        self.c2.send(f"JOIN {channel}")
        self.c1.wait_for(fr":.* JOIN {channel}")
        self.c2.wait_for(fr":.* JOIN {channel}")

        self.c2.clear_log()
        msg = "Hello everyone in the channel!"
        privmsg = f"PRIVMSG {channel} :{msg}"
        self.c1.send(privmsg)
        log_msg(privmsg)
        expected_pattern = fr":.* PRIVMSG {channel} :{msg}"
        response = self.c2.wait_for(expected_pattern)
        log_response(response)
        assert response, log_fail("PRIVMSG to channel not received")
        log_pass("PRIVMSG to channel delivered correctly")
    
    def test_privmsg_multiple_channels(self):
        log_test("PRIVMSG to multiple channel targets")

        msg = "Hello channels!"
        channel1 = "#chan1"
        channel2 = "#chan2"

        self.c1.send(f"JOIN {channel1}")
        self.c1.send(f"JOIN {channel2}")
        self.c2.send(f"JOIN {channel1}")
        self.c3.send(f"JOIN {channel2}")
        time.sleep(1)

        self.c2.clear_log()
        self.c3.clear_log()

        privmsg = f"PRIVMSG {channel1},{channel2} :{msg}"
        self.c1.send(privmsg)
        log_msg(privmsg)

        pattern1 = fr":{self.c1.nick} PRIVMSG {channel1} :{re.escape(msg)}"
        pattern2 = fr":{self.c1.nick} PRIVMSG {channel2} :{re.escape(msg)}"

        response1 = self.c2.wait_for(pattern1)
        response2 = self.c3.wait_for(pattern2)
        log_response(response1)
        log_response(response2)

        assert response1, log_fail("PRIVMSG to first channel not received")
        assert response2, log_fail("PRIVMSG to second channel not received")
        log_pass("PRIVMSG to multiple channels delivered correctly")

    def test_privmsg_no_recipient(self):
        log_test("PRIVMSG with missing recipient")
        invalid_target = "PRIVMSG :no target"
        self.c1.send(invalid_target)
        log_msg(invalid_target)
        response = self.c1.wait_for(rf".* 412 {self.c1.nick}")
        log_response(response)
        assert response, log_fail("Missing error)")
        log_pass("PRIVMSG with no recipient correctly failed")
        # the error should be ERR_NORECIPIENT but difficult to distinguish between empty
        # target and empty message in params

    def test_privmsg_no_such_channel(self):
        log_test("PRIVMSG to non-existent channel")
        nonexistent_channel = "#doesnotexist"
        message = f"PRIVMSG {nonexistent_channel} :Hello?"
        self.c1.send(message)
        log_msg(message)
        response = self.c1.wait_for(rf".* 401 {self.c1.nick}") # ERR_NOSUCHNICK
        log_response(response)
        assert response, log_fail("Missing ERR_NOSUCHNICK (401)")
        log_pass("PRIVMSG to non-existent channel correctly failed")

    def test_privmsg_no_text(self):
        log_test("PRIVMSG with missing message")
        invalid_message = f"PRIVMSG {self.c2.nick}"
        self.c1.send(invalid_message)
        log_msg(invalid_message)
        response = self.c1.wait_for(rf".* 412 {self.c1.nick}") # ERR_NOTEXTTOSEND
        log_response(response)
        assert response, log_fail("Missing ERR_NOTEXTTOSEND (412)")
        log_pass("PRIVMSG with no text correctly failed")

class TestChannelNames:
    def __init__(self, client):
        self.client = client

    def test_valid_channel_names(self):
        log_test("Channel names - Valid formats")
        valid_channels = ["#test", "#test123", "#test-channel", "#test_chan", "#3stooges"]
        
        for channel in valid_channels:
            self.client.send(f"JOIN {channel}")
            log_msg(f"JOIN {channel}")
            response = self.client.wait_for(rf":.* JOIN {re.escape(channel)}")
            log_response(response)
            assert response, log_fail(f"Failed to join valid channel {channel}")
            
            self.client.send(f"PART {channel}")
            self.client.wait_for(rf":.* PART {re.escape(channel)}")
        
        log_pass("All valid channel names accepted")

    def test_invalid_channel_names(self):
        log_test("Channel names - Invalid formats")
        invalid_channels = ["test", "#comma,trouble", "#", "#$bling:bling", "#space\ncowboys", "'#chan chan'"] #"#waywaytoolongchannelnameforitsowngoodtoworkinanyway"]
        
        for channel in invalid_channels:
            self.client.send(f"JOIN {channel}")
            log_msg(f"JOIN {channel}")
            response = self.client.wait_for(r":.* (403|476) .*")  # ERR_NOSUCHCHANNEL or ERR_BADCHANMASK
            log_response(response)
            assert response, log_fail(f"Invalid channel {channel} was accepted")
        
        log_pass("All invalid channel names rejected")

class TestChannelMembership:
    def __init__(self, c1, c2, c3, chan="#testchannel"):
        self.c1 = c1
        self.c2 = c2
        self.c3 = c3
        self.channel = chan
    
    def test_create_channel(self):
        log_test("Channel - Create")
        self.c1.clear_log()
        msg = f"JOIN {self.channel}"
        self.c1.send(msg)
        log_msg(msg)
        response = self.c1.wait_for(rf"{self.c1.nick}![^ ]+ JOIN {self.channel}")
        log_response(response)
        assert response, log_fail(f"c1 failed to join/create {self.channel}")
        log_pass(f"c1 successfully joined/created {self.channel}")
        
    def test_join_multiple(self):
        log_test("Channel - Multiple clients join")
        msg_c2 = f"JOIN {self.channel}"
        self.c2.send(msg_c2)
        log_msg(msg_c2)
        response = self.c2.wait_for(rf":{self.c2.nick}![^ ]+ JOIN {self.channel}")
        log_response(response)
        assert response, log_fail(f"c2 failed to join {self.channel}")

        msg_c3 = f"JOIN {self.channel}"
        self.c3.send(msg_c3)
        log_msg(msg_c3)
        response = self.c3.wait_for(rf":{self.c3.nick}![^ ]+ JOIN {self.channel}")
        log_response(response)
        assert response, log_fail(f"c3 failed to join {self.channel}")
        log_pass(f"c2 and c3 joined {self.channel}")
        
    def test_join_invalid(self):
        log_test("Channel - Invalid join")
        self.channel = "bad&chan"
        msg = f"JOIN {self.channel}"
        self.c2.send(msg)
        log_msg(msg)
        response = self.c2.wait_for(rf":.* 476 {self.c2.nick} {self.channel}")
        log_response(response)
        assert response, log_fail("No ERR_BADCHANMASK when joining invalid channel")
        log_pass("Invalid channel name rejected - received 476 ERR_BADCHANMASK")
    
    def test_part_and_join_all(self):
        log_test("Channel - PART and join all clients")
        self.channel = "#testchannel"
        partMsg = "good bye"
        for client in [self.c1, self.c2, self.c3]:
            msg = f"PART {self.channel} :{partMsg}"
            log_msg(msg)
            client.send(msg)
            response = client.wait_for(rf":{client.nick}![^ ]+ PART {self.channel} :{re.escape(partMsg)}")
            log_response(response)
            assert response, log_fail(f"{client.nick} did not send PART message")
    
        for client in [self.c1, self.c2, self.c3]:
            client.clear_log()
            msg = f"JOIN {self.channel}"
            client.send(msg)
            log_msg(msg)
            join_msg = client.wait_for(rf":{client.nick}![^ ]+ JOIN {self.channel}")
            log_response(join_msg)
            assert join_msg, log_fail(f"{client.nick} could not rejoin {self.channel}")
        log_pass(f"Clients successfully parted and rejoined {self.channel}")

class TestTopic:
    def __init__(self, c1, c2):
        self.c1 = c1
        self.c2 = c2
        self.channel = "#topictest"

    def setup_channel(self):
        self.c1.send(f"JOIN {self.channel}")
        self.c1.wait_for(rf":.* JOIN {self.channel}")
        self.c2.send(f"JOIN {self.channel}")
        self.c2.wait_for(rf":.* JOIN {self.channel}")

    def test_topic_query(self):
        log_test("TOPIC - Query current topic")
        self.setup_channel()
        
        self.c1.send(f"TOPIC {self.channel}")
        log_msg(f"TOPIC {self.channel}")
        
        # Should receive either RPL_TOPIC or RPL_NOTOPIC
        response = self.c1.wait_for(r":.* (331|332) .*")
        log_response(response)
        assert response, log_fail("No topic response received")
        log_pass("TOPIC query works")

    def test_topic_set_and_broadcast(self):
        log_test("TOPIC - Set and broadcast")
        self.setup_channel()
        
        topic_text = "Test topic message"
        self.c1.send(f"TOPIC {self.channel} :{topic_text}")
        log_msg(f"TOPIC {self.channel} :{topic_text}")
        
        # c2 should receive the topic change
        response = self.c2.wait_for(rf":.* TOPIC {self.channel} :{re.escape(topic_text)}")
        log_response(response)
        assert response, log_fail("Topic change not broadcast to other users")
        log_pass("TOPIC set and broadcast works")

class ChannelModeTestBase:
    def __init__(self, c1, c2, c3, channel="#modetest"):
        self.c1 = c1  # Operator
        self.c2 = c2  # Non-operator
        self.c3 = c3  # Optional third client
        self.channel = channel

    def join_all(self):
        for client in [self.c1, self.c2, self.c3]:
            client.send(f"JOIN {self.channel}")
            client.wait_for(rf":.* JOIN {self.channel}")

    def part_all(self):
        for client in [self.c1, self.c2, self.c3]:
            client.send(f"PART {self.channel}")
            client.wait_for(rf":.* PART {self.channel}")

class TestInviteOnlyMode(ChannelModeTestBase):
    def test_enable_by_non_operator(self):
        log_test("Channel Mode +i (Invite-only) by non-operator")
        msg = f"MODE {self.channel} +i"
        self.c2.send(msg)
        log_msg(msg)
        response = self.c2.wait_for(rf":.* 482 {self.c2.nick} {self.channel}")
        log_response(response)
        assert response, log_fail("Missing ERR_CHANOPRIVSNEEDED")
        log_pass("Correctly blocked non-operator from setting +i got ERR_CHANOPRIVSNEEDED")

    def test_enable_by_operator(self):
        log_test("Channel Mode +i by operator")
        msg = f"MODE {self.channel} +i"
        self.c1.send(msg)
        log_msg(msg)
        response = self.c1.wait_for(rf":{self.c1.nick}![^ ]+ MODE {self.channel} \+i")
        log_response(response)
        assert response, log_fail(f"Mode +i not set for channel {self.channel}")
        log_pass(f"Mode +i set by operator for {self.channel}")

    def test_invite_only_effect(self):
        log_test("Joining invite-only channel without invite")
        self.c3.send(f"PART {self.channel}")
        msg = f"JOIN {self.channel}"
        self.c3.send(msg)
        log_msg(msg)
        response = self.c3.wait_for(rf".* 473 {self.c3.nick} {self.channel}") # ERR_INVITEONLYCHAN
        log_response(response)
        assert response, log_fail("Missing ERR_INVITEONLYCHAN")
        log_pass("JOIN blocked by +i mode - got ERR_INVITEONLYCHAN")
        
    def test_disable_by_operator(self):
        log_test("Channel Mode -i (disable invite-only)")
        msg_c1 = f"MODE {self.channel} -i"
        self.c1.send(msg_c1)
        log_msg(msg_c1)
        response = self.c1.wait_for(rf":{self.c1.nick}![^ ]+ MODE {self.channel} -i")
        log_response(response)
        assert response, log_fail("Failed to disable +i")
        log_pass("Mode -i set by operator")
   
        msg_c3 = f"JOIN {self.channel}"
        self.c3.send(msg_c3)
        log_msg(msg_c3)
        response_c3 = self.c3.wait_for(rf":{self.c3.nick}![^ ]+ JOIN {self.channel}")
        log_response(response_c3)
        assert response_c3, log_fail("Could not join channel")
        log_pass("Disabled invite-only mode tested - channel joined successfully")

class TestTopicRestriction(ChannelModeTestBase):
    def test_topic_mode(self):
        log_test("Channel Mode +t (Topic restriction)")
        channel_topic = ":News"
        msg_c1 = f"MODE {self.channel} +t"
        self.c1.send(msg_c1)
        log_msg(msg_c1)
        response_c1 = self.c1.wait_for(rf":{self.c1.nick}![^ ]+ MODE {self.channel} \+t")
        log_response(response_c1)
        assert response_c1, log_fail("Mode +t was not set")
        log_pass("Mode +t was set correctly")
        
        msg_c2 = f"TOPIC {self.channel} {channel_topic}"
        self.c2.send(msg_c2)
        log_msg(msg_c2) # sent by non-operator 
        response_c2 = self.c2.wait_for(rf".* 482 {self.c2.nick} {self.channel}") # ERR_CHANOPRIVSNEEDED
        log_response(response_c2)
        assert response_c2, log_fail("Did not receive ERR_CHANOPRIVSNEEDED")
        log_pass("Topic restriction mode tested for non-operator - received ERR_CHANOPRIVSNEEDED")
        
        self.c1.send(msg_c2)
        log_msg(msg_c2)  # sent by operator
        response_c1 = self.c1.wait_for(rf":{self.c1.nick}![^ ]+ TOPIC {self.channel} {channel_topic}")
        log_response(response_c1)
        assert response_c1, log_fail("Did not receive correct response")
        log_pass("Topic restriction mode tested successfully for operator")

class TestChannelKey(ChannelModeTestBase):
    def test_channel_key_behavior(self):
        log_test("Channel Mode +k (Channel key)")
        key = "secret123"
        self.channel = "#keytest"
        self.c1.send(f"JOIN {self.channel}")
        self.c1.wait_for(rf":{self.c1.nick}![^ ]+ JOIN {self.channel}")
        msg_c1 = f"MODE {self.channel} +k {key}"
        self.c1.send(msg_c1)
        log_msg(msg_c1)
        response_c1 = self.c1.wait_for(rf":{self.c1.nick}![^ ]+ MODE {self.channel} \+k")
        log_response(response_c1)
        assert response_c1, log_fail("Mode +k not set for channel")
        log_pass("Mode +k set correctly for channel")

        msg_c2_1 = f"JOIN {self.channel}"
        self.c2.send(msg_c2_1)
        log_msg(msg_c2_1)
        response_c2_1 = self.c2.wait_for(rf".* 475 {self.c2.nick} {self.channel} .*") # ERR_BADCHANNELKEY
        log_response(response_c2_1)
        assert response_c2_1, log_fail("No 475 ERR_BADCHANNELKEY received")
        log_pass(f"Received 475 ERR_BADCHANNELKEY")

        self.c2.clear_log()
        msg_c2_2 = f"JOIN {self.channel} {key}"
        log_msg(msg_c2_2)
        self.c2.send(msg_c2_2)
        response_c2_2 = self.c2.wait_for(rf":.* JOIN {self.channel}")
        log_response(response_c2_2)
        assert response_c2_2, log_fail("Could not join with correct key")
        log_pass("Channel key join tested")
        
    def test_join_multiple_channels_with_keys(self):
        log_test("Joining multiple channels with keys")
        
        chan1 = "#chanKey1"
        chan2 = "#chanKey2"
        key1 = "apple123"
        key2 = "banana456"

        # c1 creates/joins both channels
        join_msg = f"JOIN {chan1},{chan2}"
        self.c1.send(join_msg)
        log_msg(join_msg)
        patterns = [
            rf":{self.c1.nick}![^ ]+ JOIN {chan1}",
            rf":{self.c1.nick}![^ ]+ JOIN {chan2}"
        ]
        responses = self.c1.collect_expected_responses(patterns)
        for pat, line in responses.items():
            log_response(line)
            assert line, log_fail(f"Missing expected response: {pat}")
        log_pass("JOIN responses received for both channels")
        
        # c1 sets keys for both channels
        for chan, key in [(chan1, key1), (chan2, key2)]:
            mode_msg = f"MODE {chan} +k {key}"
            self.c1.send(mode_msg)
            log_msg(mode_msg)
            pattern = rf":{self.c1.nick}![^ ]+ MODE {chan} \+k {key}"
            mode_result = self.c1.wait_for(pattern)
            log_response(mode_result)
            assert mode_result, log_fail(f"Mode +k not set for {chan}")
        log_pass("Mode +k set for both channels")

        # c2 tries to join both channels WITHOUT keys
        self.c2.clear_log()
        self.c2.send(f"JOIN {chan1},{chan2}")
        log_msg(f"JOIN {chan1},{chan2} (no keys)")
        err_patterns = [
            rf".* 475 {self.c2.nick} {chan1} .*",
            rf".* 475 {self.c2.nick} {chan2} .*"
        ]
        err_results = self.c2.collect_expected_responses(err_patterns)
        for pat, matched in err_results.items():
            log_response(matched)
            assert matched, log_fail("Missing ERR_BADCHANNELKEY for a channel")
        log_pass("Received ERR_BADCHANNELKEY for both channels")

        # c2 tries again WITH keys
        self.c2.clear_log()
        join_cmd = f"JOIN {chan1},{chan2} {key1},{key2}"
        self.c2.send(join_cmd)
        log_msg(join_cmd)
        join_patterns = [
            rf":{self.c2.nick}![^ ]+ JOIN {chan1}",
            rf":{self.c2.nick}![^ ]+ JOIN {chan2}"
        ]
        join_results = self.c2.collect_expected_responses(join_patterns)
        for pat, matched in join_results.items():
            log_response(matched)
            assert matched, log_fail("JOIN failed for one of the channels")
        log_pass("c2 joined both channels with correct keys")

class TestOperatorMode(ChannelModeTestBase):
    def test_grant_and_remove_operator(self):
        channel_topic = ":Fake news"
        log_test("Channel Mode +o (Operator mode)")
        
        msg_c2 = f"TOPIC {self.channel} {channel_topic}"
        self.c2.send(msg_c2)
        log_msg(msg_c2) # sent by non-operator before +o
        response_c2 = self.c2.wait_for(rf".* 482 {self.c2.nick} {self.channel}")  # ERR_CHANOPRIVSNEEDED
        log_response(response_c2)
        assert response_c2, log_fail("Did not receive ERR_CHANOPRIVSNEEDED")
        log_pass("Channel privileges tested for non-operator - received ERR_CHANOPRIVSNEEDED")
        
        msg_c1 = f"MODE {self.channel} +o {self.c2.nick}"
        self.c1.send(msg_c1)
        log_msg(msg_c1) # sent by operator to grant operator privileges to client
        response_c1 = self.c1.wait_for(fr":{self.c1.nick}![^ ]+ MODE {self.channel} \+o {self.c2.nick}")
        log_response(response_c1)
        assert response_c1, log_fail("Operator privileges not granted")
        log_pass("Operator privileges granted")
        
        self.c2.send(msg_c2)
        log_msg(msg_c2) # sent by client after +o
        response_c2_2 = self.c2.wait_for(rf":{self.c2.nick}![^ ]+ TOPIC {self.channel} {channel_topic}")
        log_response(response_c2_2)
        assert response_c2_2, log_fail("Client cannot set TOPIC after +o")
        log_pass("Channel privileges work correctly for user after +o")
        
        topic2 = ":Real news"
        self.c2.send(f"TOPIC {self.channel} {topic2}")
        self.c2.wait_for(rf".* 482 {self.c2.nick} {self.channel}")
        log_pass("Operator +o/-o works as expected")

    def test_disable_operator_mode(self):
        log_test("Channel Mode -o (Operator mode removed)")
        msg_c1 = f"MODE {self.channel} -o {self.c2.nick}"
        self.c1.send(msg_c1)
        log_msg(msg_c1) # sent by operator to remove privileges
        response_c1 = self.c1.wait_for(fr":{self.c1.nick}![^ ]+ MODE {self.channel} -o")
        log_response(response_c1)
        assert response_c1, log_fail("Failed to remove operator priviledges")
        log_pass("Operator privileges were successfully removed")
        
        channel_topic = ":True news"
        msg_c2 = f"TOPIC {self.channel} {channel_topic}"
        self.c2.send(msg_c2)
        log_msg(msg_c2) # sent by non-operator after -o
        response_c2 = self.c2.wait_for(rf".* 482 {self.c2.nick} {self.channel}")
        log_response(response_c2)
        assert response_c2, log_fail("Did not receive ERR_CHANOPRIVSNEEDED")
        log_pass("Channel privileges tested after -o - received ERR_CHANOPRIVSNEEDED")

    def test_mode_without_params(self):
        log_test("Mode without parameters")
        msg = "MODE"
        self.c1.send(msg)
        log_msg(msg)
        response = self.c1.wait_for(rf" 461 {self.c1.nick} MODE")
        log_response(response)
        assert response, log_fail("Did not receive ERR_NEEDMOREPARAMS")
        log_pass("Mode without parameters - received ERR_NEEDMOREPARAMS")

class TestInvite:
    def __init__(self, c1, c2):
        self.operator = c1  # Channel operator
        self.invited = c2   # Client to be invited
        self.channel = "#invitetest"

    def setup_channel(self):
        # Operator joins and creates channel
        self.operator.send(f"JOIN {self.channel}")
        self.operator.wait_for(rf":{self.operator.nick}![^ ]+ JOIN {self.channel}")

        # Set +i mode (invite-only)
        self.operator.send(f"MODE {self.channel} +i")
        self.operator.wait_for(rf":{self.operator.nick}![^ ]+ MODE {self.channel} \+i")

    def test_invite_and_join(self):
        log_test("INVITE - invite user to +i channel")

        self.setup_channel()

        # Invites other client and should receive a confirmation
        invite_cmd = f"INVITE {self.invited.nick} {self.channel}"
        self.operator.send(invite_cmd)
        log_msg(invite_cmd)
        invite_response = self.operator.wait_for(rf":.* 341 {self.operator.nick} {self.invited.nick} {self.channel}")
        log_response(invite_response)
        assert invite_response, log_fail("Invite confirmation not received by inviter")
        log_pass("Invite confirmation received by inviter")

        # Invited client should receive INVITE message
        invite_msg = self.invited.wait_for(rf":{self.operator.nick} INVITE {self.invited.nick} :{self.channel}")
        log_response(invite_msg)
        assert invite_msg, log_fail("INVITE message not received by invited client")
        log_pass("INVITE message received by invited client")

        # Invited client attempts to join
        join_msg = f"JOIN {self.channel}"
        self.invited.send(join_msg)
        log_msg(join_msg)
        join_response = self.invited.wait_for(rf":{self.invited.nick}![^ ]+ JOIN {self.channel}")
        log_response(join_response)
        assert join_response, log_fail("Invited client could not join invite-only channel")
        log_pass("INVITE command worked correctly")

    def test_invite_without_privilege(self):
        log_test("INVITE - non-operator tries to invite")

        self.setup_channel()
        # Non-operator tries to invite someone
        invite_cmd = f"INVITE {self.operator.nick} {self.channel}"
        self.invited.send(invite_cmd)
        log_msg(invite_cmd)

        error_msg = self.invited.wait_for(rf":.* 482 {self.invited.nick} {self.channel}")
        log_response(error_msg)
        assert error_msg, log_fail("Missing ERR_CHANOPRIVSNEEDED on INVITE by non-operator")
        log_pass("Non-operator correctly blocked from sending INVITE")

class TestKick:
    def __init__(self, c1, c2, c3):
        self.c1 = c1  # Operator
        self.c2 = c2  # Target of kick
        self.c3 = c3  # Not in channel
        self.channel = "#kicktest"

    def setup_channel(self):
        # All clients join the channel, c1 becomes op
        self.c1.send(f"JOIN {self.channel}")
        joined = self.c1.wait_for(rf":{self.c1.nick}![^ ]+ JOIN {self.channel}")

        self.c2.send(f"JOIN {self.channel}")
        joined2 = self.c2.wait_for(rf":{self.c2.nick}![^ ]+ JOIN {self.channel}")

    def test_kick_valid(self):
        log_test("KICK - Valid kick by operator")
        self.setup_channel()

        kickReason = "good riddance"
        msg = f"KICK {self.channel} {self.c2.nick} :{kickReason}"
        self.c1.send(msg)
        log_msg(msg)

        kicked = self.c2.wait_for(rf":{self.c1.nick}![^ ]+ KICK {self.channel} {self.c2.nick} :{re.escape(kickReason)}")
        log_response(kicked)
        assert kicked, log_fail("KICK message not received by c2")
        log_pass("KICK message received by c2")

    def test_kick_nonexistent_channel(self):
        log_test("KICK - Nonexistent channel")
        msg = f"KICK #nochannel {self.c2.nick} :test"
        self.c1.send(msg)
        log_msg(msg)
        err = self.c1.wait_for(rf".* 403 {self.c1.nick} #nochannel .*")  # ERR_NOSUCHCHANNEL
        log_response(err)
        assert err, log_fail("No ERR_NOSUCHCHANNEL received")
        log_pass("ERR_NOSUCHCHANNEL received correctly")

    def test_kick_not_operator(self):
        log_test("KICK - Not operator")
        self.c2.send(f"JOIN {self.channel}")
        self.c2.clear_log()
        msg = f"KICK {self.channel} {self.c1.nick} :oops"
        self.c2.send(msg)
        log_msg(msg)
        err = self.c2.wait_for(rf".* 482 {self.c2.nick} {self.channel} .*")  # ERR_CHANOPRIVSNEEDED
        log_response(err)
        assert err, log_fail("No ERR_CHANOPRIVSNEEDED received")
        log_pass("ERR_CHANOPRIVSNEEDED received correctly")

    def test_kick_user_not_in_channel(self):
        log_test("KICK - User not in channel")
        msg = f"KICK {self.channel} {self.c3.nick} :not here"
        self.c1.send(msg)
        log_msg(msg)
        response = self.c1.wait_for(rf".* 441 {self.c1.nick} {self.channel} .*")  # ERR_USERNOTINCHANNEL
        log_response(response)
        assert response, log_fail("No ERR_USERNOTINCHANNEL received")
        log_pass("ERR_USERNOTINCHANNEL received correctly")

    def test_kick_too_many_targets(self):
        log_test("KICK - Too many targets")
        targets = ",".join([f"user{i}" for i in range(1, 11)])  # More than PRIVMSG_MAX_TARGETS
        msg = f"KICK {self.channel} {targets} :boom"
        self.c1.send(msg)
        log_msg(msg)
        err = self.c1.wait_for(rf".* 407 {self.c1.nick} .*")  # ERR_TOOMANYTARGETS
        log_response(err)
        assert err, log_fail("No ERR_TOOMANYTARGETS received")
        log_pass("ERR_TOOMANYTARGETS received correctly")

class TestQuit:
    def __init__(self, c1, c2, c3):
        self.c1 = c1
        self.c2 = c2  
        self.c3 = c3

    def test_quit_message_broadcast(self):
        log_test("QUIT - Message broadcast to channels")
        channel = "#quitest"
        
        # c1 and c2 join same channel
        self.c1.send(f"JOIN {channel}")
        self.c1.wait_for(rf":.* JOIN {channel}")
        self.c2.send(f"JOIN {channel}")
        self.c2.wait_for(rf":.* JOIN {channel}")
        
        self.c2.clear_log()
        quit_msg = "Goodbye everyone!"
        self.c1.send(f"QUIT :{quit_msg}")
        log_msg(f"QUIT :{quit_msg}")
        
        # c2 should receive quit message
        response = self.c2.wait_for(rf":.* QUIT :{re.escape(quit_msg)}")
        log_response(response)
        assert response, log_fail("QUIT message not broadcast")
        log_pass("QUIT message broadcast correctly")

class TestErrorHandling:
    def __init__(self, client):
        self.client = client

    def test_unknown_command(self):
        log_test("Error - Unknown command")
        self.client.send("UNKNOWN test")
        log_msg("UNKNOWN test")
        response = self.client.wait_for(r":.* 421 .* UNKNOWN .*")  # ERR_UNKNOWNCOMMAND
        log_response(response)
        assert response, log_fail("No ERR_UNKNOWNCOMMAND received")
        log_pass("Unknown command correctly rejected")

    def test_malformed_messages(self):
        log_test("Error - Malformed messages")
        malformed = [
            "NICK\x00invalid",  # Null byte
            "NICK \x01\x02\x03",  # Control characters
            "NICK" + "x" * 400,  # Long message
        ]

        for msg in malformed:
            self.client.send_raw(msg + "\r\n")
            log_msg(repr(msg))
            response = self.client.wait_for(r":.* (421|432) .*", timeout=2)
            if response:
                log_response(response)
                log_pass(f"Malformed message rejected")
            else:
                log_pass(f"Malformed message ignored")

class TestLimits:
    def __init__(self, client):
        self.client = client

    def test_channel_limit(self):
        log_test("Limits - Maximum channels per user")
        channels = [f"#limit{i}" for i in range(1, 21)]
        
        joined_count = 0
        for channel in channels:
            self.client.send(f"JOIN {channel}")
            response = self.client.wait_for(rf":.* JOIN {channel}", timeout=1)
            if response:
                joined_count += 1
            else:
                # Should get ERR_TOOMANYCHANNELS
                error = self.client.wait_for(r":.* 405 .*")
                if error:
                    log_response(error)
                    break
        
        log_pass(f"Successfully joined {joined_count} channels before hitting limit")

    def test_message_length_limit(self):
        log_test("Limits - Message length")
        long_message = "x" * 600
        self.client.send(f"PRIVMSG {self.client.nick} :{long_message}")
        log_msg(f"PRIVMSG {self.client.nick} :[{len(long_message)} chars]")
        
        # Server should either truncate or reject
        response = self.client.wait_for(r":.* (PRIVMSG|400|417) .*", timeout=2)
        log_response(response)
        if response:
            log_pass("Long message handled (truncated or rejected)")
        else:
            log_pass("Long message ignored by server")

# --- Main test runner ---

def main():
     # Connection tests
    print("\n[*] Running  connection tests")
    conn_tests = TestConnection()
    conn_tests.test_connection_without_password()
    conn_tests.test_wrong_password()
    
    # Registration tests
    print("\n[*] Running registration order tests")
    c1 = make_client("RegTest1")
    c1.send("USER RegTest1 0 * :Registration Test")
    reg_tests = TestRegistration(c1)
    reg_tests.test_registration_order_nick_first()
    reg_tests.test_registration_order_user_first()
    reg_tests.test_commands_before_registration()
    
    print("\n[*] Running registration tests for client1")
    user_tests1 = TestUser(c1)
    user_tests1.test_user_sanitization_cases()
    user_tests1.test_user_reregistration()
    
    #Nick tests
    print("\n[*] Running Nick Tests for client1")
    nick_tests1 = TestNick(c1)
    nick_tests1.test_nick_changes()
    nick_tests1.test_duplicate_nick("Nicky")
    nick_tests1.test_invalid_nick()
    nick_tests1.test_nick_without_parameter()

    # Message buffering tests
    print("\n[*] Running buffering test for client3")
    c3 = make_client("Spooky")
    c3.send("USER Spooky whatever * :Realrealspook")
    buff_tests3 = TestMessageBuffering(c3)
    time.sleep(0.5)
    buff_tests3.test_partial_message("NICK ", "3Spock")
    buff_tests3.test_multiple_commands_in_one_message("NICK !Sloppy", "NICK _Sloppy")
    buff_tests3.test_character_by_character_message()
    buff_tests3.test_mixed_line_endings()
    buff_tests3.test_very_long_partial_messages()
    buff_tests3.test_ping_pong()
    #buff_tests3.test_output_buffer_flush()
    time.sleep(2)

    # Privmsg tests
    c2 = make_client("Lucky")
    c2.send("USER Lucky whatever * :Realreallucky")
    print("\n[*] Running privmessaging tests")
    privmsg_tests = TestPrivmsg(c1, c2, c3)
    privmsg_tests.test_privmsg_user()
    privmsg_tests.test_privmsg_multiple_targets()
    privmsg_tests.test_privmsg_channel()
    privmsg_tests.test_privmsg_multiple_channels()
    privmsg_tests.test_privmsg_no_recipient()
    privmsg_tests.test_privmsg_no_such_channel()
    privmsg_tests.test_privmsg_no_text()

    # Channel name tests
    print("\n[*] Running channel name tests")
    chan_name_tests = TestChannelNames(c1)
    chan_name_tests.test_valid_channel_names()
    chan_name_tests.test_invalid_channel_names()

    # Join tests
    print("\n[*] Running Channel Membership Tests")
    chan_tests = TestChannelMembership(c1, c2, c3)
    chan_tests.test_create_channel()
    chan_tests.test_join_multiple()
    chan_tests.test_join_invalid()
    chan_tests.test_part_and_join_all()
    
    # Topic tests
    print("\n[*] Running Topic tests")
    topic_tests = TestTopic(c1, c2)
    topic_tests.test_topic_query()
    topic_tests.test_topic_set_and_broadcast()

    # Channel mode tests
    print("\n[*] Running Mode Tests")
    mode_tests = ChannelModeTestBase(c1, c2, c3)
    mode_tests.join_all()
    
    imode_tests = TestInviteOnlyMode(c1, c2, c3)
    imode_tests.test_enable_by_non_operator()
    imode_tests.test_enable_by_operator()
    imode_tests.test_invite_only_effect()
    imode_tests.test_disable_by_operator()
    
    tmode_tests = TestTopicRestriction(c1, c2, c3)
    tmode_tests.test_topic_mode()
    
    keymode_tests = TestChannelKey(c1, c2, c3)
    keymode_tests.test_channel_key_behavior()
    keymode_tests.test_join_multiple_channels_with_keys()
    
    #User mode tests
    omode_tests = TestOperatorMode(c1, c2, c3)
    omode_tests.test_grant_and_remove_operator()
    omode_tests.test_disable_operator_mode()
    omode_tests.test_mode_without_params()
    
    mode_tests.part_all()

    # Invite tests
    print("\n[*] Running Invite Tests")
    invite_tests = TestInvite(c1, c2)
    invite_tests.test_invite_and_join()
    invite_tests.test_invite_without_privilege()

    #Kick tests
    print("\n[*] Running Kick Tests")
    kick_tests = TestKick(c1, c2, c3)
    kick_tests.test_kick_valid()
    kick_tests.test_kick_nonexistent_channel()
    kick_tests.test_kick_not_operator()
    kick_tests.test_kick_user_not_in_channel()
    kick_tests.test_kick_too_many_targets()
    
    # QUIT tests
    print("\n[*] Running QUIT tests")
    quit_tests = TestQuit(c1, c2, c3)
    quit_tests.test_quit_message_broadcast()
    
    # Error handling tests
    print("\n[*] Running error handling tests")
    error_tests = TestErrorHandling(c2)
    error_tests.test_unknown_command()
    error_tests.test_malformed_messages()
    
    # Limits tests
    print("\n[*] Running limits tests")
    limit_tests = TestLimits(c3)
    limit_tests.test_channel_limit()
    limit_tests.test_message_length_limit()

    c1.close()
    c2.close()
    c3.close()

if __name__ == "__main__":
    main()
