
#ifndef __DNAKE_MISC_H__
#define	__DNAKE_MISC_H__

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "types.h"

int __local_if_addr(const char *dev, struct sockaddr_in *addr);

/*��ȡeth0�ӿ� IP��ַ*/
int local_if_addr (struct sockaddr_in *addr);

/*��ȡeth0�ӿ� MAC��ַ*/
int local_if_mac(const char *ifr, uint8_t *mac, uint8_t *mask);

/*��ȡ��������״̬ 0:�쳣 1:����*/
int ethtool_get_link(void);

void mkdir2(const char *url);

#endif
