#include "cJSON.h"
#include "esp_log.h"
#include "string.h"
#include "driver/gpio.h"

// #include "big_iot.h"
#include "oled.h"
#define TAG "control"
#define CONTROL_IO (23)

/** 
 * 处理云平台的控制命令以及数据
 * @param[in]   json_parse_data: 存放解析之后的云平台json数据
 * @retval      null 
 *              其他:          失败 
 * @par         修改日志 
 *               Ver0.0.1:
                    Helon_Chan, 2018/08/14, 初始化版本\n 
 */
void control(const cJSON *json_parse_data)
{
  char *cmd = NULL;
  /* 获取云平台返回的json数据中当前的控制命令是什么 */
  cmd = cJSON_Print(cJSON_GetObjectItem(json_parse_data, "C"));
  /* 根据云平台返回的method执行不同的动作 */
  switch (strcmp(cmd, "\"play\"") == 0 ? 1 : strcmp(cmd, "\"stop\"") == 0 ? 0 : -1)
  {
  case 1:
    ESP_LOGW(TAG, "Switch ON\n");
    oled_re_show_str(0,15,  "Switch ON", &Font_7x10, 1);
    gpio_pad_select_gpio(CONTROL_IO);
    gpio_set_direction(CONTROL_IO,GPIO_MODE_OUTPUT);
    gpio_set_level(CONTROL_IO,1);
    break;
  case 0:
    ESP_LOGW(TAG, "Switch OFF\n");
    oled_re_show_str(0,15,  "Switch OFF", &Font_7x10, 1);
    gpio_pad_select_gpio(CONTROL_IO);
    gpio_set_direction(CONTROL_IO,GPIO_MODE_OUTPUT);
    gpio_set_level(CONTROL_IO,0);
    break;
  default:
    ESP_LOGW(TAG, "other control:%s\n",cJSON_Print(json_parse_data));
    oled_re_show_str(0,15, cmd, &Font_7x10, 1);
    break;
  }
}