#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_3    CONFIG_GPIO_OUTPUT_3
#define GPIO_OUTPUT_PIN_SEL  1ULL<<GPIO_OUTPUT_IO_3

void app_main(void)
{
	
	//zero-initialize the config structure.
    gpio_config_t io_conf = {};
    
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    
     //configure GPIO with the given settings
    gpio_config(&io_conf);
    
    int cnt = 0;
    while (1) {
        printf("cnt: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_OUTPUT_IO_3, cnt % 2);
    }
}

