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
 * @file    STM32F4xx/stm32_rcc.h
 * @brief   RCC helper driver header.
 * @note    This file requires definitions from the ST header file
 *          @p stm32f4xx.h.
 *
 * @addtogroup STM32F4xx_RCC
 * @{
 */
#ifndef STM32_RCC_H
#define STM32_RCC_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Generic RCC operations
 * @{
 */

/**
 * @brief   Enables the clock of one or more peripheral on the APB1 bus.
 *
 * @param[in] mask      APB1 peripherals mask
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnablePeriph(mask, lp) {                                           \
  crm_periph_clock_enable(mask, TRUE);                                       \
}

/**
 * @brief   Disables the clock of one or more peripheral on the APB1 bus.
 *
 * @param[in] mask      APB1 peripherals mask
 *
 * @api
 */
#define rccDisablePeriph(mask) {											      \
	crm_periph_clock_enable(mask, FALSE);                                     \
}
//#define rccDisableAPB1(mask) {
//  RCC->APB1ENR &= ~(mask);
//  RCC->APB1LPENR &= ~(mask);
//  (void)RCC->APB1LPENR;
//}

/**
 * @brief   Resets one or more peripheral on the APB1 bus.
 *
 * @param[in] mask      APB1 peripherals mask
 *
 * @api
 */
#define rccResetPeriph(mask){													  \
	crm_periph_reset(mask, TRUE);											  \
	crm_periph_reset(mask, FALSE);											  \
}


/**
 * @brief   Enables the clock of one or more peripheral on the APB1 bus.
 *
 * @param[in] mask      APB1 peripherals mask
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableAPB1(mask, lp) {                                           \
  crm_periph_clock_enable(mask, TRUE);                                       \
}

/**
 * @brief   Disables the clock of one or more peripheral on the APB1 bus.
 *
 * @param[in] mask      APB1 peripherals mask
 *
 * @api
 */
#define rccDisableAPB1(mask) {											      \
	crm_periph_clock_enable(mask, FALSE);                                     \
}
//#define rccDisableAPB1(mask) {
//  RCC->APB1ENR &= ~(mask);
//  RCC->APB1LPENR &= ~(mask);
//  (void)RCC->APB1LPENR;
//}

/**
 * @brief   Resets one or more peripheral on the APB1 bus.
 *
 * @param[in] mask      APB1 peripherals mask
 *
 * @api
 */
#define rccResetAPB1(mask){													  \
	crm_periph_reset(mask, TRUE);											  \
	crm_periph_reset(mask, FALSE);											  \
}
//#define rccResetAPB1(mask) {
//  RCC->APB1RSTR |= (mask);
//  RCC->APB1RSTR &= ~(mask);
//  (void)RCC->APB1RSTR;
//
//}

/**
 * @brief   Enables the clock of one or more peripheral on the APB2 bus.
 *
 * @param[in] mask      APB2 peripherals mask
 *
 * @api
 */
#define rccEnableAPB2(mask, lp){                                           \
	 crm_periph_clock_enable(mask, TRUE);                                  \
}
//#define rccEnableAPB2(mask, lp) {
//  RCC->APB2ENR |= (mask);
//  if (lp)
//    RCC->APB2LPENR |= (mask);
//  else
//    RCC->APB2LPENR &= ~(mask);
//  (void)RCC->APB2LPENR;
//}

/**
 * @brief   Disables the clock of one or more peripheral on the APB2 bus.
 *
 * @param[in] mask      APB2 peripherals mask
 *
 * @api
 */
#define rccDisableAPB2(mask){											      \
	crm_periph_clock_enable(mask, FALSE);                                     \
}
//#define rccDisableAPB2(mask) {
//  RCC->APB2ENR &= ~(mask);
//  RCC->APB2LPENR &= ~(mask);
//  (void)RCC->APB2LPENR;
//}

/**
 * @brief   Resets one or more peripheral on the APB2 bus.
 *
 * @param[in] mask      APB2 peripherals mask
 *
 * @api
 */
#define rccResetAPB2(mask){													  \
	crm_periph_reset(mask, TRUE);											  \
	crm_periph_reset(mask, FALSE);											  \
}
//#define rccResetAPB2(mask) {
//  RCC->APB2RSTR |= (mask);
//  RCC->APB2RSTR &= ~(mask);
//  (void)RCC->APB2RSTR;
//}

/**
 * @brief   Enables the clock of one or more peripheral on the AHB1 bus.
 *
 * @param[in] mask      AHB1 peripherals mask
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableAHB1(mask, lp)
//#define rccEnableAHB1(mask, lp) {
//  RCC->AHB1ENR |= (mask);
//  if (lp)
//    RCC->AHB1LPENR |= (mask);
//  else
//    RCC->AHB1LPENR &= ~(mask);
//  (void)RCC->AHB1LPENR;
//}

/**
 * @brief   Disables the clock of one or more peripheral on the AHB1 bus.
 *
 * @param[in] mask      AHB1 peripherals mask
 *
 * @api
 */
#define rccDisableAHB1(mask)
//#define rccDisableAHB1(mask) {
//  RCC->AHB1ENR &= ~(mask);
//  RCC->AHB1LPENR &= ~(mask);
//  (void)RCC->AHB1LPENR;
//}

/**
 * @brief   Resets one or more peripheral on the AHB1 bus.
 *
 * @param[in] mask      AHB1 peripherals mask
 *
 * @api
 */
#define rccResetAHB1(mask)
//#define rccResetAHB1(mask) {
//  RCC->AHB1RSTR |= (mask);
//  RCC->AHB1RSTR &= ~(mask);
//  (void)RCC->AHB1RSTR;
//}

/**
 * @brief   Enables the clock of one or more peripheral on the AHB2 bus.
 *
 * @param[in] mask      AHB2 peripherals mask
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableAHB2(mask, lp)
//#define rccEnableAHB2(mask, lp) {
//  RCC->AHB2ENR |= (mask);
//  if (lp)
//    RCC->AHB2LPENR |= (mask);
//  else
//    RCC->AHB2LPENR &= ~(mask);
//  (void)RCC->AHB2LPENR;
//}

/**
 * @brief   Disables the clock of one or more peripheral on the AHB2 bus.
 *
 * @param[in] mask      AHB2 peripherals mask
 *
 * @api
 */
#define rccDisableAHB2(mask)
//#define rccDisableAHB2(mask) {
//  RCC->AHB2ENR &= ~(mask);
//  RCC->AHB2LPENR &= ~(mask);
//  (void)RCC->AHB2LPENR;
//}

/**
 * @brief   Resets one or more peripheral on the AHB2 bus.
 *
 * @param[in] mask      AHB2 peripherals mask
 *
 * @api
 */
#define rccResetAHB2(mask)
//#define rccResetAHB2(mask) {
//  RCC->AHB2RSTR |= (mask);
//  RCC->AHB2RSTR &= ~(mask);
//  (void)RCC->AHB2RSTR;
//}

/**
 * @brief   Enables the clock of one or more peripheral on the AHB3 (FSMC) bus.
 *
 * @param[in] mask      AHB3 peripherals mask
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableAHB3(mask, lp)
//#define rccEnableAHB3(mask, lp) {
//  RCC->AHB3ENR |= (mask);
//  if (lp)
//    RCC->AHB3LPENR |= (mask);
//  else
//    RCC->AHB3LPENR &= ~(mask);
//  (void)RCC->AHB3LPENR;
//}

/**
 * @brief   Disables the clock of one or more peripheral on the AHB3 (FSMC) bus.
 *
 * @param[in] mask      AHB3 peripherals mask
 *
 * @api
 */
#define rccDisableAHB3(mask)
//#define rccDisableAHB3(mask) {
//  RCC->AHB3ENR &= ~(mask);
//  RCC->AHB3LPENR &= ~(mask);
//  (void)RCC->AHB3LPENR;
//}

/**
 * @brief   Resets one or more peripheral on the AHB3 (FSMC) bus.
 *
 * @param[in] mask      AHB3 peripherals mask
 *
 * @api
 */
#define rccResetAHB3(mask)
//#define rccResetAHB3(mask) {
//  RCC->AHB3RSTR |= (mask);
//  RCC->AHB3RSTR &= ~(mask);
//  (void)RCC->AHB3RSTR;
//}
/** @} */

/**
 * @name    ADC peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the ADC1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableADC1(lp) rccEnablePeriph(CRM_ADC1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the ADC1 peripheral clock.
 *
 * @api
 */
#define rccDisableADC1() rccDisablePeriph(CRM_ADC1_PERIPH_CLOCK)

/**
 * @brief   Resets the ADC1 peripheral.
 *
 * @api
 */
#define rccResetADC1() rccResetPeriph(CRM_ADC_PERIPH_RESET)

/**
 * @brief   Enables the ADC2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableADC2(lp) rccEnablePeriph(CRM_ADC2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the ADC2 peripheral clock.
 *
 * @api
 */
#define rccDisableADC2() rccDisablePeriph(CRM_ADC2_PERIPH_CLOCK)

/**
 * @brief   Resets the ADC2 peripheral.
 *
 * @api
 */
#define rccResetADC2() rccResetPeriph(CRM_ADC_PERIPH_RESET)

/**
 * @brief   Enables the ADC3 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableADC3(lp) rccEnablePeriph(CRM_ADC3_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the ADC3 peripheral clock.
 *
 * @api
 */
#define rccDisableADC3() rccDisablePeriph(CRM_ADC3_PERIPH_CLOCK)

/**
 * @brief   Resets the ADC3 peripheral.
 *
 * @api
 */
#define rccResetADC3() rccResetPeriph(CRM_ADC_PERIPH_RESET)
/** @} */

/**
 * @name    DAC peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the DAC1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableDAC1(lp) rccEnablePeriph(CRM_DAC_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the DAC1 peripheral clock.
 *
 * @api
 */
#define rccDisableDAC1() rccDisablePeriph(CRM_DAC_PERIPH_CLOCK)

/**
 * @brief   Resets the DAC1 peripheral.
 *
 * @api
 */
#define rccResetDAC1() rccResetPeriph(CRM_DAC_PERIPH_RESET)
/** @} */

/**
 * @name    DMA peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the DMA1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableDMA1(lp) rccEnablePeriph(CRM_DMA1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the DMA1 peripheral clock.
 *
 * @api
 */
#define rccDisableDMA1() rccDisablePeriph(CRM_DMA1_PERIPH_CLOCK)

/**
 * @brief   Resets the DMA1 peripheral.
 *
 * @api
 */
#define rccResetDMA1() rccResetPeriph(CRM_DMA1_PERIPH_RESET)

/**
 * @brief   Enables the DMA2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableDMA2(lp) rccEnablePeriph(CRM_DMA2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the DMA2 peripheral clock.
 *
 * @api
 */
#define rccDisableDMA2() rccDisablePeriph(CRM_DMA2_PERIPH_CLOCK)

/**
 * @brief   Resets the DMA2 peripheral.
 *
 * @api
 */
#define rccResetDMA2() rccResetPeriph(CRM_DMA2_PERIPH_RESET)
/** @} */

/**
 * @name    BKPSRAM specific RCC operations
 * @{
 */
/**
 * @brief   Enables the BKPSRAM peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#ifdef RCC_AHB1ENR_BKPSRAMEN
#define rccEnableBKPSRAM(lp) //rccEnableAHB1(RCC_AHB1ENR_BKPSRAMEN, lp)
#else
#define rccEnableBKPSRAM(lp)
#endif

/**
 * @brief   Disables the BKPSRAM peripheral clock.
 *
 * @api
 */
#ifdef RCC_AHB1ENR_BKPSRAMEN
#define rccDisableBKPSRAM() //rccDisableAHB1(RCC_AHB1ENR_BKPSRAMEN)
#else
#define rccDisableBKPSRAM()
#endif
/** @} */

/**
 * @name    PWR interface specific RCC operations
 * @{
 */
/**
 * @brief   Enables the PWR interface clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnablePWRInterface(lp) rccEnablePeriph(CRM_PWC_PERIPH_CLOCK, lp)

/**
 * @brief   Disables PWR interface clock.
 *
 * @api
 */
#define rccDisablePWRInterface() rccDisablePeriph(CRM_PWC_PERIPH_CLOCK)

/**
 * @brief   Resets the PWR interface.
 *
 * @api
 */
#define rccResetPWRInterface() rccResetPeriph(CRM_PWC_PERIPH_RESET)
/** @} */

/**
 * @name    CAN peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the CAN1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableCAN1(lp) rccEnablePeriph(CRM_CAN1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the CAN1 peripheral clock.
 *
 * @api
 */
#define rccDisableCAN1() rccDisablePeriph(CRM_CAN1_PERIPH_CLOCK)

/**
 * @brief   Resets the CAN1 peripheral.
 *
 * @api
 */
#define rccResetCAN1() rccResetPeriph(CRM_CAN1_PERIPH_RESET)

/**
 * @brief   Enables the CAN2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableCAN2(lp) rccEnablePeriph(CRM_CAN2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the CAN2 peripheral clock.
 *
 * @api
 */
#define rccDisableCAN2() rccDisablePeriph(CRM_CAN2_PERIPH_CLOCK)

/**
 * @brief   Resets the CAN2 peripheral.
 *
 * @api
 */
#define rccResetCAN2() rccResetPeriph(CRM_CAN2_PERIPH_RESET)
/** @} */

/**
 * @name    ETH peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the ETH peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableETH(lp){						\
	rccEnablePeriph(CRM_EMAC_PERIPH_CLOCK, lp);  \
	rccEnablePeriph(CRM_EMACTX_PERIPH_CLOCK, lp); \
	rccEnablePeriph(CRM_EMACRX_PERIPH_CLOCK, lp); \
}
/**
 * @brief   Disables the ETH peripheral clock.
 *
 * @api
 */
#define rccDisableETH(){                         \
	rccDisablePeriph(CRM_EMAC_PERIPH_CLOCK);     \
	rccDisablePeriph(CRM_EMACTX_PERIPH_CLOCK);     \
	rccDisablePeriph(CRM_EMACRX_PERIPH_CLOCK);      \
}

/**
 * @brief   Resets the ETH peripheral.
 *
 * @api
 */
#define rccResetETH() rccResetPeriph(CRM_EMAC_PERIPH_RESET)
/** @} */

/**
 * @name    I2C peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the I2C1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableI2C1(lp) rccEnablePeriph(CRM_I2C1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the I2C1 peripheral clock.
 *
 * @api
 */
#define rccDisableI2C1() rccDisablePeriph(CRM_I2C1_PERIPH_CLOCK)

/**
 * @brief   Resets the I2C1 peripheral.
 *
 * @api
 */
#define rccResetI2C1() rccResetPeriph(CRM_I2C1_PERIPH_RESET)

/**
 * @brief   Enables the I2C2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableI2C2(lp) rccEnablePeriph(CRM_I2C2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the I2C2 peripheral clock.
 *
 * @api
 */
#define rccDisableI2C2() rccDisablePeriph(CRM_I2C2_PERIPH_CLOCK)

/**
 * @brief   Resets the I2C2 peripheral.
 *
 * @api
 */
#define rccResetI2C2() rccResetPeriph(CRM_I2C2_PERIPH_RESET)

/**
 * @brief   Enables the I2C3 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableI2C3(lp) rccEnablePeriph(CRM_I2C3_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the I2C3 peripheral clock.
 *
 * @api
 */
#define rccDisableI2C3() rccDisablePeriph(CRM_I2C3_PERIPH_CLOCK)

/**
 * @brief   Resets the I2C3 peripheral.
 *
 * @api
 */
#define rccResetI2C3() rccResetPeriph(CRM_I2C3_PERIPH_RESET)
/** @} */

/**
 * @brief   Enables the I2C4 peripheral clock.
 *
 * @api
 */
#define rccEnableI2C4() //rccEnableAPB1(RCC_APB1ENR_FMPI2C1EN, lp)

/**
 * @brief   Disables the I2C4 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccDisableI2C4(lp) //rccDisableAPB1(RCC_APB1ENR_FMPI2C1EN, lp)

/**
 * @brief   Resets the I2C4 peripheral.
 *
 * @api
 */
#define rccResetI2C4() //rccResetAPB1(RCC_APB1RSTR_FMPI2C1RST)
/** @} */

/**
 * @name    OTG peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the OTG_FS peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableOTG_FS(lp) rccEnablePeriph(CRM_OTGFS1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the OTG_FS peripheral clock.
 *
 * @api
 */
#define rccDisableOTG_FS() rccDisablePeriph(CRM_OTGFS1_PERIPH_CLOCK)

/**
 * @brief   Resets the OTG_FS peripheral.
 *
 * @api
 */
#define rccResetOTG_FS() rccResetPeriph(CRM_OTGFS1_PERIPH_RESET)

/**
 * @brief   Enables the OTG_FS peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableOTG2_FS(lp) rccEnablePeriph(CRM_OTGFS2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the OTG_FS peripheral clock.
 *
 * @api
 */
#define rccDisableOTG2_FS() rccDisablePeriph(CRM_OTGFS2_PERIPH_CLOCK)

/**
 * @brief   Resets the OTG_FS peripheral.
 *
 * @api
 */
#define rccResetOTG2_FS() rccResetPeriph(CRM_OTGFS2_PERIPH_RESET)

/**
 * @brief   Enables the OTG_HS peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableOTG_HS(lp) //rccEnableAHB1(RCC_AHB1ENR_OTGHSEN, lp)

/**
 * @brief   Disables the OTG_HS peripheral clock.
 *
 * @api
 */
#define rccDisableOTG_HS() //rccDisableAHB1(RCC_AHB1ENR_OTGHSEN)

/**
 * @brief   Resets the OTG_HS peripheral.
 *
 * @api
 */
#define rccResetOTG_HS() //rccResetAHB1(RCC_AHB1RSTR_OTGHRST)

/**
 * @brief   Enables the OTG_HS peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableOTG_HSULPI(lp) //rccEnableAHB1(RCC_AHB1ENR_OTGHSULPIEN, lp)

/**
 * @brief   Disables the OTG_HS peripheral clock.
 *
 * @api
 */
#define rccDisableOTG_HSULPI() //rccDisableAHB1(RCC_AHB1ENR_OTGHSULPIEN)
/** @} */

/**
 * @name    QUADSPI peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the QUADSPI1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableQUADSPI1(lp) rccEnablePeriph(CRM_QSPI1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the QUADSPI1 peripheral clock.
 *
 * @api
 */
#define rccDisableQUADSPI1() rccDisablePeriph(CRM_QSPI1_PERIPH_CLOCK)

/**
 * @brief   Resets the QUADSPI1 peripheral.
 *
 * @api
 */
#define rccResetQUADSPI1() rccResetPeriph(CRM_QSPI1_PERIPH_RESET)

/**
 * @brief   Enables the QUADSPI1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableQUADSPI2(lp) rccEnablePeriph(CRM_QSPI2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the QUADSPI1 peripheral clock.
 *
 * @api
 */
#define rccDisableQUADSPI2() rccDisablePeriph(CRM_QSPI2_PERIPH_CLOCK)

/**
 * @brief   Resets the QUADSPI1 peripheral.
 *
 * @api
 */
#define rccResetQUADSPI2() rccResetPeriph(CRM_QSPI2_PERIPH_RESET)
/** @} */

/**
 * @name    SDIO peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the SDIO peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSDIO(lp) rccEnablePeriph(CRM_SDIO1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the SDIO peripheral clock.
 *
 * @api
 */
#define rccDisableSDIO() rccDisablePeriph(CRM_SDIO1_PERIPH_CLOCK)

/**
 * @brief   Resets the SDIO peripheral.
 *
 * @api
 */
#define rccResetSDIO() rccResetPeriph(CRM_SDIO1_PERIPH_RESET)

/**
 * @brief   Enables the SDIO peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSDIO2(lp) rccEnablePeriph(CRM_SDIO2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the SDIO peripheral clock.
 *
 * @api
 */
#define rccDisableSDIO2() rccDisablePeriph(CRM_SDIO2_PERIPH_CLOCK)

/**
 * @brief   Resets the SDIO peripheral.
 *
 * @api
 */
#define rccResetSDIO2() rccResetPeriph(CRM_SDIO2_PERIPH_RESET)
/** @} */

/**
 * @name    SPI peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the SPI1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSPI1(lp) rccEnablePeriph(CRM_SPI1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the SPI1 peripheral clock.
 *
 * @api
 */
#define rccDisableSPI1() rccDisablePeriph(CRM_SPI1_PERIPH_CLOCK)

/**
 * @brief   Resets the SPI1 peripheral.
 *
 * @api
 */
#define rccResetSPI1() rccResetPeriph(CRM_SPI1_PERIPH_RESET)

/**
 * @brief   Enables the SPI2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSPI2(lp) rccEnablePeriph(CRM_SPI2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the SPI2 peripheral clock.
 *
 * @api
 */
#define rccDisableSPI2() rccDisablePeriph(CRM_SPI2_PERIPH_CLOCK)

/**
 * @brief   Resets the SPI2 peripheral.
 *
 * @api
 */
#define rccResetSPI2() rccResetPeriph(CRM_SPI2_PERIPH_RESET)

/**
 * @brief   Enables the SPI3 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSPI3(lp) rccEnablePeriph(CRM_SPI3_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the SPI3 peripheral clock.
 *
 * @api
 */
#define rccDisableSPI3() rccDisablePeriph(CRM_SPI3_PERIPH_CLOCK)

/**
 * @brief   Resets the SPI3 peripheral.
 *
 * @api
 */
#define rccResetSPI3() rccResetPeriph(CRM_SPI3_PERIPH_RESET)

/**
 * @brief   Enables the SPI4 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSPI4(lp) rccEnablePeriph(CRM_SPI4_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the SPI4 peripheral clock.
 *
 * @api
 */
#define rccDisableSPI4() rccDisablePeriph(CRM_SPI4_PERIPH_CLOCK)

/**
 * @brief   Resets the SPI4 peripheral.
 *
 * @api
 */
#define rccResetSPI4() rccResetPeriph(CRM_SPI4_PERIPH_RESET)

/**
 * @brief   Enables the SPI5 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSPI5(lp) //rccEnableAPB2(RCC_APB2ENR_SPI5EN, lp)

/**
 * @brief   Disables the SPI5 peripheral clock.
 *
 * @api
 */
#define rccDisableSPI5() //rccDisableAPB2(RCC_APB2ENR_SPI5EN)

/**
 * @brief   Resets the SPI5 peripheral.
 *
 * @api
 */
#define rccResetSPI5() //rccResetAPB2(RCC_APB2RSTR_SPI5RST)

/**
 * @brief   Enables the SPI6 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableSPI6(lp) //rccEnableAPB2(RCC_APB2ENR_SPI6EN, lp)

/**
 * @brief   Disables the SPI6 peripheral clock.
 *
 * @api
 */
#define rccDisableSPI6() //rccDisableAPB2(RCC_APB2ENR_SPI6EN)

/**
 * @brief   Resets the SPI6 peripheral.
 *
 * @api
 */
#define rccResetSPI6() //rccResetAPB2(RCC_APB2RSTR_SPI6RST)
/** @} */

/**
 * @name    TIM peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the TIM1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM1(lp) rccEnablePeriph(CRM_TMR1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM1 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM1() rccDisablePeriph(CRM_TMR1_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM1 peripheral.
 *
 * @api
 */
#define rccResetTIM1() rccResetPeriph(CRM_TMR1_PERIPH_RESET)

/**
 * @brief   Enables the TIM2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM2(lp) rccEnablePeriph(CRM_TMR2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM2 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM2() rccDisablePeriph(CRM_TMR2_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM2 peripheral.
 *
 * @api
 */
#define rccResetTIM2() rccResetPeriph(CRM_TMR2_PERIPH_RESET)

/**
 * @brief   Enables the TIM3 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM3(lp) rccEnablePeriph(CRM_TMR3_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM3 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM3() rccDisablePeriph(CRM_TMR3_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM3 peripheral.
 *
 * @api
 */
#define rccResetTIM3() rccResetPeriph(CRM_TMR3_PERIPH_RESET)

/**
 * @brief   Enables the TIM4 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM4(lp) rccEnablePeriph(CRM_TMR4_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM4 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM4() rccDisablePeriph(CRM_TMR4_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM4 peripheral.
 *
 * @api
 */
#define rccResetTIM4() rccResetPeriph(CRM_TMR4_PERIPH_RESET)

/**
 * @brief   Enables the TIM5 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM5(lp) rccEnablePeriph(CRM_TMR5_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM5 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM5() rccDisablePeriph(CRM_TMR5_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM5 peripheral.
 *
 * @api
 */
#define rccResetTIM5() rccResetPeriph(CRM_TMR5_PERIPH_RESET)

/**
 * @brief   Enables the TIM6 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM6(lp) rccEnablePeriph(CRM_TMR6_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM6 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM6() rccDisablePeriph(CRM_TMR6_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM6 peripheral.
 *
 * @api
 */
#define rccResetTIM6() rccResetPeriph(CRM_TMR6_PERIPH_RESET)

/**
 * @brief   Enables the TIM7 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM7(lp) rccEnablePeriph(CRM_TMR7_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM7 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM7() rccDisablePeriph(CRM_TMR7_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM7 peripheral.
 *
 * @api
 */
#define rccResetTIM7() rccResetPeriph(CRM_TMR7_PERIPH_RESET)

/**
 * @brief   Enables the TIM8 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM8(lp) rccEnablePeriph(CRM_TMR8_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM8 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM8() rccDisablePeriph(CRM_TMR8_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM8 peripheral.
 *
 * @api
 */
#define rccResetTIM8() rccResetPeriph(CRM_TMR8_PERIPH_RESET)

/**
 * @brief   Enables the TIM9 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM9(lp) rccEnablePeriph(CRM_TMR9_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM9 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM9() rccDisablePeriph(CRM_TMR9_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM9 peripheral.
 *
 * @api
 */
#define rccResetTIM9() rccResetPeriph(CRM_TMR9_PERIPH_RESET)

/**
 * @brief   Enables the TIM10 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM10(lp) rccEnablePeriph(CRM_TMR10_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM10 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM10() rccDisablePeriph(CRM_TMR10_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM10 peripheral.
 *
 * @api
 */
#define rccResetTIM10() rccResetPeriph(CRM_TMR10_PERIPH_RESET)

/**
 * @brief   Enables the TIM11 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM11(lp) rccEnablePeriph(CRM_TMR11_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM11 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM11() rccDisablePeriph(CRM_TMR11_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM11 peripheral.
 *
 * @api
 */
#define rccResetTIM11() rccResetPeriph(CRM_TMR11_PERIPH_RESET)

/**
 * @brief   Enables the TIM12 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM12(lp) rccEnablePeriph(CRM_TMR12_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM12 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM12() rccDisablePeriph(CRM_TMR12_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM12 peripheral.
 *
 * @api
 */
#define rccResetTIM12() rccResetPeriph(CRM_TMR12_PERIPH_RESET)

/**
 * @brief   Enables the TIM13 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM13(lp) rccEnablePeriph(CRM_TMR13_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM13 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM13() rccDisablePeriph(CRM_TMR13_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM13 peripheral.
 *
 * @api
 */
#define rccResetTIM13() rccResetPeriph(CRM_TMR13_PERIPH_RESET)

/**
 * @brief   Enables the TIM14 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM14(lp) rccEnablePeriph(CRM_TMR14_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM14 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM14() rccDisablePeriph(CRM_TMR14_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM14 peripheral.
 *
 * @api
 */
#define rccResetTIM14() rccResetPeriph(CRM_TMR14_PERIPH_RESET)
/**
 * @brief   Enables the TIM20 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableTIM20(lp) rccEnablePeriph(CRM_TMR20_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the TIM14 peripheral clock.
 *
 * @api
 */
#define rccDisableTIM20() rccDisablePeriph(CRM_TMR20_PERIPH_CLOCK)

/**
 * @brief   Resets the TIM14 peripheral.
 *
 * @api
 */
#define rccResetTIM20() rccResetPeriph(CRM_TMR20_PERIPH_RESET)
/** @} */

/**
 * @brief   Enables the LPTIM1 peripheral clock.
 * @note    The @p lp parameter is ignored in this family.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableLPTIM1(lp) //rccEnableAPB1(RCC_APB1ENR_LPTIM1EN, lp)

/**
 * @brief   Disables the LPTIM1 peripheral clock.
 *
 * @api
 */
#define rccDisableLPTIM1() //rccDisableAPB1(RCC_APB1ENR_LPTIM1EN, lp)

/**
 * @brief   Resets the LPTIM1 peripheral.
 *
 * @api
 */
#define rccResetLPTIM1() //rccResetAPB1(RCC_APB1RSTR_LPTIM1RST)
/** @} */

/**
 * @name    USART/UART peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the USART1 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUSART1(lp) rccEnablePeriph(CRM_USART1_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the USART1 peripheral clock.
 *
 * @api
 */
#define rccDisableUSART1() rccDisablePeriph(CRM_USART1_PERIPH_CLOCK)

/**
 * @brief   Resets the USART1 peripheral.
 *
 * @api
 */
#define rccResetUSART1() rccResetPeriph(CRM_USART1_PERIPH_RESET)

/**
 * @brief   Enables the USART2 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUSART2(lp) rccEnablePeriph(CRM_USART2_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the USART2 peripheral clock.
 *
 * @api
 */
#define rccDisableUSART2() rccDisablePeriph(CRM_USART2_PERIPH_CLOCK)

/**
 * @brief   Resets the USART2 peripheral.
 *
 * @api
 */
#define rccResetUSART2() rccResetPeriph(CRM_USART2_PERIPH_RESET)

/**
 * @brief   Enables the USART3 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUSART3(lp) rccEnablePeriph(CRM_USART3_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the USART3 peripheral clock.
 *
 * @api
 */
#define rccDisableUSART3() rccDisablePeriph(CRM_USART3_PERIPH_CLOCK)

/**
 * @brief   Resets the USART3 peripheral.
 *
 * @api
 */
#define rccResetUSART3() rccResetPeriph(CRM_USART3_PERIPH_RESET)

/**
 * @brief   Enables the UART4 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUART4(lp) rccEnablePeriph(CRM_UART4_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the UART4 peripheral clock.
 *
 * @api
 */
#define rccDisableUART4() rccDisablePeriph(CRM_UART4_PERIPH_CLOCK)

/**
 * @brief   Resets the UART4 peripheral.
 *
 * @api
 */
#define rccResetUART4() rccResetPeriph(CRM_UART4_PERIPH_RESET)

/**
 * @brief   Enables the UART5 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUART5(lp) rccEnablePeriph(CRM_UART5_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the UART5 peripheral clock.
 *
 * @api
 */
#define rccDisableUART5() rccDisablePeriph(CRM_UART5_PERIPH_CLOCK)

/**
 * @brief   Resets the UART5 peripheral.
 *
 * @api
 */
#define rccResetUART5() rccResetPeriph(CRM_UART5_PERIPH_RESET)

/**
 * @brief   Enables the USART6 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUSART6(lp) rccEnablePeriph(CRM_USART6_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the USART6 peripheral clock.
 *
 * @api
 */
#define rccDisableUSART6() rccDisablePeriph(CRM_USART6_PERIPH_CLOCK)

/**
 * @brief   Resets the USART6 peripheral.
 *
 * @api
 */
#define rccResetUSART6() rccResetPeriph(CRM_USART6_PERIPH_RESET)

/**
 * @brief   Enables the UART7 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUART7(lp) rccEnablePeriph(CRM_UART7_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the UART7 peripheral clock.
 *
 * @api
 */
#define rccDisableUART7() rccDisablePeriph(CRM_UART7_PERIPH_CLOCK)

/**
 * @brief   Resets the UART7 peripheral.
 *
 * @api
 */
#define rccResetUART7() rccResetPeriph(CRM_UART7_PERIPH_RESET)

/**
 * @brief   Enables the UART8 peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUART8(lp) rccEnablePeriph(CRM_UART8_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the UART8 peripheral clock.
 *
 * @api
 */
#define rccDisableUART8() rccDisablePeriph(CRM_UART8_PERIPH_CLOCK)

/**
 * @brief   Resets the UART8 peripheral.
 *
 * @api
 */
#define rccResetUART8() rccResetPeriph(CRM_UART8_PERIPH_RESET)
/** @} */

/**
 * @brief   Enables the UART9 peripheral clock.
 * @note    The @p lp parameter is ignored in this family.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUART9(lp) //rccEnableAPB2(RCC_APB2ENR_UART9EN, lp)

/**
 * @brief   Disables the UART9 peripheral clock.
 *
 * @api
 */
#define rccDisableUART9() //rccDisableAPB2(RCC_APB2ENR_UART9EN, lp)

/**
 * @brief   Resets the UART9 peripheral.
 *
 * @api
 */
#define rccResetUART9() //rccResetAPB2(RCC_APB2RSTR_UART9RST)
/** @} */

/**
 * @brief   Enables the UART10 peripheral clock.
 * @note    The @p lp parameter is ignored in this family.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableUART10(lp) //rccEnableAPB2(RCC_APB2ENR_UART10EN, lp)

/**
 * @brief   Disables the UART10 peripheral clock.
 *
 * @api
 */
#define rccDisableUART10(lp) //rccDisableAPB2(RCC_APB2ENR_UART10EN, lp)

/**
 * @brief   Resets the UART10 peripheral.
 *
 * @api
 */
#define rccResetUART10() //rccResetAPB2(RCC_APB2RSTR_UART10RST)
/** @} */

/**
 * @name    LTDC peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the LTDC peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableLTDC(lp) //rccEnableAPB2(RCC_APB2ENR_LTDCEN, lp)

/**
 * @brief   Disables the LTDC peripheral clock.
 *
 * @api
 */
#define rccDisableLTDC() //rccDisableAPB2(RCC_APB2ENR_LTDCEN)

/**
 * @brief   Resets the LTDC peripheral.
 *
 * @api
 */
#define rccResetLTDC() //rccResetAPB2(RCC_APB2RSTR_LTDCRST)

/**
 * @name    DMA2D peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the DMA2D peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableDMA2D(lp) //rccEnableAHB1(RCC_AHB1ENR_DMA2DEN, lp)

/**
 * @brief   Disables the DMA2D peripheral clock.
 *
 * @api
 */
#define rccDisableDMA2D() //rccDisableAHB1(RCC_AHB1ENR_DMA2DEN)

/**
 * @brief   Resets the DMA2D peripheral.
 *
 * @api
 */
#define rccResetDMA2D() //rccResetAHB1(RCC_AHB1RSTR_DMA2DRST)
/** @} */

/**
 * @name    CRC peripheral specific RCC operations
 * @{
 */
/**
 * @brief   Enables the CRC peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#define rccEnableCRC(lp) rccEnablePeriph(CRM_CRC_PERIPH_CLOCK, lp)

/**
 * @brief   Disables the CRC peripheral clock.
 *
 * @api
 */
#define rccDisableCRC() rccDisablePeriph(CRM_CRC_PERIPH_CLOCK)

/**
 * @brief   Resets the CRC peripheral.
 *
 * @api
 */
#define rccResetCRC() rccResetPeriph(CRM_CRC_PERIPH_RESET)
/** @} */

/**
 * @name    FSMC peripherals specific RCC operations
 * @{
 */
/**
 * @brief   Enables the FSMC peripheral clock.
 *
 * @param[in] lp        low power enable flag
 *
 * @api
 */
#if STM32_HAS_FSMC || defined(__DOXYGEN__)
#if STM32_FSMC_IS_FMC || defined(__DOXYGEN__)
  #define rccEnableFSMC(lp) rccEnablePeriph(CRM_XMC_PERIPH_CLOCK, lp)
#else
  #define rccEnableFSMC(lp) rccEnablePeriph(CRM_XMC_PERIPH_CLOCK, lp)
#endif
#endif

/**
 * @brief   Disables the FSMC peripheral clock.
 *
 * @api
 */
#if STM32_HAS_FSMC || defined(__DOXYGEN__)
#if STM32_FSMC_IS_FMC || defined(__DOXYGEN__)
  #define rccDisableFSMC() rccDisablePeriph(CRM_XMC_PERIPH_CLOCK)
#else
  #define rccDisableFSMC() rccDisablePeriph(CRM_XMC_PERIPH_CLOCK)
#endif
#endif

/**
 * @brief   Resets the FSMC peripheral.
 *
 * @api
 */
#if STM32_HAS_FSMC || defined(__DOXYGEN__)
#if STM32_FSMC_IS_FMC || defined(__DOXYGEN__)
  #define rccResetFSMC() rccResetPeriph(CRM_XMC_PERIPH_RESET)
#else
  #define rccResetFSMC() rccResetPeriph(CRM_XMC_PERIPH_RESET)
#endif
#endif
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

#endif /* STM32_RCC_H */

/** @} */
