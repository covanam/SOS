/* Entry Point */
ENTRY(main)

/* Specify the memory areas */
MEMORY
{
    RAM (rw) : ORIGIN = 0x08001000, LENGTH = 128K
}

SECTIONS
{
	.header :
	{
		KEEP(*(.header))
	} >RAM

	.text :
	{
		*(.text)
	} >RAM

	.rodata :
	{
		*(.rodata)
	} >RAM

	.data : 
	{
		*(.data)
	} >RAM

	.bss :
	{
		*(.bss)
	} >RAM

	_program_size = . - 0x08001000;
}
