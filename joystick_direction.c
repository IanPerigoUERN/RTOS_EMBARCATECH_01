#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "inc_joystick/joystick_lib.h"
#include "inc_OLED/ssd1306.h"

ssd1306_t disp;

void show_last_joystick_direction()
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
    ssd1306_init_display(&disp);

    xTaskCreate(show_last_joystick_direction, "show_joystick_direction", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}