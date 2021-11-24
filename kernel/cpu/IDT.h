/**
 * @file        idt.h
 * @author      Amrit Bhogal (@Frityet)
 * @brief       The interrupt descriptor table, and utilities for registering interrupts
 * @attention   Also see @b interrupt_handler.asm 
 * @version     1.0
 * @date        2021-11-24
 * 
 * @copyright Copyright Amrit Bhogal(c) 2021
 * 
 */
#ifndef LUAOS_IDT
#define LUAOS_IDT

#include <common.h>

struct interrupt_frame {
    uint64_t    error_code;
    uint64_t    rip;
    uint64_t    cs;
    uint64_t    register_flags;
    uint64_t    rsp;
    uint64_t    ss;
};
struct idt_gate {
    uint16_t    offset0;
    uint16_t    selector;
    uint8_t     interrupt_stack_table;
    uint8_t     type;
    uint16_t    offset1;
    uint32_t    offset2;
    uint32_t    zero;
} __attribute__((packed));

struct idt_descriptor {
    uint16_t            limit;
    uint64_t            offset;

} __attribute__((packed));


void initialise_idt(void);

void register_interrupt_handler(uintmax_t   index,
                                uint64_t    address, 
                                uint8_t     gate_type,
                                uint8_t     interrupt_stack_table);


#endif //LUAOS_IDT
