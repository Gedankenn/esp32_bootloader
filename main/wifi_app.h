#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "lwip/netdb.h"

#include "esp_netif.h"

// Callback typefed
typedef void (*wifi_connected_event_callback_t)(void);

#define WIFI_AP_SSID                "fabio_esp"     //AP name
#define WIFI_AP_PASSWORD            "password"      // AP password
#define WIFI_AP_CHANNEL             1               // AP channel
#define WIFI_AP_SSID_HIDDEN         0               // AP visibility
#define WIFI_AP_MAX_CONNECTIONS     5               // AP max connections
#define WIFI_AP_BEACON_INTERVAL     100             // AP beacon: 100 millisecons recommended
#define WIFI_AP_IP                  "192.168.5.1"   // AP deault ip
#define WIFI_AP_GATEWAY             "192.168.5.1"   // AP default gateway
#define WIFI_AP_NETMASK             "255.255.255.0" // AP default mask
#define WIFI_AP_BAMDWIDTH           WIFI_BW_HT20    // AP bandwidth 20MHZ
#define WIFI_STA_POWER_SAVE         WIFI_PS_NONE    // Power save not used
#define MAX_SSID_LENGHT             32              // IEEE standart maximun
#define MAX_PASSWORD_LENGHT         64              // IEEE standart maximun
#define MAX_CONNECTION_RETRIES      5               // Retry number on disconnection

// netif objetct for the Station and Acess Point
extern esp_netif_t* esp_netif_sta;
extern esp_netif_t* esp_netif_ap;

/**
*   
*/
typedef enum wifi_app_message
{
    WIFI_APP_MSG_START_HTTP_SERVER = 0,
    WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER,
    WIFI_APP_MSG_STA_CONNECTED_GOT_IP,
    WIFI_APP_MSG_USER_REQUESTED_STA_DISCONNECT,
    WIFI_APP_MSG_LOAD_SAVED_CREDENTIALS,
    WIFI_APP_MSG_STA_DISCONNECTED,

} wifi_app_message_e;

/**
 * Struct for the message queue
 * @note Expand this based on application requirements e.g
*/
typedef struct wifi_app_queue_message
{
    wifi_app_message_e msgID;
} wifi_app_queue_message_t;

/**
 * Sends a message tothe queue
 * @param msgID message ID frm the wifi_app_message_e enum.
 * @return pdTRUE if an item was successfully sent to the queue, otherwise pdFALSE
*/
BaseType_t wifi_app_send_message(wifi_app_message_e msgID);

/**
 * Starts wifi RTOS Task
*/
void wifi_app_start(void);

/**
 * Gets the wifi configuration
*/
wifi_config_t* wifi_app_get_wifi_config(void);

/**
 * Sets the callback function.
*/
void wifi_app_set_callback(wifi_connected_event_callback_t cb);

/**
 * Calls the callback function
*/
void wifi_app_call_callback(void);