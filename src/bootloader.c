#include <bootloader.h>
#include <uart.h>
#include <string.h>
#include <reboot.h>

#define BLOCK_SIZE 4096
#define PROTECT_START 0x00000
#define PROTECT_END   0x40000

// identifilers form boot code and linker script
// stored at start & end address of current image
extern void _start;
extern void _end;

void loadimg() {
	// back up current kernel image to protected area
	uart_puts("Start backing up current kernel image...\n");

	unsigned int backup_start = PROTECT_START;
	unsigned int offset = &_start - backup_start;
	//unsigned int backup_end = &_end + offset;
	
	memcpy((void*)backup_start, (void*)&_start, (unsigned int)(&_end - &_start));

	uart_puts("Backup finished. Ready to load.\n");
	uart_puts("Please run sendImg.sh from host now:\n\n");
	/* run sendImg.sh as root */

	/* receive load address */
	/* receive kernel size */
	/* receive kernel image data */
	
	unsigned int load_addr = read_int();
	unsigned int ker_size = read_int();
	// block number of the kernel image, for alignment
	unsigned int ker_blkn = ((ker_size - 1) / BLOCK_SIZE + 1);
	
	unsigned int new_start = load_addr;
	unsigned int new_end = new_start + ker_blkn * BLOCK_SIZE;

	// check for address alignment, load address should align to 0x1000
	if(load_addr % BLOCK_SIZE) {
		uart_puts("Error: address alignment fault\n");
		return;
	}
	
	// check location, image data can't be stored in protected area
	if((new_start < PROTECT_END && new_start > PROTECT_START) || \
	   (new_end < PROTECT_END && new_end > PROTECT_START)) {
		uart_puts("Error: load address is protected\n");
		return;
	}
	
	if(new_start != 0x80000) {
		uart_puts("Error: only location 0x80000 is allowed currently...");
		return;
	}
	
	// read kernel image data
	uart_puts("Loading kernel image...\n");



}

// for loadimg protocol, return the integer value of received string
int read_int() {
	int result = 0;

	while(1) {
		char c = uart_getc();
		if(c == '\n')
			break;
		result = result * 10 + c - '0';
	}

	return result;
}

