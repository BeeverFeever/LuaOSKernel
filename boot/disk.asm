[bits 16]
load_disk:
    pusha
    push        dx

    mov         ah, 0x02
    mov         al, dh
    mov         cl, 0x02

    mov         ch, 0x00

    mov         dh, 0x00

    int         0x13
    jc          disk_err

    pop         dx
    cmp         al, dh
    jne         sect_err

    popa
    ret

disk_err:
    mov         bx, DISK_ERROR
    call        println
    mov         dh, ah
    call        hexprintln
    jmp         disk_loop

sect_err:
    mov         bx, SECT_ERROR
    call        println

    jmp         disk_loop

disk_loop:
    jmp         $


DISK_ERROR      db "DISK ERROR", 0
SECT_ERROR      db "SECTOR ERROR", 0