ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
        /*
         *  Let's define some basic markers that tell us where the kernel starts & ends.
         *  These include `start_of_kernel` as well as `end_of_kernel`.
         */
		start_of_kernel = .;

        /* Let's align the multiboot structure defined in arch/i386/boot.S here. */
		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		end_of_kernel = .;
	}
}