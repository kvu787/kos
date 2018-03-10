start:
	@ This is basically a UART driver.
	@ The most helpful resources I found while implementing this were
	@   * Stanford's cs140e class: https://web.stanford.edu/class/cs140e/assignments/1-shell/
	@   * dwelch67's working bare metal programs: https://github.com/dwelch67/raspberrypi
	@     * The uart01/ folder in particular.
	@   * The BCM2835 manual. Try to get the BCM2837 manual with errata fixes:
	@     https://raspberrypi.stackexchange.com/a/78792/80441

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

@ Wait about 8 seconds.
@ The user should start their terminal before this delay finishes.
@
@ Before I put this here, about 50% of the time I was getting gibberish in
@ in my output.
@ I'm guessing that since my client terminal always connected after this began
@ blasting characters, the client sometimes picked up the middle of a UART
@ transmission and started getting gibberish.
DELAY_VALUE: .word 99999999
wait:
	ldr r1, DELAY_VALUE
	mov r0, #0
	loop:
		add r0, r0, #1
		cmp r0, r1
		blt loop

@ Write all ASCII graphic characters forever. 
mov r0, #0x20
print:
	@ Write character
	bl print_char

	@ Increment to next character, with wraparound
	add r0, r0, #1
	cmp r0, #0x7f
	movge r0, #0x20

	@ Loop
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
AUX_MU_IIR_REG: .word 0x20215048
AUX_MU_LCR_REG: .word 0x2021504C
AUX_MU_BAUD_REG: .word 0x20215068
AUX_MU_LSR_REG: .word 0x20215054

@ This subroutine transmits the character stored in r0 through the UART
@ caller-saved registers: r0-r3
@ callee-saved registers: r4-r11
@ r0 = character to print
@ TODO?: return from this function only when we know the character has left
@ the transmit queue. I.e. flush it.
print_char:
	@ Poll until transmitter is idle and empty
	@
	@ Based on the 700 MHz processor speed, we should be running "print" way
	@ faster than the UART is able to process (see baudrate).
	@
	@ I verified that check_ready actually is looping by putting "bne hang"
	@ at the end, and verifying no output in the console.
	check_ready:
		ldr r4, AUX_MU_LSR_REG
		ldr r5, [r4]
		and r5, r5, #0b01100000
		teq r5, #0b01100000
		bne check_ready

	@ Write character to transmitter
	ldr r4, AUX_MU_IO_REG
	str r0, [r4]

	@ return
	bx lr
