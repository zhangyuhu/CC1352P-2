#ifndef BSP_INIT_H
#define BSP_INIT_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include "string.h"

#include <ti/drivers/apps/Button.h>
#include <ti/drivers/apps/LED.h>


#ifdef __cplusplus
extern "C" {
#endif

void bsp_init(void);
int uart_writeString(void * _buffer, size_t _size);

#ifdef __cplusplus
}
#endif

#endif
