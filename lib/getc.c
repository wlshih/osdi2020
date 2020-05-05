/*
 * get character with buffer
 */

#include <uart.h>
#include <getc.h>

#define BUF_SIZE 8

static char read_buffer[BUF_SIZE];
static unsigned int head = 0;
static unsigned int rear = 1;

void readbuf_enqueue(char c) {
	if(head != rear) { // buffer is not full
		read_buffer[rear] = c;
		rear = (rear + 1) % BUF_SIZE;
	}
	// drop char if buffer is full
}

char readbuf_dequeue() {
	while(head == (rear-1) % BUF_SIZE); // wait if buffer is empty
	head = (head + 1) % BUF_SIZE;
	return read_buffer[head];
}

char getc() {
	return readbuf_dequeue();
}
