/*
    ChibiOS - Copyright (C) 2006..2019 Giovanni Di Sirio

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
 * @file    DMAv2/stm32_dma.h
 * @brief   Enhanced-DMA helper driver header.
 *
 * @addtogroup STM32_DMA
 * @{
 */

#ifndef STM32_DMA_H
#define STM32_DMA_H

#if 1
/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   DMA capability.
 * @details if @p TRUE then the DMA is able of burst transfers, FIFOs,
 *          scatter gather and other advanced features.
 */
#define STM32_DMA_ADVANCED          TRUE

/**
 * @brief   Total number of DMA streams.
 * @details This is the total number of streams among all the DMA units.
 */
#define STM32_DMA_STREAMS           8U

/**
 * @brief   Mask of the ISR bits passed to the DMA callback functions.
 */
#define STM32_DMA_ISR_MASK          0x3DU

/**
 * @brief   Returns the channel associated to the specified stream.
 *
 * @param[in] id        the unique numeric stream identifier
 * @param[in] c         a stream/channel association word, one channel per
 *                      nibble
 * @return              Returns the channel associated to the stream.
 */
#define STM32_DMA_GETCHANNEL(id, c) (((c) >> (((id) & 7U) * 4U)) & 15U)

/**
 * @brief   Checks if a DMA priority is within the valid range.
 * @param[in] prio      DMA priority
 *
 * @retval              The check result.
 * @retval false        invalid DMA priority.
 * @retval true         correct DMA priority.
 */
#define STM32_DMA_IS_VALID_PRIORITY(prio) (((prio) >= 0U) && ((prio) <= 3U))

#if (STM32_DMA_SUPPORTS_DMAMUX == FALSE) || defined(_DOXYGEN__)
/**
 * @brief   Checks if a DMA stream id is within the valid range.
 *
 * @param[in] id        DMA stream id
 * @retval              The check result.
 * @retval false        invalid DMA stream.
 * @retval true         correct DMA stream.
 */
#define STM32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= STM32_DMA_STREAMS))
#else /* STM32_DMA_SUPPORTS_DMAMUX == FALSE */
#if STM32_HAS_DMA2 == TRUE
#define STM32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= (STM32_DMA_STREAMS + 2)))
#else
#define STM32_DMA_IS_VALID_STREAM(id) (((id) >= 0U) &&                      \
                                       ((id) <= (STM32_DMA_STREAMS + 1)))
#endif
#endif /* STM32_DMA_SUPPORTS_DMAMUX == FALSE */

/**
 * @brief   Returns an unique numeric identifier for a DMA stream.
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              An unique numeric stream identifier.
 */
#define STM32_DMA_STREAM_ID(dma, stream) ((((dma) - 1U) * 8U) + (stream))

/**
 * @brief   Returns a DMA stream identifier mask.
 *
 *
 * @param[in] dma       the DMA unit number
 * @param[in] stream    the stream number
 * @return              A DMA stream identifier mask.
 */
#define STM32_DMA_STREAM_ID_MSK(dma, stream)                                \
  (1U << STM32_DMA_STREAM_ID(dma, stream))

/**
 * @brief   Checks if a DMA stream unique identifier belongs to a mask.
 * @param[in] id        the stream numeric identifier
 * @param[in] mask      the stream numeric identifiers mask
 *
 * @retval              The check result.
 * @retval false        id does not belong to the mask.
 * @retval true         id belongs to the mask.
 */
#define STM32_DMA_IS_VALID_ID(id, mask) (((1U << (id)) & (mask)))

#if (STM32_DMA_SUPPORTS_DMAMUX == TRUE) || defined(_DOXYGEN__)
/**
 * @name    Special stream identifiers
 * @{
 */
#define STM32_DMA_STREAM_ID_ANY         STM32_DMA_STREAMS
#define STM32_DMA_STREAM_ID_ANY_DMA1    (STM32_DMA_STREAM_ID_ANY + 1)
#if STM32_HAS_DMA2 == TRUE
#define STM32_DMA_STREAM_ID_ANY_DMA2    (STM32_DMA_STREAM_ID_ANY_DMA1 + 1)
#endif
/** @} */
#endif

/**
 * @name    DMA streams identifiers
 * @{
 */
/**
 * @brief   Returns a pointer to a stm32_dma_stream_t structure.
 *
 * @param[in] id        the stream numeric identifier
 * @return              A pointer to the stm32_dma_stream_t constant structure
 *                      associated to the DMA stream.
 */
#define STM32_DMA_STREAM(id)        (&_stm32_dma_streams[id])

#define STM32_DMA1_STREAM0          STM32_DMA_STREAM(0)
#define STM32_DMA1_STREAM1          STM32_DMA_STREAM(1)
#define STM32_DMA1_STREAM2          STM32_DMA_STREAM(2)
#define STM32_DMA1_STREAM3          STM32_DMA_STREAM(3)
#define STM32_DMA1_STREAM4          STM32_DMA_STREAM(4)
#define STM32_DMA1_STREAM5          STM32_DMA_STREAM(5)
#define STM32_DMA1_STREAM6          STM32_DMA_STREAM(6)
#define STM32_DMA1_STREAM7          STM32_DMA_STREAM(7)
#define STM32_DMA2_STREAM0          STM32_DMA_STREAM(8)
#define STM32_DMA2_STREAM1          STM32_DMA_STREAM(9)
#define STM32_DMA2_STREAM2          STM32_DMA_STREAM(10)
#define STM32_DMA2_STREAM3          STM32_DMA_STREAM(11)
#define STM32_DMA2_STREAM4          STM32_DMA_STREAM(12)
#define STM32_DMA2_STREAM5          STM32_DMA_STREAM(13)
#define STM32_DMA2_STREAM6          STM32_DMA_STREAM(14)
#define STM32_DMA2_STREAM7          STM32_DMA_STREAM(15)
/** @} */

/**
 * @name    CR register constants common to all DMA types
 * @{
 */

/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/
/********************  Bits definition for DMA_SxCR register  *****************/
#define DMA_SxCR_CHSEL_Pos       (25U)
#define DMA_SxCR_CHSEL_Msk       (0x7U << DMA_SxCR_CHSEL_Pos)                  /*!< 0x0E000000 */
#define DMA_SxCR_CHSEL           DMA_SxCR_CHSEL_Msk
#define DMA_SxCR_CHSEL_0         0x02000000U
#define DMA_SxCR_CHSEL_1         0x04000000U
#define DMA_SxCR_CHSEL_2         0x08000000U
#define DMA_SxCR_MBURST_Pos      (23U)
#define DMA_SxCR_MBURST_Msk      (0x3U << DMA_SxCR_MBURST_Pos)                 /*!< 0x01800000 */
#define DMA_SxCR_MBURST          DMA_SxCR_MBURST_Msk
#define DMA_SxCR_MBURST_0        (0x1U << DMA_SxCR_MBURST_Pos)                 /*!< 0x00800000 */
#define DMA_SxCR_MBURST_1        (0x2U << DMA_SxCR_MBURST_Pos)                 /*!< 0x01000000 */
#define DMA_SxCR_PBURST_Pos      (21U)
#define DMA_SxCR_PBURST_Msk      (0x3U << DMA_SxCR_PBURST_Pos)                 /*!< 0x00600000 */
#define DMA_SxCR_PBURST          DMA_SxCR_PBURST_Msk
#define DMA_SxCR_PBURST_0        (0x1U << DMA_SxCR_PBURST_Pos)                 /*!< 0x00200000 */
#define DMA_SxCR_PBURST_1        (0x2U << DMA_SxCR_PBURST_Pos)                 /*!< 0x00400000 */
#define DMA_SxCR_CT_Pos          (19U)
#define DMA_SxCR_CT_Msk          (0x1U << DMA_SxCR_CT_Pos)                     /*!< 0x00080000 */
#define DMA_SxCR_CT              DMA_SxCR_CT_Msk
#define DMA_SxCR_DBM_Pos         (18U)
#define DMA_SxCR_DBM_Msk         (0x1U << DMA_SxCR_DBM_Pos)                    /*!< 0x00040000 */
#define DMA_SxCR_DBM             DMA_SxCR_DBM_Msk
#define DMA_SxCR_PL_Pos          (16U)
#define DMA_SxCR_PL_Msk          (0x3U << DMA_SxCR_PL_Pos)                     /*!< 0x00030000 */
#define DMA_SxCR_PL              DMA_SxCR_PL_Msk
#define DMA_SxCR_PL_0            (0x1U << DMA_SxCR_PL_Pos)                     /*!< 0x00010000 */
#define DMA_SxCR_PL_1            (0x2U << DMA_SxCR_PL_Pos)                     /*!< 0x00020000 */
#define DMA_SxCR_PINCOS_Pos      (15U)
#define DMA_SxCR_PINCOS_Msk      (0x1U << DMA_SxCR_PINCOS_Pos)                 /*!< 0x00008000 */
#define DMA_SxCR_PINCOS          DMA_SxCR_PINCOS_Msk
#define DMA_SxCR_MSIZE_Pos       (13U)
#define DMA_SxCR_MSIZE_Msk       (0x3U << DMA_SxCR_MSIZE_Pos)                  /*!< 0x00006000 */
#define DMA_SxCR_MSIZE           DMA_SxCR_MSIZE_Msk
#define DMA_SxCR_MSIZE_0         (0x1U << DMA_SxCR_MSIZE_Pos)                  /*!< 0x00002000 */
#define DMA_SxCR_MSIZE_1         (0x2U << DMA_SxCR_MSIZE_Pos)                  /*!< 0x00004000 */
#define DMA_SxCR_PSIZE_Pos       (11U)
#define DMA_SxCR_PSIZE_Msk       (0x3U << DMA_SxCR_PSIZE_Pos)                  /*!< 0x00001800 */
#define DMA_SxCR_PSIZE           DMA_SxCR_PSIZE_Msk
#define DMA_SxCR_PSIZE_0         (0x1U << DMA_SxCR_PSIZE_Pos)                  /*!< 0x00000800 */
#define DMA_SxCR_PSIZE_1         (0x2U << DMA_SxCR_PSIZE_Pos)                  /*!< 0x00001000 */
#define DMA_SxCR_MINC_Pos        (10U)
#define DMA_SxCR_MINC_Msk        (0x1U << DMA_SxCR_MINC_Pos)                   /*!< 0x00000400 */
#define DMA_SxCR_MINC            DMA_SxCR_MINC_Msk
#define DMA_SxCR_PINC_Pos        (9U)
#define DMA_SxCR_PINC_Msk        (0x1U << DMA_SxCR_PINC_Pos)                   /*!< 0x00000200 */
#define DMA_SxCR_PINC            DMA_SxCR_PINC_Msk
#define DMA_SxCR_CIRC_Pos        (8U)
#define DMA_SxCR_CIRC_Msk        (0x1U << DMA_SxCR_CIRC_Pos)                   /*!< 0x00000100 */
#define DMA_SxCR_CIRC            DMA_SxCR_CIRC_Msk
#define DMA_SxCR_DIR_Pos         (6U)
#define DMA_SxCR_DIR_Msk         (0x3U << DMA_SxCR_DIR_Pos)                    /*!< 0x000000C0 */
#define DMA_SxCR_DIR             DMA_SxCR_DIR_Msk
#define DMA_SxCR_DIR_0           (0x1U << DMA_SxCR_DIR_Pos)                    /*!< 0x00000040 */
#define DMA_SxCR_DIR_1           (0x2U << DMA_SxCR_DIR_Pos)                    /*!< 0x00000080 */
#define DMA_SxCR_PFCTRL_Pos      (5U)
#define DMA_SxCR_PFCTRL_Msk      (0x1U << DMA_SxCR_PFCTRL_Pos)                 /*!< 0x00000020 */
#define DMA_SxCR_PFCTRL          DMA_SxCR_PFCTRL_Msk
#define DMA_SxCR_TCIE_Pos        (4U)
#define DMA_SxCR_TCIE_Msk        (0x1U << DMA_SxCR_TCIE_Pos)                   /*!< 0x00000010 */
#define DMA_SxCR_TCIE            DMA_SxCR_TCIE_Msk
#define DMA_SxCR_HTIE_Pos        (3U)
#define DMA_SxCR_HTIE_Msk        (0x1U << DMA_SxCR_HTIE_Pos)                   /*!< 0x00000008 */
#define DMA_SxCR_HTIE            DMA_SxCR_HTIE_Msk
#define DMA_SxCR_TEIE_Pos        (2U)
#define DMA_SxCR_TEIE_Msk        (0x1U << DMA_SxCR_TEIE_Pos)                   /*!< 0x00000004 */
#define DMA_SxCR_TEIE            DMA_SxCR_TEIE_Msk
#define DMA_SxCR_DMEIE_Pos       (1U)
#define DMA_SxCR_DMEIE_Msk       (0x1U << DMA_SxCR_DMEIE_Pos)                  /*!< 0x00000002 */
#define DMA_SxCR_DMEIE           DMA_SxCR_DMEIE_Msk
#define DMA_SxCR_EN_Pos          (0U)
#define DMA_SxCR_EN_Msk          (0x1U << DMA_SxCR_EN_Pos)                     /*!< 0x00000001 */
#define DMA_SxCR_EN              DMA_SxCR_EN_Msk

/********************  Bits definition for DMA_LISR register  *****************/
#define DMA_LISR_TCIF3_Pos       (27U)
#define DMA_LISR_TCIF3_Msk       (0x1U << DMA_LISR_TCIF3_Pos)                  /*!< 0x08000000 */
#define DMA_LISR_TCIF3           DMA_LISR_TCIF3_Msk
#define DMA_LISR_HTIF3_Pos       (26U)
#define DMA_LISR_HTIF3_Msk       (0x1U << DMA_LISR_HTIF3_Pos)                  /*!< 0x04000000 */
#define DMA_LISR_HTIF3           DMA_LISR_HTIF3_Msk
#define DMA_LISR_TEIF3_Pos       (25U)
#define DMA_LISR_TEIF3_Msk       (0x1U << DMA_LISR_TEIF3_Pos)                  /*!< 0x02000000 */
#define DMA_LISR_TEIF3           DMA_LISR_TEIF3_Msk
#define DMA_LISR_DMEIF3_Pos      (24U)
#define DMA_LISR_DMEIF3_Msk      (0x1U << DMA_LISR_DMEIF3_Pos)                 /*!< 0x01000000 */
#define DMA_LISR_DMEIF3          DMA_LISR_DMEIF3_Msk
#define DMA_LISR_FEIF3_Pos       (22U)
#define DMA_LISR_FEIF3_Msk       (0x1U << DMA_LISR_FEIF3_Pos)                  /*!< 0x00400000 */
#define DMA_LISR_FEIF3           DMA_LISR_FEIF3_Msk
#define DMA_LISR_TCIF2_Pos       (21U)
#define DMA_LISR_TCIF2_Msk       (0x1U << DMA_LISR_TCIF2_Pos)                  /*!< 0x00200000 */
#define DMA_LISR_TCIF2           DMA_LISR_TCIF2_Msk
#define DMA_LISR_HTIF2_Pos       (20U)
#define DMA_LISR_HTIF2_Msk       (0x1U << DMA_LISR_HTIF2_Pos)                  /*!< 0x00100000 */
#define DMA_LISR_HTIF2           DMA_LISR_HTIF2_Msk
#define DMA_LISR_TEIF2_Pos       (19U)
#define DMA_LISR_TEIF2_Msk       (0x1U << DMA_LISR_TEIF2_Pos)                  /*!< 0x00080000 */
#define DMA_LISR_TEIF2           DMA_LISR_TEIF2_Msk
#define DMA_LISR_DMEIF2_Pos      (18U)
#define DMA_LISR_DMEIF2_Msk      (0x1U << DMA_LISR_DMEIF2_Pos)                 /*!< 0x00040000 */
#define DMA_LISR_DMEIF2          DMA_LISR_DMEIF2_Msk
#define DMA_LISR_FEIF2_Pos       (16U)
#define DMA_LISR_FEIF2_Msk       (0x1U << DMA_LISR_FEIF2_Pos)                  /*!< 0x00010000 */
#define DMA_LISR_FEIF2           DMA_LISR_FEIF2_Msk
#define DMA_LISR_TCIF1_Pos       (11U)
#define DMA_LISR_TCIF1_Msk       (0x1U << DMA_LISR_TCIF1_Pos)                  /*!< 0x00000800 */
#define DMA_LISR_TCIF1           DMA_LISR_TCIF1_Msk
#define DMA_LISR_HTIF1_Pos       (10U)
#define DMA_LISR_HTIF1_Msk       (0x1U << DMA_LISR_HTIF1_Pos)                  /*!< 0x00000400 */
#define DMA_LISR_HTIF1           DMA_LISR_HTIF1_Msk
#define DMA_LISR_TEIF1_Pos       (9U)
#define DMA_LISR_TEIF1_Msk       (0x1U << DMA_LISR_TEIF1_Pos)                  /*!< 0x00000200 */
#define DMA_LISR_TEIF1           DMA_LISR_TEIF1_Msk
#define DMA_LISR_DMEIF1_Pos      (8U)
#define DMA_LISR_DMEIF1_Msk      (0x1U << DMA_LISR_DMEIF1_Pos)                 /*!< 0x00000100 */
#define DMA_LISR_DMEIF1          DMA_LISR_DMEIF1_Msk
#define DMA_LISR_FEIF1_Pos       (6U)
#define DMA_LISR_FEIF1_Msk       (0x1U << DMA_LISR_FEIF1_Pos)                  /*!< 0x00000040 */
#define DMA_LISR_FEIF1           DMA_LISR_FEIF1_Msk
#define DMA_LISR_TCIF0_Pos       (5U)
#define DMA_LISR_TCIF0_Msk       (0x1U << DMA_LISR_TCIF0_Pos)                  /*!< 0x00000020 */
#define DMA_LISR_TCIF0           DMA_LISR_TCIF0_Msk
#define DMA_LISR_HTIF0_Pos       (4U)
#define DMA_LISR_HTIF0_Msk       (0x1U << DMA_LISR_HTIF0_Pos)                  /*!< 0x00000010 */
#define DMA_LISR_HTIF0           DMA_LISR_HTIF0_Msk
#define DMA_LISR_TEIF0_Pos       (3U)
#define DMA_LISR_TEIF0_Msk       (0x1U << DMA_LISR_TEIF0_Pos)                  /*!< 0x00000008 */
#define DMA_LISR_TEIF0           DMA_LISR_TEIF0_Msk
#define DMA_LISR_DMEIF0_Pos      (2U)
#define DMA_LISR_DMEIF0_Msk      (0x1U << DMA_LISR_DMEIF0_Pos)                 /*!< 0x00000004 */
#define DMA_LISR_DMEIF0          DMA_LISR_DMEIF0_Msk
#define DMA_LISR_FEIF0_Pos       (0U)
#define DMA_LISR_FEIF0_Msk       (0x1U << DMA_LISR_FEIF0_Pos)                  /*!< 0x00000001 */

#define STM32_DMA_CR_RESET_VALUE    0x00000000U
#define STM32_DMA_CR_EN             DMA_SxCR_EN
#define STM32_DMA_CR_TEIE           DMA_SxCR_TEIE
#define STM32_DMA_CR_HTIE           DMA_SxCR_HTIE
#define STM32_DMA_CR_TCIE           DMA_SxCR_TCIE
#define STM32_DMA_CR_PFCTRL         DMA_SxCR_PFCTRL
#define STM32_DMA_CR_DIR_MASK       DMA_SxCR_DIR
#define STM32_DMA_CR_DIR_P2M        0
#define STM32_DMA_CR_DIR_M2P        DMA_SxCR_DIR_0
#define STM32_DMA_CR_DIR_M2M        DMA_SxCR_DIR_1
#define STM32_DMA_CR_CIRC           DMA_SxCR_CIRC
#define STM32_DMA_CR_PINC           DMA_SxCR_PINC
#define STM32_DMA_CR_MINC           DMA_SxCR_MINC
#define STM32_DMA_CR_PSIZE_MASK     DMA_SxCR_PSIZE
#define STM32_DMA_CR_PSIZE_BYTE     0
#define STM32_DMA_CR_PSIZE_HWORD    DMA_SxCR_PSIZE_0
#define STM32_DMA_CR_PSIZE_WORD     DMA_SxCR_PSIZE_1
#define STM32_DMA_CR_MSIZE_MASK     DMA_SxCR_MSIZE
#define STM32_DMA_CR_MSIZE_BYTE     0
#define STM32_DMA_CR_MSIZE_HWORD    DMA_SxCR_MSIZE_0
#define STM32_DMA_CR_MSIZE_WORD     DMA_SxCR_MSIZE_1
#define STM32_DMA_CR_SIZE_MASK      (STM32_DMA_CR_PSIZE_MASK |              \
                                     STM32_DMA_CR_MSIZE_MASK)
#define STM32_DMA_CR_PL_MASK        DMA_SxCR_PL
#define STM32_DMA_CR_PL(n)          ((n) << 16U)


/********************  Bits definition for DMA_SxFCR register  ****************/
#define DMA_SxFCR_FEIE_Pos       (7U)
#define DMA_SxFCR_FEIE_Msk       (0x1U << DMA_SxFCR_FEIE_Pos)                  /*!< 0x00000080 */
#define DMA_SxFCR_FEIE           DMA_SxFCR_FEIE_Msk
#define DMA_SxFCR_FS_Pos         (3U)
#define DMA_SxFCR_FS_Msk         (0x7U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000038 */
#define DMA_SxFCR_FS             DMA_SxFCR_FS_Msk
#define DMA_SxFCR_FS_0           (0x1U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000008 */
#define DMA_SxFCR_FS_1           (0x2U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000010 */
#define DMA_SxFCR_FS_2           (0x4U << DMA_SxFCR_FS_Pos)                    /*!< 0x00000020 */
#define DMA_SxFCR_DMDIS_Pos      (2U)
#define DMA_SxFCR_DMDIS_Msk      (0x1U << DMA_SxFCR_DMDIS_Pos)                 /*!< 0x00000004 */
#define DMA_SxFCR_DMDIS          DMA_SxFCR_DMDIS_Msk
#define DMA_SxFCR_FTH_Pos        (0U)
#define DMA_SxFCR_FTH_Msk        (0x3U << DMA_SxFCR_FTH_Pos)                   /*!< 0x00000003 */
#define DMA_SxFCR_FTH            DMA_SxFCR_FTH_Msk
#define DMA_SxFCR_FTH_0          (0x1U << DMA_SxFCR_FTH_Pos)                   /*!< 0x00000001 */
#define DMA_SxFCR_FTH_1          (0x2U << DMA_SxFCR_FTH_Pos)                   /*!< 0x00000002 */
/** @} */

/**
 * @name    CR register constants only found in DMAv2
 * @{
 */
#define STM32_DMA_CR_DMEIE          DMA_SxCR_DMEIE
#define STM32_DMA_CR_PFCTRL         DMA_SxCR_PFCTRL
#define STM32_DMA_CR_PINCOS         DMA_SxCR_PINCOS
#define STM32_DMA_CR_DBM            DMA_SxCR_DBM
#define STM32_DMA_CR_CT             DMA_SxCR_CT
#define STM32_DMA_CR_PBURST_MASK    DMA_SxCR_PBURST
#define STM32_DMA_CR_PBURST_SINGLE  0U
#define STM32_DMA_CR_PBURST_INCR4   DMA_SxCR_PBURST_0
#define STM32_DMA_CR_PBURST_INCR8   DMA_SxCR_PBURST_1
#define STM32_DMA_CR_PBURST_INCR16  (DMA_SxCR_PBURST_0 | DMA_SxCR_PBURST_1)
#define STM32_DMA_CR_MBURST_MASK    DMA_SxCR_MBURST
#define STM32_DMA_CR_MBURST_SINGLE  0U
#define STM32_DMA_CR_MBURST_INCR4   DMA_SxCR_MBURST_0
#define STM32_DMA_CR_MBURST_INCR8   DMA_SxCR_MBURST_1
#define STM32_DMA_CR_MBURST_INCR16  (DMA_SxCR_MBURST_0 | DMA_SxCR_MBURST_1)
#if (STM32_DMA_SUPPORTS_DMAMUX == FALSE) || defined(__DOXYGEN__)
#define STM32_DMA_CR_CHSEL_MASK     DMA_SxCR_CHSEL
#define STM32_DMA_CR_CHSEL(n)       ((n) << 25U)
#else
#define STM32_DMA_CR_CHSEL_MASK     0U
#define STM32_DMA_CR_CHSEL(n)       0U
#endif
/** @} */

/**
 * @name    FCR register constants only found in DMAv2
 * @{
 */
#define STM32_DMA_FCR_RESET_VALUE   0x00000021U
#define STM32_DMA_FCR_FEIE          DMA_SxFCR_FEIE
#define STM32_DMA_FCR_FS_MASK       DMA_SxFCR_FS
#define STM32_DMA_FCR_DMDIS         DMA_SxFCR_DMDIS
#define STM32_DMA_FCR_FTH_MASK      DMA_SxFCR_FTH
#define STM32_DMA_FCR_FTH_1Q        0
#define STM32_DMA_FCR_FTH_HALF      DMA_SxFCR_FTH_0
#define STM32_DMA_FCR_FTH_3Q        DMA_SxFCR_FTH_1
#define STM32_DMA_FCR_FTH_FULL      (DMA_SxFCR_FTH_0 | DMA_SxFCR_FTH_1)
/** @} */

/**
 * @name    Status flags passed to the ISR callbacks
 */
#define STM32_DMA_ISR_FEIF          DMA_LISR_FEIF0
#define STM32_DMA_ISR_DMEIF         DMA_LISR_DMEIF0
#define STM32_DMA_ISR_TEIF          DMA_LISR_TEIF0
#define STM32_DMA_ISR_HTIF          DMA_LISR_HTIF0
#define STM32_DMA_ISR_TCIF          DMA_LISR_TCIF0
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !defined(STM32_DMA_SUPPORTS_DMAMUX)
#error "STM32_DMA_SUPPORTS_DMAMUX not defined in registry"
#endif

#if !defined(STM32_HAS_DMA1)
#error "STM32_HAS_DMA1 missing in registry"
#endif

#if !defined(STM32_HAS_DMA2)
#error "STM32_HAS_DMA2 missing in registry"
#endif

#if !defined(STM32_DMA1_CH0_HANDLER)
#error "STM32_DMA1_CH0_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH1_HANDLER)
#error "STM32_DMA1_CH1_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH2_HANDLER)
#error "STM32_DMA1_CH2_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH3_HANDLER)
#error "STM32_DMA1_CH3_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH4_HANDLER)
#error "STM32_DMA1_CH4_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH5_HANDLER)
#error "STM32_DMA1_CH5_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH6_HANDLER)
#error "STM32_DMA1_CH6_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH7_HANDLER)
#error "STM32_DMA1_CH7_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH0_HANDLER)
#error "STM32_DMA2_CH0_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH1_HANDLER)
#error "STM32_DMA2_CH1_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH2_HANDLER)
#error "STM32_DMA2_CH2_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH3_HANDLER)
#error "STM32_DMA2_CH3_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH4_HANDLER)
#error "STM32_DMA2_CH4_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH5_HANDLER)
#error "STM32_DMA2_CH5_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH6_HANDLER)
#error "STM32_DMA2_CH6_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA2_CH7_HANDLER)
#error "STM32_DMA2_CH7_HANDLER missing in registry"
#endif

#if !defined(STM32_DMA1_CH0_NUMBER)
#error "STM32_DMA1_CH0_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH1_NUMBER)
#error "STM32_DMA1_CH1_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH2_NUMBER)
#error "STM32_DMA1_CH2_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH3_NUMBER)
#error "STM32_DMA1_CH3_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH4_NUMBER)
#error "STM32_DMA1_CH4_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH5_NUMBER)
#error "STM32_DMA1_CH5_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH6_NUMBER)
#error "STM32_DMA1_CH6_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA1_CH7_NUMBER)
#error "STM32_DMA1_CH7_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH0_NUMBER)
#error "STM32_DMA2_CH0_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH1_NUMBER)
#error "STM32_DMA2_CH1_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH2_NUMBER)
#error "STM32_DMA2_CH2_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH3_NUMBER)
#error "STM32_DMA2_CH3_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH4_NUMBER)
#error "STM32_DMA2_CH4_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH5_NUMBER)
#error "STM32_DMA2_CH5_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH6_NUMBER)
#error "STM32_DMA2_CH6_NUMBER missing in registry"
#endif

#if !defined(STM32_DMA2_CH7_NUMBER)
#error "STM32_DMA2_CH7_NUMBER missing in registry"
#endif

#if (STM32_DMA_SUPPORTS_DMAMUX == TRUE) || defined(__DOXYGEN__)
#include "stm32_dmamux.h"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   STM32 DMA ISR function type.
 *
 * @param[in] p         parameter for the registered function
 * @param[in] flags     pre-shifted content of the xISR register, the bits
 *                      are aligned to bit zero
 */
typedef void (*stm32_dmaisr_t)(void *p, uint32_t flags);

/**
 * @brief   STM32 DMA stream descriptor structure.
 */
typedef struct {
	edma_stream_type    *stream;        /**< @brief Associated DMA stream.  */
  volatile uint32_t     *ifcr;          /**< @brief Associated IFCR reg.    */
#if (STM32_DMA_SUPPORTS_DMAMUX == TRUE) || defined(__DOXYGEN__)
  DMAMUX_Channel_TypeDef *mux;          /**< @brief Associated DMA mux.     */
#else
  uint8_t               dummy;          /**< @brief Filler.                 */
#endif
  uint8_t               shift;          /**< @brief Bits offset in xIFCR
                                             register.                      */
  uint8_t               selfindex;      /**< @brief Index to self in array. */
  uint8_t               vector;         /**< @brief Associated IRQ vector.  */
} stm32_dma_stream_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Associates a peripheral data register to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] addr      value to be written in the PAR register
 *
 * @special
 */
#define dmaStreamSetPeripheral(dmastp, addr) {                              \
  (dmastp)->stream->paddr  = (uint32_t)(addr);                                \
}

/**
 * @brief   Associates a memory destination to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] addr      value to be written in the M0AR register
 *
 * @special
 */
#define dmaStreamSetMemory0(dmastp, addr) {                                 \
  (dmastp)->stream->m0addr  = (uint32_t)(addr);                               \
}

/**
 * @brief   Associates an alternate memory destination to a DMA stream.
 * @note    This function can be invoked in both ISR or thread context.
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] addr      value to be written in the M1AR register
 *
 * @special
 */
#define dmaStreamSetMemory1(dmastp, addr) {                                 \
  (dmastp)->stream->m1addr  = (uint32_t)(addr);                               \
}

/**
 * @brief   Sets the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] size      value to be written in the CNDTR register
 *
 * @special
 */
#define dmaStreamSetTransactionSize(dmastp, size) {                         \
  (dmastp)->stream->dtcnt  = (uint32_t)(size);                               \
}

/**
 * @brief   Returns the number of transfers to be performed.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @return              The number of transfers to be performed.
 *
 * @special
 */
#define dmaStreamGetTransactionSize(dmastp) ((size_t)((dmastp)->stream->dtcnt))

/**
 * @brief   Programs the stream mode settings.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] mode      value to be written in the CR register
 *
 * @special
 */
#define dmaStreamSetMode(dmastp, mode) {                                    \
  (dmastp)->stream->ctrl  = (uint32_t)(mode);                                 \
}

/**
 * @brief   Programs the stream FIFO settings.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] mode      value to be written in the FCR register
 *
 * @special
 */
#define dmaStreamSetFIFO(dmastp, mode) {                                    \
  (dmastp)->stream->fctrl = (uint32_t)(mode);                                 \
}

/**
 * @brief   DMA stream enable.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamEnable(dmastp) {                                           \
  (dmastp)->stream->ctrl |= STM32_DMA_CR_EN;                                  \
}

/**
 * @brief   DMA stream disable.
 * @details The function disables the specified stream, waits for the disable
 *          operation to complete and then clears any pending interrupt.
 * @note    This function can be invoked in both ISR or thread context.
 * @note    Interrupts enabling flags are set to zero after this call, see
 *          bug 3607518.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamDisable(dmastp) {                                          \
  (dmastp)->stream->ctrl &= ~(STM32_DMA_CR_TCIE | STM32_DMA_CR_HTIE  |        \
                            STM32_DMA_CR_TEIE | STM32_DMA_CR_DMEIE |        \
                            STM32_DMA_CR_EN);                               \
  while (((dmastp)->stream->ctrl & STM32_DMA_CR_EN) != 0)                     \
    ;                                                                       \
  dmaStreamClearInterrupt(dmastp);                                          \
}

/**
 * @brief   DMA stream interrupt sources clear.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 *
 * @special
 */
#define dmaStreamClearInterrupt(dmastp) {                                   \
  *(dmastp)->ifcr = STM32_DMA_ISR_MASK << (dmastp)->shift;                  \
}

/**
 * @brief   Starts a memory to memory operation using the specified stream.
 * @note    The default transfer data mode is "byte to byte" but it can be
 *          changed by specifying extra options in the @p mode parameter.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @param[in] mode      value to be written in the CCR register, this value
 *                      is implicitly ORed with:
 *                      - @p STM32_DMA_CR_MINC
 *                      - @p STM32_DMA_CR_PINC
 *                      - @p STM32_DMA_CR_DIR_M2M
 *                      - @p STM32_DMA_CR_EN
 *                      .
 * @param[in] src       source address
 * @param[in] dst       destination address
 * @param[in] n         number of data units to copy
 */
#define dmaStartMemCopy(dmastp, mode, src, dst, n) {                        \
  dmaStreamSetPeripheral(dmastp, src);                                      \
  dmaStreamSetMemory0(dmastp, dst);                                         \
  dmaStreamSetTransactionSize(dmastp, n);                                   \
  dmaStreamSetMode(dmastp, (mode) |                                         \
                           STM32_DMA_CR_MINC | STM32_DMA_CR_PINC |          \
                           STM32_DMA_CR_DIR_M2M);                           \
  dmaStreamEnable(dmastp);                                                  \
}

/**
 * @brief   Polled wait for DMA transfer end.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 */
#define dmaWaitCompletion(dmastp) {                                         \
  (dmastp)->stream->CR &= ~(STM32_DMA_CR_TCIE | STM32_DMA_CR_HTIE  |        \
                            STM32_DMA_CR_TEIE | STM32_DMA_CR_DMEIE);        \
  while ((dmastp)->stream->CR & STM32_DMA_CR_EN)                            \
    ;                                                                       \
  dmaStreamClearInterrupt(dmastp);                                          \
}

/**
 * @brief   DMA stream current target.
 * @note    This function can be invoked in both ISR or thread context.
 * @pre     The stream must have been allocated using @p dmaStreamAlloc().
 * @post    After use the stream can be released using @p dmaStreamFree().
 *
 * @param[in] dmastp    pointer to a stm32_dma_stream_t structure
 * @return              Current memory target index.
 *
 * @special
 */
#define dmaStreamGetCurrentTarget(dmastp)                                   \
  (((dmastp)->stream->ctrl >> DMA_SxCR_CT_Pos) & 1U)
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
extern const stm32_dma_stream_t _stm32_dma_streams[STM32_DMA_STREAMS];
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void dmaInit(void);
  const stm32_dma_stream_t *dmaStreamAllocI(uint32_t id,
                                            uint32_t priority,
                                            stm32_dmaisr_t func,
                                            void *param);
  const stm32_dma_stream_t *dmaStreamAlloc(uint32_t id,
                                           uint32_t priority,
                                           stm32_dmaisr_t func,
                                           void *param);
  void dmaStreamFreeI(const stm32_dma_stream_t *dmastp);
  void dmaStreamFree(const stm32_dma_stream_t *dmastp);
#if STM32_DMA_SUPPORTS_DMAMUX == TRUE
  void dmaSetRequestSource(const stm32_dma_stream_t *dmastp, uint32_t per);
#endif
#ifdef __cplusplus
}
#endif
#endif
#endif /* STM32_DMA_H */

/** @} */
