build : hw2.o solution.o
	g++ -o build hw2.o solution.o #注意前面必须是tab，不能是空格
hw2.o : hw2.cpp solution.h
	g++ -g -c hw2.cpp
solution.o : solution.h solution.cpp
	g++ -g -c solution.cpp
clean :
	rm hw2.o solution.o build
	
OBJS := start.o main.o dev/dev.o lib/lib.o

CFLAGS := -fno-builtin -I$(shell pwd)/include
export CFLAGS

gboot.bin : gboot.elf
	arm-linux-objcopy -O binary gboot.elf gboot.bin

gboot.elf : $(OBJS)
	arm-linux-ld -Tgboot.lds -o gboot.elf $^

%.o : %.S 
	arm-linux-gcc -g -c $^

%.o : %.c
	arm-linux-gcc $(CFLAGS) -c $^

lib/lib.o : 
	make -C lib all

dev/dev.o :
	make -C dev all

.PHONY : clean
clean:
	rm *.o *.elf *.bin
	make -C lib clean
	make -C dev clean