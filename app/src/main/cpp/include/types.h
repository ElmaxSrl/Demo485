
#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef void * HANDLE;

#define UNUSED(x) (void)x

#if 0
//typedef char			int8_t;
typedef unsigned char		uint8_t;
typedef short			int16_t;
typedef unsigned short		uint16_t;
typedef int			int32_t;
typedef unsigned int		uint32_t;
typedef long long		int64_t;
typedef unsigned long long	uint64_t;
#endif

#ifndef MIN
#define MIN(a, b) ((a)>(b) ? (b) : (a))
#endif

#endif
