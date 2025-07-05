#include "library.h"



void main()
{

    stdio_init_all();

    adc_init();
    adc_set_temp_sensor_enabled(true);
    
    gpio_init(led_pin_blue);

    gpio_set_dir(led_pin_blue, GPIO_OUT);

    xTaskCreate(vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
    xTaskCreate(vTemperatureUpdate, "Temperature Task", 128, NULL, 1, NULL);

    vTaskStartScheduler();
   
}