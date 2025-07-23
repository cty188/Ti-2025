#ifndef BMI088MIDDLEWARE_H
#define BMI088MIDDLEWARE_H

#include "headfile.h"

#define BMI088_USE_SPI

#define ACC_CS_Pin CS_ACC_CS_Pin_PIN
#define ACC_CS_GPIO_Port CS_PORT
#define GYRO_CS_Pin CS_GYRO_CS_Pin_PIN
#define GYRO_CS_GPIO_Port CS_PORT

extern void BMI088_GPIO_init(void);
extern void BMI088_com_init(void);
extern void BMI088_delay_ms(uint16_t ms);
extern void BMI088_delay_us(uint16_t us);

#if defined(BMI088_USE_SPI)
extern void BMI088_ACCEL_NS_L(void);
extern void BMI088_ACCEL_NS_H(void);

extern void BMI088_GYRO_NS_L(void);
extern void BMI088_GYRO_NS_H(void);

extern uint8_t BMI088_read_write_byte(uint8_t reg);


#endif

#endif
