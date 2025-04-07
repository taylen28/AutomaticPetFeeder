/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;   // <-- global handle for I2C1

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

void MX_I2C1_Init(void);          // <-- function to initialize I2C1

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */
