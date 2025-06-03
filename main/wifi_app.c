#include "wifi_app.h"

#define TAG "wifi_app"


void wifi_app_init(void)
{
    ESP_LOGI(TAG, "Initializing Wi-Fi application...");
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}
