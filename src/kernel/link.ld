SECTIONS
{
	. = 0x9000;
	.text : { *(.text) }
	.rodata : { *(.rodata) }
}
