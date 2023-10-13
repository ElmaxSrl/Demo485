#include "dmsg.h"
#include "sys_rs485.h"

int main(int argc, char *argv[])
{
	uint8_t data[] = {0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03};
	int sz = sizeof(data);
	sys_rs485.start();
	
	while (1) {
{
	fprintf(stderr, "--> ");
	for(int i=0; i<sz; i++)
		fprintf(stderr, "%02X ", data[i]);
	fprintf(stderr, "\n");
}
		sys_rs485.dtx(data, sz);
		sleep(5);
	}
	return 0;
}

