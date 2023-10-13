
#ifndef __DMSG_H__
#define __DMSG_H__

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "dxml.h"

typedef void (*dmsg_android_callback_t)(const char *url, const char *body);

typedef void (*dmsg_callback_t)(const char *body);

int dmsg_setup (const char *url, dmsg_callback_t func);

/*
 * resultֵ 2xx:OK 4xx:���� ����http����ֵ
 */
int dmsg_ack (int result, const char *params);

int dmsg_init (const char *prefix);

class dmsg {
public:
	dmsg();
	~dmsg();

	/*
	 * ����ֵ 2xx:OK 4xx:���� ����http����ֵ
	 */
	int request (const char *url, const char *body);

	const char *body() {return m_body;};

private:
	char *m_data;
	char *m_body;
};

extern dmsg_android_callback_t android_callback;

#endif
