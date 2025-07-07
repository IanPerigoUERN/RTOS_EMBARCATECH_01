#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "inc_joystick/joystick_lib.h"
#include "inc_OLED/ssd1306.h"
#include "Temperature/temp.h"
#include "Blink/new_blink.h"

ssd1306_t disp;


void vShowLastJoystickDirection()
{
    show_direction_of_joystick(&disp, "Centro");

    for (;;)
    {
        // Read the joystick position on the Y axis
        int joystick_y = value_of_the_pos_of_joystick_y();

        // Read the joystick position on the X axis
        int joystick_x = value_of_the_pos_of_joystick_x();

        // Blink the LED based on the joystick position
        if (joystick_y == 1) {
            show_direction_of_joystick(&disp, "Baixo");

        } else if (joystick_y == -1) {
            show_direction_of_joystick(&disp, "Cima");
            
        }

        if(joystick_x == 1) {
            show_direction_of_joystick(&disp, "Esquerda");

        } else if (joystick_x == -1) {
            show_direction_of_joystick(&disp, "Direita");
        }

        vTaskDelay(pdMS_TO_TICKS(100)); 
        
    }
}

void main()
{
   
    stdio_init_all();
    joystick_init();
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);
    adc_set_temp_sensor_enabled(true);
    ssd1306_init_display(&disp);
    

    xTaskCreate(vShowLastJoystickDirection, "show_joystick_direction", 128, NULL, 1, NULL);
    xTaskCreate(vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
    xTaskCreate(vTemperatureUpdate, "Temperature Task", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1){

    }
}