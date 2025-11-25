#include "tester.h"

static void print_list(t_list *l) {
	while (l) { printf("[%s] -> ", (char*)l->data); l = l->next; }
	printf("NULL\n");
}


static t_list *create_elem(void *data) {
	t_list *node = malloc(sizeof(t_list));
	if (!node) return NULL;
	node->data = data;
	node->next = NULL;
	return node;
}

int main() {

	/* Strlen */
	{
		printf("--- Testing ft_strlen ---\n");

		const char *test1 = "Hello Assembly";
		const char *test2 = "";
		const char *test3 = NULL;

		printf("Test 1 (%s): %zu\n", test1, ft_strlen(test1));
		printf("Test 2 (%s): %zu\n", test2, ft_strlen(test2));
		printf("Test 3 (NULL): %zu\n", ft_strlen(test3));
		printf("\n");
	}
	/* Strcpy */
	{
		printf("--- Testing ft_strcpy ---\n");

		char buffer[100];
		const char *source = "Copy this string!";
		char *ret = ft_strcpy(buffer, source);

		printf("Dest Buffer: %s\n", buffer);
		printf("Return Val:  %s\n", ret);
		if (ret == buffer) {
			printf(">> SUCCESS: Return value matches buffer address.\n");
		} else {
			printf(">> FAILURE: Return value is wrong.\n");
		}
		printf("\n");
	}
	/* Strcmp */
	{
		printf("--- Testing ft_strcmp ---\n");

		printf("strcmp('A', 'A') = %d\n", ft_strcmp("A", "A"));
		printf("strcmp('A', 'B') = %d\n", ft_strcmp("A", "B"));
		printf("strcmp('B', 'A') = %d\n", ft_strcmp("B", "A"));
		printf("strcmp('B', 'AB') = %d\n", ft_strcmp("B", "AB"));
		printf("\n");
	}
	/* Write */
	{
		printf("--- Testing ft_write ---\n");

		printf("Writing to stdout: ");
		fflush(stdout); // Force flush before we use raw write
		ssize_t ret = ft_write(1, "Hello World!\n", 13);
		printf("Return: %zd (Expected 13)\n", ret);

		errno = 0; // Reset errno
		ret = ft_write(-1, "This fail", 9);
		printf("Test Bad FD (-1): Return = %zd, errno = %d\n", ret, errno);

		if (ret == -1 && errno == EBADF) // EBADF is usually 9
			printf(">> SUCCESS: Correctly handled error.\n");
		else
			printf(">> FAILURE: Did not set errno correctly.\n");
		printf("\n");
	}
	/* Read */
	{
		printf("--- Testing ft_read ---\n");
		int fd = open("srcs/main.c", O_RDONLY);
		if (fd > 0) {
			char buf[50];
			memset(buf, 0, 50);
			ssize_t ret = ft_read(fd, buf, 49);
			close(fd);

			printf("Read %zd bytes from main.c\n", ret);
			printf("Preview: [%.100s...]\n", buf);
		} else {
			printf("Skipping read test (could not open main.c)\n");
		}

		errno = 0;
		ssize_t ret = ft_read(-42, "buffer", 5);
		printf("Test Bad FD (-42): Return = %zd, errno = %d\n", ret, errno);

		if (ret == -1 && errno == EBADF)
			printf(">> SUCCESS: Correctly handled error.\n");
		else
			printf(">> FAILURE: Did not set errno correctly.\n");
		printf("\n");
	}
	/* Strdup */
	{
		printf("--- Testing ft_strdup ---\n");
		const char *original = "I am a duplicate!";
		char *copy = ft_strdup(original);
		if (copy == NULL) {
			printf(">> FAILURE: Malloc returned NULL.\n");
		} else {
			printf("Original: %s\n", original);
			printf("Copy:     %s\n", copy);

			if (copy != original) {
				printf(">> SUCCESS: Address Check: Different (Good!)\n");
			} else {
				printf(">> FAILURE: Address Check: SAME (Bad! You just returned the pointer!)\n");
			}

			if (strcmp(copy, original) == 0) {
				printf(">> SUCCESS: Content Check: Match (Good!)\n");
			} else {
				printf(">> FAILURE: Content Check: Mismatch (Bad!)\n");
			}

			free(copy);
			printf(">> SUCCESS: Memory freed successfully.\n");
		}
		printf("\n");
	}
	/* Atoi_base */
	{
		printf("--- Testing ft_atoi_base ---\n");
		printf("Binary '101' (base 2):  %d (Exp: 5)\n", ft_atoi_base("101", "01"));
		printf("Hex 'FF' (base 16):     %d (Exp: 255)\n", ft_atoi_base("FF", "0123456789ABCDEF"));
		printf("Octal '-7' (base 8):    %d (Exp: -7)\n", ft_atoi_base("-7", "01234567"));
		printf("Invalid Base (+):       %d (Exp: 0)\n", ft_atoi_base("123", "01+"));
		printf("Invalid Base (dup):     %d (Exp: 0)\n", ft_atoi_base("123", "001"));
		printf("\n");
	}
	/* List remove if */
	{
		printf("--- Testing ft_list_remove_if ---\n");

		// Setup List: A -> B -> A -> C -> A
		t_list *head = NULL;
		ft_list_push_front(&head, create_elem(ft_strdup("A")));
		ft_list_push_front(&head, create_elem(ft_strdup("C")));
		ft_list_push_front(&head, create_elem(ft_strdup("A")));
		ft_list_push_front(&head, create_elem(ft_strdup("B")));
		ft_list_push_front(&head, create_elem(ft_strdup("A")));

		printf("Before: ");
		print_list(head);

		// Remove 'A'
		char *ref = "A";
		ft_list_remove_if(&head, ref, ft_strcmp, free);

		printf("After:  ");
		print_list(head);

		// Verify only B -> C -> NULL remains
		if (head && ft_strcmp(head->data, "B") == 0 &&
			head->next && ft_strcmp(head->next->data, "C") == 0 &&
			head->next->next == NULL) {
			printf(">> SUCCESS: List filtered correctly.\n");
		} else {
			printf(">> FAILURE: List structure is wrong.\n");
		}
		printf("\n");
	}
	return 0;
}
