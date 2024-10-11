/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      driver_ags02ma_read_test.c
 * @brief     driver ags02ma read test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-10-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/10/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ags02ma_read_test.h"
#include <stdlib.h>

static ags02ma_handle_t gs_handle;        /**< ags02ma handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t ags02ma_read_test(uint32_t times)
{
    uint8_t res;
    uint8_t version;
    uint8_t addr_7bit;
    double ohm;
    uint32_t i;
    uint32_t raw;
    uint32_t ppb;
    ags02ma_info_t info;

    /* link interface function */
    DRIVER_AGS02MA_LINK_INIT(&gs_handle, ags02ma_handle_t);
    DRIVER_AGS02MA_LINK_IIC_INIT(&gs_handle, ags02ma_interface_iic_init);
    DRIVER_AGS02MA_LINK_IIC_DEINIT(&gs_handle, ags02ma_interface_iic_deinit);
    DRIVER_AGS02MA_LINK_IIC_READ_COMMAND(&gs_handle, ags02ma_interface_iic_read_cmd);
    DRIVER_AGS02MA_LINK_IIC_WRITE_COMMAND(&gs_handle, ags02ma_interface_iic_write_cmd);
    DRIVER_AGS02MA_LINK_IIC_WRITE(&gs_handle, ags02ma_interface_iic_write);
    DRIVER_AGS02MA_LINK_DELAY_MS(&gs_handle, ags02ma_interface_delay_ms);
    DRIVER_AGS02MA_LINK_DEBUG_PRINT(&gs_handle, ags02ma_interface_debug_print);

    /* get ags02ma information */
    res = ags02ma_info(&info);
    if (res != 0)
    {
        ags02ma_interface_debug_print("ags02ma: get info failed.\n");

        return 1;
    }
    else
    {
        /* print ags02ma information */
        ags02ma_interface_debug_print("ags02ma: chip is %s.\n", info.chip_name);
        ags02ma_interface_debug_print("ags02ma: manufacturer is %s.\n", info.manufacturer_name);
        ags02ma_interface_debug_print("ags02ma: interface is %s.\n", info.interface);
        ags02ma_interface_debug_print("ags02ma: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ags02ma_interface_debug_print("ags02ma: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ags02ma_interface_debug_print("ags02ma: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ags02ma_interface_debug_print("ags02ma: max current is %0.2fmA.\n", info.max_current_ma);
        ags02ma_interface_debug_print("ags02ma: max temperature is %0.1fC.\n", info.temperature_max);
        ags02ma_interface_debug_print("ags02ma: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start basic read test */
    ags02ma_interface_debug_print("ags02ma: start read test.\n");

    /* ags02ma init */
    res = ags02ma_init(&gs_handle);
    if (res != 0)
    {
        ags02ma_interface_debug_print("ags02ma: init failed.\n");

        return 1;
    }

    /* get version */
    res = ags02ma_get_version(&gs_handle, &version);
    if (res != 0)
    {
        ags02ma_interface_debug_print("ags02ma: get version failed.\n");
        (void)ags02ma_deinit(&gs_handle);

        return 1;
    }

    /* print result */
    ags02ma_interface_debug_print("ags02ma: version is 0x%02X.\n", version);

    /* delay 2000 ms for read */
    ags02ma_interface_delay_ms(2000);
    for (i = 0; i < times; i++)
    {
        /* read tvoc */
        res = ags02ma_read_tvoc(&gs_handle, (uint32_t *)&raw, (uint32_t *)&ppb);
        if (res != 0)
        {
            ags02ma_interface_debug_print("ags02ma: read tvoc failed.\n");
            (void)ags02ma_deinit(&gs_handle);

            return 1;
        }

        /* print result */
        ags02ma_interface_debug_print("ags02ma: tvoc is %dppb.\n", ppb);

        /* delay 2000 ms*/
        ags02ma_interface_delay_ms(2000);
    }

    /* get resistance */
    res = ags02ma_get_resistance(&gs_handle, &raw, &ohm);
    if (res != 0)
    {
        ags02ma_interface_debug_print("ags02ma: get resistance failed.\n");
        (void)ags02ma_deinit(&gs_handle);

        return 1;
    }

    /* print result */
    ags02ma_interface_debug_print("ags02ma: resistance is %0.2fohm.\n", ohm);

    /* delay 2000 ms*/
    ags02ma_interface_delay_ms(2000);

    addr_7bit = 0x1A;
    res = ags02ma_modify_slave_address(&gs_handle, addr_7bit);
    if (res != 0)
    {
        ags02ma_interface_debug_print("ags02ma: modify slave address failed.\n");
        (void)ags02ma_deinit(&gs_handle);

        return 1;
    }

    /* print result */
    ags02ma_interface_debug_print("ags02ma: modify slave address 0x%02X.\n", addr_7bit);

    /* finish read test */
    ags02ma_interface_debug_print("ags02ma: finish read test.\n");
    (void)ags02ma_deinit(&gs_handle);

    return 0;
}
