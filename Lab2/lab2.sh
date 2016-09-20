#!/bin/bash 

arm-none-eabi-gcc -mcpu=cortex-a8 -I ./newlib-2.2.0-1/newlib/libc/include -c -o mem_alloc.o /home/raj/RTOS/Lab2/mem_alloc.c
arm-none-eabi-as -mcpu=cortex-a8 -o startup.o /home/raj/RTOS/Lab2/startup.s
arm-none-eabi-gcc -mcpu=cortex-a8 -I ./newlib-2.2.0-1/newlib/libc/include -c -o syscalls.o /home/raj/RTOS/Lab2/syscalls.c
arm-none-eabi-gcc -nostdlib -T /home/raj/RTOS/Lab2/mem_alloc.ld mem_alloc.o startup.o syscalls.o /home/raj/Downloads/newlib-2.2.0-1/arm-none-eabi/newlib/libc.a /usr/lib/gcc/arm-none-eabi/4.8.2/fpu/libgcc.a -o mem_alloc
arm-none-eabi-objcopy -O binary mem_alloc /home/raj/RTOS/Lab2/mem_alloc.bin
./arm-softmmu/qemu-system-arm -M realview-pb-a8 -nographic -kernel /home/raj/RTOS/Lab2/mem_alloc.bin
