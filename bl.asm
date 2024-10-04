[bits 16]
[org 0x7c00]


KERNEL_ADDRESS 	equ 0x1000	
NUM_SECTORS 	equ 0x1
BL_LAST_BYTE	equ 0x11ff


; Entry point
main:
	mov [boot_drive], DL

	mov bp, 0x9000
	mov sp, bp

	call disk_test
	call test_success
	call idle_permanently


disk_test:
	pusha			
				
	mov AH, 0x02		; READ mode
	mov AL, NUM_SECTORS	
	mov BX, KERNEL_ADDRESS	

	mov CH, 0x00		; CHS = 0-1-0		
	mov CL, 0x01						
	mov DH, 0x00
		
	mov DL, [boot_drive]	

	INT 13h			
	
	jc ERROR_disk_test
				
    disk_test_sectors:
	cmp AL, NUM_SECTORS	
	jne ERROR_disk_sector_error

	popa	
	ret


test_success:
	pusha
	mov AL, [BL_LAST_BYTE]
	cmp AL, 0xaa
	jne ERROR_disk_read_failed
	mov bx, disk_read_success
	call print_string
	popa
	ret
	

ERROR_disk_test:
	mov bx, err_msg_disk_fail 
	call ERROR_EXIT


ERROR_disk_sector_error:
	mov bx, err_msg_disk_sector_error
	call ERROR_EXIT


ERROR_disk_read_failed:
	mov bx, err_msg_disk_read_failed
	call ERROR_EXIT


ERROR_EXIT:
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
boot_drive	db 0

hello_world db 'Hello World', 0
err_msg_disk_fail db 'ERROR: Disk cannot be read.', 0
err_msg_disk_sector_error db 'ERROR: Disk can be read but the number of sectors is wrong', 0
err_msg_disk_read_failed db 'ERROR: Different data appears than what is expected.',0
disk_read_success db 'Disk read success!', 0

; Pad file with zeroes
times 510-($-$$) db 0	

; Magic Number
db 0x55
db 0xaa
