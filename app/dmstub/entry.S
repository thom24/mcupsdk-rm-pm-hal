;
; DM Stub firmware
;
; Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
;
; This software is licensed under the standard terms and conditions in the
; Texas Instruments Incorporated Technology and Software Publicly
; Available Software License Agreement, a copy of which is included in
; the software download.
;

	.global _stub_start
	.global undef_handler
	.global swi_handler
	.global prefetch_abt_handler
	.global data_abt_handler
	.global reserved_handler
	.global irq_handler
	.global fiq_handler
	.global stub_entry
	.global _end_stack

	.retain
	.retainrefs

       .text
       .arm
       .retain
       .retainrefs

_vectors:

_reset:			ldr pc, _reset_handler
_undef:			ldr pc, _undef_handler
_swi:			ldr pc, _swi_handler
_prefetch_abt:		ldr pc, _prefetch_abt_handler
_data_abt:		ldr pc, _data_abt_handler
_reserved:		ldr pc, _reserved_handler
_irq:			ldr pc, _irq_handler
_fiq:			ldr pc, _fiq_handler

_reset_handler:
	.word _stub_start
_undef_handler:
	.word undef_handler
_swi_handler:
	.word swi_handler
_prefetch_abt_handler:
	.word prefetch_abt_handler
_data_abt_handler:
	.word data_abt_handler
_reserved_handler:
	.word reserved_handler
_irq_handler:
	.word irq_handler_asm
_fiq_handler:
	.word fiq_handler
_end_vectors:

_reset_vector_address:
	.word 0x00000000

_stub_start:
	; Save current stack pointer
	adr r1, _sys_stack_pointer
	str sp, [r1]
	adr r1, _sys_lr_register
	str lr, [r1]

	; Copy vector table
	adr     r0, _reset
	ldr     r1, _reset_vector_address
	MOV     r2, #0x10
wordcopy:
	ldr     r3, [r0], #4
	str     r3, [r1], #4
	SUBS    r2, r2, #1
	BNE     wordcopy

	; initialize the stack
	ldr sp, _stack_addr
	; Space for the jump
	nop
	nop

	; At this point we should be CPU0
	; jump to proper reset handler
	ldr pc, _c_stub_entry

irq_handler_asm:
	stmdb	sp!,{r0-r3,r12,lr}
	bl irq_handler
	ldmia	sp!,{r0-r3,r12,lr}
	subs	pc, lr, #4

_c_stub_entry:
	.word stub_entry
_stack_addr:
	.word _end_stack
_sys_stack_pointer:
	.word 0x00000000
_sys_lr_register:
	.word 0x00000000
