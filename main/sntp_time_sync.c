#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lwip/apps/sntp.h"

#include "http_server.h"
#include "sntp_time_sync.h"
#include "tasks_common.h"
#include "wifi_app.h"

static const char TAG[] = "SNTP_TIME_SYNC";

// SNTP operating mode set setatus
static bool sntp_op_mode_set = false;

/**
 * Initialize SNTP service using SNTP_OP_MODE_POLL mode
 */
static void sntp_time_sync_init_sntp(void) {
  ESP_LOGI(TAG, "Initializing the sntp service");
  if (!sntp_op_mode_set) {
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_op_mode_set = true;
  }

  sntp_setservername(0, "pool.ntp.org");

  // Initialize the servers
  sntp_init();

  // Let the http server know the service is initialized
  http_server_monitor_send_message(HTTP_MSG_TIME_SERVICE_INITIALIZED);
}

/**
 * Gets the current time and if the current time is not up to date the
 * sntp_time_sync_init_sntp function is called
 */
static void sntp_time_sync_obtain_time(void) {
  time_t now = 0;
  struct tm time_info = {0};

  time(&now);
  localtime_r(&now, &time_info);

  // Check the time in case we need to initializa/reinitialize
  if (time_info.tm_year < (2023 - 1900)) {
    sntp_time_sync_init_sntp();

    // Set the local time zone
    setenv("TZ", "BRST+3BRDT+2,M10.3.0,M2.3.0", 1);
    tzset();
  }
}

/**
 * The SNTP sime synchronization task
 * @param arg pvParam
 */
static void sntp_time_sync(void *pvParam) {
  while (1) {
    sntp_time_sync_obtain_time();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

char *sntp_time_sync_get_time(void) {
  static char time_buffer[100] = {0};

  time_t now = 0;
  struct tm time_info = {0};

  time(&now);
  localtime_r(&now, &time_info);

  if (time_info.tm_year < (2023 - 1900)) {
    ESP_LOGI(TAG, "Time not set yet");
  } else {
    strftime(time_buffer, sizeof(time_buffer), "%d.%m.Y %H:%M:S", &time_info);
    ESP_LOGI(TAG, "Current time info: %s", time_buffer);
  }
  return time_buffer;
}

void sntp_time_sync_task_start(void) {
  xTaskCreatePinnedToCore(
      &sntp_time_sync, "sntp_time_sync", SNTP_TIME_SYNC_TASKS_STACK_SIZE, NULL,
      SNTP_TIME_SYNC_TASK_PRIORITY, NULL, SNTP_TIME_SYNC_TASK_CORE_ID);
}
