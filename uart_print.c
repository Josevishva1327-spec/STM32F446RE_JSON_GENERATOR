#include "uart_print.h"
#include "main.h"
#include <string.h>

void uart_print(const char *s)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)s, strlen(s), HAL_MAX_DELAY);
}
