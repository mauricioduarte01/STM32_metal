#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "core/system.h"
#include "core/timer.h"

#include "../shared/src/inc/uart.h"


#define LED_PORT (GPIOB)
#define LED_PIN (GPIO13)

#define UART_PORT (GPIOA)
#define RX_PIN (GPIO3)
#define TX_PIN (GPIO2)

static void gpio_setup(void)
{
  rcc_periph_clock_enable(RCC_GPIOB);
  // Alternate function 1 (AF1) from GPIOA15 for timer 2 channel 1
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);

  gpio_mode_setup(UART_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, TX_PIN | RX_PIN);
  gpio_set_af(UART_PORT,GPIO_AF7, TX_PIN | RX_PIN);
}

int main(void)
{

  system_setup();
  gpio_setup();
  uart_setup();

  uint64_t start_time = system_get_ticks();
  while (1)
  {
    if (system_get_ticks() - start_time >= 1000)
    {
      gpio_toggle(LED_PORT, LED_PIN);
      start_time = system_get_ticks();
    }

    if(uart_data_available()) {
      uint8_t data = uart_read_byte();
      uart_write_byte(data + 1);
    }
    // do more useful work
  }
  return 0;
}