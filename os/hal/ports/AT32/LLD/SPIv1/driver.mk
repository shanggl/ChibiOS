ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_I2S TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/SPIv1/hal_i2s_lld.c
endif
ifneq ($(findstring HAL_USE_SPI TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/SPIv1/hal_spi_lld.c
endif
else
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/SPIv1/hal_i2s_lld.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/LLD/SPIv1/hal_spi_lld.c
endif

PLATFORMINC += $(CHIBIOS)/os/hal/ports/AT32/LLD/SPIv1
