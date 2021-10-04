[BITS 64]
LOAD_GDT:
    LGDT                [RDI]       ; Loads the GDT from the RDI register, which is where the GDT will be located once called from the Kernel
    MOV                 AX, 0x10    ; Selector for the kernel data segment 
    MOV                 DS, AX      ; Load the kernel data segment into all of the data segment registers
    MOV                 ES, AX
    MOV                 FS, AX
    MOV                 GS, AX
    MOV                 SS, AX
    POP                 RDI
    MOV                 RAX, 0x08   ; Kernel code segment selector 
    PUSH                RAX
    PUSH                RDI
    RETFQ

GLOBAL  LOAD_GDT    
    