/*
 * The Roll Control Module is responsible for activating a PWM servo. Commands
 * sent from the FC over ethernet set the pulsewidth. An external pin
 * determines launch detect.
 */

// ChibiOS
#include "ch.h"
#include "hal.h"
//#include "lwipopts.h"
#include "lwipthread.h"
#include "chprintf.h"

// PSAS common
#include "net_addrs.h"
#include "utils_led.h"

// servo_control
#include "launch_detect.h"
#include "servo_control.h"

//#define DEBUG_PWM 1 //FIXME: this should be set as a make target

#if DEBUG_PWM
#include "debug_pwm.h"
#endif


void main(void) {
    /* Initialize Chibios */
    halInit();
    chSysInit();
    /* Diagnostic led */
    led_init(&e407_led_cfg);
    /* Start lwip stack */
    chThdCreateStatic( wa_lwip_thread
                     , sizeof(wa_lwip_thread)
                     , NORMALPRIO + 2
                     , lwip_thread
                     , ROLL_LWIP
                     );
    /* activate PWM output */
    pwm_start();
#if DEBUG_PWM
    debug_pwm_start();
#endif
    /* initialize launch detection subsystem */
    launch_detect_init();


    while (true) {
        chThdSleep(TIME_INFINITE);
    }
}