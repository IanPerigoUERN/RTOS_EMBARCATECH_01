#include "temp.h"
//static const float CONVERSION_FACTOR = 3.3f / (1 << 12);

void vTemperatureUpdate(void *pvParameters) {   
    uint16_t adc_value;
    float volt;
    float temperature;
    // Aguarda a conexão USB antes de imprimir
    while (!stdio_usb_connected()) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    while (1) {
        adc_select_input(sensor_temp); // Canal 4 é o sensor de temperatura interno
        uint16_t adc_value = adc_read();
        float volt = (3.3f / 4095) * adc_value;
        float temperature = 27.0f - (volt - 0.706f) / 0.001721f;
        printf("Temperatura: %.2f °C\n", temperature);
        vTaskDelay(pdMS_TO_TICKS(2000)); // 2 segundos
    }
        
}