#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

constexpr uint16_t LEDS{GPIO9|GPIO13};
constexpr uint16_t PERIOD_MS{1000};

void setup_LEDS (){
rcc_periph_clock_enable(RCC_GPIOE);

gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO8);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO9);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO10);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO11);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO12);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO13);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO14);
gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,GPIO15);
}

void setup_timer (){
    rcc_periph_clock_enable(RCC_TIM6);
timer_set_prescaler(TIM6, rcc_get_timer_clk_freq(TIM6)/PERIOD_MS-1);
timer_set_period(TIM6, PERIOD_MS-1);
timer_enable_counter(TIM6);
}

void blink_LEDS (){
if (timer_get_counter(TIM6)<PERIOD_MS/2)
gpio_set(GPIOE,LEDS);
else
gpio_clear(GPIOE,LEDS);
}

int main () {
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
setup_LEDS ();
blink_LEDS ();
setup_timer ();

while (true) {
       gpio_set(GPIOE, GPIO8|GPIO12);
       for(volatile uint32_t i=0;i<100'000;++i);
       gpio_clear(GPIOE, GPIO8|GPIO12);
       gpio_set(GPIOE, GPIO9|GPIO13);
       for(volatile uint32_t i=0;i<100'000;++i);
       gpio_clear(GPIOE, GPIO9|GPIO13);
    }
}