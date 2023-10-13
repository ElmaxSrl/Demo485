
#ifndef __DNAKE_FIFO_H__
#define __DNAKE_FIFO_H__

#include <pthread.h>
#include "types.h"

class DnakeFifo {
public:
	DnakeFifo(int max = 8*1024);
	~DnakeFifo();

	void realloc(int max);

	int put(uint8_t *data, int length);
	int get(uint8_t *data, int length);
	int used() {return m_used;};
	void flush();
	const uint8_t *data(void) { return m_data; };
	int copy(uint8_t *data, int length);

private:
	uint8_t *m_data;
	int m_max;
	int m_read;
	int m_write;
	int m_used;

	pthread_mutex_t m_mutex;
};

#endif
