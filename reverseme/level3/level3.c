#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char* const LEVEL = "L3";
const char* const PASS = "********";

__attribute__((noreturn)) void nope(void *ctx_ptr, int64_t error_code, int64_t sub_code, int64_t rcx_value) __asm__("___syscall_malloc");
void success(void) __asm__("____syscall_malloc");


int main(void)
{
	int result = 0;
	char input[24];
	char output[9];

	printf("Please enter key: ");
	
	if (scanf("%23s", input) != 1)
		nope((void *)LEVEL, 0, 0, 0);
	if (input[1] != '2')
		nope(NULL, 10, 0, '2');
	if (input[0] != '4')
		nope(NULL, 10, 0, '4');

	fflush(stdin);
	memset(output, 0, 9);
	output[0] = '*';

	size_t in_idx = 2;
	int out_idx = 1;
	char some_flag = 0;
	while (1)
	{
		if (strlen(output) >= 8)
			break;
		if (in_idx >= strlen(input)) // Seems that there is a flaw in the code, programmer should check in_idx + 2
			break;
		char c[4] = { input[in_idx], input[in_idx + 1], input[in_idx + 2], '\0' };
		output[out_idx] = (char)atoi(c);
		in_idx += 3;
		out_idx++;
		output[out_idx] = '\0';
	}
	output[out_idx] = '\0';
	if (strcmp(output, PASS) == -2 || strcmp(output, PASS) == -1)
		nope(NULL, 10, 0, 0);
	if (strcmp(output, PASS) == 0)
		success();
	else
		nope(NULL, 11, 0, 0);
	return result;
}

// Assembly code tells us the programmer is calling an external function with these
// values, but since we don't have access to the error logger, they are unused.
__attribute__((noreturn)) void nope(
		void *ctx_ptr,
		int64_t error_code,
		int64_t sub_code,
		int64_t rcx_value)
{
	(void)ctx_ptr;
	(void)error_code;
	(void)sub_code;
	(void)rcx_value;

	puts("Nope.");
	exit(1);
}

void success(void)
{
	puts("Good job.");
	return;
}

