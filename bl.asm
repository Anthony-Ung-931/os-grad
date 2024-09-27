[bits 16]
[org 0x7c00]			; Task 1: Set 16-bit mode and origin.

; Entry point
mov AH, 0x0e			; Teletype screen
mov AL, 0x58			; Put the letter 'x'
INT 10h

mov AL, 0x0a
INT 10h

mov [DRIVE_NUM], DL
mov AL, [DRIVE_NUM]
INT 10h

mov bp, 0x9000			; Task 4: Set up the stack
mov sp, bp

jmp $				; Infinite loop

; data
KERN_ADDRESS 	dw 0x1000	; Task 2: Store kernel address
DRIVE_NUM	db 0		; Task 3: Inspect the value printed.
				; Should be 0x80

hello_world db 'Hello World', 0

; Pad file with zeroes
times 510-($-$$) db 0	

; Magic Number
db 0x55
db 0xaa
