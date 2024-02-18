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
 * @file    SPIv3/hal_spi_v2_lld.h
 * @brief   STM32 SPI (v2) subsystem low level driver header.
 *
 * @addtogroup SPI
 * @{
 */

#ifndef HAL_SPI_V2_LLD_H
#define HAL_SPI_V2_LLD_H

#if HAL_USE_SPI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Circular mode support flag.
 */
#define SPI_SUPPORTS_CIRCULAR           TRUE

/**
 * @brief   Slave mode support flag.
 */
#define SPI_SUPPORTS_SLAVE_MODE         TRUE

/**
 * @name    Register helpers not found in ST headers
 * @{
 */
#define SPI_CFG1_MBR_VALUE(n)           ((n) << SPI_CFG1_MBR_Pos)
#define SPI_CFG1_MBR_DIV2               SPI_CFG1_MBR_VALUE(0)
#define SPI_CFG1_MBR_DIV4               SPI_CFG1_MBR_VALUE(1)
#define SPI_CFG1_MBR_DIV8               SPI_CFG1_MBR_VALUE(2)
#define SPI_CFG1_MBR_DIV16              SPI_CFG1_MBR_VALUE(3)
#define SPI_CFG1_MBR_DIV32              SPI_CFG1_MBR_VALUE(4)
#define SPI_CFG1_MBR_DIV64              SPI_CFG1_MBR_VALUE(5)
#define SPI_CFG1_MBR_DIV128             SPI_CFG1_MBR_VALUE(6)
#define SPI_CFG1_MBR_DIV256             SPI_CFG1_MBR_VALUE(7)
#define SPI_CFG1_CRCSIZE_VALUE(n)       ((n) << SPI_CFG1_CRCSIZE_Pos)
#define SPI_CFG1_UDRDET_VALUE(n)        ((n) << SPI_CFG1_UDRDET_Pos)
#define SPI_CFG1_UDRCFG_VALUE(n)        ((n) << SPI_CFG1_UDRCFG_Pos)
#define SPI_CFG1_FTHLV_VALUE(n)         ((n) << SPI_CFG1_FTHLV_Pos)
#define SPI_CFG1_DSIZE_VALUE(n)         ((n) << SPI_CFG1_DSIZE_Pos)

#define SPI_CFG2_SP_VALUE(n)            ((n) << SPI_CFG2_SP_Pos)
#define SPI_CFG2_COMM_VALUE(n)          ((n) << SPI_CFG2_COMM_Pos)
#define SPI_CFG2_COMM_FULL_DUPLEX       SPI_CFG2_COMM_VALUE(0)
#define SPI_CFG2_COMM_TRANSMITTER       SPI_CFG2_COMM_VALUE(1)
#define SPI_CFG2_COMM_RECEIVER          SPI_CFG2_COMM_VALUE(2)
#define SPI_CFG2_COMM_HALF_DUPLEX       SPI_CFG2_COMM_VALUE(3)
#define SPI_CFG2_MIDI_VALUE(n)          ((n) << SPI_CFG2_MIDI_Pos)
#define SPI_CFG2_MSSI_VALUE(n)          ((n) << SPI_CFG2_MSSI_Pos)
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   SPI1 driver enable switch.
 * @details If set to @p TRUE the support for SPI1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SPI_USE_SPI1) || defined(__DOXYGEN__)
#define STM32_SPI_USE_SPI1                  FALSE
#endif

/**
 * @brief   SPI2 driver enable switch.
 * @details If set to @p TRUE the support for SPI2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SPI_USE_SPI2) || defined(__DOXYGEN__)
#define STM32_SPI_USE_SPI2                  FALSE
#endif

/**
 * @brief   SPI3 driver enable switch.
 * @details If set to @p TRUE the support for SPI3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SPI_USE_SPI3) || defined(__DOXYGEN__)
#define STM32_SPI_USE_SPI3                  FALSE
#endif

/**
 * @brief   SPI4 driver enable switch.
 * @details If set to @p TRUE the support for SPI4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SPI_USE_SPI4) || defined(__DOXYGEN__)
#define STM32_SPI_USE_SPI4                  FALSE
#endif

/**
 * @brief   SPI5 driver enable switch.
 * @details If set to @p TRUE the support for SPI5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SPI_USE_SPI5) || defined(__DOXYGEN__)
#define STM32_SPI_USE_SPI5                  FALSE
#endif

/**
 * @brief   SPI6 driver enable switch.
 * @details If set to @p TRUE the support for SPI6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SPI_USE_SPI6) || defined(__DOXYGEN__)
#define STM32_SPI_USE_SPI6                  FALSE
#endif

/**
 * @brief   Filler pattern used when there is nothing to transmit.
 */
#if !defined(STM32_SPI_FILLER_PATTERN) || defined(__DOXYGEN__)
#define STM32_SPI_FILLER_PATTERN            0xFFFFFFFFU
#endif

/**
 * @brief   SPI1 interrupt priority level setting.
 */
#if !defined(STM32_SPI_SPI1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI1_IRQ_PRIORITY         10
#endif

/**
 * @brief   SPI2 interrupt priority level setting.
 */
#if !defined(STM32_SPI_SPI2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI2_IRQ_PRIORITY         10
#endif

/**
 * @brief   SPI3 interrupt priority level setting.
 */
#if !defined(STM32_SPI_SPI3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI3_IRQ_PRIORITY         10
#endif

/**
 * @brief   SPI4 interrupt priority level setting.
 */
#if !defined(STM32_SPI_SPI4_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI4_IRQ_PRIORITY         10
#endif

/**
 * @brief   SPI5 interrupt priority level setting.
 */
#if !defined(STM32_SPI_SPI5_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI5_IRQ_PRIORITY         10
#endif

/**
 * @brief   SPI6 interrupt priority level setting.
 */
#if !defined(STM32_SPI_SPI6_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI6_IRQ_PRIORITY         10
#endif

/**
 * @brief   SPI1 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(STM32_SPI_SPI1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI1_DMA_PRIORITY         1
#endif

/**
 * @brief   SPI2 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(STM32_SPI_SPI2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI2_DMA_PRIORITY         1
#endif

/**
 * @brief   SPI3 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(STM32_SPI_SPI3_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI3_DMA_PRIORITY         1
#endif

/**
 * @brief   SPI4 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(STM32_SPI_SPI4_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI4_DMA_PRIORITY         1
#endif

/**
 * @brief   SPI5 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(STM32_SPI_SPI5_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI5_DMA_PRIORITY         1
#endif

/**
 * @brief   SPI6 DMA priority (0..3|lowest..highest).
 * @note    The priority level is used for both the TX and RX DMA streams but
 *          because of the streams ordering the RX stream has always priority
 *          over the TX stream.
 */
#if !defined(STM32_SPI_SPI6_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SPI_SPI6_DMA_PRIORITY         1
#endif

/**
 * @brief   SPI DMA error hook.
 */
#if !defined(STM32_SPI_DMA_ERROR_HOOK) || defined(__DOXYGEN__)
#define STM32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if STM32_SPI_USE_SPI1 && !STM32_HAS_SPI1
#error "SPI1 not present in the selected device"
#endif

#if STM32_SPI_USE_SPI2 && !STM32_HAS_SPI2
#error "SPI2 not present in the selected device"
#endif

#if STM32_SPI_USE_SPI3 && !STM32_HAS_SPI3
#error "SPI3 not present in the selected device"
#endif

#if STM32_SPI_USE_SPI4 && !STM32_HAS_SPI4
#error "SPI4 not present in the selected device"
#endif

#if STM32_SPI_USE_SPI5 && !STM32_HAS_SPI5
#error "SPI5 not present in the selected device"
#endif

#if STM32_SPI_USE_SPI6 && !STM32_HAS_SPI6
#error "SPI6 not present in the selected device"
#endif

#if !STM32_SPI_USE_SPI1 && !STM32_SPI_USE_SPI2 && !STM32_SPI_USE_SPI3 &&    \
    !STM32_SPI_USE_SPI4 && !STM32_SPI_USE_SPI5 && !STM32_SPI_USE_SPI6
#error "SPI driver activated but no SPI peripheral assigned"
#endif

#if STM32_SPI_USE_SPI1 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SPI_SPI1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPI1"
#endif

#if STM32_SPI_USE_SPI2 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SPI_SPI2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPI2"
#endif

#if STM32_SPI_USE_SPI3 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SPI_SPI3_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPI3"
#endif

#if STM32_SPI_USE_SPI4 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SPI_SPI4_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPI4"
#endif

#if STM32_SPI_USE_SPI5 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SPI_SPI5_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPI5"
#endif

#if STM32_SPI_USE_SPI6 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SPI_SPI6_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SPI6"
#endif

/* The following checks are only required when there is a DMA able to
   reassign streams to different channels.*/
#if STM32_ADVANCED_DMA
/* Check on the presence of the DMA streams settings in mcuconf.h.*/
#if STM32_SPI_USE_SPI1 && (!defined(STM32_SPI_SPI1_RX_DMA_STREAM) ||        \
                           !defined(STM32_SPI_SPI1_TX_DMA_STREAM))
#error "SPI1 DMA streams not defined"
#endif

#if STM32_SPI_USE_SPI2 && (!defined(STM32_SPI_SPI2_RX_DMA_STREAM) ||        \
                           !defined(STM32_SPI_SPI2_TX_DMA_STREAM))
#error "SPI2 DMA streams not defined"
#endif

#if STM32_SPI_USE_SPI3 && (!defined(STM32_SPI_SPI3_RX_DMA_STREAM) ||        \
                           !defined(STM32_SPI_SPI3_TX_DMA_STREAM))
#error "SPI3 DMA streams not defined"
#endif

#if STM32_SPI_USE_SPI4 && (!defined(STM32_SPI_SPI4_RX_DMA_STREAM) ||        \
                           !defined(STM32_SPI_SPI4_TX_DMA_STREAM))
#error "SPI4 DMA streams not defined"
#endif

#if STM32_SPI_USE_SPI5 && (!defined(STM32_SPI_SPI5_RX_DMA_STREAM) ||        \
                           !defined(STM32_SPI_SPI5_TX_DMA_STREAM))
#error "SPI5 DMA streams not defined"
#endif

#if STM32_SPI_USE_SPI6 && (!defined(STM32_SPI_SPI6_RX_BDMA_STREAM) ||       \
                           !defined(STM32_SPI_SPI6_TX_BDMA_STREAM))
#error "SPI6 BDMA streams not defined"
#endif

/* Check on the validity of the assigned DMA channels.*/
#if STM32_SPI_USE_SPI1 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI1_RX_DMA_STREAM, STM32_SPI1_RX_DMA_MSK)
#error "invalid DMA stream associated to SPI1 RX"
#endif

#if STM32_SPI_USE_SPI1 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI1_TX_DMA_STREAM, STM32_SPI1_TX_DMA_MSK)
#error "invalid DMA stream associated to SPI1 TX"
#endif

#if STM32_SPI_USE_SPI2 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI2_RX_DMA_STREAM, STM32_SPI2_RX_DMA_MSK)
#error "invalid DMA stream associated to SPI2 RX"
#endif

#if STM32_SPI_USE_SPI2 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI2_TX_DMA_STREAM, STM32_SPI2_TX_DMA_MSK)
#error "invalid DMA stream associated to SPI2 TX"
#endif

#if STM32_SPI_USE_SPI3 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI3_RX_DMA_STREAM, STM32_SPI3_RX_DMA_MSK)
#error "invalid DMA stream associated to SPI3 RX"
#endif

#if STM32_SPI_USE_SPI3 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI3_TX_DMA_STREAM, STM32_SPI3_TX_DMA_MSK)
#error "invalid DMA stream associated to SPI3 TX"
#endif

#if STM32_SPI_USE_SPI4 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI4_RX_DMA_STREAM, STM32_SPI4_RX_DMA_MSK)
#error "invalid DMA stream associated to SPI4 RX"
#endif

#if STM32_SPI_USE_SPI4 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI4_TX_DMA_STREAM, STM32_SPI4_TX_DMA_MSK)
#error "invalid DMA stream associated to SPI4 TX"
#endif

#if STM32_SPI_USE_SPI5 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI5_RX_DMA_STREAM, STM32_SPI5_RX_DMA_MSK)
#error "invalid DMA stream associated to SPI5 RX"
#endif

#if STM32_SPI_USE_SPI5 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI5_TX_DMA_STREAM, STM32_SPI5_TX_DMA_MSK)
#error "invalid DMA stream associated to SPI5 TX"
#endif

#if STM32_SPI_USE_SPI6 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI6_RX_DMA_STREAM, STM32_SPI6_RX_DMA_MSK)
#error "invalid DMA stream associated to SPI6 RX"
#endif

#if STM32_SPI_USE_SPI6 &&                                                   \
    !STM32_DMA_IS_VALID_ID(STM32_SPI_SPI6_TX_DMA_STREAM, STM32_SPI6_TX_DMA_MSK)
#error "invalid DMA stream associated to SPI6 TX"
#endif
#endif /* STM32_ADVANCED_DMA */

#if !defined(STM32_DMA_REQUIRED)
#define STM32_DMA_REQUIRED
#endif

#if SPI_SELECT_MODE == SPI_SELECT_MODE_LLD
#error "SPI_SELECT_MODE_LLD not supported by this driver"
#endif


/*******************  Bit definition for SPI_CR1 register  ********************/
#define SPI_CR1_CPHA_Pos            (0U)
#define SPI_CR1_CPHA_Msk            (0x1U << SPI_CR1_CPHA_Pos)                 /*!< 0x00000001 */
#define SPI_CR1_CPHA                SPI_CR1_CPHA_Msk                           /*!<Clock Phase      */
#define SPI_CR1_CPOL_Pos            (1U)
#define SPI_CR1_CPOL_Msk            (0x1U << SPI_CR1_CPOL_Pos)                 /*!< 0x00000002 */
#define SPI_CR1_CPOL                SPI_CR1_CPOL_Msk                           /*!<Clock Polarity   */
#define SPI_CR1_MSTR_Pos            (2U)
#define SPI_CR1_MSTR_Msk            (0x1U << SPI_CR1_MSTR_Pos)                 /*!< 0x00000004 */
#define SPI_CR1_MSTR                SPI_CR1_MSTR_Msk                           /*!<Master Selection */

#define SPI_CR1_BR_Pos              (3U)
#define SPI_CR1_BR_Msk              (0x7U << SPI_CR1_BR_Pos)                   /*!< 0x00000038 */
#define SPI_CR1_BR                  SPI_CR1_BR_Msk                             /*!<BR[2:0] bits (Baud Rate Control) */
#define SPI_CR1_BR_0                (0x1U << SPI_CR1_BR_Pos)                   /*!< 0x00000008 */
#define SPI_CR1_BR_1                (0x2U << SPI_CR1_BR_Pos)                   /*!< 0x00000010 */
#define SPI_CR1_BR_2                (0x4U << SPI_CR1_BR_Pos)                   /*!< 0x00000020 */

#define SPI_CR1_SPE_Pos             (6U)
#define SPI_CR1_SPE_Msk             (0x1U << SPI_CR1_SPE_Pos)                  /*!< 0x00000040 */
#define SPI_CR1_SPE                 SPI_CR1_SPE_Msk                            /*!<SPI Enable                          */
#define SPI_CR1_LSBFIRST_Pos        (7U)
#define SPI_CR1_LSBFIRST_Msk        (0x1U << SPI_CR1_LSBFIRST_Pos)             /*!< 0x00000080 */
#define SPI_CR1_LSBFIRST            SPI_CR1_LSBFIRST_Msk                       /*!<Frame Format                        */
#define SPI_CR1_SSI_Pos             (8U)
#define SPI_CR1_SSI_Msk             (0x1U << SPI_CR1_SSI_Pos)                  /*!< 0x00000100 */
#define SPI_CR1_SSI                 SPI_CR1_SSI_Msk                            /*!<Internal slave select               */
#define SPI_CR1_SSM_Pos             (9U)
#define SPI_CR1_SSM_Msk             (0x1U << SPI_CR1_SSM_Pos)                  /*!< 0x00000200 */
#define SPI_CR1_SSM                 SPI_CR1_SSM_Msk                            /*!<Software slave management           */
#define SPI_CR1_RXONLY_Pos          (10U)
#define SPI_CR1_RXONLY_Msk          (0x1U << SPI_CR1_RXONLY_Pos)               /*!< 0x00000400 */
#define SPI_CR1_RXONLY              SPI_CR1_RXONLY_Msk                         /*!<Receive only                        */
#define SPI_CR1_DFF_Pos             (11U)
#define SPI_CR1_DFF_Msk             (0x1U << SPI_CR1_DFF_Pos)                  /*!< 0x00000800 */
#define SPI_CR1_DFF                 SPI_CR1_DFF_Msk                            /*!<Data Frame Format                   */
#define SPI_CR1_CRCNEXT_Pos         (12U)
#define SPI_CR1_CRCNEXT_Msk         (0x1U << SPI_CR1_CRCNEXT_Pos)              /*!< 0x00001000 */
#define SPI_CR1_CRCNEXT             SPI_CR1_CRCNEXT_Msk                        /*!<Transmit CRC next                   */
#define SPI_CR1_CRCEN_Pos           (13U)
#define SPI_CR1_CRCEN_Msk           (0x1U << SPI_CR1_CRCEN_Pos)                /*!< 0x00002000 */
#define SPI_CR1_CRCEN               SPI_CR1_CRCEN_Msk                          /*!<Hardware CRC calculation enable     */
#define SPI_CR1_BIDIOE_Pos          (14U)
#define SPI_CR1_BIDIOE_Msk          (0x1U << SPI_CR1_BIDIOE_Pos)               /*!< 0x00004000 */
#define SPI_CR1_BIDIOE              SPI_CR1_BIDIOE_Msk                         /*!<Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE_Pos        (15U)
#define SPI_CR1_BIDIMODE_Msk        (0x1U << SPI_CR1_BIDIMODE_Pos)             /*!< 0x00008000 */
#define SPI_CR1_BIDIMODE            SPI_CR1_BIDIMODE_Msk                       /*!<Bidirectional data mode enable      */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define SPI_CR2_RXDMAEN_Pos         (0U)
#define SPI_CR2_RXDMAEN_Msk         (0x1U << SPI_CR2_RXDMAEN_Pos)              /*!< 0x00000001 */
#define SPI_CR2_RXDMAEN             SPI_CR2_RXDMAEN_Msk                        /*!<Rx Buffer DMA Enable                 */
#define SPI_CR2_TXDMAEN_Pos         (1U)
#define SPI_CR2_TXDMAEN_Msk         (0x1U << SPI_CR2_TXDMAEN_Pos)              /*!< 0x00000002 */
#define SPI_CR2_TXDMAEN             SPI_CR2_TXDMAEN_Msk                        /*!<Tx Buffer DMA Enable                 */
#define SPI_CR2_SSOE_Pos            (2U)
#define SPI_CR2_SSOE_Msk            (0x1U << SPI_CR2_SSOE_Pos)                 /*!< 0x00000004 */
#define SPI_CR2_SSOE                SPI_CR2_SSOE_Msk                           /*!<SS Output Enable                     */
#define SPI_CR2_FRF_Pos             (4U)
#define SPI_CR2_FRF_Msk             (0x1U << SPI_CR2_FRF_Pos)                  /*!< 0x00000010 */
#define SPI_CR2_FRF                 SPI_CR2_FRF_Msk                            /*!<Frame Format                         */
#define SPI_CR2_ERRIE_Pos           (5U)
#define SPI_CR2_ERRIE_Msk           (0x1U << SPI_CR2_ERRIE_Pos)                /*!< 0x00000020 */
#define SPI_CR2_ERRIE               SPI_CR2_ERRIE_Msk                          /*!<Error Interrupt Enable               */
#define SPI_CR2_RXNEIE_Pos          (6U)
#define SPI_CR2_RXNEIE_Msk          (0x1U << SPI_CR2_RXNEIE_Pos)               /*!< 0x00000040 */
#define SPI_CR2_RXNEIE              SPI_CR2_RXNEIE_Msk                         /*!<RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE_Pos           (7U)
#define SPI_CR2_TXEIE_Msk           (0x1U << SPI_CR2_TXEIE_Pos)                /*!< 0x00000080 */
#define SPI_CR2_TXEIE               SPI_CR2_TXEIE_Msk                          /*!<Tx buffer Empty Interrupt Enable     */

/********************  Bit definition for SPI_SR register  ********************/
#define SPI_SR_RXNE_Pos             (0U)
#define SPI_SR_RXNE_Msk             (0x1U << SPI_SR_RXNE_Pos)                  /*!< 0x00000001 */
#define SPI_SR_RXNE                 SPI_SR_RXNE_Msk                            /*!<Receive buffer Not Empty */
#define SPI_SR_TXE_Pos              (1U)
#define SPI_SR_TXE_Msk              (0x1U << SPI_SR_TXE_Pos)                   /*!< 0x00000002 */
#define SPI_SR_TXE                  SPI_SR_TXE_Msk                             /*!<Transmit buffer Empty    */
#define SPI_SR_CHSIDE_Pos           (2U)
#define SPI_SR_CHSIDE_Msk           (0x1U << SPI_SR_CHSIDE_Pos)                /*!< 0x00000004 */
#define SPI_SR_CHSIDE               SPI_SR_CHSIDE_Msk                          /*!<Channel side             */
#define SPI_SR_UDR_Pos              (3U)
#define SPI_SR_UDR_Msk              (0x1U << SPI_SR_UDR_Pos)                   /*!< 0x00000008 */
#define SPI_SR_UDR                  SPI_SR_UDR_Msk                             /*!<Underrun flag            */
#define SPI_SR_CRCERR_Pos           (4U)
#define SPI_SR_CRCERR_Msk           (0x1U << SPI_SR_CRCERR_Pos)                /*!< 0x00000010 */
#define SPI_SR_CRCERR               SPI_SR_CRCERR_Msk                          /*!<CRC Error flag           */
#define SPI_SR_MODF_Pos             (5U)
#define SPI_SR_MODF_Msk             (0x1U << SPI_SR_MODF_Pos)                  /*!< 0x00000020 */
#define SPI_SR_MODF                 SPI_SR_MODF_Msk                            /*!<Mode fault               */
#define SPI_SR_OVR_Pos              (6U)
#define SPI_SR_OVR_Msk              (0x1U << SPI_SR_OVR_Pos)                   /*!< 0x00000040 */
#define SPI_SR_OVR                  SPI_SR_OVR_Msk                             /*!<Overrun flag             */
#define SPI_SR_BSY_Pos              (7U)
#define SPI_SR_BSY_Msk              (0x1U << SPI_SR_BSY_Pos)                   /*!< 0x00000080 */
#define SPI_SR_BSY                  SPI_SR_BSY_Msk                             /*!<Busy flag                */
#define SPI_SR_FRE_Pos              (8U)
#define SPI_SR_FRE_Msk              (0x1U << SPI_SR_FRE_Pos)                   /*!< 0x00000100 */
#define SPI_SR_FRE                  SPI_SR_FRE_Msk                             /*!<Frame format error flag  */

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#define spi_lld_driver_fields                                               \
  /* Pointer to the SPIx registers block.*/                                 \
  spi_type               *spi;                                           \
  /** DMA type for this instance.*/                                         \
  bool                      is_bdma;                                        \
  /* Receive DMA stream.*/                                                  \
  const stm32_dma_stream_t  *dmarx;                                         \
  /* Transmit DMA stream.*/                                                 \
  const stm32_dma_stream_t  *dmatx;                                         \
  /* RX DMA mode bit mask.*/                                                \
  uint32_t                  rxdmamode;                                      \
  /* TX DMA mode bit mask.*/                                                \
  uint32_t                  txdmamode;                                      \
  /* Sink for discarded data.*/                                             \
  uint32_t                  rxsink;                                         \
  /* Source for default TX pattern.*/                                       \
  uint32_t                  txsource

/**
 * @brief   Low level fields of the SPI configuration structure.
 */
#define spi_lld_config_fields                                               \
  /* SPI CR1 register initialization data.*/                                \
  uint16_t                  cr1;                                            \
  /* SPI CR2 register initialization data.*/                                \
  uint16_t                  cr2

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_SPI_USE_SPI1 && !defined(__DOXYGEN__)
extern SPIDriver SPID1;
#endif

#if STM32_SPI_USE_SPI2 && !defined(__DOXYGEN__)
extern SPIDriver SPID2;
#endif

#if STM32_SPI_USE_SPI3 && !defined(__DOXYGEN__)
extern SPIDriver SPID3;
#endif

#if STM32_SPI_USE_SPI4 && !defined(__DOXYGEN__)
extern SPIDriver SPID4;
#endif

#if STM32_SPI_USE_SPI5 && !defined(__DOXYGEN__)
extern SPIDriver SPID5;
#endif

#if STM32_SPI_USE_SPI6 && !defined(__DOXYGEN__)
extern SPIDriver SPID6;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void spi_lld_init(void);
  msg_t spi_lld_start(SPIDriver *spip);
  void spi_lld_stop(SPIDriver *spip);
#if (SPI_SELECT_MODE == SPI_SELECT_MODE_LLD) || defined(__DOXYGEN__)
  void spi_lld_select(SPIDriver *spip);
  void spi_lld_unselect(SPIDriver *spip);
#endif
  msg_t spi_lld_ignore(SPIDriver *spip, size_t n);
  msg_t spi_lld_exchange(SPIDriver *spip, size_t n,
                         const void *txbuf, void *rxbuf);
  msg_t spi_lld_send(SPIDriver *spip, size_t n, const void *txbuf);
  msg_t spi_lld_receive(SPIDriver *spip, size_t n, void *rxbuf);
  msg_t spi_lld_stop_transfer(SPIDriver *spip, size_t *sizep);
  uint16_t spi_lld_polled_exchange(SPIDriver *spip, uint16_t frame);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SPI */

#endif /* HAL_SPI_V2_LLD_H */

/** @} */
