
#if 0
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

#include "ch.h"
#include "hal.h"
#include "rt_test_root.h"
#include "oslib_test_root.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetLine(LINE_LED1);
    chThdSleepMilliseconds(5);
    palSetLine(LINE_LED2);
    chThdSleepMilliseconds(5);
    palSetLine(LINE_LED3);
    chThdSleepMilliseconds(5);
    palClearLine(LINE_LED1);
    chThdSleepMilliseconds(5);
    palClearLine(LINE_LED2);
    chThdSleepMilliseconds(5);
    palClearLine(LINE_LED3);
    chThdSleepMilliseconds(5);
  }
}

//const uint32_t aa[1024 * 40] ={0};
//uint32_t i = 0;
/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  palClearLine(LINE_LED1);
//  chThdSleepMilliseconds(5);
  palClearLine(LINE_LED2);
//  chThdSleepMilliseconds(5);
  palClearLine(LINE_LED3);
//  chThdSleepMilliseconds(5);
  /*
   * Activates the serial driver 3 using the driver default configuration.
   */
  sdStart(&SD1, NULL);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    if (palReadLine(LINE_BUTTON)) {
      test_execute((BaseSequentialStream *)&SD1, &rt_test_suite);
      test_execute((BaseSequentialStream *)&SD1, &oslib_test_suite);
    }
    chThdSleepMilliseconds(500);
  }
}

#endif



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

#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"

#include "usbcfg.h"

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

/* Can be measured using dd if=/dev/xxxx of=/dev/null bs=512 count=10000.*/
static void cmd_write(BaseSequentialStream *chp, int argc, char *argv[]) {
  static uint8_t buf[] =
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
      "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: write\r\n");
    return;
  }

  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
#if 1
    /* Writing in channel mode.*/
    chnWrite(&SDU1, buf, sizeof buf - 1);
#else
    /* Writing in buffer mode.*/
    (void) obqGetEmptyBufferTimeout(&SDU1.obqueue, TIME_INFINITE);
    memcpy(SDU1.obqueue.ptr, buf, SERIAL_USB_BUFFERS_SIZE);
    obqPostFullBuffer(&SDU1.obqueue, SERIAL_USB_BUFFERS_SIZE);
#endif
  }
  chprintf(chp, "\r\n\nstopped\r\n");
}

static const ShellCommand commands[] = {
  {"write", cmd_write},
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};

static const ShellConfig shell_cfg2 = {
  (BaseSequentialStream *)&SDU2,
  commands
};

/*===========================================================================*/
/* Generic code.                                                             */
/*===========================================================================*/

#define PORTAB_UART3                UARTD3
UARTConfig uart_cfg_1 = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  38400,
  0,
  USART_CR2_LINEN,
  0
};
void portab_setup(void) {

}
void uart_test(void)
{
  static const char teststr[] = "Chibios USART Test";
  char read_buffer[64] = {0};
  msg_t msg;
  size_t sz;
  portab_setup();
  uartStart(&PORTAB_UART3, &uart_cfg_1);

  sz = 18;
  msg = uartSendTimeout(&PORTAB_UART3, &sz, teststr, TIME_INFINITE);
  if (msg != MSG_OK)
    chSysHalt("invalid return code");

#if 0
  while(true)
  {
	sz = 1;
	msg = uartReceiveTimeout(&PORTAB_UART3, &sz, read_buffer, TIME_INFINITE);
	if (msg != MSG_OK)
	  chSysHalt("invalid return code");
	msg = uartSendTimeout(&PORTAB_UART3, &sz, read_buffer, TIME_INFINITE);
	if (msg != MSG_OK)
	  chSysHalt("invalid return code");
  }
    /*
     * Normal main() thread activity.
     */
  while (true) {
    chThdSleepMilliseconds(500);
  }
#endif

}

void otg_test(void)
{
  thread_t *shelltp1 = NULL;
  thread_t *shelltp2 = NULL;
  event_listener_t shell_el;
  /*
  * Initializes two serial-over-USB CDC drivers.
  */
  sduObjectInit(&SDU1);

  sduStart(&SDU1, &serusbcfg1);

  sduObjectInit(&SDU2);

  sduStart(&SDU2, &serusbcfg2);


  /*
  * Activates the USB driver and then the USB bus pull-up on D+.
  * Note, a delay is inserted in order to not have to disconnect the cable
  * after a reset.
  */

  usbDisconnectBus(serusbcfg1.usbp);

  chThdSleepMilliseconds(1500);

  usbStart(serusbcfg1.usbp, &usbcfg);

  usbConnectBus(serusbcfg1.usbp);

  shellInit();

  chEvtRegister(&shell_terminated, &shell_el, 0);

  /*
  * Normal main() thread activity, managing two shells.
  */
  while (true) {

	  if (SDU1.config->usbp->state == USB_ACTIVE) {

	  /* Starting shells.*/

		if (shelltp1 == NULL) {
	      shelltp1 = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
	                                       "shell1", NORMALPRIO + 1,
	                                       shellThread, (void *)&shell_cfg1);
	    }

		if (shelltp2 == NULL) {
	        shelltp2 = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
	                                       "shell2", NORMALPRIO + 1,
	                                       shellThread, (void *)&shell_cfg2);
	    }

	    /* Waiting for an exit event then freeing terminated shells.*/
	    chEvtWaitAny(EVENT_MASK(0));
	    if (chThdTerminatedX(shelltp1)) {
	      chThdRelease(shelltp1);
	      shelltp1 = NULL;
	    }
	    if (chThdTerminatedX(shelltp2)) {
	      chThdRelease(shelltp2);
	      shelltp2 = NULL;
	    }
	  }
	  else {
	    chThdSleepMilliseconds(1000);
	  }
	}

}


#define ADC_GRP1_NUM_CHANNELS   1
#define ADC_GRP1_BUF_DEPTH      8

#define ADC_GRP2_NUM_CHANNELS   8
#define ADC_GRP2_BUF_DEPTH      16

static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];

/*
 * ADC streaming callback.
 */
size_t nx = 0, ny = 0;
static void adccallback(ADCDriver *adcp) {

  if (adcIsBufferComplete(adcp)) {
    nx += 1;
  }
  else {
    ny += 1;
  }
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 8 samples of 1 channel, SW triggered.
 * Channels:    IN11.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  0,                        /* CR1 */
  ADC_CR2_SWSTART,          /* CR2 */
  ADC_SMPR1_SMP_AN11(ADC_SAMPLE_640_5),
  0,                        /* SMPR2 */
  0,                        /* HTR */
  0,                        /* LTR */
  0,                        /* SQR1 */
  0,                        /* SQR2 */
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
};

/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN11, IN12, IN11, IN12, IN11, IN12, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg2 = {
  TRUE,
  ADC_GRP2_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  0,                        /* CR1 */
  ADC_CR2_SWSTART,          /* CR2 */
  ADC_SMPR1_SMP_AN12(ADC_SAMPLE_47_5) | ADC_SMPR1_SMP_AN11(ADC_SAMPLE_47_5) |
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_92_5) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_92_5),
  0,                        /* SMPR2 */
  0,                        /* HTR */
  0,                        /* LTR */
  0,                        /* SQR1 */
  ADC_SQR2_SQ8_N(ADC_CHANNEL_SENSOR) | ADC_SQR2_SQ7_N(ADC_CHANNEL_VREFINT),
  ADC_SQR3_SQ6_N(ADC_CHANNEL_IN12)   | ADC_SQR3_SQ5_N(ADC_CHANNEL_IN11) |
  ADC_SQR3_SQ4_N(ADC_CHANNEL_IN12)   | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN11) |
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN12)   | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
};

void adc_test(void)
{
	size_t sz;
	msg_t msg;

	sz = 9;
	msg = uartSendTimeout(&PORTAB_UART3, &sz, "ADC Test:", TIME_INFINITE);
	if (msg != MSG_OK)
		    chSysHalt("invalid return code");
	/*
	   * Setting up analog inputs used by the demo.
	   */
	  palSetGroupMode(GPIOC, PAL_PORT_BIT(1) | PAL_PORT_BIT(2),
	                  0, PAL_MODE_INPUT_ANALOG);

	  /*
	   * Activates the ADC1 driver and the temperature sensor.
	   */
	  adcStart(&ADCD1, NULL);
	  adcSTM32EnableTSVREFE();

	  /*
	   * Linear conversion.
	   */
	  adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
	  chThdSleepMilliseconds(1000);

	  /*
	   * Starts an ADC continuous conversion.
	   */
	  adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);

}


static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
	palSetLine(LINE_LED1);
	chThdSleepMilliseconds(200);
    palSetLine(LINE_LED2);
    chThdSleepMilliseconds(200);
    palSetLine(LINE_LED3);
    chThdSleepMilliseconds(200);
    palClearLine(LINE_LED1);
    chThdSleepMilliseconds(200);
    palClearLine(LINE_LED2);
    chThdSleepMilliseconds(200);
    palClearLine(LINE_LED3);
    chThdSleepMilliseconds(200);
  }
}

/*
 * Application entry point.
 */
int main(void) {
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);

  uart_test();
  adc_test();
  otg_test();

}
