/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* https://www.renesas.com/disclaimer
*
* Copyright (C) 2023 Renesas Electronics Corporation.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : qe_touch_config.c
* Description  : This file includes module implementations.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : MM/DD/YYYY Version Description
*              : 06/23/2020 1.00    First Release
*              : 07/15/2021 1.10    Adding Diagnosis Supporting
*              : 11/13/2021 1.20    Adding information for Initial Offset Tuning
*              : 03/16/2022 1.30    Adding Multiple Electrode Connection Supporting
*              : 03/31/2023 1.31    Improving Traceability
*              : 04/18/2023 1.40    Adding 3 Frequency Judgement Supporting
***********************************************************************************************************************/
/***********************************************************************************************************************
* Touch I/F Configuration File  : RL78_G16_CapTouch.tifcfg
* Tuning Log File               : RL78_G16_CapTouch_log_tuning20240918164020.log
***********************************************************************************************************************/

#include "qe_touch_config.h"

volatile uint8_t      g_qe_touch_flag;
volatile ctsu_event_t g_qe_ctsu_event;

void qe_touch_callback(touch_callback_args_t * p_args)
{
    g_qe_touch_flag = 1;
    g_qe_ctsu_event = p_args -> event;
}





/***********************************************************************************************************************
CTSU Related Information for [CONFIG01] configuration.
***********************************************************************************************************************/

const ctsu_element_cfg_t g_qe_ctsu_element_cfg_config01[] =
{
    { .ssdiv = CTSU_SSDIV_1000, .so = 0x117, .snum = 0x01, .sdpa = 0x07 },
    { .ssdiv = CTSU_SSDIV_1000, .so = 0x10C, .snum = 0x01, .sdpa = 0x07 },
    { .ssdiv = CTSU_SSDIV_1000, .so = 0x110, .snum = 0x01, .sdpa = 0x07 },
    { .ssdiv = CTSU_SSDIV_1000, .so = 0x0F9, .snum = 0x01, .sdpa = 0x07 },
    { .ssdiv = CTSU_SSDIV_1000, .so = 0x0E2, .snum = 0x01, .sdpa = 0x07 },
    { .ssdiv = CTSU_SSDIV_1000, .so = 0x0F5, .snum = 0x01, .sdpa = 0x07 },
};

const ctsu_cfg_t g_qe_ctsu_cfg_config01 =
{
    .cap = CTSU_CAP_SOFTWARE,

    .txvsel = CTSU_TXVSEL_VCC,

    .atune1 = CTSU_ATUNE1_NORMAL,

    .md     = CTSU_MODE_SELF_MULTI_SCAN,



    .ctsuchac0  = 0x06, /* ch0-ch7 enable mask */
    .ctsuchac1  = 0x6C, /* ch8-ch15 enable mask */
    .ctsuchac2  = 0x00, /* ch16-ch23 enable mask */
    .ctsuchac3  = 0x00, /* ch24-ch31 enable mask */
    .ctsuchac4  = 0x00, /* ch32-ch39 enable mask */
    .ctsuchtrc0 = 0x00, /* ch0-ch7 mutual tx mask */
    .ctsuchtrc1 = 0x00, /* ch8-ch15 mutual tx mask */
    .ctsuchtrc2 = 0x00, /* ch16-ch23 mutual tx mask */
    .ctsuchtrc3 = 0x00, /* ch24-ch31 mutual tx mask */
    .ctsuchtrc4 = 0x00, /* ch32-ch39 mutual tx mask */
    .num_rx     = 6,
    .num_tx     = 0,
    .p_elements = g_qe_ctsu_element_cfg_config01,

#if (CTSU_TARGET_VALUE_CONFIG_SUPPORT == 1)
    .tuning_self_target_value   = 15360,
    .tuning_mutual_target_value = 10240,
#endif

    .num_moving_average = 4,
    .tunning_enable     = true,
    .p_callback    = &qe_touch_callback,
};

ctsu_instance_ctrl_t g_qe_ctsu_ctrl_config01;

const ctsu_instance_t g_qe_ctsu_instance_config01 =
{
    .p_ctrl = &g_qe_ctsu_ctrl_config01,
    .p_cfg  = &g_qe_ctsu_cfg_config01,
    .p_api  = &g_ctsu_on_ctsu,
};

/***********************************************************************************************************************
Touch Related Information for [CONFIG01] configuration.
***********************************************************************************************************************/

#define QE_TOUCH_CONFIG01_NUM_BUTTONS (6)
#define QE_TOUCH_CONFIG01_NUM_SLIDERS (0)
#define QE_TOUCH_CONFIG01_NUM_WHEELS  (0)

/* Button configurations */
#if (QE_TOUCH_CONFIG01_NUM_BUTTONS != 0)
const touch_button_cfg_t g_qe_touch_button_cfg_config01[] =
{


    /* button00 */
    {
        .elem_index = 0,
        .threshold  = 12336,
        .hysteresis = 616,
    },
    /* button01 */
    {
        .elem_index = 1,
        .threshold  = 7914,
        .hysteresis = 395,
    },
    /* button02 */
    {
        .elem_index = 2,
        .threshold  = 8090,
        .hysteresis = 404,
    },
    /* button03 */
    {
        .elem_index = 3,
        .threshold  = 1641,
        .hysteresis = 82,
    },
    /* button04 */
    {
        .elem_index = 4,
        .threshold  = 9439,
        .hysteresis = 471,
    },
    /* button05 */
    {
        .elem_index = 5,
        .threshold  = 8328,
        .hysteresis = 416,
    },

};
#endif

/* Slider configurations */
#if (QE_TOUCH_CONFIG01_NUM_SLIDERS != 0)
const touch_slider_cfg_t g_qe_touch_slider_cfg_config01[] =
{


    NULL

};
#endif

/* Wheel configurations */
#if (QE_TOUCH_CONFIG01_NUM_WHEELS != 0)
const touch_wheel_cfg_t g_qe_touch_wheel_cfg_config01[] =
{


    NULL

};
#endif

/* Touch configurations */
const touch_cfg_t g_qe_touch_cfg_config01 =
{
    .p_buttons   = g_qe_touch_button_cfg_config01,
    .p_sliders   = NULL,
    .p_wheels    = NULL,
    .num_buttons = QE_TOUCH_CONFIG01_NUM_BUTTONS,
    .num_sliders = QE_TOUCH_CONFIG01_NUM_SLIDERS,
    .num_wheels  = QE_TOUCH_CONFIG01_NUM_WHEELS,

    .number        = 0,

    .on_freq     = 3,
    .off_freq    = 3,
    .drift_freq  = 255,
    .cancel_freq = 0,

    .p_ctsu_instance = &g_qe_ctsu_instance_config01,
};

touch_instance_ctrl_t g_qe_touch_ctrl_config01;

const touch_instance_t g_qe_touch_instance_config01 =
{
    .p_ctrl = &g_qe_touch_ctrl_config01,
    .p_cfg  = &g_qe_touch_cfg_config01,
    .p_api  = &g_touch_on_ctsu,
};

