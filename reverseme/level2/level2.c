#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char input[20];
	char output[50];
	char password[] = "delabere";

	printf("Please enter key: ");
	if (scanf("%s", input) != 1)
	{
		puts("Nope.");
		exit(1);
	}
	if (input[0] != '0' || input[1] != '0')
	{
		puts("Nope.");
		exit(1);
	}

	memset(output, 0, 9);
	output[0] = 'd';
	int out_idx = 1;
	for (int i = 2 ; ; i += 3)
	{
		if (strlen(output) >= 8)
			break;
		if (i + 2 >= strlen(input))
			break;
		char c[4] = { input[i], input[i + 1], input[i + 2], '\0' };
		output[out_idx++] = (char)atoi(c);
		output[out_idx] = '\0';
	}
	output[out_idx] = '\0';
	
	if (strcmp(output, password) != 0)
	{
		puts("Nope.");
		exit(1);
	}
	puts("Nope.");
	return 0;
}
