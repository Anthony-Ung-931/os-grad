bits 16
org 0x7c00

mov AH, 0x0e		; Teletype screen
mov AL, 0x58		; Put the letter 'x'
INT 10h
jmp $			; Infinite loop

times 510-($-$$) db 0	; Pad the file with zeros
dw 0xAA55		; Put the magic number
