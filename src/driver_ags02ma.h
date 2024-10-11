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
 * @file      driver_ags02ma.h
 * @brief     driver ags02ma header file
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

#ifndef DRIVER_AGS02MA_H
#define DRIVER_AGS02MA_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ags02ma_driver ags02ma driver function
 * @brief    ags02ma driver modules
 * @{
 */

/**
 * @addtogroup ags02ma_base_driver
 * @{
 */

/**
 * @brief ags02ma handle structure definition
 */
typedef struct ags02ma_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                  /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                 /**< point to an iic_write_cmd function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t iic_addr;                                                                   /**< iic address */
} ags02ma_handle_t;

/**
 * @brief ags02ma information structure definition
 */
typedef struct ags02ma_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ags02ma_info_t;

/**
 * @}
 */

/**
 * @defgroup ags02ma_link_driver ags02ma link driver function
 * @brief    ags02ma link driver modules
 * @ingroup  ags02ma_driver
 * @{
 */

/**
 * @brief     initialize ags02ma_handle_t structure
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] STRUCTURE is ags02ma_handle_t
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_IIC_INIT(HANDLE, FUC)                (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_IIC_DEINIT(HANDLE, FUC)              (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_IIC_READ_COMMAND(HANDLE, FUC)        (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)       (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_IIC_WRITE(HANDLE, FUC)               (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_DELAY_MS(HANDLE, FUC)                (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an ags02ma handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_AGS02MA_LINK_DEBUG_PRINT(HANDLE, FUC)             (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ags02ma_base_driver ags02ma base driver function
 * @brief    ags02ma base driver modules
 * @ingroup  ags02ma_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an ags02ma info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ags02ma_info(ags02ma_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an ags02ma handle structure
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t ags02ma_init(ags02ma_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an ags02ma handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ags02ma_deinit(ags02ma_handle_t *handle);

/**
 * @brief      read tvoc
 * @param[in]  *handle points to an ags02ma handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *ppb points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read tvoc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 *             - 5 chip is busy
 * @note       none
 */
uint8_t ags02ma_read_tvoc(ags02ma_handle_t *handle, uint32_t *raw, uint32_t *ppb);

/**
 * @brief     zero point calibration
 * @param[in] *handle points to an ags02ma handle structure
 * @return    status code
 *            - 0 success
 *            - 1 zero point calibration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ags02ma_zero_point_calibration(ags02ma_handle_t *handle);

/**
 * @brief      get resistance
 * @param[in]  *handle points to an ags02ma handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *ohm points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resistance failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 * @note       none
 */
uint8_t ags02ma_get_resistance(ags02ma_handle_t *handle, uint32_t *raw, double *ohm);

/**
 * @brief      get version
 * @param[in]  *handle points to an ags02ma handle structure
 * @param[out] *version points to a version buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resistance failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc is error
 * @note       none
 */
uint8_t ags02ma_get_version(ags02ma_handle_t *handle, uint8_t *version);

/**
 * @brief     modify slave address
 * @param[in] *handle points to an ags02ma handle structure
 * @param[in] addr_7bit is the new slave address
 * @return    status code
 *            - 0 success
 *            - 1 modify slave address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ags02ma_modify_slave_address(ags02ma_handle_t *handle, uint8_t addr_7bit);

/**
 * @brief     set slave address
 * @param[in] *handle points to an ags02ma handle structure
 * @param[in] addr is the slave address
 * @return    status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t ags02ma_set_slave_address(ags02ma_handle_t *handle, uint8_t addr);

/**
 * @brief      get slave address
 * @param[in]  *handle points to an ags02ma handle structure
 * @param[out] *addr points to a slave address buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ags02ma_get_slave_address(ags02ma_handle_t *handle, uint8_t *addr);

/**
 * @}
 */

/**
 * @defgroup ags02ma_extend_driver ags02ma extend driver function
 * @brief    ags02ma extend driver modules
 * @ingroup  ags02ma_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an ags02ma handle structure
 * @param[in] reg is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ags02ma_set_reg(ags02ma_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an ags02ma handle structure
 * @param[in]  reg is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ags02ma_get_reg(ags02ma_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
