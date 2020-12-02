#include "cJSON.h"
#include "esp_log.h"
#include "string.h"

#include "big_iot.h"

#define TAG "control"

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
  ESP_LOGI(TAG, "command:%s",cmd);
  /* 根据云平台返回的method执行不同的动作 */
  switch (strcmp(cmd, "\"play\"") == 0 ? ON : strcmp(cmd, "\"stop\"") == 0 ? OFF : INVALID_METHOD)
  {
  case ON:
    ESP_LOGI("cloud_cmd_data_hander", "Switch ON\n");
    break;
  case OFF:
    ESP_LOGI("cloud_cmd_data_hander", "Switch OFF\n");
    break;
  default:
    break;
  }
}