# My 42 projects

### myLibft
- 24/11/06: Not up to date (did some fixes to printf and libft that are not yet here).
- This is the libft with additions such as ft_printf and get_next_line

## Rank 00

### Libft
_Started 2024/07/31_
- To compile main.c for testing, run `make` inside tests/ folder
- Everything should be functional.

## Rank 01

### Ft_printf
_Started 2024/08/07_
- Printf works.
- Check how %s and %c behave with `0` flag w/ linux -- in macOS, prints 0, but in some
  online compilers the 0 is just ignored. In my current implementation the flag is ignored,
  but can be easily changed by replacing `pad_width(flags.width, len, 0);` with `pad_width(flags.width, len, flags.zero_pad);`
  in function print_str.
- If user tries to run the program with false parameters, f.ex. ft_printf("%s\n", 'b'); leads to a segfault,
  since va_arg leads to undefined behaviour if it tries to read a character as a string. Probably ok, since regular
  printf doesn't work with false flags either.
- To compile for testing, run `make` inside tests/ folder.
- In linux null pointer with %p returns (nil), on macOS 0x0. To change from linux version to mac implementation, just remove lines 61&62 from print_ptr.c

### Get_next_line
_Started 2024/08/12_
- Works almost, bonus works too (really simple addition really).
- Still needs some further testing.

### Born2beroot
- Will finish in the clusters, but the concept and implementation ok.

## Rank 02

### FdF
### fract-oi
### minitalk
_Wrote 2024/08/16-17_
- To test with a really long string, run `cat ./text.txt|xargs -0 ./client <SERVER_PID>`
- To test unicode support, `make bonus`. There's a txt file with different unicode characters in the project folder, run `cat ./textunicode.txt|xargs -0 ./client_bonus <SERVER_PID>`
- Still needs some further testing

### pipex
### push_swap
### so_long
