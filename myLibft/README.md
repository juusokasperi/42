### myLibft
- Modified version of the libft for 42 curriculum.
- Added functions;
```
ft_printf
get_next_line
ft_free
ft_count_digits
ft_abs
ft_ltoi
ft_strtol
ft_error
ft_realloc
ft_min
ft_max
```
- All the put -functions are edited to return the value of write.

### [ft_printf](/myLibft/srcs/ft_printf/)

- A simplified version of the printf() function.
- Accepts specifiers %cspdiuxX%, no flags (yet).

### [get_next_line](/myLibft/srcs/get_next_line/)

- A function that reads next line from a file descriptor.
- The function declares a static buffer that reads from the file to stack memory. Once a \n or EOF is discovered, it allocates to heap the line from start to the first \n (or EOF) it encounters, and cleans the buffer so that it contains only the remaining part of the buffer (or in case of eof, is null).
