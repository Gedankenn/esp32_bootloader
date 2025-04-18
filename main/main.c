#include <stdio.h>

#include "nvs_flash.h"
#include "wifi_app.h"
#include "wifi_reset_button.h"
#include "esp_log.h"
#include "sntp_time_sync.h"

static const char TAG[] = "main";

void wifi_application_connected_events(void)
{
    ESP_LOGI(TAG,"wifi applicaiton connected");
    sntp_time_sync_task_start();
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Start wifi
    wifi_app_start();
    
    // Configure wifi reset button
    wifi_reset_button_config();

    // Set connected event callback
    wifi_app_set_callback(&wifi_application_connected_events);
}
