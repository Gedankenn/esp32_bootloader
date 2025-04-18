/**
 * Messages for the HTTP monitor
*/

#define OTA_UPDATE_PENDING          0
#define OTA_UPDATE_SUCESSFUL        1
#define OTA_UPDATE_FAILED           -1

/**
 * connection status for wifi
*/
typedef enum http_server_wifi_connect_status
{
    NONE = 0,
    HTTP_WIFI_STATUS_CONNECTING,
    HTTP_WIFI_STATUS_FAILED,
    HTTP_WIFI_STATUS_SUCCESS,
    HTTP_WIFI_STATUS_DISCONNECT,
}http_server_wifi_connect_status_e;


typedef enum http_server_message
{
    HTTP_MSG_WIFI_CONNECT_INIT = 0,
    HTTP_MSG_WIFI_CONNECTED_SUCCESS,
    HTTP_MSG_WIFI_CONNECTED_FAIL,
    HTTP_MSG_WIFI_USER_DISCONNECT,
    HTTP_MSG_OTA_UPDATE_SUCCESSFUL,
    HTTP_MSG_OTA_UPDATE_FAILED,
    HTTP_MSG_TIME_SERVICE_INITIALIZED,
    HTTP_MSG_OTA_UPDATE_INITIALIZED
} http_server_message_e;

/**
 * Struct for the message queue
*/
typedef struct http_server_queue_message
{
    http_server_message_e msgID;
} http_server_queue_message_t;

/**
 * Sends a message to th queue
 * @param msgID message ID fromthe http_server_message_e enum.
 * @return pdTRUE if item was sucessfully sent to the queue, else FALSE
*/
BaseType_t http_server_monitor_send_message(http_server_message_e msgID);

/**
 * Starts he HTTP Server.
*/
void http_server_start(void);

/**
 * Stops the HTTP server.
*/
void http_server_stop(void);

/**
 * Timer callback function withc calls esp_restart upon successful firmware update
*/
void http_server_fw_update_reset_callback(void *arg);