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
 * @file    CANv1/hal_can_lld.h
 * @brief   STM32 CAN subsystem low level driver header.
 *
 * @addtogroup CAN
 * @{
 */

#ifndef HAL_CAN_LLD_H
#define HAL_CAN_LLD_H

#if HAL_USE_CAN || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * The following macros from the ST header file are replaced with better
 * equivalents.
 */
#undef CAN_BTR_BRP
#undef CAN_BTR_TS1
#undef CAN_BTR_TS2
#undef CAN_BTR_SJW

/**
 * @brief   This switch defines whether the driver implementation supports
 *          a low power switch mode with automatic an wakeup feature.
 */
#define CAN_SUPPORTS_SLEEP          TRUE

/**
 * @brief   This implementation supports three transmit mailboxes.
 */
#define CAN_TX_MAILBOXES            3

/**
 * @brief   This implementation supports two receive mailboxes.
 */
#define CAN_RX_MAILBOXES            2

/**
 * @name    CAN registers helper macros
 * @{
 */
#define CAN_BTR_BRP(n)              (n)         /**< @brief BRP field macro.*/
#define CAN_BTR_TS1(n)              ((n) << 16) /**< @brief TS1 field macro.*/
#define CAN_BTR_TS2(n)              ((n) << 20) /**< @brief TS2 field macro.*/
#define CAN_BTR_SJW(n)              ((n) << 24) /**< @brief SJW field macro.*/

#define CAN_IDE_STD                 0           /**< @brief Standard id.    */
#define CAN_IDE_EXT                 1           /**< @brief Extended id.    */

#define CAN_RTR_DATA                0           /**< @brief Data frame.     */
#define CAN_RTR_REMOTE              1           /**< @brief Remote frame.   */
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   CAN pedantic errors report.
 * @details Use of this option is IRQ-intensive.
 */
#if !defined(STM32_CAN_REPORT_ALL_ERRORS) || defined(__DOXYGEN__)
#define STM32_CAN_REPORT_ALL_ERRORS         FALSE
#endif

/**
 * @brief   CAN1 driver enable switch.
 * @details If set to @p TRUE the support for CAN1 is included.
 */
#if !defined(STM32_CAN_USE_CAN1) || defined(__DOXYGEN__)
#define STM32_CAN_USE_CAN1                  FALSE
#endif

/**
 * @brief   CAN2 driver enable switch.
 * @details If set to @p TRUE the support for CAN2 is included.
 */
#if !defined(STM32_CAN_USE_CAN2) || defined(__DOXYGEN__)
#define STM32_CAN_USE_CAN2                  FALSE
#endif

/**
 * @brief   CAN3 driver enable switch.
 * @details If set to @p TRUE the support for CAN3 is included.
 */
#if !defined(STM32_CAN_USE_CAN3) || defined(__DOXYGEN__)
#define STM32_CAN_USE_CAN3                  FALSE
#endif

/**
 * @brief   CAN1 interrupt priority level setting.
 */
#if !defined(STM32_CAN_CAN1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_CAN_CAN1_IRQ_PRIORITY         11
#endif

/**
 * @brief   CAN2 interrupt priority level setting.
 */
#if !defined(STM32_CAN_CAN2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_CAN_CAN2_IRQ_PRIORITY         11
#endif

/**
 * @brief   CAN3 interrupt priority level setting.
 */
#if !defined(STM32_CAN_CAN3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_CAN_CAN3_IRQ_PRIORITY         11
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(STM32_HAS_CAN1)
#error "STM32_HAS_CAN1 not defined in registry"
#endif

#if !defined(STM32_HAS_CAN2)
#error "STM32_HAS_CAN2 not defined in registry"
#endif

#if !defined(STM32_HAS_CAN3)
#error "STM32_HAS_CAN3 not defined in registry"
#endif

#if (STM32_HAS_CAN1 | STM32_HAS_CAN2) && !defined(STM32_CAN_MAX_FILTERS)
#error "STM32_CAN_MAX_FILTERS not defined in registry"
#endif

#if STM32_HAS_CAN3 && !defined(STM32_CAN3_MAX_FILTERS)
#error "STM32_CAN3_MAX_FILTERS not defined in registry"
#endif

#if STM32_CAN_USE_CAN1 && !STM32_HAS_CAN1
#error "CAN1 not present in the selected device"
#endif

#if STM32_CAN_USE_CAN2 && !STM32_HAS_CAN2
#error "CAN2 not present in the selected device"
#endif

#if STM32_CAN_USE_CAN3 && !STM32_HAS_CAN3
#error "CAN2 not present in the selected device"
#endif

#if !STM32_CAN_USE_CAN1 && !STM32_CAN_USE_CAN2 && !STM32_CAN_USE_CAN3
#error "CAN driver activated but no CAN peripheral assigned"
#endif

#if !STM32_CAN_USE_CAN1 && STM32_CAN_USE_CAN2
#error "CAN2 requires CAN1, it cannot operate independently"
#endif

#if CAN_USE_SLEEP_MODE && !CAN_SUPPORTS_SLEEP
#error "CAN sleep mode not supported in this architecture"
#endif

/*******************  Bit definition for CAN_MSR register  ********************/
#define CAN_MSR_INAK_Pos       (0U)
#define CAN_MSR_INAK_Msk       (0x1U << CAN_MSR_INAK_Pos)                      /*!< 0x00000001 */
#define CAN_MSR_INAK           CAN_MSR_INAK_Msk                                /*!<Initialization Acknowledge */
#define CAN_MSR_SLAK_Pos       (1U)
#define CAN_MSR_SLAK_Msk       (0x1U << CAN_MSR_SLAK_Pos)                      /*!< 0x00000002 */
#define CAN_MSR_SLAK           CAN_MSR_SLAK_Msk                                /*!<Sleep Acknowledge */
#define CAN_MSR_ERRI_Pos       (2U)
#define CAN_MSR_ERRI_Msk       (0x1U << CAN_MSR_ERRI_Pos)                      /*!< 0x00000004 */
#define CAN_MSR_ERRI           CAN_MSR_ERRI_Msk                                /*!<Error Interrupt */
#define CAN_MSR_WKUI_Pos       (3U)
#define CAN_MSR_WKUI_Msk       (0x1U << CAN_MSR_WKUI_Pos)                      /*!< 0x00000008 */
#define CAN_MSR_WKUI           CAN_MSR_WKUI_Msk                                /*!<Wakeup Interrupt */
#define CAN_MSR_SLAKI_Pos      (4U)
#define CAN_MSR_SLAKI_Msk      (0x1U << CAN_MSR_SLAKI_Pos)                     /*!< 0x00000010 */
#define CAN_MSR_SLAKI          CAN_MSR_SLAKI_Msk                               /*!<Sleep Acknowledge Interrupt */
#define CAN_MSR_TXM_Pos        (8U)
#define CAN_MSR_TXM_Msk        (0x1U << CAN_MSR_TXM_Pos)                       /*!< 0x00000100 */
#define CAN_MSR_TXM            CAN_MSR_TXM_Msk                                 /*!<Transmit Mode */
#define CAN_MSR_RXM_Pos        (9U)
#define CAN_MSR_RXM_Msk        (0x1U << CAN_MSR_RXM_Pos)                       /*!< 0x00000200 */
#define CAN_MSR_RXM            CAN_MSR_RXM_Msk                                 /*!<Receive Mode */
#define CAN_MSR_SAMP_Pos       (10U)
#define CAN_MSR_SAMP_Msk       (0x1U << CAN_MSR_SAMP_Pos)                      /*!< 0x00000400 */
#define CAN_MSR_SAMP           CAN_MSR_SAMP_Msk                                /*!<Last Sample Point */
#define CAN_MSR_RX_Pos         (11U)
#define CAN_MSR_RX_Msk         (0x1U << CAN_MSR_RX_Pos)                        /*!< 0x00000800 */
#define CAN_MSR_RX             CAN_MSR_RX_Msk                                  /*!<CAN Rx Signal */

#define CAN_TSR_RQCP0_Pos      (0U)
#define CAN_TSR_RQCP0_Msk      (0x1U << CAN_TSR_RQCP0_Pos)                     /*!< 0x00000001 */
#define CAN_TSR_RQCP0          CAN_TSR_RQCP0_Msk                               /*!<Request Completed Mailbox0 */
#define CAN_TSR_TXOK0_Pos      (1U)
#define CAN_TSR_TXOK0_Msk      (0x1U << CAN_TSR_TXOK0_Pos)                     /*!< 0x00000002 */
#define CAN_TSR_TXOK0          CAN_TSR_TXOK0_Msk                               /*!<Transmission OK of Mailbox0 */
#define CAN_TSR_ALST0_Pos      (2U)
#define CAN_TSR_ALST0_Msk      (0x1U << CAN_TSR_ALST0_Pos)                     /*!< 0x00000004 */
#define CAN_TSR_ALST0          CAN_TSR_ALST0_Msk                               /*!<Arbitration Lost for Mailbox0 */
#define CAN_TSR_TERR0_Pos      (3U)
#define CAN_TSR_TERR0_Msk      (0x1U << CAN_TSR_TERR0_Pos)                     /*!< 0x00000008 */
#define CAN_TSR_TERR0          CAN_TSR_TERR0_Msk                               /*!<Transmission Error of Mailbox0 */
#define CAN_TSR_ABRQ0_Pos      (7U)
#define CAN_TSR_ABRQ0_Msk      (0x1U << CAN_TSR_ABRQ0_Pos)                     /*!< 0x00000080 */
#define CAN_TSR_ABRQ0          CAN_TSR_ABRQ0_Msk                               /*!<Abort Request for Mailbox0 */
#define CAN_TSR_RQCP1_Pos      (8U)
#define CAN_TSR_RQCP1_Msk      (0x1U << CAN_TSR_RQCP1_Pos)                     /*!< 0x00000100 */
#define CAN_TSR_RQCP1          CAN_TSR_RQCP1_Msk                               /*!<Request Completed Mailbox1 */
#define CAN_TSR_TXOK1_Pos      (9U)
#define CAN_TSR_TXOK1_Msk      (0x1U << CAN_TSR_TXOK1_Pos)                     /*!< 0x00000200 */
#define CAN_TSR_TXOK1          CAN_TSR_TXOK1_Msk                               /*!<Transmission OK of Mailbox1 */
#define CAN_TSR_ALST1_Pos      (10U)
#define CAN_TSR_ALST1_Msk      (0x1U << CAN_TSR_ALST1_Pos)                     /*!< 0x00000400 */
#define CAN_TSR_ALST1          CAN_TSR_ALST1_Msk                               /*!<Arbitration Lost for Mailbox1 */
#define CAN_TSR_TERR1_Pos      (11U)
#define CAN_TSR_TERR1_Msk      (0x1U << CAN_TSR_TERR1_Pos)                     /*!< 0x00000800 */
#define CAN_TSR_TERR1          CAN_TSR_TERR1_Msk                               /*!<Transmission Error of Mailbox1 */
#define CAN_TSR_ABRQ1_Pos      (15U)
#define CAN_TSR_ABRQ1_Msk      (0x1U << CAN_TSR_ABRQ1_Pos)                     /*!< 0x00008000 */
#define CAN_TSR_ABRQ1          CAN_TSR_ABRQ1_Msk                               /*!<Abort Request for Mailbox 1 */
#define CAN_TSR_RQCP2_Pos      (16U)
#define CAN_TSR_RQCP2_Msk      (0x1U << CAN_TSR_RQCP2_Pos)                     /*!< 0x00010000 */
#define CAN_TSR_RQCP2          CAN_TSR_RQCP2_Msk                               /*!<Request Completed Mailbox2 */
#define CAN_TSR_TXOK2_Pos      (17U)
#define CAN_TSR_TXOK2_Msk      (0x1U << CAN_TSR_TXOK2_Pos)                     /*!< 0x00020000 */
#define CAN_TSR_TXOK2          CAN_TSR_TXOK2_Msk                               /*!<Transmission OK of Mailbox 2 */
#define CAN_TSR_ALST2_Pos      (18U)
#define CAN_TSR_ALST2_Msk      (0x1U << CAN_TSR_ALST2_Pos)                     /*!< 0x00040000 */
#define CAN_TSR_ALST2          CAN_TSR_ALST2_Msk                               /*!<Arbitration Lost for mailbox 2 */
#define CAN_TSR_TERR2_Pos      (19U)
#define CAN_TSR_TERR2_Msk      (0x1U << CAN_TSR_TERR2_Pos)                     /*!< 0x00080000 */
#define CAN_TSR_TERR2          CAN_TSR_TERR2_Msk                               /*!<Transmission Error of Mailbox 2 */
#define CAN_TSR_ABRQ2_Pos      (23U)
#define CAN_TSR_ABRQ2_Msk      (0x1U << CAN_TSR_ABRQ2_Pos)                     /*!< 0x00800000 */
#define CAN_TSR_ABRQ2          CAN_TSR_ABRQ2_Msk                               /*!<Abort Request for Mailbox 2 */
#define CAN_TSR_CODE_Pos       (24U)
#define CAN_TSR_CODE_Msk       (0x3U << CAN_TSR_CODE_Pos)                      /*!< 0x03000000 */
#define CAN_TSR_CODE           CAN_TSR_CODE_Msk                                /*!<Mailbox Code */

/********************  Bit definition for CAN_IER register  *******************/
#define CAN_IER_TMEIE_Pos      (0U)
#define CAN_IER_TMEIE_Msk      (0x1U << CAN_IER_TMEIE_Pos)                     /*!< 0x00000001 */
#define CAN_IER_TMEIE          CAN_IER_TMEIE_Msk                               /*!<Transmit Mailbox Empty Interrupt Enable */
#define CAN_IER_FMPIE0_Pos     (1U)
#define CAN_IER_FMPIE0_Msk     (0x1U << CAN_IER_FMPIE0_Pos)                    /*!< 0x00000002 */
#define CAN_IER_FMPIE0         CAN_IER_FMPIE0_Msk                              /*!<FIFO Message Pending Interrupt Enable */
#define CAN_IER_FFIE0_Pos      (2U)
#define CAN_IER_FFIE0_Msk      (0x1U << CAN_IER_FFIE0_Pos)                     /*!< 0x00000004 */
#define CAN_IER_FFIE0          CAN_IER_FFIE0_Msk                               /*!<FIFO Full Interrupt Enable */
#define CAN_IER_FOVIE0_Pos     (3U)
#define CAN_IER_FOVIE0_Msk     (0x1U << CAN_IER_FOVIE0_Pos)                    /*!< 0x00000008 */
#define CAN_IER_FOVIE0         CAN_IER_FOVIE0_Msk                              /*!<FIFO Overrun Interrupt Enable */
#define CAN_IER_FMPIE1_Pos     (4U)
#define CAN_IER_FMPIE1_Msk     (0x1U << CAN_IER_FMPIE1_Pos)                    /*!< 0x00000010 */
#define CAN_IER_FMPIE1         CAN_IER_FMPIE1_Msk                              /*!<FIFO Message Pending Interrupt Enable */
#define CAN_IER_FFIE1_Pos      (5U)
#define CAN_IER_FFIE1_Msk      (0x1U << CAN_IER_FFIE1_Pos)                     /*!< 0x00000020 */
#define CAN_IER_FFIE1          CAN_IER_FFIE1_Msk                               /*!<FIFO Full Interrupt Enable */
#define CAN_IER_FOVIE1_Pos     (6U)
#define CAN_IER_FOVIE1_Msk     (0x1U << CAN_IER_FOVIE1_Pos)                    /*!< 0x00000040 */
#define CAN_IER_FOVIE1         CAN_IER_FOVIE1_Msk                              /*!<FIFO Overrun Interrupt Enable */
#define CAN_IER_EWGIE_Pos      (8U)
#define CAN_IER_EWGIE_Msk      (0x1U << CAN_IER_EWGIE_Pos)                     /*!< 0x00000100 */
#define CAN_IER_EWGIE          CAN_IER_EWGIE_Msk                               /*!<Error Warning Interrupt Enable */
#define CAN_IER_EPVIE_Pos      (9U)
#define CAN_IER_EPVIE_Msk      (0x1U << CAN_IER_EPVIE_Pos)                     /*!< 0x00000200 */
#define CAN_IER_EPVIE          CAN_IER_EPVIE_Msk                               /*!<Error Passive Interrupt Enable */
#define CAN_IER_BOFIE_Pos      (10U)
#define CAN_IER_BOFIE_Msk      (0x1U << CAN_IER_BOFIE_Pos)                     /*!< 0x00000400 */
#define CAN_IER_BOFIE          CAN_IER_BOFIE_Msk                               /*!<Bus-Off Interrupt Enable */
#define CAN_IER_LECIE_Pos      (11U)
#define CAN_IER_LECIE_Msk      (0x1U << CAN_IER_LECIE_Pos)                     /*!< 0x00000800 */
#define CAN_IER_LECIE          CAN_IER_LECIE_Msk                               /*!<Last Error Code Interrupt Enable */
#define CAN_IER_ERRIE_Pos      (15U)
#define CAN_IER_ERRIE_Msk      (0x1U << CAN_IER_ERRIE_Pos)                     /*!< 0x00008000 */
#define CAN_IER_ERRIE          CAN_IER_ERRIE_Msk                               /*!<Error Interrupt Enable */
#define CAN_IER_WKUIE_Pos      (16U)
#define CAN_IER_WKUIE_Msk      (0x1U << CAN_IER_WKUIE_Pos)                     /*!< 0x00010000 */
#define CAN_IER_WKUIE          CAN_IER_WKUIE_Msk                               /*!<Wakeup Interrupt Enable */
#define CAN_IER_SLKIE_Pos      (17U)
#define CAN_IER_SLKIE_Msk      (0x1U << CAN_IER_SLKIE_Pos)                     /*!< 0x00020000 */
#define CAN_IER_SLKIE          CAN_IER_SLKIE_Msk                               /*!<Sleep Interrupt Enable */
#define CAN_IER_EWGIE_Pos      (8U)



/*******************  Bit definition for CAN_RF0R register  *******************/
#define CAN_RF0R_FMP0_Pos      (0U)
#define CAN_RF0R_FMP0_Msk      (0x3U << CAN_RF0R_FMP0_Pos)                     /*!< 0x00000003 */
#define CAN_RF0R_FMP0          CAN_RF0R_FMP0_Msk                               /*!<FIFO 0 Message Pending */
#define CAN_RF0R_FULL0_Pos     (3U)
#define CAN_RF0R_FULL0_Msk     (0x1U << CAN_RF0R_FULL0_Pos)                    /*!< 0x00000008 */
#define CAN_RF0R_FULL0         CAN_RF0R_FULL0_Msk                              /*!<FIFO 0 Full */
#define CAN_RF0R_FOVR0_Pos     (4U)
#define CAN_RF0R_FOVR0_Msk     (0x1U << CAN_RF0R_FOVR0_Pos)                    /*!< 0x00000010 */
#define CAN_RF0R_FOVR0         CAN_RF0R_FOVR0_Msk                              /*!<FIFO 0 Overrun */
#define CAN_RF0R_RFOM0_Pos     (5U)
#define CAN_RF0R_RFOM0_Msk     (0x1U << CAN_RF0R_RFOM0_Pos)                    /*!< 0x00000020 */
#define CAN_RF0R_RFOM0         CAN_RF0R_RFOM0_Msk                              /*!<Release FIFO 0 Output Mailbox */

/*******************  Bit definition for CAN_RF1R register  *******************/
#define CAN_RF1R_FMP1_Pos      (0U)
#define CAN_RF1R_FMP1_Msk      (0x3U << CAN_RF1R_FMP1_Pos)                     /*!< 0x00000003 */
#define CAN_RF1R_FMP1          CAN_RF1R_FMP1_Msk                               /*!<FIFO 1 Message Pending */
#define CAN_RF1R_FULL1_Pos     (3U)
#define CAN_RF1R_FULL1_Msk     (0x1U << CAN_RF1R_FULL1_Pos)                    /*!< 0x00000008 */
#define CAN_RF1R_FULL1         CAN_RF1R_FULL1_Msk                              /*!<FIFO 1 Full */
#define CAN_RF1R_FOVR1_Pos     (4U)
#define CAN_RF1R_FOVR1_Msk     (0x1U << CAN_RF1R_FOVR1_Pos)                    /*!< 0x00000010 */
#define CAN_RF1R_FOVR1         CAN_RF1R_FOVR1_Msk                              /*!<FIFO 1 Overrun */
#define CAN_RF1R_RFOM1_Pos     (5U)
#define CAN_RF1R_RFOM1_Msk     (0x1U << CAN_RF1R_RFOM1_Pos)                    /*!< 0x00000020 */
#define CAN_RF1R_RFOM1         CAN_RF1R_RFOM1_Msk                              /*!<Release FIFO 1 Output Mailbox */


/*!<Mailbox registers */
/******************  Bit definition for CAN_TI0R register  ********************/
#define CAN_TI0R_TXRQ_Pos      (0U)
#define CAN_TI0R_TXRQ_Msk      (0x1U << CAN_TI0R_TXRQ_Pos)                     /*!< 0x00000001 */
#define CAN_TI0R_TXRQ          CAN_TI0R_TXRQ_Msk                               /*!<Transmit Mailbox Request */
#define CAN_TI0R_RTR_Pos       (1U)
#define CAN_TI0R_RTR_Msk       (0x1U << CAN_TI0R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_TI0R_RTR           CAN_TI0R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_TI0R_IDE_Pos       (2U)
#define CAN_TI0R_IDE_Msk       (0x1U << CAN_TI0R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_TI0R_IDE           CAN_TI0R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_TI0R_EXID_Pos      (3U)
#define CAN_TI0R_EXID_Msk      (0x3FFFFU << CAN_TI0R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_TI0R_EXID          CAN_TI0R_EXID_Msk                               /*!<Extended Identifier */
#define CAN_TI0R_STID_Pos      (21U)
#define CAN_TI0R_STID_Msk      (0x7FFU << CAN_TI0R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_TI0R_STID          CAN_TI0R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RI0R register  *******************/
#define CAN_RI0R_RTR_Pos       (1U)
#define CAN_RI0R_RTR_Msk       (0x1U << CAN_RI0R_RTR_Pos)                      /*!< 0x00000002 */
#define CAN_RI0R_RTR           CAN_RI0R_RTR_Msk                                /*!<Remote Transmission Request */
#define CAN_RI0R_IDE_Pos       (2U)
#define CAN_RI0R_IDE_Msk       (0x1U << CAN_RI0R_IDE_Pos)                      /*!< 0x00000004 */
#define CAN_RI0R_IDE           CAN_RI0R_IDE_Msk                                /*!<Identifier Extension */
#define CAN_RI0R_EXID_Pos      (3U)
#define CAN_RI0R_EXID_Msk      (0x3FFFFU << CAN_RI0R_EXID_Pos)                 /*!< 0x001FFFF8 */
#define CAN_RI0R_EXID          CAN_RI0R_EXID_Msk                               /*!<Extended Identifier */
#define CAN_RI0R_STID_Pos      (21U)
#define CAN_RI0R_STID_Msk      (0x7FFU << CAN_RI0R_STID_Pos)                   /*!< 0xFFE00000 */
#define CAN_RI0R_STID          CAN_RI0R_STID_Msk                               /*!<Standard Identifier or Extended Identifier */

/*******************  Bit definition for CAN_RDT0R register  ******************/
#define CAN_RDT0R_DLC_Pos      (0U)
#define CAN_RDT0R_DLC_Msk      (0xFU << CAN_RDT0R_DLC_Pos)                     /*!< 0x0000000F */
#define CAN_RDT0R_DLC          CAN_RDT0R_DLC_Msk                               /*!<Data Length Code */
#define CAN_RDT0R_FMI_Pos      (8U)
#define CAN_RDT0R_FMI_Msk      (0xFFU << CAN_RDT0R_FMI_Pos)                    /*!< 0x0000FF00 */
#define CAN_RDT0R_FMI          CAN_RDT0R_FMI_Msk                               /*!<Filter Match Index */
#define CAN_RDT0R_TIME_Pos     (16U)
#define CAN_RDT0R_TIME_Msk     (0xFFFFU << CAN_RDT0R_TIME_Pos)                 /*!< 0xFFFF0000 */
#define CAN_RDT0R_TIME         CAN_RDT0R_TIME_Msk                              /*!<Message Time Stamp */

/*******************  Bit definition for CAN_RDL0R register  ******************/
#define CAN_RDL0R_DATA0_Pos    (0U)
#define CAN_RDL0R_DATA0_Msk    (0xFFU << CAN_RDL0R_DATA0_Pos)                  /*!< 0x000000FF */
#define CAN_RDL0R_DATA0        CAN_RDL0R_DATA0_Msk                             /*!<Data byte 0 */
#define CAN_RDL0R_DATA1_Pos    (8U)
#define CAN_RDL0R_DATA1_Msk    (0xFFU << CAN_RDL0R_DATA1_Pos)                  /*!< 0x0000FF00 */
#define CAN_RDL0R_DATA1        CAN_RDL0R_DATA1_Msk                             /*!<Data byte 1 */
#define CAN_RDL0R_DATA2_Pos    (16U)
#define CAN_RDL0R_DATA2_Msk    (0xFFU << CAN_RDL0R_DATA2_Pos)                  /*!< 0x00FF0000 */
#define CAN_RDL0R_DATA2        CAN_RDL0R_DATA2_Msk                             /*!<Data byte 2 */
#define CAN_RDL0R_DATA3_Pos    (24U)
#define CAN_RDL0R_DATA3_Msk    (0xFFU << CAN_RDL0R_DATA3_Pos)                  /*!< 0xFF000000 */
#define CAN_RDL0R_DATA3        CAN_RDL0R_DATA3_Msk                             /*!<Data byte 3 */

/*******************  Bit definition for CAN_RDH0R register  ******************/
#define CAN_RDH0R_DATA4_Pos    (0U)
#define CAN_RDH0R_DATA4_Msk    (0xFFU << CAN_RDH0R_DATA4_Pos)                  /*!< 0x000000FF */
#define CAN_RDH0R_DATA4        CAN_RDH0R_DATA4_Msk                             /*!<Data byte 4 */
#define CAN_RDH0R_DATA5_Pos    (8U)
#define CAN_RDH0R_DATA5_Msk    (0xFFU << CAN_RDH0R_DATA5_Pos)                  /*!< 0x0000FF00 */
#define CAN_RDH0R_DATA5        CAN_RDH0R_DATA5_Msk                             /*!<Data byte 5 */
#define CAN_RDH0R_DATA6_Pos    (16U)
#define CAN_RDH0R_DATA6_Msk    (0xFFU << CAN_RDH0R_DATA6_Pos)                  /*!< 0x00FF0000 */
#define CAN_RDH0R_DATA6        CAN_RDH0R_DATA6_Msk                             /*!<Data byte 6 */
#define CAN_RDH0R_DATA7_Pos    (24U)
#define CAN_RDH0R_DATA7_Msk    (0xFFU << CAN_RDH0R_DATA7_Pos)                  /*!< 0xFF000000 */
#define CAN_RDH0R_DATA7        CAN_RDH0R_DATA7_Msk                             /*!<Data byte 7 */


/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a CAN driver.
 */
typedef struct hal_can_driver CANDriver;

/**
 * @brief   Type of a transmission mailbox index.
 */
typedef uint32_t canmbx_t;

#if (CAN_ENFORCE_USE_CALLBACKS == TRUE) || defined(__DOXYGEN__)
/**
 * @brief   Type of a CAN notification callback.
 *
 * @param[in] canp      pointer to the @p CANDriver object triggering the
 *                      callback
 * @param[in] flags     flags associated to the mailbox callback
 */
typedef void (*can_callback_t)(CANDriver *canp, uint32_t flags);
#endif

/**
 * @brief   CAN transmission frame.
 * @note    Accessing the frame data as word16 or word32 is not portable because
 *          machine data endianness, it can be still useful for a quick filling.
 */
typedef struct {
  struct {
    uint8_t                 DLC:4;          /**< @brief Data length.        */
    uint8_t                 RTR:1;          /**< @brief Frame type.         */
    uint8_t                 IDE:1;          /**< @brief Identifier type.    */
  };
  union {
    struct {
      uint32_t              SID:11;         /**< @brief Standard identifier.*/
    };
    struct {
      uint32_t              EID:29;         /**< @brief Extended identifier.*/
    };
  };
  union {
    uint8_t                 data8[8];       /**< @brief Frame data.         */
    uint16_t                data16[4];      /**< @brief Frame data.         */
    uint32_t                data32[2];      /**< @brief Frame data.         */
    uint64_t                data64[1];      /**< @brief Frame data.         */
  };
} CANTxFrame;

/**
 * @brief   CAN received frame.
 * @note    Accessing the frame data as word16 or word32 is not portable because
 *          machine data endianness, it can be still useful for a quick filling.
 */
typedef struct {
  struct {
    uint8_t                 FMI;            /**< @brief Filter id.          */
    uint16_t                TIME;           /**< @brief Time stamp.         */
  };
  struct {
    uint8_t                 DLC:4;          /**< @brief Data length.        */
    uint8_t                 RTR:1;          /**< @brief Frame type.         */
    uint8_t                 IDE:1;          /**< @brief Identifier type.    */
  };
  union {
    struct {
      uint32_t              SID:11;         /**< @brief Standard identifier.*/
    };
    struct {
      uint32_t              EID:29;         /**< @brief Extended identifier.*/
    };
  };
  union {
    uint8_t                 data8[8];       /**< @brief Frame data.         */
    uint16_t                data16[4];      /**< @brief Frame data.         */
    uint32_t                data32[2];      /**< @brief Frame data.         */
    uint64_t                data64[1];      /**< @brief Frame data.         */
  };
} CANRxFrame;

/**
 * @brief   CAN filter.
 * @note    Refer to the STM32 reference manual for info about filters.
 */
typedef struct {
  /**
   * @brief   Number of the filter bank to be programmed.
   */
  uint32_t                  filter:16;
  /**
   * @brief   Filter mode.
   * @note    This bit represent the CAN_FM1R register bit associated to this
   *          filter (0=mask mode, 1=list mode).
   */
  uint32_t                  mode:1;
  /**
   * @brief   Filter scale.
   * @note    This bit represent the CAN_FS1R register bit associated to this
   *          filter (0=16 bits mode, 1=32 bits mode).
   */
  uint32_t                  scale:1;
  /**
   * @brief   Filter mode.
   * @note    This bit represent the CAN_FFA1R register bit associated to this
   *          filter, must be set to zero in this version of the driver.
   */
  uint32_t                  assignment:1;
  /**
   * @brief   Filter register 1 (identifier).
   */
  uint32_t                  register1;
  /**
   * @brief   Filter register 2 (mask/identifier depending on mode=0/1).
   */
  uint32_t                  register2;
} CANFilter;

/**
 * @brief   Type of a CAN configuration structure.
 */
typedef struct hal_can_config {
  /**
   * @brief   CAN MCR register initialization data.
   * @note    Some bits in this register are enforced by the driver regardless
   *          their status in this field.
   */
  uint32_t                  mcr;
  /**
   * @brief   CAN BTR register initialization data.
   * @note    Some bits in this register are enforced by the driver regardless
   *          their status in this field.
   */
  uint32_t                  btr;
} CANConfig;

/**
 * @brief   Structure representing an CAN driver.
 */
struct hal_can_driver {
  /**
   * @brief   Driver state.
   */
  canstate_t                state;
  /**
   * @brief   Current configuration data.
   */
  const CANConfig           *config;
  /**
   * @brief   Transmission threads queue.
   */
  threads_queue_t           txqueue;
  /**
   * @brief   Receive threads queue.
   */
  threads_queue_t           rxqueue;
#if (CAN_ENFORCE_USE_CALLBACKS == FALSE) || defined(__DOXYGEN__)
  /**
   * @brief   One or more frames become available.
   * @note    After broadcasting this event it will not be broadcasted again
   *          until the received frames queue has been completely emptied. It
   *          is <b>not</b> broadcasted for each received frame. It is
   *          responsibility of the application to empty the queue by
   *          repeatedly invoking @p canReceive() when listening to this event.
   *          This behavior minimizes the interrupt served by the system
   *          because CAN traffic.
   * @note    The flags associated to the listeners will indicate which
   *          receive mailboxes become non-empty.
   */
  event_source_t            rxfull_event;
  /**
   * @brief   One or more transmission mailbox become available.
   * @note    The flags associated to the listeners will indicate which
   *          transmit mailboxes become empty.
   * @note    The upper 16 bits are transmission error flags associated
   *          to the transmit mailboxes.
   */
  event_source_t            txempty_event;
  /**
   * @brief   A CAN bus error happened.
   * @note    The flags associated to the listeners will indicate that
   *          receive error(s) have occurred.
   * @note    In this implementation the upper 16 bits are filled with the
   *          unprocessed content of the ESR register.
   */
  event_source_t            error_event;
#if CAN_USE_SLEEP_MODE || defined (__DOXYGEN__)
  /**
   * @brief   Entering sleep state event.
   */
  event_source_t            sleep_event;
  /**
   * @brief   Exiting sleep state event.
   */
  event_source_t            wakeup_event;
#endif /* CAN_USE_SLEEP_MODE */
#else /* CAN_ENFORCE_USE_CALLBACKS == TRUE */
  /**
   * @brief   One or more frames become available.
   * @note    After calling this function it will not be called again
   *          until the received frames queue has been completely emptied. It
   *          is <b>not</b> called for each received frame. It is
   *          responsibility of the application to empty the queue by
   *          repeatedly invoking @p chTryReceiveI().
   *          This behavior minimizes the interrupt served by the system
   *          because CAN traffic.
   */
  can_callback_t            rxfull_cb;
  /**
   * @brief   One or more transmission mailbox become available.
   * @note    The flags associated to the callback will indicate which
   *          transmit mailboxes become empty.
   */
  can_callback_t            txempty_cb;
  /**
   * @brief   A CAN bus error happened.
   */
  can_callback_t            error_cb;
#if (CAN_USE_SLEEP_MODE == TRUE) || defined (__DOXYGEN__)
  /**
   * @brief   Exiting sleep state.
   */
  can_callback_t            wakeup_cb;
#endif
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief   Pointer to the CAN registers.
   */
  can_type               *can;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_CAN_USE_CAN1 && !defined(__DOXYGEN__)
extern CANDriver CAND1;
#endif

#if STM32_CAN_USE_CAN2 && !defined(__DOXYGEN__)
extern CANDriver CAND2;
#endif

#if STM32_CAN_USE_CAN3 && !defined(__DOXYGEN__)
extern CANDriver CAND3;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void can_lld_init(void);
  void can_lld_start(CANDriver *canp);
  void can_lld_stop(CANDriver *canp);
  bool can_lld_is_tx_empty(CANDriver *canp, canmbx_t mailbox);
  void can_lld_transmit(CANDriver *canp,
                        canmbx_t mailbox,
                        const CANTxFrame *crfp);
  bool can_lld_is_rx_nonempty(CANDriver *canp, canmbx_t mailbox);
  void can_lld_receive(CANDriver *canp,
                       canmbx_t mailbox,
                       CANRxFrame *ctfp);
  void can_lld_abort(CANDriver *canp,
                     canmbx_t mailbox);
#if CAN_USE_SLEEP_MODE
  void can_lld_sleep(CANDriver *canp);
  void can_lld_wakeup(CANDriver *canp);
#endif /* CAN_USE_SLEEP_MODE */
  void canSTM32SetFilters(CANDriver *canp, uint32_t can2sb,
                          uint32_t num, const CANFilter *cfp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_CAN */

#endif /* HAL_CAN_LLD_H */

/** @} */
