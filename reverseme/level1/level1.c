#include <stdio.h>
#include <string.h>

int main(void)
{
	char input[14];
	char *password;

	password = "__stack_check";
	printf("Please enter key: ");
	scanf("%s", input);
	if (strcmp(input, password) == 0)
		printf("Good job.\n");
	else
		printf("Nope.\n");
	return 0;
}
