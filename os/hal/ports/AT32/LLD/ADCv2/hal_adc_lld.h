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
 * @file    ADCv2/hal_adc_lld.h
 * @brief   STM32 ADC subsystem low level driver header.
 *
 * @addtogroup ADC
 * @{
 */

#ifndef HAL_ADC_LLD_H
#define HAL_ADC_LLD_H


#if HAL_USE_ADC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Possible ADC errors mask bits.
 * @{
 */
#define ADC_ERR_DMAFAILURE      1U  /**< DMA operations failure.            */
#define ADC_ERR_OVERFLOW        2U  /**< ADC overflow condition.            */
#define ADC_ERR_AWD             4U  /**< Watchdog triggered.                */
/** @} */

/**
 * @name    Absolute Maximum Ratings
 * @{
 */
/**
 * @brief   Minimum ADC clock frequency.
 */
#define STM32_ADCCLK_MIN        600000

/**
 * @brief   Maximum ADC clock frequency.
 */
#if defined(STM32F4XX) || defined(__DOXYGEN__)
#define STM32_ADCCLK_MAX        36000000
#else
#define STM32_ADCCLK_MAX        30000000
#endif
/** @} */

/**
 * @name    Triggers selection
 * @{
 */
#define ADC_CR2_EXTEN_MASK      (3U << 28U)
#define ADC_CR2_EXTEN_DISABLED  (0U << 28U)
#define ADC_CR2_EXTEN_RISING    (1U << 28U)
#define ADC_CR2_EXTEN_FALLING   (2U << 28U)
#define ADC_CR2_EXTEN_BOTH      (3U << 28U)

#define ADC_CR2_EXTSEL_MASK     (15U << 24U)
#define ADC_CR2_EXTSEL_SRC(n)   ((n) << 24U)
/** @} */

/**
 * @name    ADC clock divider settings
 * @{
 */
#define ADC_CCR_ADCPRE_DIV2     0
#define ADC_CCR_ADCPRE_DIV3     1
#define ADC_CCR_ADCPRE_DIV4     2
#define ADC_CCR_ADCPRE_DIV5     3
#define ADC_CCR_ADCPRE_DIV6     4
#define ADC_CCR_ADCPRE_DIV7     5
#define ADC_CCR_ADCPRE_DIV8     6
#define ADC_CCR_ADCPRE_DIV9     7
#define ADC_CCR_ADCPRE_DIV10     8
#define ADC_CCR_ADCPRE_DIV11     9
#define ADC_CCR_ADCPRE_DIV12     10
#define ADC_CCR_ADCPRE_DIV13     11
#define ADC_CCR_ADCPRE_DIV14     12
#define ADC_CCR_ADCPRE_DIV15     13
#define ADC_CCR_ADCPRE_DIV16     14
#define ADC_CCR_ADCPRE_DIV17     15
/** @} */

/**
 * @name    Available analog channels
 * @{
 */
#define ADC_CHANNEL_IN0         0   /**< @brief External analog input 0.    */
#define ADC_CHANNEL_IN1         1   /**< @brief External analog input 1.    */
#define ADC_CHANNEL_IN2         2   /**< @brief External analog input 2.    */
#define ADC_CHANNEL_IN3         3   /**< @brief External analog input 3.    */
#define ADC_CHANNEL_IN4         4   /**< @brief External analog input 4.    */
#define ADC_CHANNEL_IN5         5   /**< @brief External analog input 5.    */
#define ADC_CHANNEL_IN6         6   /**< @brief External analog input 6.    */
#define ADC_CHANNEL_IN7         7   /**< @brief External analog input 7.    */
#define ADC_CHANNEL_IN8         8   /**< @brief External analog input 8.    */
#define ADC_CHANNEL_IN9         9   /**< @brief External analog input 9.    */
#define ADC_CHANNEL_IN10        10  /**< @brief External analog input 10.   */
#define ADC_CHANNEL_IN11        11  /**< @brief External analog input 11.   */
#define ADC_CHANNEL_IN12        12  /**< @brief External analog input 12.   */
#define ADC_CHANNEL_IN13        13  /**< @brief External analog input 13.   */
#define ADC_CHANNEL_IN14        14  /**< @brief External analog input 14.   */
#define ADC_CHANNEL_IN15        15  /**< @brief External analog input 15.   */
#define ADC_CHANNEL_SENSOR      16  /**< @brief Internal temperature sensor.
                                         @note Available onADC1 only.       */
#define ADC_CHANNEL_VREFINT     17  /**< @brief Internal reference.
                                         @note Available onADC1 only.       */
#define ADC_CHANNEL_VBAT        18  /**< @brief VBAT.
                                         @note Available onADC1 only.       */
/** @} */

/**
 * @name    Sampling rates
 * @{
 */
#define ADC_SAMPLE_2_5           0   /**< @brief 2.5 cycles sampling time.     */
#define ADC_SAMPLE_6_5           1   /**< @brief 6.5 cycles sampling time.    */
#define ADC_SAMPLE_12_5          2   /**< @brief 12.5 cycles sampling time.    */
#define ADC_SAMPLE_24_5          3   /**< @brief 24.5 cycles sampling time.    */
#define ADC_SAMPLE_47_5          4   /**< @brief 47.5 cycles sampling time.    */
#define ADC_SAMPLE_92_5          5   /**< @brief 92.5 cycles sampling time.   */
#define ADC_SAMPLE_247_5         6   /**< @brief 247.5 cycles sampling time.   */
#define ADC_SAMPLE_640_5         7   /**< @brief 640.5 cycles sampling time.   */
#define ADC_SAMPLE_480           ADC_SAMPLE_640_5   /**< @brief 640.5 cycles sampling time.   */
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   ADC common clock divider.
 * @note    This setting is influenced by the VDDA voltage and other
 *          external conditions, please refer to the datasheet for more
 *          info.<br>
 *          See section 5.3.20 "12-bit ADC characteristics".
 */
#if !defined(STM32_ADC_ADCPRE) || defined(__DOXYGEN__)
#define STM32_ADC_ADCPRE                    ADC_CCR_ADCPRE_DIV2
#endif

/**
 * @brief   ADC1 driver enable switch.
 * @details If set to @p TRUE the support for ADC1 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_ADC_USE_ADC1) || defined(__DOXYGEN__)
#define STM32_ADC_USE_ADC1                  TRUE
#endif

/**
 * @brief   ADC2 driver enable switch.
 * @details If set to @p TRUE the support for ADC2 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_ADC_USE_ADC2) || defined(__DOXYGEN__)
#define STM32_ADC_USE_ADC2                  TRUE
#endif

/**
 * @brief   ADC3 driver enable switch.
 * @details If set to @p TRUE the support for ADC3 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_ADC_USE_ADC3) || defined(__DOXYGEN__)
#define STM32_ADC_USE_ADC3                  TRUE
#endif

/**
 * @brief   DMA stream used for ADC1 operations.
 */
#if !defined(STM32_ADC_ADC1_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID(2, 4)
#endif

/**
 * @brief   DMA stream used for ADC2 operations.
 */
#if !defined(STM32_ADC_ADC2_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_ADC_ADC2_DMA_STREAM           STM32_DMA_STREAM_ID(2, 2)
#endif

/**
 * @brief   DMA stream used for ADC3 operations.
 */
#if !defined(STM32_ADC_ADC3_DMA_STREAM) || defined(__DOXYGEN__)
#define STM32_ADC_ADC3_DMA_STREAM           STM32_DMA_STREAM_ID(2, 1)
#endif

/**
 * @brief   ADC1 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_ADC_ADC1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC1_DMA_PRIORITY         2
#endif

/**
 * @brief   ADC2 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_ADC_ADC2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC2_DMA_PRIORITY         2
#endif

/**
 * @brief   ADC3 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_ADC_ADC3_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC3_DMA_PRIORITY         2
#endif

/**
 * @brief   ADC interrupt priority level setting.
 * @note    This setting is shared among ADC1, ADC2 and ADC3 because
 *          all ADCs share the same vector.
 */
#if !defined(STM32_ADC_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_IRQ_PRIORITY              5
#endif

/**
 * @brief   ADC1 DMA interrupt priority level setting.
 */
#if !defined(STM32_ADC_ADC1_DMA_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC1_DMA_IRQ_PRIORITY     5
#endif

/**
 * @brief   ADC2 DMA interrupt priority level setting.
 */
#if !defined(STM32_ADC_ADC2_DMA_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC2_DMA_IRQ_PRIORITY     5
#endif

/**
 * @brief   ADC3 DMA interrupt priority level setting.
 */
#if !defined(STM32_ADC_ADC3_DMA_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC3_DMA_IRQ_PRIORITY     5
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if STM32_ADC_USE_ADC1 && !STM32_HAS_ADC1
#error "ADC1 not present in the selected device"
#endif

#if STM32_ADC_USE_ADC2 && !STM32_HAS_ADC2
#error "ADC2 not present in the selected device"
#endif

#if STM32_ADC_USE_ADC3 && !STM32_HAS_ADC3
#error "ADC3 not present in the selected device"
#endif

#if !STM32_ADC_USE_ADC1 && !STM32_ADC_USE_ADC2 && !STM32_ADC_USE_ADC3
#error "ADC driver activated but no ADC peripheral assigned"
#endif
#if 0
#if STM32_ADC_USE_ADC1 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_ADC_ADC1_DMA_STREAM, STM32_ADC1_DMA_MSK)
#error "invalid DMA stream associated to ADC1"
#endif

#if STM32_ADC_USE_ADC2 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_ADC_ADC2_DMA_STREAM, STM32_ADC2_DMA_MSK)
#error "invalid DMA stream associated to ADC2"
#endif

#if STM32_ADC_USE_ADC3 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_ADC_ADC3_DMA_STREAM, STM32_ADC3_DMA_MSK)
#error "invalid DMA stream associated to ADC3"
#endif
#endif
/* ADC clock related settings and checks.*/
#if STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV2
#define STM32_ADCCLK                        (STM32_PCLK2 / 2)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV3
#define STM32_ADCCLK                        (STM32_PCLK2 / 3)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV4
#define STM32_ADCCLK                        (STM32_PCLK2 / 4)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV5
#define STM32_ADCCLK                        (STM32_PCLK2 / 5)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV6
#define STM32_ADCCLK                        (STM32_PCLK2 / 6)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV7
#define STM32_ADCCLK                        (STM32_PCLK2 / 7)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV8
#define STM32_ADCCLK                        (STM32_PCLK2 / 8)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV9
#define STM32_ADCCLK                        (STM32_PCLK2 / 9)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV10
#define STM32_ADCCLK                        (STM32_PCLK2 / 10)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV11
#define STM32_ADCCLK                        (STM32_PCLK2 / 11)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV12
#define STM32_ADCCLK                        (STM32_PCLK2 / 12)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV13
#define STM32_ADCCLK                        (STM32_PCLK2 / 13)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV14
#define STM32_ADCCLK                        (STM32_PCLK2 / 14)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV15
#define STM32_ADCCLK                        (STM32_PCLK2 / 15)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV16
#define STM32_ADCCLK                        (STM32_PCLK2 / 16)
#elif STM32_ADC_ADCPRE == ADC_CCR_ADCPRE_DIV17
#define STM32_ADCCLK                        (STM32_PCLK2 / 17)
#else
#error "invalid STM32_ADC_ADCPRE value specified"
#endif

#if (STM32_ADCCLK < STM32_ADCCLK_MIN) || (STM32_ADCCLK > STM32_ADCCLK_MAX)
#error "STM32_ADCCLK outside acceptable range (STM32_ADCCLK_MIN...STM32_ADCCLK_MAX)"
#endif

#if !defined(STM32_DMA_REQUIRED)
#define STM32_DMA_REQUIRED
#endif

/******************************************************************************/
/*                         Peripheral Registers_Bits_Definition               */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                        Analog to Digital Converter                         */
/*                                                                            */
/******************************************************************************/
/*
 * @brief Specific device feature definitions (not present on all devices in the STM32F4 serie)
 */
#define ADC_MULTIMODE_SUPPORT                                                  /*!<ADC Multimode feature available on specific devices */

/********************  Bit definition for ADC_SR register  ********************/
#define ADC_SR_AWD_Pos            (0U)
#define ADC_SR_AWD_Msk            (0x1U << ADC_SR_AWD_Pos)                     /*!< 0x00000001 */
#define ADC_SR_AWD                ADC_SR_AWD_Msk                               /*!<Analog watchdog flag */
#define ADC_SR_EOC_Pos            (1U)
#define ADC_SR_EOC_Msk            (0x1U << ADC_SR_EOC_Pos)                     /*!< 0x00000002 */
#define ADC_SR_EOC                ADC_SR_EOC_Msk                               /*!<End of conversion */
#define ADC_SR_JEOC_Pos           (2U)
#define ADC_SR_JEOC_Msk           (0x1U << ADC_SR_JEOC_Pos)                    /*!< 0x00000004 */
#define ADC_SR_JEOC               ADC_SR_JEOC_Msk                              /*!<Injected channel end of conversion */
#define ADC_SR_JSTRT_Pos          (3U)
#define ADC_SR_JSTRT_Msk          (0x1U << ADC_SR_JSTRT_Pos)                   /*!< 0x00000008 */
#define ADC_SR_JSTRT              ADC_SR_JSTRT_Msk                             /*!<Injected channel Start flag */
#define ADC_SR_STRT_Pos           (4U)
#define ADC_SR_STRT_Msk           (0x1U << ADC_SR_STRT_Pos)                    /*!< 0x00000010 */
#define ADC_SR_STRT               ADC_SR_STRT_Msk                              /*!<Regular channel Start flag */
#define ADC_SR_OVR_Pos            (5U)
#define ADC_SR_OVR_Msk            (0x1U << ADC_SR_OVR_Pos)                     /*!< 0x00000020 */
#define ADC_SR_OVR                ADC_SR_OVR_Msk                               /*!<Overrun flag */

/*******************  Bit definition for ADC_CR1 register  ********************/
#define ADC_CR1_AWDCH_Pos         (0U)
#define ADC_CR1_AWDCH_Msk         (0x1FU << ADC_CR1_AWDCH_Pos)                 /*!< 0x0000001F */
#define ADC_CR1_AWDCH             ADC_CR1_AWDCH_Msk                            /*!<AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_CR1_AWDCH_0           (0x01U << ADC_CR1_AWDCH_Pos)                 /*!< 0x00000001 */
#define ADC_CR1_AWDCH_1           (0x02U << ADC_CR1_AWDCH_Pos)                 /*!< 0x00000002 */
#define ADC_CR1_AWDCH_2           (0x04U << ADC_CR1_AWDCH_Pos)                 /*!< 0x00000004 */
#define ADC_CR1_AWDCH_3           (0x08U << ADC_CR1_AWDCH_Pos)                 /*!< 0x00000008 */
#define ADC_CR1_AWDCH_4           (0x10U << ADC_CR1_AWDCH_Pos)                 /*!< 0x00000010 */
#define ADC_CR1_EOCIE_Pos         (5U)
#define ADC_CR1_EOCIE_Msk         (0x1U << ADC_CR1_EOCIE_Pos)                  /*!< 0x00000020 */
#define ADC_CR1_EOCIE             ADC_CR1_EOCIE_Msk                            /*!<Interrupt enable for EOC */
#define ADC_CR1_AWDIE_Pos         (6U)
#define ADC_CR1_AWDIE_Msk         (0x1U << ADC_CR1_AWDIE_Pos)                  /*!< 0x00000040 */
#define ADC_CR1_AWDIE             ADC_CR1_AWDIE_Msk                            /*!<AAnalog Watchdog interrupt enable */
#define ADC_CR1_JEOCIE_Pos        (7U)
#define ADC_CR1_JEOCIE_Msk        (0x1U << ADC_CR1_JEOCIE_Pos)                 /*!< 0x00000080 */
#define ADC_CR1_JEOCIE            ADC_CR1_JEOCIE_Msk                           /*!<Interrupt enable for injected channels */
#define ADC_CR1_SCAN_Pos          (8U)
#define ADC_CR1_SCAN_Msk          (0x1U << ADC_CR1_SCAN_Pos)                   /*!< 0x00000100 */
#define ADC_CR1_SCAN              ADC_CR1_SCAN_Msk                             /*!<Scan mode */
#define ADC_CR1_AWDSGL_Pos        (9U)
#define ADC_CR1_AWDSGL_Msk        (0x1U << ADC_CR1_AWDSGL_Pos)                 /*!< 0x00000200 */
#define ADC_CR1_AWDSGL            ADC_CR1_AWDSGL_Msk                           /*!<Enable the watchdog on a single channel in scan mode */
#define ADC_CR1_JAUTO_Pos         (10U)
#define ADC_CR1_JAUTO_Msk         (0x1U << ADC_CR1_JAUTO_Pos)                  /*!< 0x00000400 */
#define ADC_CR1_JAUTO             ADC_CR1_JAUTO_Msk                            /*!<Automatic injected group conversion */
#define ADC_CR1_DISCEN_Pos        (11U)
#define ADC_CR1_DISCEN_Msk        (0x1U << ADC_CR1_DISCEN_Pos)                 /*!< 0x00000800 */
#define ADC_CR1_DISCEN            ADC_CR1_DISCEN_Msk                           /*!<Discontinuous mode on regular channels */
#define ADC_CR1_JDISCEN_Pos       (12U)
#define ADC_CR1_JDISCEN_Msk       (0x1U << ADC_CR1_JDISCEN_Pos)                /*!< 0x00001000 */
#define ADC_CR1_JDISCEN           ADC_CR1_JDISCEN_Msk                          /*!<Discontinuous mode on injected channels */
#define ADC_CR1_DISCNUM_Pos       (13U)
#define ADC_CR1_DISCNUM_Msk       (0x7U << ADC_CR1_DISCNUM_Pos)                /*!< 0x0000E000 */
#define ADC_CR1_DISCNUM           ADC_CR1_DISCNUM_Msk                          /*!<DISCNUM[2:0] bits (Discontinuous mode channel count) */
#define ADC_CR1_DISCNUM_0         (0x1U << ADC_CR1_DISCNUM_Pos)                /*!< 0x00002000 */
#define ADC_CR1_DISCNUM_1         (0x2U << ADC_CR1_DISCNUM_Pos)                /*!< 0x00004000 */
#define ADC_CR1_DISCNUM_2         (0x4U << ADC_CR1_DISCNUM_Pos)                /*!< 0x00008000 */
#define ADC_CR1_JAWDEN_Pos        (22U)
#define ADC_CR1_JAWDEN_Msk        (0x1U << ADC_CR1_JAWDEN_Pos)                 /*!< 0x00400000 */
#define ADC_CR1_JAWDEN            ADC_CR1_JAWDEN_Msk                           /*!<Analog watchdog enable on injected channels */
#define ADC_CR1_AWDEN_Pos         (23U)
#define ADC_CR1_AWDEN_Msk         (0x1U << ADC_CR1_AWDEN_Pos)                  /*!< 0x00800000 */
#define ADC_CR1_AWDEN             ADC_CR1_AWDEN_Msk                            /*!<Analog watchdog enable on regular channels */
#define ADC_CR1_RES_Pos           (24U)
#define ADC_CR1_RES_Msk           (0x3U << ADC_CR1_RES_Pos)                    /*!< 0x03000000 */
#define ADC_CR1_RES               ADC_CR1_RES_Msk                              /*!<RES[2:0] bits (Resolution) */
#define ADC_CR1_RES_0             (0x1U << ADC_CR1_RES_Pos)                    /*!< 0x01000000 */
#define ADC_CR1_RES_1             (0x2U << ADC_CR1_RES_Pos)                    /*!< 0x02000000 */
#define ADC_CR1_OVRIE_Pos         (26U)
#define ADC_CR1_OVRIE_Msk         (0x1U << ADC_CR1_OVRIE_Pos)                  /*!< 0x04000000 */
#define ADC_CR1_OVRIE             ADC_CR1_OVRIE_Msk                            /*!<overrun interrupt enable */

/*******************  Bit definition for ADC_CR2 register  ********************/
#define ADC_CR2_ADON_Pos          (0U)
#define ADC_CR2_ADON_Msk          (0x1U << ADC_CR2_ADON_Pos)                   /*!< 0x00000001 */
#define ADC_CR2_ADON              ADC_CR2_ADON_Msk                             /*!<A/D Converter ON / OFF */
#define ADC_CR2_CONT_Pos          (1U)
#define ADC_CR2_CONT_Msk          (0x1U << ADC_CR2_CONT_Pos)                   /*!< 0x00000002 */
#define ADC_CR2_CONT              ADC_CR2_CONT_Msk                             /*!<Continuous Conversion */
#define ADC_CR2_DMA_Pos           (8U)
#define ADC_CR2_DMA_Msk           (0x1U << ADC_CR2_DMA_Pos)                    /*!< 0x00000100 */
#define ADC_CR2_DMA               ADC_CR2_DMA_Msk                              /*!<Direct Memory access mode */
#define ADC_CR2_DDS_Pos           (9U)
#define ADC_CR2_DDS_Msk           (0x1U << ADC_CR2_DDS_Pos)                    /*!< 0x00000200 */
#define ADC_CR2_DDS               ADC_CR2_DDS_Msk                              /*!<DMA disable selection (Single ADC) */
#define ADC_CR2_EOCS_Pos          (10U)
#define ADC_CR2_EOCS_Msk          (0x1U << ADC_CR2_EOCS_Pos)                   /*!< 0x00000400 */
#define ADC_CR2_EOCS              ADC_CR2_EOCS_Msk                             /*!<End of conversion selection */
#define ADC_CR2_ALIGN_Pos         (11U)
#define ADC_CR2_ALIGN_Msk         (0x1U << ADC_CR2_ALIGN_Pos)                  /*!< 0x00000800 */
#define ADC_CR2_ALIGN             ADC_CR2_ALIGN_Msk                            /*!<Data Alignment */
#define ADC_CR2_JEXTSEL_Pos       (16U)
#define ADC_CR2_JEXTSEL_Msk       (0xFU << ADC_CR2_JEXTSEL_Pos)                /*!< 0x000F0000 */
#define ADC_CR2_JEXTSEL           ADC_CR2_JEXTSEL_Msk                          /*!<JEXTSEL[3:0] bits (External event select for injected group) */
#define ADC_CR2_JEXTSEL_0         (0x1U << ADC_CR2_JEXTSEL_Pos)                /*!< 0x00010000 */
#define ADC_CR2_JEXTSEL_1         (0x2U << ADC_CR2_JEXTSEL_Pos)                /*!< 0x00020000 */
#define ADC_CR2_JEXTSEL_2         (0x4U << ADC_CR2_JEXTSEL_Pos)                /*!< 0x00040000 */
#define ADC_CR2_JEXTSEL_3         (0x8U << ADC_CR2_JEXTSEL_Pos)                /*!< 0x00080000 */
#define ADC_CR2_JEXTEN_Pos        (20U)
#define ADC_CR2_JEXTEN_Msk        (0x3U << ADC_CR2_JEXTEN_Pos)                 /*!< 0x00300000 */
#define ADC_CR2_JEXTEN            ADC_CR2_JEXTEN_Msk                           /*!<JEXTEN[1:0] bits (External Trigger Conversion mode for injected channelsp) */
#define ADC_CR2_JEXTEN_0          (0x1U << ADC_CR2_JEXTEN_Pos)                 /*!< 0x00100000 */
#define ADC_CR2_JEXTEN_1          (0x2U << ADC_CR2_JEXTEN_Pos)                 /*!< 0x00200000 */
#define ADC_CR2_JSWSTART_Pos      (22U)
#define ADC_CR2_JSWSTART_Msk      (0x1U << ADC_CR2_JSWSTART_Pos)               /*!< 0x00400000 */
#define ADC_CR2_JSWSTART          ADC_CR2_JSWSTART_Msk                         /*!<Start Conversion of injected channels */
#define ADC_CR2_EXTSEL_Pos        (24U)
#define ADC_CR2_EXTSEL_Msk        (0xFU << ADC_CR2_EXTSEL_Pos)                 /*!< 0x0F000000 */
#define ADC_CR2_EXTSEL            ADC_CR2_EXTSEL_Msk                           /*!<EXTSEL[3:0] bits (External Event Select for regular group) */
#define ADC_CR2_EXTSEL_0          (0x1U << ADC_CR2_EXTSEL_Pos)                 /*!< 0x01000000 */
#define ADC_CR2_EXTSEL_1          (0x2U << ADC_CR2_EXTSEL_Pos)                 /*!< 0x02000000 */
#define ADC_CR2_EXTSEL_2          (0x4U << ADC_CR2_EXTSEL_Pos)                 /*!< 0x04000000 */
#define ADC_CR2_EXTSEL_3          (0x8U << ADC_CR2_EXTSEL_Pos)                 /*!< 0x08000000 */
#define ADC_CR2_EXTEN_Pos         (28U)
#define ADC_CR2_EXTEN_Msk         (0x3U << ADC_CR2_EXTEN_Pos)                  /*!< 0x30000000 */
#define ADC_CR2_EXTEN             ADC_CR2_EXTEN_Msk                            /*!<EXTEN[1:0] bits (External Trigger Conversion mode for regular channelsp) */
#define ADC_CR2_EXTEN_0           (0x1U << ADC_CR2_EXTEN_Pos)                  /*!< 0x10000000 */
#define ADC_CR2_EXTEN_1           (0x2U << ADC_CR2_EXTEN_Pos)                  /*!< 0x20000000 */
#define ADC_CR2_SWSTART_Pos       (30U)
#define ADC_CR2_SWSTART_Msk       (0x1U << ADC_CR2_SWSTART_Pos)                /*!< 0x40000000 */
#define ADC_CR2_SWSTART           ADC_CR2_SWSTART_Msk                          /*!<Start Conversion of regular channels */

/******************  Bit definition for ADC_SMPR1 register  *******************/
#define ADC_SMPR1_SMP10_Pos       (0U)
#define ADC_SMPR1_SMP10_Msk       (0x7U << ADC_SMPR1_SMP10_Pos)                /*!< 0x00000007 */
#define ADC_SMPR1_SMP10           ADC_SMPR1_SMP10_Msk                          /*!<SMP10[2:0] bits (Channel 10 Sample time selection) */
#define ADC_SMPR1_SMP10_0         (0x1U << ADC_SMPR1_SMP10_Pos)                /*!< 0x00000001 */
#define ADC_SMPR1_SMP10_1         (0x2U << ADC_SMPR1_SMP10_Pos)                /*!< 0x00000002 */
#define ADC_SMPR1_SMP10_2         (0x4U << ADC_SMPR1_SMP10_Pos)                /*!< 0x00000004 */
#define ADC_SMPR1_SMP11_Pos       (3U)
#define ADC_SMPR1_SMP11_Msk       (0x7U << ADC_SMPR1_SMP11_Pos)                /*!< 0x00000038 */
#define ADC_SMPR1_SMP11           ADC_SMPR1_SMP11_Msk                          /*!<SMP11[2:0] bits (Channel 11 Sample time selection) */
#define ADC_SMPR1_SMP11_0         (0x1U << ADC_SMPR1_SMP11_Pos)                /*!< 0x00000008 */
#define ADC_SMPR1_SMP11_1         (0x2U << ADC_SMPR1_SMP11_Pos)                /*!< 0x00000010 */
#define ADC_SMPR1_SMP11_2         (0x4U << ADC_SMPR1_SMP11_Pos)                /*!< 0x00000020 */
#define ADC_SMPR1_SMP12_Pos       (6U)
#define ADC_SMPR1_SMP12_Msk       (0x7U << ADC_SMPR1_SMP12_Pos)                /*!< 0x000001C0 */
#define ADC_SMPR1_SMP12           ADC_SMPR1_SMP12_Msk                          /*!<SMP12[2:0] bits (Channel 12 Sample time selection) */
#define ADC_SMPR1_SMP12_0         (0x1U << ADC_SMPR1_SMP12_Pos)                /*!< 0x00000040 */
#define ADC_SMPR1_SMP12_1         (0x2U << ADC_SMPR1_SMP12_Pos)                /*!< 0x00000080 */
#define ADC_SMPR1_SMP12_2         (0x4U << ADC_SMPR1_SMP12_Pos)                /*!< 0x00000100 */
#define ADC_SMPR1_SMP13_Pos       (9U)
#define ADC_SMPR1_SMP13_Msk       (0x7U << ADC_SMPR1_SMP13_Pos)                /*!< 0x00000E00 */
#define ADC_SMPR1_SMP13           ADC_SMPR1_SMP13_Msk                          /*!<SMP13[2:0] bits (Channel 13 Sample time selection) */
#define ADC_SMPR1_SMP13_0         (0x1U << ADC_SMPR1_SMP13_Pos)                /*!< 0x00000200 */
#define ADC_SMPR1_SMP13_1         (0x2U << ADC_SMPR1_SMP13_Pos)                /*!< 0x00000400 */
#define ADC_SMPR1_SMP13_2         (0x4U << ADC_SMPR1_SMP13_Pos)                /*!< 0x00000800 */
#define ADC_SMPR1_SMP14_Pos       (12U)
#define ADC_SMPR1_SMP14_Msk       (0x7U << ADC_SMPR1_SMP14_Pos)                /*!< 0x00007000 */
#define ADC_SMPR1_SMP14           ADC_SMPR1_SMP14_Msk                          /*!<SMP14[2:0] bits (Channel 14 Sample time selection) */
#define ADC_SMPR1_SMP14_0         (0x1U << ADC_SMPR1_SMP14_Pos)                /*!< 0x00001000 */
#define ADC_SMPR1_SMP14_1         (0x2U << ADC_SMPR1_SMP14_Pos)                /*!< 0x00002000 */
#define ADC_SMPR1_SMP14_2         (0x4U << ADC_SMPR1_SMP14_Pos)                /*!< 0x00004000 */
#define ADC_SMPR1_SMP15_Pos       (15U)
#define ADC_SMPR1_SMP15_Msk       (0x7U << ADC_SMPR1_SMP15_Pos)                /*!< 0x00038000 */
#define ADC_SMPR1_SMP15           ADC_SMPR1_SMP15_Msk                          /*!<SMP15[2:0] bits (Channel 15 Sample time selection) */
#define ADC_SMPR1_SMP15_0         (0x1U << ADC_SMPR1_SMP15_Pos)                /*!< 0x00008000 */
#define ADC_SMPR1_SMP15_1         (0x2U << ADC_SMPR1_SMP15_Pos)                /*!< 0x00010000 */
#define ADC_SMPR1_SMP15_2         (0x4U << ADC_SMPR1_SMP15_Pos)                /*!< 0x00020000 */
#define ADC_SMPR1_SMP16_Pos       (18U)
#define ADC_SMPR1_SMP16_Msk       (0x7U << ADC_SMPR1_SMP16_Pos)                /*!< 0x001C0000 */
#define ADC_SMPR1_SMP16           ADC_SMPR1_SMP16_Msk                          /*!<SMP16[2:0] bits (Channel 16 Sample time selection) */
#define ADC_SMPR1_SMP16_0         (0x1U << ADC_SMPR1_SMP16_Pos)                /*!< 0x00040000 */
#define ADC_SMPR1_SMP16_1         (0x2U << ADC_SMPR1_SMP16_Pos)                /*!< 0x00080000 */
#define ADC_SMPR1_SMP16_2         (0x4U << ADC_SMPR1_SMP16_Pos)                /*!< 0x00100000 */
#define ADC_SMPR1_SMP17_Pos       (21U)
#define ADC_SMPR1_SMP17_Msk       (0x7U << ADC_SMPR1_SMP17_Pos)                /*!< 0x00E00000 */
#define ADC_SMPR1_SMP17           ADC_SMPR1_SMP17_Msk                          /*!<SMP17[2:0] bits (Channel 17 Sample time selection) */
#define ADC_SMPR1_SMP17_0         (0x1U << ADC_SMPR1_SMP17_Pos)                /*!< 0x00200000 */
#define ADC_SMPR1_SMP17_1         (0x2U << ADC_SMPR1_SMP17_Pos)                /*!< 0x00400000 */
#define ADC_SMPR1_SMP17_2         (0x4U << ADC_SMPR1_SMP17_Pos)                /*!< 0x00800000 */
#define ADC_SMPR1_SMP18_Pos       (24U)
#define ADC_SMPR1_SMP18_Msk       (0x7U << ADC_SMPR1_SMP18_Pos)                /*!< 0x07000000 */
#define ADC_SMPR1_SMP18           ADC_SMPR1_SMP18_Msk                          /*!<SMP18[2:0] bits (Channel 18 Sample time selection) */
#define ADC_SMPR1_SMP18_0         (0x1U << ADC_SMPR1_SMP18_Pos)                /*!< 0x01000000 */
#define ADC_SMPR1_SMP18_1         (0x2U << ADC_SMPR1_SMP18_Pos)                /*!< 0x02000000 */
#define ADC_SMPR1_SMP18_2         (0x4U << ADC_SMPR1_SMP18_Pos)                /*!< 0x04000000 */

/******************  Bit definition for ADC_SMPR2 register  *******************/
#define ADC_SMPR2_SMP0_Pos        (0U)
#define ADC_SMPR2_SMP0_Msk        (0x7U << ADC_SMPR2_SMP0_Pos)                 /*!< 0x00000007 */
#define ADC_SMPR2_SMP0            ADC_SMPR2_SMP0_Msk                           /*!<SMP0[2:0] bits (Channel 0 Sample time selection) */
#define ADC_SMPR2_SMP0_0          (0x1U << ADC_SMPR2_SMP0_Pos)                 /*!< 0x00000001 */
#define ADC_SMPR2_SMP0_1          (0x2U << ADC_SMPR2_SMP0_Pos)                 /*!< 0x00000002 */
#define ADC_SMPR2_SMP0_2          (0x4U << ADC_SMPR2_SMP0_Pos)                 /*!< 0x00000004 */
#define ADC_SMPR2_SMP1_Pos        (3U)
#define ADC_SMPR2_SMP1_Msk        (0x7U << ADC_SMPR2_SMP1_Pos)                 /*!< 0x00000038 */
#define ADC_SMPR2_SMP1            ADC_SMPR2_SMP1_Msk                           /*!<SMP1[2:0] bits (Channel 1 Sample time selection) */
#define ADC_SMPR2_SMP1_0          (0x1U << ADC_SMPR2_SMP1_Pos)                 /*!< 0x00000008 */
#define ADC_SMPR2_SMP1_1          (0x2U << ADC_SMPR2_SMP1_Pos)                 /*!< 0x00000010 */
#define ADC_SMPR2_SMP1_2          (0x4U << ADC_SMPR2_SMP1_Pos)                 /*!< 0x00000020 */
#define ADC_SMPR2_SMP2_Pos        (6U)
#define ADC_SMPR2_SMP2_Msk        (0x7U << ADC_SMPR2_SMP2_Pos)                 /*!< 0x000001C0 */
#define ADC_SMPR2_SMP2            ADC_SMPR2_SMP2_Msk                           /*!<SMP2[2:0] bits (Channel 2 Sample time selection) */
#define ADC_SMPR2_SMP2_0          (0x1U << ADC_SMPR2_SMP2_Pos)                 /*!< 0x00000040 */
#define ADC_SMPR2_SMP2_1          (0x2U << ADC_SMPR2_SMP2_Pos)                 /*!< 0x00000080 */
#define ADC_SMPR2_SMP2_2          (0x4U << ADC_SMPR2_SMP2_Pos)                 /*!< 0x00000100 */
#define ADC_SMPR2_SMP3_Pos        (9U)
#define ADC_SMPR2_SMP3_Msk        (0x7U << ADC_SMPR2_SMP3_Pos)                 /*!< 0x00000E00 */
#define ADC_SMPR2_SMP3            ADC_SMPR2_SMP3_Msk                           /*!<SMP3[2:0] bits (Channel 3 Sample time selection) */
#define ADC_SMPR2_SMP3_0          (0x1U << ADC_SMPR2_SMP3_Pos)                 /*!< 0x00000200 */
#define ADC_SMPR2_SMP3_1          (0x2U << ADC_SMPR2_SMP3_Pos)                 /*!< 0x00000400 */
#define ADC_SMPR2_SMP3_2          (0x4U << ADC_SMPR2_SMP3_Pos)                 /*!< 0x00000800 */
#define ADC_SMPR2_SMP4_Pos        (12U)
#define ADC_SMPR2_SMP4_Msk        (0x7U << ADC_SMPR2_SMP4_Pos)                 /*!< 0x00007000 */
#define ADC_SMPR2_SMP4            ADC_SMPR2_SMP4_Msk                           /*!<SMP4[2:0] bits (Channel 4 Sample time selection) */
#define ADC_SMPR2_SMP4_0          (0x1U << ADC_SMPR2_SMP4_Pos)                 /*!< 0x00001000 */
#define ADC_SMPR2_SMP4_1          (0x2U << ADC_SMPR2_SMP4_Pos)                 /*!< 0x00002000 */
#define ADC_SMPR2_SMP4_2          (0x4U << ADC_SMPR2_SMP4_Pos)                 /*!< 0x00004000 */
#define ADC_SMPR2_SMP5_Pos        (15U)
#define ADC_SMPR2_SMP5_Msk        (0x7U << ADC_SMPR2_SMP5_Pos)                 /*!< 0x00038000 */
#define ADC_SMPR2_SMP5            ADC_SMPR2_SMP5_Msk                           /*!<SMP5[2:0] bits (Channel 5 Sample time selection) */
#define ADC_SMPR2_SMP5_0          (0x1U << ADC_SMPR2_SMP5_Pos)                 /*!< 0x00008000 */
#define ADC_SMPR2_SMP5_1          (0x2U << ADC_SMPR2_SMP5_Pos)                 /*!< 0x00010000 */
#define ADC_SMPR2_SMP5_2          (0x4U << ADC_SMPR2_SMP5_Pos)                 /*!< 0x00020000 */
#define ADC_SMPR2_SMP6_Pos        (18U)
#define ADC_SMPR2_SMP6_Msk        (0x7U << ADC_SMPR2_SMP6_Pos)                 /*!< 0x001C0000 */
#define ADC_SMPR2_SMP6            ADC_SMPR2_SMP6_Msk                           /*!<SMP6[2:0] bits (Channel 6 Sample time selection) */
#define ADC_SMPR2_SMP6_0          (0x1U << ADC_SMPR2_SMP6_Pos)                 /*!< 0x00040000 */
#define ADC_SMPR2_SMP6_1          (0x2U << ADC_SMPR2_SMP6_Pos)                 /*!< 0x00080000 */
#define ADC_SMPR2_SMP6_2          (0x4U << ADC_SMPR2_SMP6_Pos)                 /*!< 0x00100000 */
#define ADC_SMPR2_SMP7_Pos        (21U)
#define ADC_SMPR2_SMP7_Msk        (0x7U << ADC_SMPR2_SMP7_Pos)                 /*!< 0x00E00000 */
#define ADC_SMPR2_SMP7            ADC_SMPR2_SMP7_Msk                           /*!<SMP7[2:0] bits (Channel 7 Sample time selection) */
#define ADC_SMPR2_SMP7_0          (0x1U << ADC_SMPR2_SMP7_Pos)                 /*!< 0x00200000 */
#define ADC_SMPR2_SMP7_1          (0x2U << ADC_SMPR2_SMP7_Pos)                 /*!< 0x00400000 */
#define ADC_SMPR2_SMP7_2          (0x4U << ADC_SMPR2_SMP7_Pos)                 /*!< 0x00800000 */
#define ADC_SMPR2_SMP8_Pos        (24U)
#define ADC_SMPR2_SMP8_Msk        (0x7U << ADC_SMPR2_SMP8_Pos)                 /*!< 0x07000000 */
#define ADC_SMPR2_SMP8            ADC_SMPR2_SMP8_Msk                           /*!<SMP8[2:0] bits (Channel 8 Sample time selection) */
#define ADC_SMPR2_SMP8_0          (0x1U << ADC_SMPR2_SMP8_Pos)                 /*!< 0x01000000 */
#define ADC_SMPR2_SMP8_1          (0x2U << ADC_SMPR2_SMP8_Pos)                 /*!< 0x02000000 */
#define ADC_SMPR2_SMP8_2          (0x4U << ADC_SMPR2_SMP8_Pos)                 /*!< 0x04000000 */
#define ADC_SMPR2_SMP9_Pos        (27U)
#define ADC_SMPR2_SMP9_Msk        (0x7U << ADC_SMPR2_SMP9_Pos)                 /*!< 0x38000000 */
#define ADC_SMPR2_SMP9            ADC_SMPR2_SMP9_Msk                           /*!<SMP9[2:0] bits (Channel 9 Sample time selection) */
#define ADC_SMPR2_SMP9_0          (0x1U << ADC_SMPR2_SMP9_Pos)                 /*!< 0x08000000 */
#define ADC_SMPR2_SMP9_1          (0x2U << ADC_SMPR2_SMP9_Pos)                 /*!< 0x10000000 */
#define ADC_SMPR2_SMP9_2          (0x4U << ADC_SMPR2_SMP9_Pos)                 /*!< 0x20000000 */

/******************  Bit definition for ADC_JOFR1 register  *******************/
#define ADC_JOFR1_JOFFSET1_Pos    (0U)
#define ADC_JOFR1_JOFFSET1_Msk    (0xFFFU << ADC_JOFR1_JOFFSET1_Pos)           /*!< 0x00000FFF */
#define ADC_JOFR1_JOFFSET1        ADC_JOFR1_JOFFSET1_Msk                       /*!<Data offset for injected channel 1 */

/******************  Bit definition for ADC_JOFR2 register  *******************/
#define ADC_JOFR2_JOFFSET2_Pos    (0U)
#define ADC_JOFR2_JOFFSET2_Msk    (0xFFFU << ADC_JOFR2_JOFFSET2_Pos)           /*!< 0x00000FFF */
#define ADC_JOFR2_JOFFSET2        ADC_JOFR2_JOFFSET2_Msk                       /*!<Data offset for injected channel 2 */

/******************  Bit definition for ADC_JOFR3 register  *******************/
#define ADC_JOFR3_JOFFSET3_Pos    (0U)
#define ADC_JOFR3_JOFFSET3_Msk    (0xFFFU << ADC_JOFR3_JOFFSET3_Pos)           /*!< 0x00000FFF */
#define ADC_JOFR3_JOFFSET3        ADC_JOFR3_JOFFSET3_Msk                       /*!<Data offset for injected channel 3 */

/******************  Bit definition for ADC_JOFR4 register  *******************/
#define ADC_JOFR4_JOFFSET4_Pos    (0U)
#define ADC_JOFR4_JOFFSET4_Msk    (0xFFFU << ADC_JOFR4_JOFFSET4_Pos)           /*!< 0x00000FFF */
#define ADC_JOFR4_JOFFSET4        ADC_JOFR4_JOFFSET4_Msk                       /*!<Data offset for injected channel 4 */

/*******************  Bit definition for ADC_HTR register  ********************/
#define ADC_HTR_HT_Pos            (0U)
#define ADC_HTR_HT_Msk            (0xFFFU << ADC_HTR_HT_Pos)                   /*!< 0x00000FFF */
#define ADC_HTR_HT                ADC_HTR_HT_Msk                               /*!<Analog watchdog high threshold */

/*******************  Bit definition for ADC_LTR register  ********************/
#define ADC_LTR_LT_Pos            (0U)
#define ADC_LTR_LT_Msk            (0xFFFU << ADC_LTR_LT_Pos)                   /*!< 0x00000FFF */
#define ADC_LTR_LT                ADC_LTR_LT_Msk                               /*!<Analog watchdog low threshold */

/*******************  Bit definition for ADC_SQR1 register  *******************/
#define ADC_SQR1_SQ13_Pos         (0U)
#define ADC_SQR1_SQ13_Msk         (0x1FU << ADC_SQR1_SQ13_Pos)                 /*!< 0x0000001F */
#define ADC_SQR1_SQ13             ADC_SQR1_SQ13_Msk                            /*!<SQ13[4:0] bits (13th conversion in regular sequence) */
#define ADC_SQR1_SQ13_0           (0x01U << ADC_SQR1_SQ13_Pos)                 /*!< 0x00000001 */
#define ADC_SQR1_SQ13_1           (0x02U << ADC_SQR1_SQ13_Pos)                 /*!< 0x00000002 */
#define ADC_SQR1_SQ13_2           (0x04U << ADC_SQR1_SQ13_Pos)                 /*!< 0x00000004 */
#define ADC_SQR1_SQ13_3           (0x08U << ADC_SQR1_SQ13_Pos)                 /*!< 0x00000008 */
#define ADC_SQR1_SQ13_4           (0x10U << ADC_SQR1_SQ13_Pos)                 /*!< 0x00000010 */
#define ADC_SQR1_SQ14_Pos         (5U)
#define ADC_SQR1_SQ14_Msk         (0x1FU << ADC_SQR1_SQ14_Pos)                 /*!< 0x000003E0 */
#define ADC_SQR1_SQ14             ADC_SQR1_SQ14_Msk                            /*!<SQ14[4:0] bits (14th conversion in regular sequence) */
#define ADC_SQR1_SQ14_0           (0x01U << ADC_SQR1_SQ14_Pos)                 /*!< 0x00000020 */
#define ADC_SQR1_SQ14_1           (0x02U << ADC_SQR1_SQ14_Pos)                 /*!< 0x00000040 */
#define ADC_SQR1_SQ14_2           (0x04U << ADC_SQR1_SQ14_Pos)                 /*!< 0x00000080 */
#define ADC_SQR1_SQ14_3           (0x08U << ADC_SQR1_SQ14_Pos)                 /*!< 0x00000100 */
#define ADC_SQR1_SQ14_4           (0x10U << ADC_SQR1_SQ14_Pos)                 /*!< 0x00000200 */
#define ADC_SQR1_SQ15_Pos         (10U)
#define ADC_SQR1_SQ15_Msk         (0x1FU << ADC_SQR1_SQ15_Pos)                 /*!< 0x00007C00 */
#define ADC_SQR1_SQ15             ADC_SQR1_SQ15_Msk                            /*!<SQ15[4:0] bits (15th conversion in regular sequence) */
#define ADC_SQR1_SQ15_0           (0x01U << ADC_SQR1_SQ15_Pos)                 /*!< 0x00000400 */
#define ADC_SQR1_SQ15_1           (0x02U << ADC_SQR1_SQ15_Pos)                 /*!< 0x00000800 */
#define ADC_SQR1_SQ15_2           (0x04U << ADC_SQR1_SQ15_Pos)                 /*!< 0x00001000 */
#define ADC_SQR1_SQ15_3           (0x08U << ADC_SQR1_SQ15_Pos)                 /*!< 0x00002000 */
#define ADC_SQR1_SQ15_4           (0x10U << ADC_SQR1_SQ15_Pos)                 /*!< 0x00004000 */
#define ADC_SQR1_SQ16_Pos         (15U)
#define ADC_SQR1_SQ16_Msk         (0x1FU << ADC_SQR1_SQ16_Pos)                 /*!< 0x000F8000 */
#define ADC_SQR1_SQ16             ADC_SQR1_SQ16_Msk                            /*!<SQ16[4:0] bits (16th conversion in regular sequence) */
#define ADC_SQR1_SQ16_0           (0x01U << ADC_SQR1_SQ16_Pos)                 /*!< 0x00008000 */
#define ADC_SQR1_SQ16_1           (0x02U << ADC_SQR1_SQ16_Pos)                 /*!< 0x00010000 */
#define ADC_SQR1_SQ16_2           (0x04U << ADC_SQR1_SQ16_Pos)                 /*!< 0x00020000 */
#define ADC_SQR1_SQ16_3           (0x08U << ADC_SQR1_SQ16_Pos)                 /*!< 0x00040000 */
#define ADC_SQR1_SQ16_4           (0x10U << ADC_SQR1_SQ16_Pos)                 /*!< 0x00080000 */
#define ADC_SQR1_L_Pos            (20U)
#define ADC_SQR1_L_Msk            (0xFU << ADC_SQR1_L_Pos)                     /*!< 0x00F00000 */
#define ADC_SQR1_L                ADC_SQR1_L_Msk                               /*!<L[3:0] bits (Regular channel sequence length) */
#define ADC_SQR1_L_0              (0x1U << ADC_SQR1_L_Pos)                     /*!< 0x00100000 */
#define ADC_SQR1_L_1              (0x2U << ADC_SQR1_L_Pos)                     /*!< 0x00200000 */
#define ADC_SQR1_L_2              (0x4U << ADC_SQR1_L_Pos)                     /*!< 0x00400000 */
#define ADC_SQR1_L_3              (0x8U << ADC_SQR1_L_Pos)                     /*!< 0x00800000 */

/*******************  Bit definition for ADC_SQR2 register  *******************/
#define ADC_SQR2_SQ7_Pos          (0U)
#define ADC_SQR2_SQ7_Msk          (0x1FU << ADC_SQR2_SQ7_Pos)                  /*!< 0x0000001F */
#define ADC_SQR2_SQ7              ADC_SQR2_SQ7_Msk                             /*!<SQ7[4:0] bits (7th conversion in regular sequence) */
#define ADC_SQR2_SQ7_0            (0x01U << ADC_SQR2_SQ7_Pos)                  /*!< 0x00000001 */
#define ADC_SQR2_SQ7_1            (0x02U << ADC_SQR2_SQ7_Pos)                  /*!< 0x00000002 */
#define ADC_SQR2_SQ7_2            (0x04U << ADC_SQR2_SQ7_Pos)                  /*!< 0x00000004 */
#define ADC_SQR2_SQ7_3            (0x08U << ADC_SQR2_SQ7_Pos)                  /*!< 0x00000008 */
#define ADC_SQR2_SQ7_4            (0x10U << ADC_SQR2_SQ7_Pos)                  /*!< 0x00000010 */
#define ADC_SQR2_SQ8_Pos          (5U)
#define ADC_SQR2_SQ8_Msk          (0x1FU << ADC_SQR2_SQ8_Pos)                  /*!< 0x000003E0 */
#define ADC_SQR2_SQ8              ADC_SQR2_SQ8_Msk                             /*!<SQ8[4:0] bits (8th conversion in regular sequence) */
#define ADC_SQR2_SQ8_0            (0x01U << ADC_SQR2_SQ8_Pos)                  /*!< 0x00000020 */
#define ADC_SQR2_SQ8_1            (0x02U << ADC_SQR2_SQ8_Pos)                  /*!< 0x00000040 */
#define ADC_SQR2_SQ8_2            (0x04U << ADC_SQR2_SQ8_Pos)                  /*!< 0x00000080 */
#define ADC_SQR2_SQ8_3            (0x08U << ADC_SQR2_SQ8_Pos)                  /*!< 0x00000100 */
#define ADC_SQR2_SQ8_4            (0x10U << ADC_SQR2_SQ8_Pos)                  /*!< 0x00000200 */
#define ADC_SQR2_SQ9_Pos          (10U)
#define ADC_SQR2_SQ9_Msk          (0x1FU << ADC_SQR2_SQ9_Pos)                  /*!< 0x00007C00 */
#define ADC_SQR2_SQ9              ADC_SQR2_SQ9_Msk                             /*!<SQ9[4:0] bits (9th conversion in regular sequence) */
#define ADC_SQR2_SQ9_0            (0x01U << ADC_SQR2_SQ9_Pos)                  /*!< 0x00000400 */
#define ADC_SQR2_SQ9_1            (0x02U << ADC_SQR2_SQ9_Pos)                  /*!< 0x00000800 */
#define ADC_SQR2_SQ9_2            (0x04U << ADC_SQR2_SQ9_Pos)                  /*!< 0x00001000 */
#define ADC_SQR2_SQ9_3            (0x08U << ADC_SQR2_SQ9_Pos)                  /*!< 0x00002000 */
#define ADC_SQR2_SQ9_4            (0x10U << ADC_SQR2_SQ9_Pos)                  /*!< 0x00004000 */
#define ADC_SQR2_SQ10_Pos         (15U)
#define ADC_SQR2_SQ10_Msk         (0x1FU << ADC_SQR2_SQ10_Pos)                 /*!< 0x000F8000 */
#define ADC_SQR2_SQ10             ADC_SQR2_SQ10_Msk                            /*!<SQ10[4:0] bits (10th conversion in regular sequence) */
#define ADC_SQR2_SQ10_0           (0x01U << ADC_SQR2_SQ10_Pos)                 /*!< 0x00008000 */
#define ADC_SQR2_SQ10_1           (0x02U << ADC_SQR2_SQ10_Pos)                 /*!< 0x00010000 */
#define ADC_SQR2_SQ10_2           (0x04U << ADC_SQR2_SQ10_Pos)                 /*!< 0x00020000 */
#define ADC_SQR2_SQ10_3           (0x08U << ADC_SQR2_SQ10_Pos)                 /*!< 0x00040000 */
#define ADC_SQR2_SQ10_4           (0x10U << ADC_SQR2_SQ10_Pos)                 /*!< 0x00080000 */
#define ADC_SQR2_SQ11_Pos         (20U)
#define ADC_SQR2_SQ11_Msk         (0x1FU << ADC_SQR2_SQ11_Pos)                 /*!< 0x01F00000 */
#define ADC_SQR2_SQ11             ADC_SQR2_SQ11_Msk                            /*!<SQ11[4:0] bits (11th conversion in regular sequence) */
#define ADC_SQR2_SQ11_0           (0x01U << ADC_SQR2_SQ11_Pos)                 /*!< 0x00100000 */
#define ADC_SQR2_SQ11_1           (0x02U << ADC_SQR2_SQ11_Pos)                 /*!< 0x00200000 */
#define ADC_SQR2_SQ11_2           (0x04U << ADC_SQR2_SQ11_Pos)                 /*!< 0x00400000 */
#define ADC_SQR2_SQ11_3           (0x08U << ADC_SQR2_SQ11_Pos)                 /*!< 0x00800000 */
#define ADC_SQR2_SQ11_4           (0x10U << ADC_SQR2_SQ11_Pos)                 /*!< 0x01000000 */
#define ADC_SQR2_SQ12_Pos         (25U)
#define ADC_SQR2_SQ12_Msk         (0x1FU << ADC_SQR2_SQ12_Pos)                 /*!< 0x3E000000 */
#define ADC_SQR2_SQ12             ADC_SQR2_SQ12_Msk                            /*!<SQ12[4:0] bits (12th conversion in regular sequence) */
#define ADC_SQR2_SQ12_0           (0x01U << ADC_SQR2_SQ12_Pos)                 /*!< 0x02000000 */
#define ADC_SQR2_SQ12_1           (0x02U << ADC_SQR2_SQ12_Pos)                 /*!< 0x04000000 */
#define ADC_SQR2_SQ12_2           (0x04U << ADC_SQR2_SQ12_Pos)                 /*!< 0x08000000 */
#define ADC_SQR2_SQ12_3           (0x08U << ADC_SQR2_SQ12_Pos)                 /*!< 0x10000000 */
#define ADC_SQR2_SQ12_4           (0x10U << ADC_SQR2_SQ12_Pos)                 /*!< 0x20000000 */

/*******************  Bit definition for ADC_SQR3 register  *******************/
#define ADC_SQR3_SQ1_Pos          (0U)
#define ADC_SQR3_SQ1_Msk          (0x1FU << ADC_SQR3_SQ1_Pos)                  /*!< 0x0000001F */
#define ADC_SQR3_SQ1              ADC_SQR3_SQ1_Msk                             /*!<SQ1[4:0] bits (1st conversion in regular sequence) */
#define ADC_SQR3_SQ1_0            (0x01U << ADC_SQR3_SQ1_Pos)                  /*!< 0x00000001 */
#define ADC_SQR3_SQ1_1            (0x02U << ADC_SQR3_SQ1_Pos)                  /*!< 0x00000002 */
#define ADC_SQR3_SQ1_2            (0x04U << ADC_SQR3_SQ1_Pos)                  /*!< 0x00000004 */
#define ADC_SQR3_SQ1_3            (0x08U << ADC_SQR3_SQ1_Pos)                  /*!< 0x00000008 */
#define ADC_SQR3_SQ1_4            (0x10U << ADC_SQR3_SQ1_Pos)                  /*!< 0x00000010 */
#define ADC_SQR3_SQ2_Pos          (5U)
#define ADC_SQR3_SQ2_Msk          (0x1FU << ADC_SQR3_SQ2_Pos)                  /*!< 0x000003E0 */
#define ADC_SQR3_SQ2              ADC_SQR3_SQ2_Msk                             /*!<SQ2[4:0] bits (2nd conversion in regular sequence) */
#define ADC_SQR3_SQ2_0            (0x01U << ADC_SQR3_SQ2_Pos)                  /*!< 0x00000020 */
#define ADC_SQR3_SQ2_1            (0x02U << ADC_SQR3_SQ2_Pos)                  /*!< 0x00000040 */
#define ADC_SQR3_SQ2_2            (0x04U << ADC_SQR3_SQ2_Pos)                  /*!< 0x00000080 */
#define ADC_SQR3_SQ2_3            (0x08U << ADC_SQR3_SQ2_Pos)                  /*!< 0x00000100 */
#define ADC_SQR3_SQ2_4            (0x10U << ADC_SQR3_SQ2_Pos)                  /*!< 0x00000200 */
#define ADC_SQR3_SQ3_Pos          (10U)
#define ADC_SQR3_SQ3_Msk          (0x1FU << ADC_SQR3_SQ3_Pos)                  /*!< 0x00007C00 */
#define ADC_SQR3_SQ3              ADC_SQR3_SQ3_Msk                             /*!<SQ3[4:0] bits (3rd conversion in regular sequence) */
#define ADC_SQR3_SQ3_0            (0x01U << ADC_SQR3_SQ3_Pos)                  /*!< 0x00000400 */
#define ADC_SQR3_SQ3_1            (0x02U << ADC_SQR3_SQ3_Pos)                  /*!< 0x00000800 */
#define ADC_SQR3_SQ3_2            (0x04U << ADC_SQR3_SQ3_Pos)                  /*!< 0x00001000 */
#define ADC_SQR3_SQ3_3            (0x08U << ADC_SQR3_SQ3_Pos)                  /*!< 0x00002000 */
#define ADC_SQR3_SQ3_4            (0x10U << ADC_SQR3_SQ3_Pos)                  /*!< 0x00004000 */
#define ADC_SQR3_SQ4_Pos          (15U)
#define ADC_SQR3_SQ4_Msk          (0x1FU << ADC_SQR3_SQ4_Pos)                  /*!< 0x000F8000 */
#define ADC_SQR3_SQ4              ADC_SQR3_SQ4_Msk                             /*!<SQ4[4:0] bits (4th conversion in regular sequence) */
#define ADC_SQR3_SQ4_0            (0x01U << ADC_SQR3_SQ4_Pos)                  /*!< 0x00008000 */
#define ADC_SQR3_SQ4_1            (0x02U << ADC_SQR3_SQ4_Pos)                  /*!< 0x00010000 */
#define ADC_SQR3_SQ4_2            (0x04U << ADC_SQR3_SQ4_Pos)                  /*!< 0x00020000 */
#define ADC_SQR3_SQ4_3            (0x08U << ADC_SQR3_SQ4_Pos)                  /*!< 0x00040000 */
#define ADC_SQR3_SQ4_4            (0x10U << ADC_SQR3_SQ4_Pos)                  /*!< 0x00080000 */
#define ADC_SQR3_SQ5_Pos          (20U)
#define ADC_SQR3_SQ5_Msk          (0x1FU << ADC_SQR3_SQ5_Pos)                  /*!< 0x01F00000 */
#define ADC_SQR3_SQ5              ADC_SQR3_SQ5_Msk                             /*!<SQ5[4:0] bits (5th conversion in regular sequence) */
#define ADC_SQR3_SQ5_0            (0x01U << ADC_SQR3_SQ5_Pos)                  /*!< 0x00100000 */
#define ADC_SQR3_SQ5_1            (0x02U << ADC_SQR3_SQ5_Pos)                  /*!< 0x00200000 */
#define ADC_SQR3_SQ5_2            (0x04U << ADC_SQR3_SQ5_Pos)                  /*!< 0x00400000 */
#define ADC_SQR3_SQ5_3            (0x08U << ADC_SQR3_SQ5_Pos)                  /*!< 0x00800000 */
#define ADC_SQR3_SQ5_4            (0x10U << ADC_SQR3_SQ5_Pos)                  /*!< 0x01000000 */
#define ADC_SQR3_SQ6_Pos          (25U)
#define ADC_SQR3_SQ6_Msk          (0x1FU << ADC_SQR3_SQ6_Pos)                  /*!< 0x3E000000 */
#define ADC_SQR3_SQ6              ADC_SQR3_SQ6_Msk                             /*!<SQ6[4:0] bits (6th conversion in regular sequence) */
#define ADC_SQR3_SQ6_0            (0x01U << ADC_SQR3_SQ6_Pos)                  /*!< 0x02000000 */
#define ADC_SQR3_SQ6_1            (0x02U << ADC_SQR3_SQ6_Pos)                  /*!< 0x04000000 */
#define ADC_SQR3_SQ6_2            (0x04U << ADC_SQR3_SQ6_Pos)                  /*!< 0x08000000 */
#define ADC_SQR3_SQ6_3            (0x08U << ADC_SQR3_SQ6_Pos)                  /*!< 0x10000000 */
#define ADC_SQR3_SQ6_4            (0x10U << ADC_SQR3_SQ6_Pos)                  /*!< 0x20000000 */

/*******************  Bit definition for ADC_JSQR register  *******************/
#define ADC_JSQR_JSQ1_Pos         (0U)
#define ADC_JSQR_JSQ1_Msk         (0x1FU << ADC_JSQR_JSQ1_Pos)                 /*!< 0x0000001F */
#define ADC_JSQR_JSQ1             ADC_JSQR_JSQ1_Msk                            /*!<JSQ1[4:0] bits (1st conversion in injected sequence) */
#define ADC_JSQR_JSQ1_0           (0x01U << ADC_JSQR_JSQ1_Pos)                 /*!< 0x00000001 */
#define ADC_JSQR_JSQ1_1           (0x02U << ADC_JSQR_JSQ1_Pos)                 /*!< 0x00000002 */
#define ADC_JSQR_JSQ1_2           (0x04U << ADC_JSQR_JSQ1_Pos)                 /*!< 0x00000004 */
#define ADC_JSQR_JSQ1_3           (0x08U << ADC_JSQR_JSQ1_Pos)                 /*!< 0x00000008 */
#define ADC_JSQR_JSQ1_4           (0x10U << ADC_JSQR_JSQ1_Pos)                 /*!< 0x00000010 */
#define ADC_JSQR_JSQ2_Pos         (5U)
#define ADC_JSQR_JSQ2_Msk         (0x1FU << ADC_JSQR_JSQ2_Pos)                 /*!< 0x000003E0 */
#define ADC_JSQR_JSQ2             ADC_JSQR_JSQ2_Msk                            /*!<JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define ADC_JSQR_JSQ2_0           (0x01U << ADC_JSQR_JSQ2_Pos)                 /*!< 0x00000020 */
#define ADC_JSQR_JSQ2_1           (0x02U << ADC_JSQR_JSQ2_Pos)                 /*!< 0x00000040 */
#define ADC_JSQR_JSQ2_2           (0x04U << ADC_JSQR_JSQ2_Pos)                 /*!< 0x00000080 */
#define ADC_JSQR_JSQ2_3           (0x08U << ADC_JSQR_JSQ2_Pos)                 /*!< 0x00000100 */
#define ADC_JSQR_JSQ2_4           (0x10U << ADC_JSQR_JSQ2_Pos)                 /*!< 0x00000200 */
#define ADC_JSQR_JSQ3_Pos         (10U)
#define ADC_JSQR_JSQ3_Msk         (0x1FU << ADC_JSQR_JSQ3_Pos)                 /*!< 0x00007C00 */
#define ADC_JSQR_JSQ3             ADC_JSQR_JSQ3_Msk                            /*!<JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define ADC_JSQR_JSQ3_0           (0x01U << ADC_JSQR_JSQ3_Pos)                 /*!< 0x00000400 */
#define ADC_JSQR_JSQ3_1           (0x02U << ADC_JSQR_JSQ3_Pos)                 /*!< 0x00000800 */
#define ADC_JSQR_JSQ3_2           (0x04U << ADC_JSQR_JSQ3_Pos)                 /*!< 0x00001000 */
#define ADC_JSQR_JSQ3_3           (0x08U << ADC_JSQR_JSQ3_Pos)                 /*!< 0x00002000 */
#define ADC_JSQR_JSQ3_4           (0x10U << ADC_JSQR_JSQ3_Pos)                 /*!< 0x00004000 */
#define ADC_JSQR_JSQ4_Pos         (15U)
#define ADC_JSQR_JSQ4_Msk         (0x1FU << ADC_JSQR_JSQ4_Pos)                 /*!< 0x000F8000 */
#define ADC_JSQR_JSQ4             ADC_JSQR_JSQ4_Msk                            /*!<JSQ4[4:0] bits (4th conversion in injected sequence) */
#define ADC_JSQR_JSQ4_0           (0x01U << ADC_JSQR_JSQ4_Pos)                 /*!< 0x00008000 */
#define ADC_JSQR_JSQ4_1           (0x02U << ADC_JSQR_JSQ4_Pos)                 /*!< 0x00010000 */
#define ADC_JSQR_JSQ4_2           (0x04U << ADC_JSQR_JSQ4_Pos)                 /*!< 0x00020000 */
#define ADC_JSQR_JSQ4_3           (0x08U << ADC_JSQR_JSQ4_Pos)                 /*!< 0x00040000 */
#define ADC_JSQR_JSQ4_4           (0x10U << ADC_JSQR_JSQ4_Pos)                 /*!< 0x00080000 */
#define ADC_JSQR_JL_Pos           (20U)
#define ADC_JSQR_JL_Msk           (0x3U << ADC_JSQR_JL_Pos)                    /*!< 0x00300000 */
#define ADC_JSQR_JL               ADC_JSQR_JL_Msk                              /*!<JL[1:0] bits (Injected Sequence length) */
#define ADC_JSQR_JL_0             (0x1U << ADC_JSQR_JL_Pos)                    /*!< 0x00100000 */
#define ADC_JSQR_JL_1             (0x2U << ADC_JSQR_JL_Pos)                    /*!< 0x00200000 */

/*******************  Bit definition for ADC_JDR1 register  *******************/
#define ADC_JDR1_JDATA_Pos        (0U)
#define ADC_JDR1_JDATA_Msk        (0xFFFFU << ADC_JDR1_JDATA_Pos)              /*!< 0x0000FFFF */
#define ADC_JDR1_JDATA            ADC_JDR1_JDATA_Msk                           /*!<Injected data */

/*******************  Bit definition for ADC_JDR2 register  *******************/
#define ADC_JDR2_JDATA_Pos        (0U)
#define ADC_JDR2_JDATA_Msk        (0xFFFFU << ADC_JDR2_JDATA_Pos)              /*!< 0x0000FFFF */
#define ADC_JDR2_JDATA            ADC_JDR2_JDATA_Msk                           /*!<Injected data */

/*******************  Bit definition for ADC_JDR3 register  *******************/
#define ADC_JDR3_JDATA_Pos        (0U)
#define ADC_JDR3_JDATA_Msk        (0xFFFFU << ADC_JDR3_JDATA_Pos)              /*!< 0x0000FFFF */
#define ADC_JDR3_JDATA            ADC_JDR3_JDATA_Msk                           /*!<Injected data */

/*******************  Bit definition for ADC_JDR4 register  *******************/
#define ADC_JDR4_JDATA_Pos        (0U)
#define ADC_JDR4_JDATA_Msk        (0xFFFFU << ADC_JDR4_JDATA_Pos)              /*!< 0x0000FFFF */
#define ADC_JDR4_JDATA            ADC_JDR4_JDATA_Msk                           /*!<Injected data */

/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_DATA_Pos           (0U)
#define ADC_DR_DATA_Msk           (0xFFFFU << ADC_DR_DATA_Pos)                 /*!< 0x0000FFFF */
#define ADC_DR_DATA               ADC_DR_DATA_Msk                              /*!<Regular data */
#define ADC_DR_ADC2DATA_Pos       (16U)
#define ADC_DR_ADC2DATA_Msk       (0xFFFFU << ADC_DR_ADC2DATA_Pos)             /*!< 0xFFFF0000 */
#define ADC_DR_ADC2DATA           ADC_DR_ADC2DATA_Msk                          /*!<ADC2 data */

/*******************  Bit definition for ADC_CSR register  ********************/
#define ADC_CSR_AWD1_Pos          (0U)
#define ADC_CSR_AWD1_Msk          (0x1U << ADC_CSR_AWD1_Pos)                   /*!< 0x00000001 */
#define ADC_CSR_AWD1              ADC_CSR_AWD1_Msk                             /*!<ADC1 Analog watchdog flag */
#define ADC_CSR_EOC1_Pos          (1U)
#define ADC_CSR_EOC1_Msk          (0x1U << ADC_CSR_EOC1_Pos)                   /*!< 0x00000002 */
#define ADC_CSR_EOC1              ADC_CSR_EOC1_Msk                             /*!<ADC1 End of conversion */
#define ADC_CSR_JEOC1_Pos         (2U)
#define ADC_CSR_JEOC1_Msk         (0x1U << ADC_CSR_JEOC1_Pos)                  /*!< 0x00000004 */
#define ADC_CSR_JEOC1             ADC_CSR_JEOC1_Msk                            /*!<ADC1 Injected channel end of conversion */
#define ADC_CSR_JSTRT1_Pos        (3U)
#define ADC_CSR_JSTRT1_Msk        (0x1U << ADC_CSR_JSTRT1_Pos)                 /*!< 0x00000008 */
#define ADC_CSR_JSTRT1            ADC_CSR_JSTRT1_Msk                           /*!<ADC1 Injected channel Start flag */
#define ADC_CSR_STRT1_Pos         (4U)
#define ADC_CSR_STRT1_Msk         (0x1U << ADC_CSR_STRT1_Pos)                  /*!< 0x00000010 */
#define ADC_CSR_STRT1             ADC_CSR_STRT1_Msk                            /*!<ADC1 Regular channel Start flag */
#define ADC_CSR_OVR1_Pos          (5U)
#define ADC_CSR_OVR1_Msk          (0x1U << ADC_CSR_OVR1_Pos)                   /*!< 0x00000020 */
#define ADC_CSR_OVR1              ADC_CSR_OVR1_Msk                             /*!<ADC1 DMA overrun  flag */
#define ADC_CSR_AWD2_Pos          (8U)
#define ADC_CSR_AWD2_Msk          (0x1U << ADC_CSR_AWD2_Pos)                   /*!< 0x00000100 */
#define ADC_CSR_AWD2              ADC_CSR_AWD2_Msk                             /*!<ADC2 Analog watchdog flag */
#define ADC_CSR_EOC2_Pos          (9U)
#define ADC_CSR_EOC2_Msk          (0x1U << ADC_CSR_EOC2_Pos)                   /*!< 0x00000200 */
#define ADC_CSR_EOC2              ADC_CSR_EOC2_Msk                             /*!<ADC2 End of conversion */
#define ADC_CSR_JEOC2_Pos         (10U)
#define ADC_CSR_JEOC2_Msk         (0x1U << ADC_CSR_JEOC2_Pos)                  /*!< 0x00000400 */
#define ADC_CSR_JEOC2             ADC_CSR_JEOC2_Msk                            /*!<ADC2 Injected channel end of conversion */
#define ADC_CSR_JSTRT2_Pos        (11U)
#define ADC_CSR_JSTRT2_Msk        (0x1U << ADC_CSR_JSTRT2_Pos)                 /*!< 0x00000800 */
#define ADC_CSR_JSTRT2            ADC_CSR_JSTRT2_Msk                           /*!<ADC2 Injected channel Start flag */
#define ADC_CSR_STRT2_Pos         (12U)
#define ADC_CSR_STRT2_Msk         (0x1U << ADC_CSR_STRT2_Pos)                  /*!< 0x00001000 */
#define ADC_CSR_STRT2             ADC_CSR_STRT2_Msk                            /*!<ADC2 Regular channel Start flag */
#define ADC_CSR_OVR2_Pos          (13U)
#define ADC_CSR_OVR2_Msk          (0x1U << ADC_CSR_OVR2_Pos)                   /*!< 0x00002000 */
#define ADC_CSR_OVR2              ADC_CSR_OVR2_Msk                             /*!<ADC2 DMA overrun  flag */
#define ADC_CSR_AWD3_Pos          (16U)
#define ADC_CSR_AWD3_Msk          (0x1U << ADC_CSR_AWD3_Pos)                   /*!< 0x00010000 */
#define ADC_CSR_AWD3              ADC_CSR_AWD3_Msk                             /*!<ADC3 Analog watchdog flag */
#define ADC_CSR_EOC3_Pos          (17U)
#define ADC_CSR_EOC3_Msk          (0x1U << ADC_CSR_EOC3_Pos)                   /*!< 0x00020000 */
#define ADC_CSR_EOC3              ADC_CSR_EOC3_Msk                             /*!<ADC3 End of conversion */
#define ADC_CSR_JEOC3_Pos         (18U)
#define ADC_CSR_JEOC3_Msk         (0x1U << ADC_CSR_JEOC3_Pos)                  /*!< 0x00040000 */
#define ADC_CSR_JEOC3             ADC_CSR_JEOC3_Msk                            /*!<ADC3 Injected channel end of conversion */
#define ADC_CSR_JSTRT3_Pos        (19U)
#define ADC_CSR_JSTRT3_Msk        (0x1U << ADC_CSR_JSTRT3_Pos)                 /*!< 0x00080000 */
#define ADC_CSR_JSTRT3            ADC_CSR_JSTRT3_Msk                           /*!<ADC3 Injected channel Start flag */
#define ADC_CSR_STRT3_Pos         (20U)
#define ADC_CSR_STRT3_Msk         (0x1U << ADC_CSR_STRT3_Pos)                  /*!< 0x00100000 */
#define ADC_CSR_STRT3             ADC_CSR_STRT3_Msk                            /*!<ADC3 Regular channel Start flag */
#define ADC_CSR_OVR3_Pos          (21U)
#define ADC_CSR_OVR3_Msk          (0x1U << ADC_CSR_OVR3_Pos)                   /*!< 0x00200000 */
#define ADC_CSR_OVR3              ADC_CSR_OVR3_Msk                             /*!<ADC3 DMA overrun  flag */

/* Legacy defines */
#define  ADC_CSR_DOVR1                        ADC_CSR_OVR1
#define  ADC_CSR_DOVR2                        ADC_CSR_OVR2
#define  ADC_CSR_DOVR3                        ADC_CSR_OVR3

/*******************  Bit definition for ADC_CCR register  ********************/
#define ADC_CCR_MULTI_Pos         (0U)
#define ADC_CCR_MULTI_Msk         (0x1FU << ADC_CCR_MULTI_Pos)                 /*!< 0x0000001F */
#define ADC_CCR_MULTI             ADC_CCR_MULTI_Msk                            /*!<MULTI[4:0] bits (Multi-ADC mode selection) */
#define ADC_CCR_MULTI_0           (0x01U << ADC_CCR_MULTI_Pos)                 /*!< 0x00000001 */
#define ADC_CCR_MULTI_1           (0x02U << ADC_CCR_MULTI_Pos)                 /*!< 0x00000002 */
#define ADC_CCR_MULTI_2           (0x04U << ADC_CCR_MULTI_Pos)                 /*!< 0x00000004 */
#define ADC_CCR_MULTI_3           (0x08U << ADC_CCR_MULTI_Pos)                 /*!< 0x00000008 */
#define ADC_CCR_MULTI_4           (0x10U << ADC_CCR_MULTI_Pos)                 /*!< 0x00000010 */
#define ADC_CCR_DELAY_Pos         (8U)
#define ADC_CCR_DELAY_Msk         (0xFU << ADC_CCR_DELAY_Pos)                  /*!< 0x00000F00 */
#define ADC_CCR_DELAY             ADC_CCR_DELAY_Msk                            /*!<DELAY[3:0] bits (Delay between 2 sampling phases) */
#define ADC_CCR_DELAY_0           (0x1U << ADC_CCR_DELAY_Pos)                  /*!< 0x00000100 */
#define ADC_CCR_DELAY_1           (0x2U << ADC_CCR_DELAY_Pos)                  /*!< 0x00000200 */
#define ADC_CCR_DELAY_2           (0x4U << ADC_CCR_DELAY_Pos)                  /*!< 0x00000400 */
#define ADC_CCR_DELAY_3           (0x8U << ADC_CCR_DELAY_Pos)                  /*!< 0x00000800 */
#define ADC_CCR_DDS_Pos           (13U)
#define ADC_CCR_DDS_Msk           (0x1U << ADC_CCR_DDS_Pos)                    /*!< 0x00002000 */
#define ADC_CCR_DDS               ADC_CCR_DDS_Msk                              /*!<DMA disable selection (Multi-ADC mode) */
#define ADC_CCR_DMA_Pos           (14U)
#define ADC_CCR_DMA_Msk           (0x3U << ADC_CCR_DMA_Pos)                    /*!< 0x0000C000 */
#define ADC_CCR_DMA               ADC_CCR_DMA_Msk                              /*!<DMA[1:0] bits (Direct Memory Access mode for multimode) */
#define ADC_CCR_DMA_0             (0x1U << ADC_CCR_DMA_Pos)                    /*!< 0x00004000 */
#define ADC_CCR_DMA_1             (0x2U << ADC_CCR_DMA_Pos)                    /*!< 0x00008000 */
#define ADC_CCR_ADCPRE_Pos        (16U)
#define ADC_CCR_ADCPRE_Msk        (0x3U << ADC_CCR_ADCPRE_Pos)                 /*!< 0x00030000 */
#define ADC_CCR_ADCPRE            ADC_CCR_ADCPRE_Msk                           /*!<ADCPRE[1:0] bits (ADC prescaler) */
#define ADC_CCR_ADCPRE_0          (0x1U << ADC_CCR_ADCPRE_Pos)                 /*!< 0x00010000 */
#define ADC_CCR_ADCPRE_1          (0x2U << ADC_CCR_ADCPRE_Pos)                 /*!< 0x00020000 */
#define ADC_CCR_VBATE_Pos         (22U)
#define ADC_CCR_VBATE_Msk         (0x1U << ADC_CCR_VBATE_Pos)                  /*!< 0x00400000 */
#define ADC_CCR_VBATE             ADC_CCR_VBATE_Msk                            /*!<VBAT Enable */
#define ADC_CCR_TSVREFE_Pos       (23U)
#define ADC_CCR_TSVREFE_Msk       (0x1U << ADC_CCR_TSVREFE_Pos)                /*!< 0x00800000 */
#define ADC_CCR_TSVREFE           ADC_CCR_TSVREFE_Msk                          /*!<Temperature Sensor and VREFINT Enable */

/*******************  Bit definition for ADC_CDR register  ********************/
#define ADC_CDR_DATA1_Pos         (0U)
#define ADC_CDR_DATA1_Msk         (0xFFFFU << ADC_CDR_DATA1_Pos)               /*!< 0x0000FFFF */
#define ADC_CDR_DATA1             ADC_CDR_DATA1_Msk                            /*!<1st data of a pair of regular conversions */
#define ADC_CDR_DATA2_Pos         (16U)
#define ADC_CDR_DATA2_Msk         (0xFFFFU << ADC_CDR_DATA2_Pos)               /*!< 0xFFFF0000 */
#define ADC_CDR_DATA2             ADC_CDR_DATA2_Msk                            /*!<2nd data of a pair of regular conversions */

/* Legacy defines */
#define ADC_CDR_RDATA_MST         ADC_CDR_DATA1
#define ADC_CDR_RDATA_SLV         ADC_CDR_DATA2

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   ADC sample data type.
 */
typedef uint16_t adcsample_t;

/**
 * @brief   Channels number in a conversion group.
 */
typedef uint16_t adc_channels_num_t;

/**
 * @brief   Type of an ADC error mask.
 */
typedef uint32_t adcerror_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Low level fields of the ADC driver structure.
 */
#define adc_lld_driver_fields                                               \
  /* Pointer to the ADCx registers block.*/                                 \
  ADC_TypeDef               *adc;                                           \
  /* Pointer to associated DMA channel.*/                                   \
  const stm32_dma_stream_t  *dmastp;                                        \
  /* DMA mode bit mask.*/                                                   \
  uint32_t                  dmamode

/**
 * @brief   Low level fields of the ADC configuration structure.
 */
#define adc_lld_config_fields                                               \
  /* Dummy configuration, it is not needed.*/                               \
  uint32_t                  dummy

/**
 * @brief   Low level fields of the ADC configuration structure.
 */
#define adc_lld_configuration_group_fields                                  \
  /* ADC CR1 register initialization data.                                  \
     NOTE: All the required bits must be defined into this field except     \
           @p ADC_CR1_SCAN that is enforced inside the driver.*/            \
  uint32_t                  cr1;                                            \
  /* ADC CR2 register initialization data.                                  \
     NOTE: All the required bits must be defined into this field except     \
           @p ADC_CR2_DMA, @p ADC_CR2_CONT and @p ADC_CR2_ADON that are     \
           enforced inside the driver.*/                                    \
  uint32_t                  cr2;                                            \
  /* ADC SMPR1 register initialization data.                                \
     NOTE: In this field must be specified the sample times for channels    \
           10...18.*/                                                       \
  uint32_t                  smpr1;                                          \
  /* ADC SMPR2 register initialization data.                                \
     NOTE: In this field must be specified the sample times for channels    \
           0...9.*/                                                         \
  uint32_t                  smpr2;                                          \
  /* ADC watchdog high threshold register.                                  \
     NOTE: This field defines the high threshold of the analog watchdog.*/  \
  uint16_t                  htr;                                            \
  /* ADC watchdog low threshold register.                                   \
     NOTE: This field defines the low threshold of the analog watchdog.*/   \
  uint16_t                  ltr;                                            \
  /* ADC SQR1 register initialization data.                                 \
     NOTE: Conversion group sequence 13...16 + sequence length.*/           \
  uint32_t                  sqr1;                                           \
  /* ADC SQR2 register initialization data.                                 \
     NOTE: Conversion group sequence 7...12.*/                              \
  uint32_t                  sqr2;                                           \
  /* ADC SQR3 register initialization data.                                 \
     NOTE: Conversion group sequence 1...6.*/                               \
  uint32_t                  sqr3

/**
 * @name    Sequences building helper macros
 * @{
 */
/**
 * @brief   Number of channels in a conversion sequence.
 */
#define ADC_SQR1_NUM_CH(n)      (((n) - 1) << 20)

#define ADC_SQR3_SQ1_N(n)       ((n) << 0)  /**< @brief 1st channel in seq. */
#define ADC_SQR3_SQ2_N(n)       ((n) << 5)  /**< @brief 2nd channel in seq. */
#define ADC_SQR3_SQ3_N(n)       ((n) << 10) /**< @brief 3rd channel in seq. */
#define ADC_SQR3_SQ4_N(n)       ((n) << 15) /**< @brief 4th channel in seq. */
#define ADC_SQR3_SQ5_N(n)       ((n) << 20) /**< @brief 5th channel in seq. */
#define ADC_SQR3_SQ6_N(n)       ((n) << 25) /**< @brief 6th channel in seq. */

#define ADC_SQR2_SQ7_N(n)       ((n) << 0)  /**< @brief 7th channel in seq. */
#define ADC_SQR2_SQ8_N(n)       ((n) << 5)  /**< @brief 8th channel in seq. */
#define ADC_SQR2_SQ9_N(n)       ((n) << 10) /**< @brief 9th channel in seq. */
#define ADC_SQR2_SQ10_N(n)      ((n) << 15) /**< @brief 10th channel in seq.*/
#define ADC_SQR2_SQ11_N(n)      ((n) << 20) /**< @brief 11th channel in seq.*/
#define ADC_SQR2_SQ12_N(n)      ((n) << 25) /**< @brief 12th channel in seq.*/

#define ADC_SQR1_SQ13_N(n)      ((n) << 0)  /**< @brief 13th channel in seq.*/
#define ADC_SQR1_SQ14_N(n)      ((n) << 5)  /**< @brief 14th channel in seq.*/
#define ADC_SQR1_SQ15_N(n)      ((n) << 10) /**< @brief 15th channel in seq.*/
#define ADC_SQR1_SQ16_N(n)      ((n) << 15) /**< @brief 16th channel in seq.*/
/** @} */

/**
 * @name    Sampling rate settings helper macros
 * @{
 */
#define ADC_SMPR2_SMP_AN0(n)    ((n) << 0)  /**< @brief AN0 sampling time.  */
#define ADC_SMPR2_SMP_AN1(n)    ((n) << 3)  /**< @brief AN1 sampling time.  */
#define ADC_SMPR2_SMP_AN2(n)    ((n) << 6)  /**< @brief AN2 sampling time.  */
#define ADC_SMPR2_SMP_AN3(n)    ((n) << 9)  /**< @brief AN3 sampling time.  */
#define ADC_SMPR2_SMP_AN4(n)    ((n) << 12) /**< @brief AN4 sampling time.  */
#define ADC_SMPR2_SMP_AN5(n)    ((n) << 15) /**< @brief AN5 sampling time.  */
#define ADC_SMPR2_SMP_AN6(n)    ((n) << 18) /**< @brief AN6 sampling time.  */
#define ADC_SMPR2_SMP_AN7(n)    ((n) << 21) /**< @brief AN7 sampling time.  */
#define ADC_SMPR2_SMP_AN8(n)    ((n) << 24) /**< @brief AN8 sampling time.  */
#define ADC_SMPR2_SMP_AN9(n)    ((n) << 27) /**< @brief AN9 sampling time.  */

#define ADC_SMPR1_SMP_AN10(n)   ((n) << 0)  /**< @brief AN10 sampling time. */
#define ADC_SMPR1_SMP_AN11(n)   ((n) << 3)  /**< @brief AN11 sampling time. */
#define ADC_SMPR1_SMP_AN12(n)   ((n) << 6)  /**< @brief AN12 sampling time. */
#define ADC_SMPR1_SMP_AN13(n)   ((n) << 9)  /**< @brief AN13 sampling time. */
#define ADC_SMPR1_SMP_AN14(n)   ((n) << 12) /**< @brief AN14 sampling time. */
#define ADC_SMPR1_SMP_AN15(n)   ((n) << 15) /**< @brief AN15 sampling time. */
#define ADC_SMPR1_SMP_SENSOR(n) ((n) << 18) /**< @brief Temperature Sensor
                                                 sampling time.             */
#define ADC_SMPR1_SMP_VREF(n)   ((n) << 21) /**< @brief Voltage Reference
                                                 sampling time.             */
#define ADC_SMPR1_SMP_VBAT(n)   ((n) << 24) /**< @brief VBAT sampling time. */
/** @} */

/**
 * @name    Threshold settings helper macros
 * @{
 */
/**
 * @brief   High threshold limitation.
 */
#define ADC_HTR(n)              ((n > ADC_HTR_HT) ? ADC_HTR_HT : n)
/**
 * @brief   Low threshold limitation.
 */
#define ADC_LTR(n)              ((n > ADC_LTR_LT) ? ADC_LTR_LT : n)
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_ADC_USE_ADC1 && !defined(__DOXYGEN__)
extern ADCDriver ADCD1;
#endif

#if STM32_ADC_USE_ADC2 && !defined(__DOXYGEN__)
extern ADCDriver ADCD2;
#endif

#if STM32_ADC_USE_ADC3 && !defined(__DOXYGEN__)
extern ADCDriver ADCD3;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void adc_lld_init(void);
  void adc_lld_start(ADCDriver *adcp);
  void adc_lld_stop(ADCDriver *adcp);
  void adc_lld_start_conversion(ADCDriver *adcp);
  void adc_lld_stop_conversion(ADCDriver *adcp);
  void adcSTM32EnableTSVREFE(void);
  void adcSTM32DisableTSVREFE(void);
  void adcSTM32EnableVBATE(void);
  void adcSTM32DisableVBATE(void);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_ADC */

#endif /* HAL_ADC_LLD_H */

/** @} */
