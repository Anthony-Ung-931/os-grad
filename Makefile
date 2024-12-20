C_FILES=./kernel.c ./console/console.c ./tests/tests.c ./device/portmap.c ./device/keyboard/keyboard.c ./commands/commands.c ./commands/term_colors.c ./strings/dios_strings.c 
O_FILES=${C_FILES:.c=.o}

all: qemu_launch

qemu_launch: os.bin
	qemu-system-i386 -drive format=raw,file=$<

os.bin: boot.bin kernel.bin
	cat $^ > $@

boot.bin: boot.asm
	nasm $< -f bin -o $@

kernel.bin: kernel-entry.o ${O_FILES}
	ld -m elf_i386 -s -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel-entry.elf
	nasm $< -f elf -o $@

${O_FILES}:
	gcc -Iinclude -fno-pie -m32 -ffreestanding -c ${@:.o=.c} -o $@

clean:
	find . -name \*.o | xargs --no-run-if-empty rm
	find . -name \*.bin | xargs --no-run-if-empty rm

