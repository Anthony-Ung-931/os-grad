#!/bin/bash

rm bl

nasm bl.asm

qemu-system-i386 -drive format=raw,file=bl
