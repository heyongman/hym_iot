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

#include "oled.h"
#include "wifi_station.h"
#include "big_iot.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

// static const char *TAG = "main";

// 通过手机app控制继电器
// 1.链接wifi
// 2.解析收到的命令
// 3.根据命令进行io控制
void app_main(void)
{
  //初始化oled
  oled_init();
  oled_show_str(8,19,  "HYM IOT", &Font_16x26, 1);

  //初始化 NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // 初始化 wifi
  // oled_show_str(0,28,  "WIFI INIT", &Font_11x18, 1);
  wifi_init_sta();

  // 初始化贝壳物联
  // oled_show_str(0,46,  "BIG IOT INIT", &Font_11x18, 1);
  oled_clear();
  oled_show_str(0,0,  "HYM IOT", &Font_7x10, 1);
  big_iot_cloud_init();

}