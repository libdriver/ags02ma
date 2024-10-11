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
 * @file      driver_ags02ma.c
 * @brief     driver ags02ma source file
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

#include "driver_ags02ma.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "ASAIR AGS02MA"      /**< chip name */
#define MANUFACTURER_NAME         "ASAIR"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.3f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                 /**< chip max supply voltage */
#define MAX_CURRENT               33.0f                /**< chip max current */
#define TEMPERATURE_MIN           0.0f                 /**< chip min operating temperature */
#define TEMPERATURE_MAX           50.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief chip address definition
 */
#define AGS02MA_ADDRESS             (0x1A << 1)          /**< iic device address */

/**
 * @brief chip register definition
 */
#define AGS02MA_REG_DATA                0x00        /**< data register */
#define AGS02MA_REG_CALIBRATION         0x01        /**< calibration register */
#define AGS02MA_REG_VERSION             0x11        /**< version register */
#define AGS02MA_REG_RESISTANCE          0x20        /**< resistance register */
#define AGS02MA_REG_SLAVE_ADDR          0x21        /**< slave address register */

/**
 * @brief      read bytes
 * @param[in]  *handle points to an ags02ma handle structure
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @param[in]  len is the data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ags02ma_iic_read(ags02ma_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write_cmd(handle->iic_addr, &reg, 1) != 0)         /* write the register */
    {
        return 1;                                                      /* return error */
    }
    handle->delay_ms(30);                                              /* delay 30ms */
    if (handle->iic_read_cmd(handle->iic_addr, data, len) != 0)        /* read the register */
    {
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an ags02ma handle structure
 * @param[in] reg is the register address
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ags02ma_iic_write(ags02ma_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(handle->iic_addr, reg, data, len) != 0)        /* write the register */
    {
        return 1;                                                        /* return error */
    }

    return 0;                                                            /* success return 0 */
}

/**
 * @brief     calculate the crc
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    crc
 * @note      none
 */
static uint8_t a_ags02ma_calc_crc(uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint8_t byte;
    uint8_t crc = 0xFF;

    for (byte = 0; byte < len; byte++)          /* len times */
    {
        crc ^= data[byte];                      /* xor byte */
        for (i = 0; i < 8; i++)                 /* one byte */
        {
            if ((crc & 0x80) != 0)              /* if high*/
            {
                crc = (crc << 1) ^ 0x31;        /* xor 0x31 */
            }
            else
            {
                crc = crc << 1;                 /* skip */
            }
        }
    }

    return crc;                                 /* return crc */
}

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
uint8_t ags02ma_init(ags02ma_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->iic_init == NULL)                                      /* check iic_init */
    {
        handle->debug_print("ags02ma: iic_init is null.\n");           /* iic_init is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_deinit == NULL)                                    /* check iic_deinit */
    {
        handle->debug_print("ags02ma: iic_deinit is null.\n");         /* iic_deinit is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                  /* check iic_read_cmd */
    {
        handle->debug_print("ags02ma: iic_read_cmd is null.\n");       /* iic_read_cmd is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                 /* check iic_write_cmd */
    {
        handle->debug_print("ags02ma: iic_write_cmd is null.\n");      /* iic_write_cmd is null */

        return 3;                                                      /* return error */
    }
    if (handle->iic_write == NULL)                                     /* check iic_write */
    {
        handle->debug_print("ags02ma: iic_write is null.\n");          /* iic_write is null */

        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("ags02ma: delay_ms is null.\n");           /* delay_ms is null */

        return 3;                                                      /* return error */
    }

    if (handle->iic_init() != 0)                                       /* iic init */
    {
        handle->debug_print("ags02ma: iic init failed.\n");            /* iic init failed */

        return 1;                                                      /* return error */
    }
    handle->iic_addr = AGS02MA_ADDRESS;                                /* set default slave address */
    handle->inited = 1;                                                /* flag finish initialization */

    return 0;                                                          /* success return 0 */
}

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
uint8_t ags02ma_deinit(ags02ma_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }

    if (handle->iic_deinit() != 0)                                 /* iic deinit */
    {
        handle->debug_print("ags02ma: iic deinit failed.\n");      /* iic deinit failed */

        return 1;                                                  /* return error */
    }
    handle->inited = 0;                                            /* set closed flag */

    return 0;                                                      /* success return 0 */
}

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
uint8_t ags02ma_set_slave_address(ags02ma_handle_t *handle, uint8_t addr)
{
    if (handle == NULL)                      /* check handle */
    {
        return 2;                            /* return error */
    }
    if (handle->inited != 1)                 /* check handle initialization */
    {
        return 3;                            /* return error */
    }

    handle->iic_addr = (uint8_t)addr;        /* set address */

    return 0;                                /* success return 0 */
}

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
uint8_t ags02ma_get_slave_address(ags02ma_handle_t *handle, uint8_t *addr)
{
    if (handle == NULL)               /* check handle */
    {
        return 2;                     /* return error */
    }
    if (handle->inited != 1)          /* check handle initialization */
    {
        return 3;                     /* return error */
    }

    *addr = handle->iic_addr ;        /* get address */

    return 0;                         /* success return 0 */
}

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
uint8_t ags02ma_read_tvoc(ags02ma_handle_t *handle, uint32_t *raw, uint32_t *ppb)
{
    uint8_t res;
    uint8_t buf[5];

    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }

    res = a_ags02ma_iic_read(handle, AGS02MA_REG_DATA, buf, 5);       /* read tvoc */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ags02ma: read tvoc failed.\n");          /* read tvoc failed */

        return 1;                                                     /* return error */
    }
    if (a_ags02ma_calc_crc(buf, 4) != buf[4])                         /* check the crc */
    {
        handle->debug_print("ags02ma: crc is error.\n");              /* crc is error */

        return 4;                                                     /* return error */
    }
    if ((buf[0] & 0x01) != 0)                                         /* check status */
    {
        handle->debug_print("ags02ma: chip is busy.\n");              /* chip is busy */

        return 5;                                                     /* return error */
    }
    *raw = (uint32_t)(buf[1]) << 16 |
           (uint32_t)(buf[2]) << 8 |
           (uint32_t)(buf[3]) << 0;                                   /* set raw data */
    *ppb = *raw;                                                      /* copy to ppb */

    return 0;                                                         /* success return 0 */
}

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
uint8_t ags02ma_zero_point_calibration(ags02ma_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[5];

    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }

    buf[0] = 0x00;                                                         /* set 0x00 */
    buf[1] = 0x0C;                                                         /* set 0x0C */
    buf[2] = 0xFF;                                                         /* set 0xFF */
    buf[3] = 0xF3;                                                         /* set 0xF3 */
    buf[4] = a_ags02ma_calc_crc(buf, 4);                                   /* get crc */
    res = a_ags02ma_iic_write(handle, AGS02MA_REG_CALIBRATION, buf, 5);    /* write calibration */
    if (res != 0)                                                          /* check the result */
    {
        handle->debug_print("ags02ma: write calibration failed.\n");       /* write calibration failed */

        return 1;                                                          /* return error */
    }
    handle->delay_ms(30);                                                  /* delay 30ms */

    return 0;                                                              /* success return 0 */
}

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
uint8_t ags02ma_get_resistance(ags02ma_handle_t *handle, uint32_t *raw, double *ohm)
{
    uint8_t res;
    uint8_t buf[5];

    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }

    res = a_ags02ma_iic_read(handle, AGS02MA_REG_RESISTANCE, buf, 5);    /* read resistance */
    if (res != 0)                                                        /* check the result */
    {
        handle->debug_print("ags02ma: read resistance failed.\n");       /* read resistance failed */

        return 1;                                                        /* return error */
    }
    if (a_ags02ma_calc_crc(buf, 4) != buf[4])                            /* check the crc */
    {
        handle->debug_print("ags02ma: crc is error.\n");                 /* crc is error */

        return 4;                                                        /* return error */
    }
    *raw = (uint32_t)(buf[0]) << 24 |
           (uint32_t)(buf[1]) << 16 |
           (uint32_t)(buf[2]) << 8 |
           (uint32_t)(buf[3]) << 0;                                      /* set raw data */
    *ohm = (double)(*raw) * 100.0;                                       /* convert to ohm */

    return 0;                                                            /* success return 0 */
}

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
uint8_t ags02ma_get_version(ags02ma_handle_t *handle, uint8_t *version)
{
    uint8_t res;
    uint8_t buf[5];

    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }

    res = a_ags02ma_iic_read(handle, AGS02MA_REG_VERSION, buf, 5);    /* read version */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ags02ma: read version failed.\n");       /* read version failed */

        return 1;                                                     /* return error */
    }
    if (a_ags02ma_calc_crc(buf, 4) != buf[4])                         /* check the crc */
    {
        handle->debug_print("ags02ma: crc is error.\n");              /* crc is error */

        return 4;                                                     /* return error */
    }
    *version = buf[3];                                                /* set version */
    handle->delay_ms(30);                                             /* delay 30ms */

    return 0;                                                         /* success return 0 */
}

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
uint8_t ags02ma_modify_slave_address(ags02ma_handle_t *handle, uint8_t addr_7bit)
{
    uint8_t res;
    uint8_t buf[5];

    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }

    buf[0] = addr_7bit;                                                      /* new addr */
    buf[1] = ~addr_7bit;                                                     /* rev new addr */
    buf[2] = addr_7bit;                                                      /* new addr */
    buf[3] = ~addr_7bit;                                                     /* rev new addr  */
    buf[4] = a_ags02ma_calc_crc(buf, 4);                                     /* get crc */
    res = a_ags02ma_iic_write(handle, AGS02MA_REG_SLAVE_ADDR, buf, 5);       /* modify slave address */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("ags02ma: modify slave address failed.\n");      /* modify slave address failed */

        return 1;                                                            /* return error */
    }
    handle->iic_addr = addr_7bit << 1;                                       /* set new address */
    handle->delay_ms(30);                                                    /* delay 30ms */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t ags02ma_set_reg(ags02ma_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }
    if (handle->inited != 1)                               /* check handle initialization */
    {
        return 3;                                          /* return error */
    }

    if (a_ags02ma_iic_write(handle, reg, buf, len) != 0)   /* write data */
    {
        return 1;                                          /* return error */
    }

    return 0;                                              /* success return 0 */
}

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
uint8_t ags02ma_get_reg(ags02ma_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }

    if (a_ags02ma_iic_read(handle, reg, buf, len) != 0)   /* read data */
    {
        return 1;                                         /* return error */
    }

    return 0;                                             /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an ags02ma info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ags02ma_info(ags02ma_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }

    memset(info, 0, sizeof(ags02ma_info_t));                        /* initialize ags02ma info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */

    return 0;                                                       /* success return 0 */
}
