[bits 16]
[org 0x7c00]			; Task 1: Set 16-bit mode and origin.

; Entry point
main:
	mov AH, 0x0e			; Teletype screen
	mov AL, 0x58
	INT 10h

	call new_line

	mov [DRIVE_NUM], DL
	mov AL, [DRIVE_NUM]
	INT 10h

	call new_line	

	mov BX, hello_world
	call print_string

	call new_line

	mov bp, 0x9000			; Task 4: Set up the stack
	mov sp, bp

	call disk_test			; Task 5: Call disk_test

	call idle_permanently

new_line:
	mov AH, 0x0e
	mov AL, 0x0a
	INT 10h

	mov AL, 0x0d
	INT 10h

	ret

disk_test:
	pusha			; Task 6: Push all registers onto the stack
	
	mov AH, 0x02		; Task 7: Set up registers properly
	mov AL, 0x01

	mov BX, [KERNEL_ADDRESS]
	
	mov CH, 0x00
	mov CL, 0x02

	mov DH, 0x00
	mov DL, [DRIVE_NUM]

	INT 13h			; Task 8: Call Interrupt

print_string:
	pusha
	mov AH, 0x0e
print_string_lp:
	mov AL, [bx]
	cmp AL, 0
	je print_done
	int 10h
	add BX, 1		; Increment BX
	jmp print_string_lp
print_done:
	popa
	ret

idle_permanently:
	jmp $			; Infinite Loop

; data
KERNEL_ADDRESS 	dw 0x1000	; Task 2: Store kernel address
DRIVE_NUM	db 0		; Task 3: Inspect the value printed.
				; Should be 0x80

hello_world db 'Hello World', 0


; Pad file with zeroes
times 510-($-$$) db 0	

; Magic Number
db 0x55
db 0xaa
