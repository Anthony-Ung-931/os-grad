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

	mov BP, 0x9000			; Task 4: Set up the stack
	mov SP, BP

	call disk_test			; Task 5: Call disk_test

	call idle_permanently


disk_test:
	pusha			; Task 6: Push all registers onto the stack
				; Task 7: Set up registers properly
	mov AH, 0x02		; 0x02: Mode - Read sectors
	mov AL, NUM_SECTORS	; Number of sectors
	mov BX, KERNEL_ADDRESS	; BX - Offset
	mov CH, 0x00		; CH - Cylinder 0
	mov CL, 0x01		; CL - Sector 1
				; 	Sector 1 contains the bootloader
				;	Sectors 2+ contain the kernel
	mov DH, 0x00		; DH - Head 0
	mov DL, [DRIVE_NUM]	; DL - Drive

	INT 13h			; Task 8: Call Interrupt
	
	jc ERROR_disk_test	; Task 9: Query interrupt flag.
				; If carry flag set, display error.
disk_test_sectors:
	cmp AL, NUM_SECTORS	; Task 10: Check number of sectors read
	jne ERROR_disk_bad_read

	popa			; Task 11: Pop all registers and return
	ret

ERROR_disk_test:
				; Task 9: Print error message 
				; 		if disk read failed
	mov bx, err_msg_disk_fail 
	call print_string
	call new_line
	call idle_permanently

ERROR_disk_bad_read:
	mov bx, err_msg_disk_bad_read 
	call print_string
	call new_line
	call idle_permanently

print_string:
	pusha
	mov AH, 0x0e
print_string_lp:
	mov AL, [BX]
	cmp AL, 0
	je print_done
	INT 10h
	add BX, 1		; Increment BX
	jmp print_string_lp
print_done:
	popa
	ret

new_line:
	mov AH, 0x0e
	mov AL, 0x0a
	INT 10h

	mov AL, 0x0d
	INT 10h

	ret

idle_permanently:
	jmp $			; Infinite Loop

; data
KERNEL_ADDRESS 	equ 0x1000	; Task 2: Store kernel address
DRIVE_NUM	equ 0		; Task 3: Inspect the value printed.
				; Should be 0x80
NUM_SECTORS 	equ 0x01

hello_world db 'Hello World', 0
err_msg_disk_fail db 'ERROR: Disk cannot be read.', 0
err_msg_disk_bad_read db 'ERROR: Disk can be read but the number of sectors is wrong', 0

; Pad file with zeroes
times 510-($-$$) db 0	

; Magic Number
db 0x55
db 0xaa
