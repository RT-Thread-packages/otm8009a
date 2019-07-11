/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define LCD_BUF_SIZE        (480 * 800 * 32 / 8)
#define LCD_NAME             "lcd"

int otm8009a_sample(void)
{
    struct rt_lcd_device *lcd;
    lcd = (struct rt_lcd_device *)rt_device_find(LCD_NAME);
    if (lcd == RT_NULL)
    {
        rt_kprintf("find a lcd device failed \n");
        return -RT_ERROR;
    }

    rt_kprintf("%d %d\r\n", lcd->gra_info.width, lcd->gra_info.height);

    for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
    {
        lcd->gra_info.framebuffer[2 * i] = 0x00;
        lcd->gra_info.framebuffer[2 * i + 1] = 0xff;
        lcd->gra_info.framebuffer[2 * i + 2] = 0x00;

    }
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    rt_thread_mdelay(1000);

    for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
    {
        lcd->gra_info.framebuffer[2 * i] = 0x00;
        lcd->gra_info.framebuffer[2 * i + 1] = 0x00;
        lcd->gra_info.framebuffer[2 * i + 2] = 0x00;

    }
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    rt_thread_mdelay(1000);

    for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
    {
        lcd->gra_info.framebuffer[2 * i] = 0xff;
        lcd->gra_info.framebuffer[2 * i + 1] = 0xff;
        lcd->gra_info.framebuffer[2 * i + 2] = 0xff;

    }
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    rt_thread_mdelay(1000);

    return RT_EOK;

}
MSH_CMD_EXPORT(otm8009a_sample, otm8009a sample);

/******************** end of file ***********************/

