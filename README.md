# My 42 projects
## Libft
_Started 2024/07/31_
- To compile main.c for testing, run `make test`
- Everything should be functional.
- Next up write thorough tests for the functions.

## Ft_printf
_Started 2024/08/07_
- Bonuses work afaik.
- Check how %s and %c behave with `0` flag w/ linux -- in macOS, prints 0, but in some
  online compilers the 0 is just ignored. In my current implementation the flag is ignored,
  but can be easily changed by replacing `pad_width(flags.width, len, 0);` with `pad_width(flags.width, len, flags.zero_pad);`
  in function print_str.
- Now it seems everything works, but the concern is if user tries to run the program with false parameters, f.ex.
  ft_printf("%s\n", 'b'); which leads to a segfault.

## Born2beroot
- Better do this in the clusters.
