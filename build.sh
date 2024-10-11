#!/bin/bash

rm boot.bin

nasm boot.asm

qemu-system-i386 -drive format=raw,file=boot
