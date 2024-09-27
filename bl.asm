[bits 16]
[org 0x7c00]			; Task 1: Set 16-bit mode and origin.

; Entry point
mov AH, 0x0e			; Teletype screen
mov AL, 0x58			; Put the letter 'x'
INT 10h
jmp $				; Infinite loop

; data
KERN_ADDRESS 	dw 0x1000	; Task 2: Store kernel address

hello_world db 'Hello World', 0

; Pad file with zeroes
times 510-($-$$) db 0	

; Magic Number
db 0x55
db 0xaa
