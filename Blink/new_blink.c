#include "new_blink.h"

void vBlinkTask(void *pvParameters)
{

    for (;;)
    {

        gpio_put(led_pin_blue, 1);

        vTaskDelay(50);

        gpio_put(led_pin_blue, 0);

        vTaskDelay(950);

        
    }
}