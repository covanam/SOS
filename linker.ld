/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20020000;    /* end of RAM */

/* Specify the memory areas */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    RAM (rw) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } >FLASH

    .text :
    {
        *(.text)
    } >FLASH

    .rodata :
    {
        *(.rodata)
    } >FLASH

    _sidata = LOADADDR(.data);

    .data : 
    {
        _sdata = .;
        *(.data)
        _edata = .;
    } >RAM AT> FLASH

    .bss :
    {
        _sbss = .;
        *(.bss)
        _ebss = .;
    } >RAM

    .osstack :
    {   
        /* 1 KB for OS stack */
        . = ALIGN(8);
        _start_os_stack = .;
        . = . + 1024;
        _end_os_stack = .;
    } >RAM

    .osheap :
    {   
        /* 50k for OS heap */
        _start_os_heap = .;
        . = . + 50K;
        _end_os_heap = .;
    } >RAM
}
