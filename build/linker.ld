MEMORY
{
	RAM (rw) : ORIGIN = 0, LENGTH = 128K
	must_be_empty (rwx) : ORIGIN = 0, LENGTH = 0
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
		*(.rodata.str1.1)
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
		*(.got)
		*(.got.plt)
		*(.data.rel.ro.local)
	} >RAM

	_program_size = .;

	_got_start = ADDR(.got);
	_got_size = SIZEOF(.got);

	/DISCARD/ :
	{
		*(.ARM.attributes)
		*(.comment)
	}

	.must_be_empty : { *(*) } > must_be_empty
}
