# My 42 projects
## Rank 00

### Libft
_Started 2024/07/31_
- To compile main.c for testing, run `make test`
- Everything should be functional.
- Next up write thorough tests for the functions.

## Rank 01

### Ft_printf
_Started 2024/08/07_
- Printf works afaik.
- Check how %s and %c behave with `0` flag w/ linux -- in macOS, prints 0, but in some
  online compilers the 0 is just ignored. In my current implementation the flag is ignored,
  but can be easily changed by replacing `pad_width(flags.width, len, 0);` with `pad_width(flags.width, len, flags.zero_pad);`
  in function print_str.
- If user tries to run the program with false parameters, f.ex. ft_printf("%s\n", 'b'); leads to a segfault, 
  since va_arg leads to undefined behaviour if it tries to read a character as a string. Probably ok, since regular
  printf doesn't work with false flags either.

### Get_next_line
_Started 2024/08/12_
- Works, bonus works too (really simple addition really).

### Born2beroot
- Better do this in the clusters.

## Rank 02

### FdF
### fract-oi
### minitalk
- To test, run `cat ./text.txt|xargs -0 ./client <SERVER_PID>`
- Everything else works but unicode support (2nd bonus)

### pipex
### push_swap
### so_long
