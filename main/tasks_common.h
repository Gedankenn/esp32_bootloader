// WiFi application task
#define WIFI_APP_TASK_STACK_SIZE                    4096
#define WIFI_APP_TASK_PRIORITY                      5
#define WIFI_APP_TASK_CORE_ID                       0

// HTTP server Task
#define HTTP_SERVER_TASK_STACK_SIZER                8192
#define HTTP_SERVER_TASK_PRIORITY                   4
#define HTTP_SERVER_TASK_CORE_ID                    0

// Wifi reset button task
#define WIFI_RESET_BUTTON_TASK_STACK_SIZE           2048
#define WIFI_RESET_BUTTON_TASK_PRIORITY             6
#define WIFI_RESET_BUTTON_TASK_CORE_ID              0

// HTTP server monitor task info
#define HTTP_SERVER_MONITOR_STACK_SIZE              4096
#define HTTP_SERVER_MONITOR_PRIORITY                3
#define HTTP_SERVER_MONITOR_CORE_ID                 0

// SNTP Time sync taks
#define SNTP_TIME_SYNC_TASKS_STACK_SIZE             4096
#define SNTP_TIME_SYNC_TASK_PRIORITY                4
#define SNTP_TIME_SYNC_TASK_CORE_ID                 1