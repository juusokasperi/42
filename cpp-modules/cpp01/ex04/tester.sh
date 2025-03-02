#! /bin/bash

YELLOW="\033[0;93m"
RESET="\033[0m"

# Make the project if no executable found
if [ ! -f ./sed ]; then \
	echo -e "${YELLOW}Building the executable..${RESET}"
	make
fi

echo && echo -e "${YELLOW}----------  TESTER.SH  ----------${RESET}" && \

# Test 1
TO_FIND=a
TO_REPLACE=" Replace this! "
echo "AaA\nBaB\nCaC\nHaHaHa\nTestament\n" > test.txt
OG=$(echo -e "${YELLOW}------  ORIGINAL TEST.TXT  ------${RESET}" && cat test.txt)
echo -e "$OG"
echo "Replacing all substrings \"${TO_FIND}\" with \"${TO_REPLACE}\""
./sed test.txt "${TO_FIND}" "${TO_REPLACE}"
RE=$(echo -e "${YELLOW}------  TEST.TXT.REPLACE   ------${RESET}" && cat test.txt.replace)
echo -e "$RE"

# Test 2
TO_FIND=BaB
TO_REPLACE=BaBBaB
echo "Replacing all substrings \"${TO_FIND}\" with \"${TO_REPLACE}\""
./sed test.txt "${TO_FIND}" "${TO_REPLACE}"
RE=$(echo -e "${YELLOW}------  TEST.TXT.REPLACE   ------${RESET}" && cat test.txt.replace)
echo -e "$RE"

# Test 3
TO_FIND=XyZ
TO_REPLACE=YzX
echo "Replacing all substrings \"${TO_FIND}\" with \"${TO_REPLACE}\""
./sed test.txt "${TO_FIND}" "${TO_REPLACE}"
RE=$(echo -e "${YELLOW}------  TEST.TXT.REPLACE   ------${RESET}" && cat test.txt.replace)
echo -e "$RE"

# Remove created .txt files
rm test.txt test.txt.replace
