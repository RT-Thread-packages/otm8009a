/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-01     tyustli        first version
 */

#include "otm8009a.h"

#ifdef PKG_USING_OTM8009A

#define DBG_TAG "otm8009a"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * @brief Constant tables of register settings used to transmit DSI
 * command packets as power up initialization sequence of the KoD LCD (OTM8009A LCD Driver)
 */
const rt_uint8_t lcdRegData1[]  = {0x80, 0x09, 0x01, 0xFF};
const rt_uint8_t lcdRegData2[]  = {0x80, 0x09, 0xFF};
const rt_uint8_t lcdRegData3[]  = {0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE1};
const rt_uint8_t lcdRegData4[]  = {0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE2};
const rt_uint8_t lcdRegData5[]  = {0x79, 0x79, 0xD8};
const rt_uint8_t lcdRegData6[]  = {0x00, 0x01, 0xB3};
const rt_uint8_t lcdRegData7[]  = {0x85, 0x01, 0x00, 0x84, 0x01, 0x00, 0xCE};
const rt_uint8_t lcdRegData8[]  = {0x18, 0x04, 0x03, 0x39, 0x00, 0x00, 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00, 0xCE};
const rt_uint8_t lcdRegData9[]  = {0x18, 0x02, 0x03, 0x3B, 0x00, 0x00, 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00, 0xCE};
const rt_uint8_t lcdRegData10[] = {0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0xCF};
const rt_uint8_t lcdRegData11[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData12[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData13[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData14[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData15[] = {0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData16[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData17[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t lcdRegData18[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCB};
const rt_uint8_t lcdRegData19[] = {0x00, 0x26, 0x09, 0x0B, 0x01, 0x25, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t lcdRegData20[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02, 0xCC};
const rt_uint8_t lcdRegData21[] = {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t lcdRegData22[] = {0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t lcdRegData23[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01, 0xCC};
const rt_uint8_t lcdRegData24[] = {0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t lcdRegData25[] = {0xFF, 0xFF, 0xFF, 0xFF};

/*
  * CASET value (Column Address Set) : X direction LCD GRAM boundaries
  * depending on LCD orientation mode and PASET value (Page Address Set) : Y direction
  * LCD GRAM boundaries depending on LCD orientation mode
  * XS[15:0] = 0x000 = 0, XE[15:0] = 0x31F = 799 for landscape mode : apply to CASET
  * YS[15:0] = 0x000 = 0, YE[15:0] = 0x31F = 799 for portrait mode : : apply to PASET
  */
const rt_uint8_t lcdRegData27[] = {0x00, 0x00, 0x03, 0x1F, OTM8009A_CMD_CASET};
/*
  * XS[15:0] = 0x000 = 0, XE[15:0] = 0x1DF = 479 for portrait mode : apply to CASET
  * YS[15:0] = 0x000 = 0, YE[15:0] = 0x1DF = 479 for landscape mode : apply to PASET
 */
const rt_uint8_t lcdRegData28[] = {0x00, 0x00, 0x01, 0xDF, OTM8009A_CMD_PASET};

const rt_uint8_t ShortRegData1[]  = {OTM8009A_CMD_NOP, 0x00};
const rt_uint8_t ShortRegData2[]  = {OTM8009A_CMD_NOP, 0x80};
const rt_uint8_t ShortRegData3[]  = {0xC4, 0x30};
const rt_uint8_t ShortRegData4[]  = {OTM8009A_CMD_NOP, 0x8A};
const rt_uint8_t ShortRegData5[]  = {0xC4, 0x40};
const rt_uint8_t ShortRegData6[]  = {OTM8009A_CMD_NOP, 0xB1};
const rt_uint8_t ShortRegData7[]  = {0xC5, 0xA9};
const rt_uint8_t ShortRegData8[]  = {OTM8009A_CMD_NOP, 0x91};
const rt_uint8_t ShortRegData9[]  = {0xC5, 0x34};
const rt_uint8_t ShortRegData10[] = {OTM8009A_CMD_NOP, 0xB4};
const rt_uint8_t ShortRegData11[] = {0xC0, 0x50};
const rt_uint8_t ShortRegData12[] = {0xD9, 0x4E};
const rt_uint8_t ShortRegData13[] = {OTM8009A_CMD_NOP, 0x81};
const rt_uint8_t ShortRegData14[] = {0xC1, 0x66};
const rt_uint8_t ShortRegData15[] = {OTM8009A_CMD_NOP, 0xA1};
const rt_uint8_t ShortRegData16[] = {0xC1, 0x08};
const rt_uint8_t ShortRegData17[] = {OTM8009A_CMD_NOP, 0x92};
const rt_uint8_t ShortRegData18[] = {0xC5, 0x01};
const rt_uint8_t ShortRegData19[] = {OTM8009A_CMD_NOP, 0x95};
const rt_uint8_t ShortRegData20[] = {OTM8009A_CMD_NOP, 0x94};
const rt_uint8_t ShortRegData21[] = {0xC5, 0x33};
const rt_uint8_t ShortRegData22[] = {OTM8009A_CMD_NOP, 0xA3};
const rt_uint8_t ShortRegData23[] = {0xC0, 0x1B};
const rt_uint8_t ShortRegData24[] = {OTM8009A_CMD_NOP, 0x82};
const rt_uint8_t ShortRegData25[] = {0xC5, 0x83};
const rt_uint8_t ShortRegData26[] = {0xC4, 0x83};
const rt_uint8_t ShortRegData27[] = {0xC1, 0x0E};
const rt_uint8_t ShortRegData28[] = {OTM8009A_CMD_NOP, 0xA6};
const rt_uint8_t ShortRegData29[] = {OTM8009A_CMD_NOP, 0xA0};
const rt_uint8_t ShortRegData30[] = {OTM8009A_CMD_NOP, 0xB0};
const rt_uint8_t ShortRegData31[] = {OTM8009A_CMD_NOP, 0xC0};
const rt_uint8_t ShortRegData32[] = {OTM8009A_CMD_NOP, 0xD0};
const rt_uint8_t ShortRegData33[] = {OTM8009A_CMD_NOP, 0x90};
const rt_uint8_t ShortRegData34[] = {OTM8009A_CMD_NOP, 0xE0};
const rt_uint8_t ShortRegData35[] = {OTM8009A_CMD_NOP, 0xF0};
const rt_uint8_t ShortRegData36[] = {OTM8009A_CMD_SLPOUT, 0x00};
const rt_uint8_t ShortRegData37[] = {OTM8009A_CMD_COLMOD, OTM8009A_COLMOD_RGB565};
const rt_uint8_t ShortRegData38[] = {OTM8009A_CMD_COLMOD, OTM8009A_COLMOD_RGB888};
const rt_uint8_t ShortRegData39[] = {OTM8009A_CMD_MADCTR, OTM8009A_MADCTR_MODE_LANDSCAPE};
const rt_uint8_t ShortRegData40[] = {OTM8009A_CMD_WRDISBV, 0x7F};
const rt_uint8_t ShortRegData41[] = {OTM8009A_CMD_WRCTRLD, 0x2C};
const rt_uint8_t ShortRegData42[] = {OTM8009A_CMD_WRCABC, 0x02};
const rt_uint8_t ShortRegData43[] = {OTM8009A_CMD_WRCABCMB, 0xFF};
const rt_uint8_t ShortRegData44[] = {OTM8009A_CMD_DISPON, 0x00};
const rt_uint8_t ShortRegData45[] = {OTM8009A_CMD_RAMWR, 0x00};
const rt_uint8_t ShortRegData46[] = {0xCF, 0x00};
const rt_uint8_t ShortRegData47[] = {0xC5, 0x66};
const rt_uint8_t ShortRegData48[] = {OTM8009A_CMD_NOP, 0xB6};
const rt_uint8_t ShortRegData49[] = {0xF5, 0x06};
const rt_uint8_t ShortRegData50[] = {OTM8009A_CMD_NOP, 0xB1};
const rt_uint8_t ShortRegData51[] = {0xC6, 0x06};
const rt_uint8_t ShortRegData52[] = {OTM8009A_CMD_DISPOFF, 0x00};
const rt_uint8_t ShortRegData53[] = {OTM8009A_CMD_DISPON, 0x00};

static struct rt_lcd_device lcd;

static rt_err_t otm8009a_write_cmd(rt_uint8_t *p, uint32_t num)
{
    return rt_lcd_intf_write_cmd(lcd.intf, (void *)p, num);
}

static rt_err_t otm8009a_init_display(rt_lcd_t device)
{
    /* Enable CMD2 to access vendor specific commands                               */
    /* Enter in command 2 mode and set EXTC to enable address shift function (0x00) */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData1, 3);

    /* Enter ORISE Command 2 */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData2, 0);  /* Shift address to 0x80 */
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData2, 2);

    /////////////////////////////////////////////////////////////////////
    /* SD_PCH_CTRL - 0xC480h - 129th parameter - Default 0x00          */
    /* Set SD_PT                                                       */
    /* -> Source output level during porch and non-display area to GND */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData2, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData3, 0);
    rt_thread_mdelay(10);
    /* Not documented */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData4, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData5, 0);
    rt_thread_mdelay(10);

    /* PWR_CTRL4 - 0xC4B0h - 178th parameter - Default 0xA8 */
    /* Set gvdd_en_test                                     */
    /* -> enable GVDD test mode !!!                         */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData6, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData7, 0);

    /* PWR_CTRL2 - 0xC590h - 146th parameter - Default 0x79      */
    /* Set pump 4 vgh voltage                                    */
    /* -> from 15.0v down to 13.0v                               */
    /* Set pump 5 vgh voltage                                    */
    /* -> from -12.0v downto -9.0v                               */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData8, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData9, 0);

    /* P_DRV_M - 0xC0B4h - 181th parameter - Default 0x00 */
    /* -> Column inversion                                */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData10, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData11, 0);

    /* VCOMDC - 0xD900h - 1st parameter - Default 0x39h */
    /* VCOM Voltage settings                            */
    /* -> from -1.0000v downto -1.2625v                 */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData12, 0);

    /* Oscillator adjustment for Idle/Normal mode (LPDT only) set to 65Hz (default is 60Hz) */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData13, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData14, 0);

    /* Video mode internal */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData15, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData16, 0);

    /* PWR_CTRL2 - 0xC590h - 147h parameter - Default 0x00 */
    /* Set pump 4&5 x6                                     */
    /* -> ONLY VALID when PUMP4_EN_ASDM_HV = "0"           */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData17, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData18, 0);

    /* PWR_CTRL2 - 0xC590h - 150th parameter - Default 0x33h */
    /* Change pump4 clock ratio                              */
    /* -> from 1 line to 1/2 line                            */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData19, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData9, 0);

    /* GVDD/NGVDD settings */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData5, 2);

    /* PWR_CTRL2 - 0xC590h - 149th parameter - Default 0x33h */
    /* Rewrite the default value !                           */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData20, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData21, 0);

    /* Panel display timing Setting 3 */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData22, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData23, 0);

    /* Power control 1 */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData24, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData25, 0);

    /* Source driver precharge */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData13, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData26, 0);


    otm8009a_write_cmd((rt_uint8_t *)ShortRegData15, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData27, 0);


    otm8009a_write_cmd((rt_uint8_t *)ShortRegData28, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData6, 2);

    /* GOAVST */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData2, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData7, 6);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData29, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData8, 14);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData30, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData9, 14);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData31, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData10, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData32, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData46, 0);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData2, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData11, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData33, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData12, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData29, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData13, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData30, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData14, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData31, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData15, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData32, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData16, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData34, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData17, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData35, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData18, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData2, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData19, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData33, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData20, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData29, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData21, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData30, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData22, 10);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData31, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData23, 15);

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData32, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData24, 15);

    /* PWR_CTRL1 - 0xc580h - 130th parameter - default 0x00 */
    /* Pump 1 min and max DM                                */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData13, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData47, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData48, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData49, 0);

    /* CABC LEDPWM frequency adjusted to 19,5kHz */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData50, 0);
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData51, 0);

    /* Exit CMD2 mode */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData25, 3);

    /* Standard DCS Initialization TO KEEP CAN BE DONE IN HSDT                   */

    /* NOP - goes back to DCS std command ? */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);

    /* Gamma correction 2.2+ table (HSDT possible) */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData3, 16);
    /* Gamma correction 2.2- table (HSDT possible) */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData4, 16);
    /* Send Sleep Out command to display : no parameter */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData36, 0);

    /* Wait for sleep out exit */
    rt_thread_mdelay(120);

    /* Set Pixel color format to RGB888 */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData38, 0);

    /* Send command to configure display in landscape orientation mode. By default
    the orientation mode is portrait  */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData39, 0);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData27, 4);
    otm8009a_write_cmd((rt_uint8_t *)lcdRegData28, 4);

    /** CABC : Content Adaptive Backlight Control section start >> */
    /* Note : defaut is 0 (lowest Brightness), 0xFF is highest Brightness, try 0x7F : intermediate value */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData40, 0);
    /* defaut is 0, try 0x2C - Brightness Control Block, Display Dimming & BackLight on */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData41, 0);
    /* defaut is 0, try 0x02 - image Content based Adaptive Brightness [Still Picture] */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData42, 0);
    /* defaut is 0 (lowest Brightness), 0xFF is highest Brightness */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData43, 0);

    /** CABC : Content Adaptive Backlight Control section end << */

    /* Send Command Display On */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData44, 0);
    /* NOP command */

    otm8009a_write_cmd((rt_uint8_t *)ShortRegData1, 0);
    /* Send Command GRAM memory write (no parameters) : this initiates frame write via other DSI commands sent by */
    /* DSI host from LTDC incoming pixels in video mode */
    otm8009a_write_cmd((rt_uint8_t *)ShortRegData45, 0);

    return RT_EOK;
}

static rt_err_t otm8009a_display_on(void)
{
    return otm8009a_write_cmd((rt_uint8_t *)ShortRegData53, 0);
}

static rt_err_t otm8009a_display_off(void)
{
    return otm8009a_write_cmd((rt_uint8_t *)ShortRegData52, 0);
}

static rt_err_t stm32_lcd_control(rt_lcd_t device, int cmd, void *args)
{
    switch(cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;

    case RTGRAPHIC_CTRL_POWERON:
        otm8009a_display_on();
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        otm8009a_display_off();
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &lcd.config.gra_info, sizeof(lcd.config.gra_info));
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;

    case RTGRAPHIC_CTRL_GET_EXT:
        break;
    }

    return RT_EOK;
}

static struct rt_lcd_device_ops otm8009a_ops =
{
    stm32_lcd_control,
    otm8009a_init_display,
};

int rt_hw_otm8009a_init(struct rt_lcd_config *config, const char *name)
{
    rt_err_t result;

    result	= RT_EOK;

    /* reset first MSP Initialize only in case of first initialization This will set IP blocks LTDC, DSI and DMA2D */
    rt_pin_mode(config->hw_info.bl_pin, PIN_MODE_OUTPUT);
    rt_pin_write(config->hw_info.bl_pin, PIN_LOW);
    rt_thread_mdelay(20);
    rt_pin_write(config->hw_info.bl_pin, PIN_HIGH);
    rt_thread_mdelay(10);

    lcd.intf = (rt_lcd_intf_t)rt_device_find(config->dev_name);
    if (lcd.intf == RT_NULL)
    {
        LOG_E("can't find interface device\n");
        return -RT_ERROR;
    }

    if (rt_device_open((rt_device_t)lcd.intf, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open lcd interface device failed\n");
        return -RT_ERROR;
    }

    lcd.config.gra_info.width          = config->gra_info.width;
    lcd.config.gra_info.height         = config->gra_info.height;
    lcd.config.gra_info.pixel_format   = config->gra_info.pixel_format;
    lcd.config.gra_info.bits_per_pixel = config->gra_info.bits_per_pixel;
    lcd.config.gra_info.framebuffer    = (rt_uint8_t *)rt_malloc(lcd.config.gra_info.width * lcd.config.gra_info.height * (lcd.config.gra_info.bits_per_pixel / 8));
    if (lcd.config.gra_info.framebuffer == RT_NULL)
    {
        LOG_E("malloc memory failed\n");
        return -RT_ERROR;
    }

    rt_memset(lcd.config.gra_info.framebuffer, 0, lcd.config.gra_info.height * lcd.config.gra_info.width * (lcd.config.gra_info.bits_per_pixel / 8));
    rt_lcd_intf_config(lcd.intf, &lcd.config);
    lcd.ops = &otm8009a_ops;

    result = rt_lcd_device_register(&lcd, "lcd", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("register lcd device failed\n");
        return -RT_ERROR;
    }

    return result;
}

#endif /* PKG_USING_OTM8009A */

/******************** end of file ******************************/
