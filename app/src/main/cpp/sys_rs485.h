
#ifndef __RS_485_H__
#define __RS_485_H__

#include "types.h"
#include "DnakeFifo.h"
#include "AutoMutex.h"

static inline int __ts(struct timeval tv)
{
	struct timeval tv2;
	gettimeofday(&tv2, NULL);
	return labs((tv2.tv_sec-tv.tv_sec)*1000+(tv2.tv_usec-tv.tv_usec)/1000);
}


class __sys_rs485 {
public:
	__sys_rs485();
	~__sys_rs485();

	int start(void);

	int tx(uint8_t *data, int length);
	int rx(uint8_t *data, int length, int timeout);

	void setup(int pb, int br);
	void process(void);
	int dtx(uint8_t *data, int length);

public:
	DnakeFifo m_rx;
	int m_used;

	int m_tty;
	pthread_mutex_t m_mutex;
};

extern __sys_rs485 sys_rs485;

#endif

