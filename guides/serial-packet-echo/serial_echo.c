/*
 * serial_echo.c
 *
 *  Created on: Apr 15, 2024
 *      Author: Jeremy Goldberger
 */

#include "sys_common.h"
#include "emac.h"
#include "sci.h"

#define RECIEVE_HDP_LOC 0xFC521010

#define UART scilinREG

uint8 txtCRLF[] = {'\r', '\n'};
uint8 txtRecv[] = {"Received packet!"};
uint8 txtInit[] = {"System initialized! Awaiting packets..."};

void sciDisplayText(uint8 *text, uint32 length);

void serial_echo_main(uint8 emacAddr[6U])
{
    uint32_t* descriptor_ptr = RECIEVE_HDP_LOC;
    uint8_t* buf_ptr;
    uint16_t buf_offset;
    uint16_t buf_len;
    uint16_t flags;
    uint16_t pkt_len;

    sciInit();
    EMACHWInit(emacAddr);
    _enable_IRQ();

    sciDisplayText(txtCRLF, sizeof(txtCRLF));
    sciDisplayText(txtInit, sizeof(txtInit));
    sciDisplayText(txtCRLF, sizeof(txtCRLF));

    while(1)
    {
        while (*descriptor_ptr)
        {
            sciDisplayText(txtRecv, sizeof(txtRecv));
            sciDisplayText(txtCRLF, sizeof(txtCRLF));
            buf_ptr = *(descriptor_ptr + 1);
            buf_offset = (uint16_t)(*(descriptor_ptr + 2) >> 16);
            buf_len = (uint16_t)(*(descriptor_ptr + 2));
            flags = (uint16_t)(*(descriptor_ptr + 3) >> 16);
            pkt_len = (uint16_t)(*(descriptor_ptr + 3));

            printf("Printing the whole thing:\n%s\n", buf_ptr + buf_offset);
            sciDisplayText(buf_ptr + buf_offset, 12);
            sciDisplayText(txtCRLF, sizeof(txtCRLF));

            descriptor_ptr = *(descriptor_ptr);
        }
    }
}

void sciDisplayText(uint8 *text,uint32 length)
{
    while(length--)
    {
        while ((UART->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(UART,*text++);      /* send out text   */
    };
}
