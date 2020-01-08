/******************************************************************************

 @file CUI.c

 @brief This file contains the interface implementation of the Combined User
         Interface.

 @detail The interface is designed to be shared between clients.
         As such a client can request access to resources whether they be
         Buttons, LEDs or UART Display without the fear that another client
         already has ownership over that resource.

         If a resource is already taken by another client then the interface
         will respond with that information.

         Only a client that has been given access to a resource may utilize
         the resource. Therefore, any calls a client makes to read/write a
         resource will be ignored if the client does not have the access
         required.

 Group: LPRF SW RND
 $Target Device: DEVICES $

 ******************************************************************************
 $License: BSD3 2016 $
 ******************************************************************************
 $Release Name: PACKAGE NAME $
 $Release Date: PACKAGE RELEASE DATE $
 *****************************************************************************/

/******************************************************************************
 Includes
 *****************************************************************************/
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

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

#include "cui.h"


CUI_retVal_t CUI_init(CUI_params_t* _pParams)
{
    return CUI_SUCCESS;
}
void CUI_paramsInit(CUI_params_t* _pParams)
{
    return;
}
CUI_clientHandle_t CUI_clientOpen(CUI_clientParams_t* _pParams)
{
    return CUI_SUCCESS;
}
void CUI_clientParamsInit(CUI_clientParams_t* _pClientParams)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_close()
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_btnResourceRequest(const CUI_clientHandle_t _clientHandle, const CUI_btnRequest_t* _pRequest)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_btnSetCb(const CUI_clientHandle_t _clientHandle, const uint32_t _index, const CUI_btnPressCB_t _appCb)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_btnGetValue(const CUI_clientHandle_t _clientHandle, const uint32_t _index, bool* _pBtnState)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_btnResourceRelease(const CUI_clientHandle_t _clientHandle, const uint32_t _index)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_ledResourceRequest(const CUI_clientHandle_t _clientHandle, const CUI_ledRequest_t* _pRequest)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_ledResourceRelease(const CUI_clientHandle_t _clientHandle, const uint32_t _index)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_ledOn(const CUI_clientHandle_t _clientHandle, const uint32_t _index, const uint8_t _brightness)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_ledOff(const CUI_clientHandle_t _clientHandle, const uint32_t _index)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_ledToggle(const CUI_clientHandle_t _clientHandle, const uint32_t _index)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_ledBlink(const CUI_clientHandle_t _clientHandle, const uint32_t _index, const uint16_t _numBlinks)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_registerMenu(const CUI_clientHandle_t _clientHandle, CUI_menu_t* _pMenu)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_deRegisterMenu(const CUI_clientHandle_t _clientHandle, CUI_menu_t* _pMenu)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_updateMultiMenuTitle(const char* _pTitle)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_menuNav(const CUI_clientHandle_t _clientHandle, CUI_menu_t* _pMenu, const uint32_t _itemIndex)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_processMenuUpdate(void)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_statusLineResourceRequest(const CUI_clientHandle_t _clientHandle, const char _pLabel[MAX_STATUS_LINE_LABEL_LEN], uint32_t* _pLineId)
{
    return CUI_SUCCESS;
}
CUI_retVal_t CUI_statusLinePrintf(const CUI_clientHandle_t _clientHandle, const uint32_t _lineId, const char *format, ...)
{
    return CUI_SUCCESS;
}

void CUI_assert(const char* _assertMsg, const bool _spinLock)
{
    return;
}

void CUI_menuActionBack(const int32_t _itemEntry)
{
    return;
}
void CUI_menuActionHelp(const char _input, char* _pLines[3], CUI_cursorInfo_t* _pCurInfo)
{
    return;
}
