#ifndef __INFRARED_H
#define __INFRARED_H

#define S1_PORT         GPIO_INFRARED_PIN_OUT1_PORT 
#define S2_PORT         GPIO_INFRARED_PIN_OUT2_PORT
#define S3_PORT         GPIO_INFRARED_PIN_OUT3_PORT   
#define S4_PORT         GPIO_INFRARED_PIN_OUT4_PORT   
#define S5_PORT         GPIO_INFRARED_PIN_OUT5_PORT   
#define S6_PORT         GPIO_INFRARED_PIN_OUT6_PORT    
#define S7_PORT         GPIO_INFRARED_PIN_OUT7_PORT   
#define S8_PORT         GPIO_INFRARED_PIN_OUT8_PORT   
#define S9_PORT         GPIO_INFRARED_PIN_OUT9_PORT   
#define S10_PORT        GPIO_INFRARED_PIN_OUT10_PORT   
#define S11_PORT        GPIO_INFRARED_PIN_OUT11_PORT    
#define S12_PORT        GPIO_INFRARED_PIN_OUT12_PORT  

#define S1_PIN      GPIO_INFRARED_PIN_OUT1_PIN 
#define S2_PIN      GPIO_INFRARED_PIN_OUT2_PIN
#define S3_PIN      GPIO_INFRARED_PIN_OUT3_PIN   
#define S4_PIN      GPIO_INFRARED_PIN_OUT4_PIN   
#define S5_PIN      GPIO_INFRARED_PIN_OUT5_PIN   
#define S6_PIN      GPIO_INFRARED_PIN_OUT6_PIN    
#define S7_PIN      GPIO_INFRARED_PIN_OUT7_PIN   
#define S8_PIN      GPIO_INFRARED_PIN_OUT8_PIN   
#define S9_PIN      GPIO_INFRARED_PIN_OUT9_PIN   
#define S10_PIN     GPIO_INFRARED_PIN_OUT10_PIN   
#define S11_PIN     GPIO_INFRARED_PIN_OUT11_PIN    
#define S12_PIN     GPIO_INFRARED_PIN_OUT12_PIN   


extern float weight_sum;  //加权和
extern float Black_count;    //检测到的黑线数量
extern float last_data;

typedef struct
{
    float Kp;          // 比例系数
    float Ki;          // 积分系数
    float Kd;          // 微分系数
    float target_data;          // 目标值
    float actully_data;          // 实际值
    float error_sum;              //累加
    float now_error;         // 当前误差
    float last_error;    // 上一次误差
    float pid_out;           // PID输出值

    float max_out;       // 最大输出限幅
    float min_out;       // 最小输出限幅
    float error_sum_max;       // 最大积分限幅
    float error_sum_min;       // 最小积分限幅

}PID_TypeDef;

typedef struct
{
    float Kp;          // 比例系数
    float Ki;          // 积分系数
    float Kd;          // 微分系数
    float target_data;          // 目标值
    float actully_data;         // 实际值
    float error_sum;            //累加
    float now_error;            // 当前误差
    float last_error;           // 上一次误差
    float pid_out;              // PID输出值

    float max_out;              // 最大输出限幅
    float min_out;              // 最小输出限幅

}PID_mpu6050_TypeDef;

extern PID_TypeDef pid;
extern PID_mpu6050_TypeDef pid_mpu6050;
extern uint8_t right_flag;
extern uint8_t left_flag;
extern uint8_t mode_flag;
extern uint8_t Black_flag;
extern uint8_t left_flag_mpu6050;
extern uint8_t right_flag_mpu6050;

void Infrared_Read(PID_TypeDef *pid);
void Pid_Init(PID_TypeDef *pid , float Kp , float Ki , float Kd , float max , float min);
void Pid_Calculate(PID_TypeDef *pid);
void Pid_Mpu6050_Init(PID_mpu6050_TypeDef *pid_mpu6050 , float Kp , float Ki , float Kd , float max , float min);
void Pid_Mpu6050_Calculate(PID_mpu6050_TypeDef *pid_mpu6050);

#endif
