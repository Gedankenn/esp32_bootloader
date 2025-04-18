/**
 * Saves station mode wifi credentials to NVS
 * @return ESP_OK if sucessful 
*/
esp_err_t app_nvs_save_sta_creds(void);

/**
 * Loads the previously saved credentials from NVS
 * @return true if preveiously saved credentials were found
*/
bool app_nvs_load_sta_creds(void);

/**
 * Clears station mode credentials from NVS
 * @return ESP_OK if sucessful
*/
esp_err_t app_nvs_clear_sta_creds(void);