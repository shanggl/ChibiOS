ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_PAL TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_acc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_adc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_can.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_crc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_crm.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_dac.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_debug.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_dma.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_dvp.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_edma.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_ertc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_exint.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_flash.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_gpio.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_i2c.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_misc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_pwc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_qspi.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_scfg.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_sdio.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_spi.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_tmr.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_usart.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_usb.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_wdt.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_wwdt.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_xmc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/system_at32f435_437.c
endif
else
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_acc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_adc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_can.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_crc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_crm.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_dac.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_debug.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_dma.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_dvp.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_edma.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_ertc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_exint.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_flash.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_gpio.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_i2c.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_misc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_pwc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_qspi.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_scfg.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_sdio.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_spi.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_tmr.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_usart.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_usb.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_wdt.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_wwdt.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/at32f435_437_xmc.c
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers/system_at32f435_437.c
endif

PLATFORMINC += $(CHIBIOS)/os/hal/ports/AT32/AT32F435_437xx/drivers
