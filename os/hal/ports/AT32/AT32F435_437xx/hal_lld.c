/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    STM32F4xx/hal_lld.c
 * @brief   STM32F4xx/STM32F2xx HAL subsystem low level driver source.
 *
 * @addtogroup HAL
 * @{
 */

#include "hal.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   CMSIS system core clock variable.
 * @note    It is declared in system_stm32f4xx.h.
 */
//uint32_t SystemCoreClock = 8000000;//STM32_HCLK;

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/


/**
  * @brief  usb 48M clock select
  * @param  clk_s:USB_CLK_HICK, USB_CLK_HEXT
  * @retval none
  */
static void usb_clock48m_select(usb_clk48_s clk_s)
{
  if(clk_s == USB_CLK_HICK)
  {
    crm_usb_clock_source_select(CRM_USB_CLOCK_SOURCE_HICK);

    /* enable the acc calibration ready interrupt */
    crm_periph_clock_enable(CRM_ACC_PERIPH_CLOCK, TRUE);

    /* update the c1\c2\c3 value */
    acc_write_c1(7980);
    acc_write_c2(8000);
    acc_write_c3(8020);
//#if (USB_ID == 0)
    acc_sof_select(ACC_SOF_OTG1);
//#else
//    acc_sof_select(ACC_SOF_OTG2);
//#endif
    /* open acc calibration */
    acc_calibration_mode_enable(ACC_CAL_HICKTRIM, TRUE);
  }
  else
  {
    switch(system_core_clock)
    {
      /* 48MHz */
      case 48000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1);
        break;

      /* 72MHz */
      case 72000000:
        crm_usb_clock_div_set(CRM_USB_DIV_1_5);
        break;

      /* 96MHz */
      case 96000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2);
        break;

      /* 120MHz */
      case 120000000:
        crm_usb_clock_div_set(CRM_USB_DIV_2_5);
        break;

      /* 144MHz */
      case 144000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3);
        break;

      /* 168MHz */
      case 168000000:
        crm_usb_clock_div_set(CRM_USB_DIV_3_5);
        break;

      /* 192MHz */
      case 192000000:
        crm_usb_clock_div_set(CRM_USB_DIV_4);
        break;

      /* 216MHz */
      case 216000000:
        crm_usb_clock_div_set(CRM_USB_DIV_4_5);
        break;

      /* 240MHz */
      case 240000000:
        crm_usb_clock_div_set(CRM_USB_DIV_5);
        break;

      /* 264MHz */
      case 264000000:
        crm_usb_clock_div_set(CRM_USB_DIV_5_5);
        break;

      /* 288MHz */
      case 288000000:
        crm_usb_clock_div_set(CRM_USB_DIV_6);
        break;

      default:
        break;

    }
  }
}
/**
 * @brief   Initializes the backup domain.
 * @note    WARNING! Changing clock source impossible without resetting
 *          of the whole BKP domain.
 */
static void hal_lld_backup_domain_init(void) {
#if 0
  /* Backup domain access enabled and left open.*/
  PWR->CR |= PWR_CR_DBP;

  /* Reset BKP domain if different clock source selected.*/
  if ((RCC->BDCR & STM32_RTCSEL_MASK) != STM32_RTCSEL) {
    /* Backup domain reset.*/
    RCC->BDCR = RCC_BDCR_BDRST;
    RCC->BDCR = 0;
  }

#if STM32_LSE_ENABLED
#if defined(STM32_LSE_BYPASS)
  /* LSE Bypass.*/
  RCC->BDCR |= RCC_BDCR_LSEON | RCC_BDCR_LSEBYP;
#else
  /* No LSE Bypass.*/
  RCC->BDCR |= RCC_BDCR_LSEON;
#endif
  while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0)
    ;                                       /* Waits until LSE is stable.   */
#endif

#if HAL_USE_RTC
  /* If the backup domain hasn't been initialized yet then proceed with
     initialization.*/
  if ((RCC->BDCR & RCC_BDCR_RTCEN) == 0) {
    /* Selects clock source.*/
    RCC->BDCR |= STM32_RTCSEL;

    /* RTC clock enabled.*/
    RCC->BDCR |= RCC_BDCR_RTCEN;
  }
#endif /* HAL_USE_RTC */

#if STM32_BKPRAM_ENABLE
  rccEnableBKPSRAM(true);

  PWR->CSR |= PWR_CSR_BRE;
  while ((PWR->CSR & PWR_CSR_BRR) == 0)
    ;                                /* Waits until the regulator is stable */
#else
  PWR->CSR &= ~PWR_CSR_BRE;
#endif /* STM32_BKPRAM_ENABLE */
#endif
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level HAL driver initialization.
 *
 * @notapi
 */
void hal_lld_init(void) {

  /* Reset of all peripherals. AHB3 is not reseted because it could have
     been initialized in the board initialization file (board.c).
     Note, GPIOs are not reset because initialized before this point in
     board files.*/
#if 0
  rccResetAHB1(~STM32_GPIO_EN_MASK);

  rccResetPeriph();
#if !defined(STM32F410xx)
  rccResetAHB2(~0);
#endif
  rccResetAPB1(~RCC_APB1RSTR_PWRRST);
  rccResetAPB2(~0);
#endif
  /* PWR clock enabled.*/
  rccEnablePWRInterface(true);

  /* Initializes the backup domain.*/
  hal_lld_backup_domain_init();

  /* DMA subsystems initialization.*/
#if defined(STM32_DMA_REQUIRED)
  dmaInit();
#endif

  /* IRQ subsystem initialization.*/
  irqInit();

  /* Programmable voltage detector enable.*/
#if STM32_PVD_ENABLE
  PWR->CR |= PWR_CR_PVDE | (STM32_PLS & STM32_PLS_MASK);
#endif /* STM32_PVD_ENABLE */
}

/**
 * @brief   STM32F2xx clocks and PLL initialization.
 * @note    All the involved constants come from the file @p board.h.
 * @note    This function should be invoked just after the system reset.
 *
 * @special
 */
void stm32_clock_init(void) {


#if !STM32_NO_INIT
  /* PWR clock enable.*/
#if defined(HAL_USE_RTC) && defined(RCC_APB1ENR_RTCAPBEN)
//  RCC->APB1ENR = RCC_APB1ENR_PWREN | RCC_APB1ENR_RTCAPBEN;
  rccEnablePWRInterface(0);
#else
//  RCC->APB1ENR = RCC_APB1ENR_PWREN;
//  rccEnablePeriph();
  rccEnablePWRInterface(0);
#endif

  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

   /* wait till hext is ready */
   while(crm_hext_stable_wait() == ERROR)
   {
   }

    /* config pll clock resource
    common frequency config list: pll source selected  hick or hext(8mhz)
    _______________________________________________________________________________________
    |        |         |         |         |         |         |         |        |        |
    |pll(mhz)|   288   |   252   |   216   |   180   |   144   |   108   |   72   |   36   |
    |________|_________|_________|_________|_________|_________|_________|_________________|
    |        |         |         |         |         |         |         |        |        |
    |pll_ns  |   72    |   63    |   108   |   90    |   72    |   108   |   72   |   72   |
    |        |         |         |         |         |         |         |        |        |
    |pll_ms  |   1     |   1     |   1     |   1     |   1     |   1     |   1    |   1    |
    |        |         |         |         |         |         |         |        |        |
    |pll_fr  |   FR_2  |   FR_2  |   FR_4  |   FR_4  |   FR_4  |   FR_8  |   FR_8 |   FR_16|
    |________|_________|_________|_________|_________|_________|_________|________|________|

    if pll clock source selects hext with other frequency values, or configure pll to other
    frequency values, please use the at32 new clock  configuration tool for configuration.  */
    crm_pll_config(CRM_PLL_SOURCE_HEXT, 72, 1, CRM_PLL_FR_2);
//    crm_pll_config(CRM_PLL_SOURCE_HEXT, 80, 1, CRM_PLL_FR_16);

    /* enable pll */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

    /* wait till pll is ready */
    while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
    {
    }

    /* config ahbclk */
    crm_ahb_div_set(CRM_AHB_DIV_1);

    /* config apb2clk */
    crm_apb2_div_set(CRM_APB2_DIV_2);

    /* config apb1clk */
    crm_apb1_div_set(CRM_APB1_DIV_2);

    /* enable auto step mode */
    crm_auto_step_mode_enable(TRUE);

    /* select pll as system clock source */
    crm_sysclk_switch(CRM_SCLK_PLL);

    /* wait till pll is used as system clock source */
    while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
    {
    }

    /* disable auto step mode */
    crm_auto_step_mode_enable(FALSE);

    /* update system_core_clock global variable */
    system_core_clock_update();

    /*set usb 48 clock */
    usb_clock48m_select(USB_CLK_HEXT);
#endif
}

/** @} */
