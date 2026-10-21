#include "esp_log.h"
#include "wifi_app.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <string.h>
#include <inttypes.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_app_format.h"
#include "esp_http_client.h"
#include "esp_flash_partitions.h"
#include "esp_partition.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "errno.h"

static const char TAG[] = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Running partition: %s", esp_ota_get_running_partition()->label);
}
