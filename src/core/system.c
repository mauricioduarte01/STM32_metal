#include "core/system.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>

// Static means no global, it belongs to this file
static void rcc_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSE8_72MHZ]);
}
// interrupt, check vector.h and sys_tick_handler (nvic.h)
// uint64 to avoid overflow.. careful microcontroller is 32-bit
// it can run forever. Anyway this should be fixed in the future since we are using uint64_int
static volatile uint64_t ticks = 0;

void sys_tick_handler(void) {
  ticks++;
}

uint64_t system_get_ticks(void) {
  return ticks;
}
static void systick_setup(void) {
  systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
  systick_counter_enable();
  // Enable interrupt
  systick_interrupt_enable();

}

void system_setup(void){
    rcc_setup();
    systick_setup();
}


