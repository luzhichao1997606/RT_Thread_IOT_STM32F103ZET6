/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

static rt_thread_t led0_task = RT_NULL;
static rt_thread_t led1_task = RT_NULL;
/* defined the LED0 pin: PF7 */
#define LED0_PIN    GET_PIN(B, 5)
#define LED1_PIN    GET_PIN(E, 5)

/**
 * @name: board_Init
 * @brief: 初始化
 * @author: lzc
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
void board_Init(void)
{
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
}

/**
 * @name: led0_thread_entry
 * @brief: LED0的线程函数
 * @author: lzc
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
static void led0_thread_entry(void *paremeter)
{
    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(1500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(1500);
    }
}

/**
 * @name: led1_thread_entry
 * @brief: LED1的线程函数
 * @author: lzc
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
static void led1_thread_entry(void *paremeter)
{
    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(1500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

/**
 * @name: main
 * @brief: 主函数
 * @author: lzc
 * @param {type} None
 * @return {type} None
 * @note: 修改记录：初次创建
 */
int main(void)
{
    board_Init();
    /****************创建动态线程函数************/
    led1_task = rt_thread_create("led1",       /*线程名字*/
                                 led1_thread_entry,/*线程入口函数*/
                                 RT_NULL,/*线程入口函数参数*/
                                 512,    /*线程栈大小*/
                                 3,     /*线程优先级*/
                                 20);   /*线程时间片*/
    led0_task = rt_thread_create("led0",      /*线程名字*/
                                 led0_thread_entry,/*线程入口函数*/
                                 RT_NULL,/*线程入口函数参数*/
                                 512,    /*线程栈大小*/
                                 3,     /*线程优先级*/
                                 20);   /*线程时间片*/
    rt_thread_startup(led1_task);
    rt_thread_startup(led0_task);
}
