nasm -f elf x86.asm
ld -m elf_i386 x86.o -o x86
./x86