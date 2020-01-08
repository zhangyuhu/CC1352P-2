#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTCC26XX.h>
#include <ti/drivers/apps/Button.h>
#include <ti/drivers/apps/LED.h>

#include <xdc/runtime/System.h>
#include DeviceFamily_constructPath(driverlib/cpu.h)
#include "ti_drivers_config.h"

#include "bsp_init.h"

#define MAX_NUM_UART_CHARS   (200)

static UART_Params gUartParams;
static UART_Handle gUartHandle = NULL;
static uint8_t gUartTxBuffer[MAX_NUM_UART_CHARS];
static uint8_t gUartRxBuffer[MAX_NUM_UART_CHARS];
static bool gUartWriteComplete = false;


static void UartWriteCallback(UART_Handle _handle, void *_buf, size_t _size);
static void UartReadCallback(UART_Handle _handle, void *_buf, size_t _size);

/******************************************************************************
 * @brief uart_device_open
 *****************************************************************************/
void bsp_init(void) {
    LED_init();
    Button_init();

    UART_init();
    UART_Params_init(&gUartParams);
    gUartParams.baudRate = 115200;
    gUartParams.writeMode     = UART_MODE_CALLBACK;
    gUartParams.writeDataMode = UART_DATA_BINARY;
    gUartParams.writeCallback = UartWriteCallback;
    gUartParams.readMode      = UART_MODE_CALLBACK;
    gUartParams.readDataMode  = UART_DATA_BINARY;
    gUartParams.readCallback  = UartReadCallback;
    gUartHandle = UART_open(CONFIG_DISPLAY_UART, &gUartParams);
}


static void UartWriteCallback(UART_Handle _handle, void *_buf, size_t _size)
{
    uint32_t key = HwiP_disable();
    gUartWriteComplete = true;
    /* Exit critical section */
    HwiP_restore(key);
}

static void UartReadCallback(UART_Handle _handle, void *_buf, size_t _size)
{
    // Make sure we received all expected bytes
    if (_size)
    {
        // If cleared, then read it
        if(gUartTxBuffer[0] == 0)
        {
            // Copy bytes from RX buffer to TX buffer
            for(size_t i = 0; i < _size; i++)
            {
                gUartTxBuffer[i] = ((uint8_t*)_buf)[i];
            }
        }
        memset(_buf, '\0', _size);
    }
    else
    {
        // Handle error or call to UART_readCancel()
        UART_readCancel(gUartHandle);
    }
}

int uart_writeString(void * _buffer, size_t _size)
{
    /*
     * Since the UART driver is in Callback mode which is non blocking.
     *  If UART_write is called before a previous call to UART_write
     *  has completed it will not be printed. By taking a quick
     *  nap we can attempt to perform the subsequent write. If the
     *  previous call still hasn't finished after this nap the write
     *  will be skipped as it would have been before.
     */

    //Error if no buffer
    if((gUartHandle == NULL) || (_buffer == NULL) )
    {
        return -1;
    }

    bool uartReady = false;
    /* Enter critical section so this function is thread safe*/
    uint32_t key = HwiP_disable();
    if (gUartWriteComplete)
    {
        uartReady = true;
    }

    /* Exit critical section */
    HwiP_restore(key);

    if (!uartReady)
    {
        /*
         * If the uart driver is not yet done with the previous call to
         * UART_write, then we can attempt to wait a small period of time.
         *
         * let's sleep 5000 ticks at 1000 tick intervals and keep checking
         * on the readiness of the UART driver.
         *
         * If it never becomes ready, we have no choice but to abandon this
         * UART_write call by returning CUI_PREV_WRITE_UNFINISHED.
         */
        uint8_t i;
        for (i = 0; i < 10; i++)
        {
            Task_sleep(1000);
            uint32_t key = HwiP_disable();
            if (gUartWriteComplete)
            {
                uartReady = true;
            }
            /* Exit critical section */
            HwiP_restore(key);
            if (uartReady)
            {
                break;
            }
        }

        // If it still isn't ready, the only option we have is to ignore
        // this print and hope that it wont be noticeable
        if (!uartReady)
        {
            return -1;
        }
    }

    key = HwiP_disable();
    gUartWriteComplete = false;
    HwiP_restore(key);

    // UART_write ret val ignored because we are in callback mode. The result
    // will always be zero.
    if (0 != UART_write(gUartHandle, (const void *)_buffer, _size))
    {
        return -1;
    }

    return 0;
}
