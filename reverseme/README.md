Exercises in extracting info from binary, reading assembly, and reverse engineering a .c file from assembly code.

## Useful commands
`file <binary>`

`strings <binary>` might show you some interesting information, such as function calls, and other stuff too.

Setting up `pwndbg` is recommended

Then when starting `gdb <binary>`, set `break main` to start stepping through.
`disass main` is also very useful.
