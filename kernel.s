start:
	@ Enable UART TX GPIO pin 14
	ldr r1, GPFSEL1
	ldr r0, [r1]
	bic	r0, r0, #28672 @ clear gpio14 register
	orr	r0, r0, #8192 @ set gpio14 register
	str r0, [r1]

	@ Enable the mini UART
	mov r0, #1
	ldr r1, AUX_ENABLES
	str r0, [r1]

	@ Use 8-bit mode, instead of 7-bit mode.
	@ I think 7-bit mode uses the 8th bit for a parity check.
	mov r0, #3
	ldr r1, AUX_MU_LCR_REG
	str r0, [r1]

	@ Clear transmit and receive FIFOs
	mov r0, #0xC6
	ldr r1, AUX_MU_IIR_REG
	str r0, [r1]

	@ This register controls the baud rate.
	@ The baud rate is a term for the bits per second transferred to and from the
	@ UART devices. The devices must agree on the same baud rate, or else they
	@ can't interpret the high and low signals properly.
	@
	@ System clock frequency = 250 MHz
	@ Baudrate = 115200
	@ baudrate_register = (250000000 / (8 * 115200)) - 1 = 270.27 ~= 270
	ldr r0, AUX_MU_BAUD_REG_VALUE
	ldr r1, AUX_MU_BAUD_REG
	str r0, [r1]

@ Write 0 to the UART forever
print:
	@ Poll until transmitter is idle and empty
	@
	@ TODO: out of curiosity, I'd like to verify that check_ready is actually
	@ looping.
	@ Based on the 700 MHz processor speed, we should be running "print" way
	@ faster than the UART is able to process (see baudrate).
	check_ready:
		ldr r1, AUX_MU_LSR_REG
		ldr r0, [r1]
		and r0, r0, #0b01100000
		teq r0, #0b01100000
		bne check_ready
	@ Write 0
	mov r0, #0x30
	ldr r1, AUX_MU_IO_REG
	str r0, [r1]
	b print

@ We need this because ARMv6 for the most part doesn't support immediates
@ outside of 0-255, so we need to load 270 from memory.
@ There are some tricks you can do to encode immediates greater than 255, but
@ I guess it doesn't work for 270.
AUX_MU_BAUD_REG_VALUE: .word 270

@ Peripheral registers (i.e. memory locations you read/write to use peripherals)
GPFSEL1: .word 0x20200004
AUX_ENABLES: .word 0x20215004
AUX_MU_IO_REG: .word 0x20215040
AUX_MU_IER_REG: .word 0x20215044
AUX_MU_IIR_REG: .word 0x20215048
AUX_MU_LCR_REG: .word 0x2021504C
AUX_MU_BAUD_REG: .word 0x20215068
AUX_MU_LSR_REG: .word 0x20215054
