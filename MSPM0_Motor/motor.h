#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

//位置环参数
#define Place_Min_Speed   20        //最小速度
#define Place_Max_Speed   40        //最大速度
#define Place_Base_Speed  30        //基准速度
//角度环参数
#define Angle_Min_Speed   20        //最小速度
#define Angle_Max_Speed   40        //最大速度
#define Angle_Base_Speed  30        //基准速度

#define AIN1_PORT      GPIO_MOTOR_PIN_AIN1_PORT   // PA12
#define AIN2_PORT      GPIO_MOTOR_PIN_AIN2_PORT   // PA13
#define BIN1_PORT      GPIO_MOTOR_PIN_BIN1_PORT   // PA15
#define BIN2_PORT      GPIO_MOTOR_PIN_BIN2_PORT   // PA16

#define AIN1_PIN       GPIO_MOTOR_PIN_AIN1_PIN   // PA12
#define AIN2_PIN       GPIO_MOTOR_PIN_AIN2_PIN   // PA13
#define BIN1_PIN       GPIO_MOTOR_PIN_BIN1_PIN   // PA15
#define BIN2_PIN       GPIO_MOTOR_PIN_BIN2_PIN   // PA16

#define diameter 0.048f   //  轮子直径0.048cm , 轮子线数11 , 减速比20.4
#define pi 3.14f            //  3.14
#define line 364.0f     //  轮子直径65mm , 轮子线数13 , 减速比28 ， line = 13 * 28 


extern int left_pwm;
extern int right_pwm;


void Motor_Init(void);
void Motor_Control(void);
void Mpu6050_Control(void);
void Motor_Show(PID_TypeDef *pid , PID_mpu6050_TypeDef *pid_mpu6050);

#endif
