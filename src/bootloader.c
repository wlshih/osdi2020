#include <bootloader.h>
#include <uart.h>
#include <string.h>

void loadimg() {
	uart_puts("Start loading kernel image...\n");
	uart_puts("Please input kernel load address(default: 0x80000):\n");
	uart_puts("Please send kernel image from UART now:\n\n");
	/* run sendImg.sh as root */

	/* receive location */
	/* receive kernel size */
	/* receive kernel image data */


}

int read_int() {
	int result = 0;

	while(1) {
		char c = uart_getc();
		if(c == '\n')
			break;
		//uart_send(c);
		result = result * 10 + c - '0';
	}

	return result;
}


