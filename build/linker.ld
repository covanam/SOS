MEMORY
{
	RAM (rw) : ORIGIN = 0, LENGTH = 128K
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
		*(.text.startup)
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

	.got :
	{
		*(.got.plt)
	} >RAM

	_program_size = .;

	_got_start = ADDR(.got);
	_got_size = SIZEOF(.got);
}
