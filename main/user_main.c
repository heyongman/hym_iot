#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "wifi_station.h"
#include "big_iot.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif


static const char *TAG = "main";

// 通过手机app控制继电器
// 1.链接wifi
// 2.解析收到的命令
// 3.根据命令进行io控制
void app_main(void) {
    ESP_LOGI(TAG, "starting...");
    //初始化 NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // 初始化 wifi
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    // 初始化贝壳物联
    big_iot_cloud_connect(BIG_IOT_URL,BIG_IOT_PORT);
    ESP_LOGI(TAG,"init end.");
    
}