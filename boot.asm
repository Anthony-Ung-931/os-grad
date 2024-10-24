[bits 16]
[org 0x7c00]


KERNEL_ADDRESS 	equ 0x1000	
NUM_SECTORS 	equ 0x11
BL_LAST_BYTE	equ 0x11ff


; Entry point
main:
	mov [boot_drive], DL

	mov BP, 0x9000
	mov SP, BP

	call disk_test
	call load_gdt


disk_test:
	pusha			
				
	mov AH, 0x02		; READ mode
	mov AL, NUM_SECTORS	
	mov BX, KERNEL_ADDRESS	

	mov CH, 0x00		; CHS = 0-1-0		
	mov CL, 0x02						
	mov DH, 0x00
		
	mov DL, [boot_drive]	

	INT 13h			
	
	jc ERROR_disk_test
				
    disk_test_sectors:
	cmp AL, NUM_SECTORS	
	jne ERROR_disk_sector_error

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
	call _HALT


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


_HALT:
	jmp $			; Infinite Loop


load_gdt:
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 01
	mov cr0, eax
	jmp CODE_SEGMENT_INDEX:begin_32_bit_mode

[bits 32]
begin_32_bit_mode:
	mov ax, DATA_SEGMENT_INDEX
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	jmp KERNEL_ADDRESS 
	
	call _HALT


CODE_SEGMENT_INDEX equ gdt_code_segment - gdt_start_segment
DATA_SEGMENT_INDEX equ gdt_data_segment - gdt_start_segment


; data
boot_drive	db 0

gdt_start_segment:
	dq 0x0

gdt_code_segment:
	dw 0xffff
	dw 0x0000
	db 0x00
	db 0x9a
	db 0xcf
	db 0x00

gdt_data_segment:
	dw 0xffff
	dw 0x0000
	db 0x00
	db 0x92
	db 0xcf
	db 0x00

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start_segment - 1
	dd gdt_start_segment


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
