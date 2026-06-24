#include "main.h"


PID_TypeDef pid;
PID_mpu6050_TypeDef pid_mpu6050;

float weight_sum = 0;  //加权和
float Black_count = 0;    //检测到的黑线数量
//pid
uint8_t right_flag = 0;
uint8_t left_flag = 0;
//角度环
uint8_t right_flag_mpu6050 = 0;
uint8_t left_flag_mpu6050 = 0;
uint8_t right_mpu6050 = 0;
uint8_t left_mpu6050 = 0;
//丢线保护
float last_data = 0.0f;

void Pid_Init(PID_TypeDef *pid , float Kp , float Ki , float Kd , float max , float min)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->actully_data = 0.0f;
    pid->target_data = 6.5f;

    pid->error_sum = 0.0f;
    pid->now_error = 0.0f;
    pid->last_error = 0.0f;
    
    pid->pid_out = 0.0f;
    pid->max_out = max;
    pid->min_out = min;
}

void Pid_Mpu6050_Init(PID_mpu6050_TypeDef *pid_mpu6050 , float Kp , float Ki , float Kd , float max , float min)
{
    pid_mpu6050->Kp = Kp;
    pid_mpu6050->Ki = Ki;
    pid_mpu6050->Kd = Kd;

    pid_mpu6050->actully_data = 0.0f;
    pid_mpu6050->target_data = 0.0f;

    pid_mpu6050->error_sum = 0.0f;
    pid_mpu6050->now_error = 0.0f;
    pid_mpu6050->last_error = 0.0f;
    
    pid_mpu6050->pid_out = 0.0f;
    pid_mpu6050->max_out = max;
    pid_mpu6050->min_out = min;
}

void Infrared_Read(PID_TypeDef *pid)
{
    weight_sum = 0;
    Black_count = 0;
    uint8_t s1, s2, s3, s4, s5 , s6, s7, s8, s9, s10, s11, s12;
    //1为黑 ， 0为白
    s1  = DL_GPIO_readPins(S1_PORT, S1_PIN) ? 1 : 0;
    s2  = DL_GPIO_readPins(S2_PORT, S2_PIN) ? 1 : 0;
    s3  = DL_GPIO_readPins(S3_PORT, S3_PIN) ? 1 : 0;
    s4  = DL_GPIO_readPins(S4_PORT, S4_PIN) ? 1 : 0;
    s5  = DL_GPIO_readPins(S5_PORT, S5_PIN) ? 1 : 0;
    s6  = DL_GPIO_readPins(S6_PORT, S6_PIN) ? 1 : 0;
    s7  = DL_GPIO_readPins(S7_PORT, S7_PIN) ? 1 : 0;
    s8  = DL_GPIO_readPins(S8_PORT, S8_PIN) ? 1 : 0;
    s9  = DL_GPIO_readPins(S9_PORT, S9_PIN) ? 1 : 0;
    s10 = DL_GPIO_readPins(S10_PORT, S10_PIN) ? 1 : 0;
    s11 = DL_GPIO_readPins(S11_PORT, S11_PIN) ? 1 : 0;
    s12 = DL_GPIO_readPins(S12_PORT, S12_PIN) ? 1 : 0;

    //计算加权和
    if(s1 == 1){ weight_sum += 1 ; Black_count++;}
    if(s2 == 1){ weight_sum += 2 ; Black_count++;}
    if(s3 == 1){ weight_sum += 3 ; Black_count++;}
    if(s4 == 1){ weight_sum += 4 ; Black_count++;}
    if(s5 == 1){ weight_sum += 5 ; Black_count++;}
    if(s6 == 1){ weight_sum += 6 ; Black_count++;}
    if(s7 == 1){ weight_sum += 7 ; Black_count++;}
    if(s8 == 1){ weight_sum += 8 ; Black_count++;}
    if(s9 == 1){ weight_sum += 9 ; Black_count++;}
    if(s10 == 1){ weight_sum += 10 ; Black_count++;}
    if(s11 == 1){ weight_sum += 11 ; Black_count++;}
    if(s12 == 1){ weight_sum += 12 ; Black_count++;}
    //得到实测值
    if(Black_count > 0)
    {
        pid->actully_data = weight_sum / Black_count;
        last_data = pid->actully_data;
    }
    else if(Black_count == 0)
    {
            pid->actully_data = last_data;
    }
}

void Pid_Calculate(PID_TypeDef *pid)
{  
    
        // 1. 计算误差
        pid->now_error = pid->target_data - pid->actully_data;     //= 误差 = 目标值 - 实测
        float P = pid->now_error;    //计算P
        
        if(pid->now_error > 0)              //rihgt_flag = 1,
        {
            P = pid->now_error;
        }
        if(pid->now_error < 0)              //left_flag = 1
        {
            P = pid->now_error - pid->now_error * 2;
        }
        // 2. I 计算 + 积分限幅
        if(pid->now_error > 0)
        {
            pid->error_sum += pid->now_error;
        }
        if(pid->now_error < 0)
        {
            pid->error_sum -= pid->now_error;
        }
        if(pid->error_sum > 20)  pid->error_sum = 20;   // 上限
        float I = pid->error_sum;
        
        // 3. D 计算
        float D = pid->now_error - pid->last_error;

        // 4.计算PID
        pid->pid_out =  pid->Kp * P + pid->Ki * I + pid->Kd * D; 

        // 5. 输出限幅
        if(pid->pid_out > pid->max_out) pid->pid_out = pid->max_out;
        if(pid->pid_out < pid->min_out) pid->pid_out = pid->min_out;

        // 6.保存上一次误差值 
        pid->last_error = pid->now_error;
        
        // 7.修正方向判断          
        if(pid->now_error == 0)
        {
            pid->error_sum = 0;
        }
        //往右边修正 , pid_out为负数
        if(pid->actully_data > 4)
        {   
            left_flag = 0;
            right_flag = 1;
        }
        //往左边修正 , pid_out为正数
        if(pid->actully_data < 4)
        {   
            right_flag = 0;
            left_flag = 1;
        }
        Motor_Control();
}


void Pid_Mpu6050_Calculate(PID_mpu6050_TypeDef *pid_mpu6050)
{  
        // 1. 计算误差
        pid_mpu6050->now_error = pid_mpu6050->target_data - pid_mpu6050->actully_data;     //= 误差 = 目标值 - 实测
        float P = pid_mpu6050->now_error;    //计算P

        if(pid_mpu6050->now_error < 0)              //left_mpu6050 = 1 , 车身偏左
        {
            P = pid_mpu6050->now_error - pid_mpu6050->now_error * 2;
        }
        if(pid_mpu6050->now_error > 0)              //rihgt_mpu6050 = 1 ，车身偏右
        {
            P = pid_mpu6050->now_error;
        }

        // 2. I 计算 + 积分限幅
        if(pid_mpu6050->now_error > 0)
        {
            pid_mpu6050->error_sum += pid_mpu6050->now_error;
        }
        if(pid_mpu6050->now_error < 0)
        {
            pid_mpu6050->error_sum -= pid_mpu6050->now_error;
        }
        if(pid_mpu6050->error_sum > 200)  pid_mpu6050->error_sum = 200;   // 上限
        float I = pid_mpu6050->error_sum;
        
        // 3. D 计算
        float D = pid_mpu6050->now_error - pid_mpu6050->last_error;

        // 4.计算PID
        pid_mpu6050->pid_out =  pid_mpu6050->Kp * P + pid_mpu6050->Ki * I + pid_mpu6050->Kd * D; 

        // 5. 输出限幅
        if(pid_mpu6050->pid_out > pid_mpu6050->max_out) pid_mpu6050->pid_out = pid_mpu6050->max_out;
        if(pid_mpu6050->pid_out < pid_mpu6050->min_out) pid_mpu6050->pid_out = pid_mpu6050->min_out;

        // 6.保存上一次误差值 
        pid_mpu6050->last_error = pid_mpu6050->now_error;

        // 7.修正方向判断          

        //往左边修正
        if(pid_mpu6050->actully_data < pid_mpu6050->target_data)
        {   
            right_flag_mpu6050 = 0;
            left_flag_mpu6050 = 1;      
        }
        //往右边修正
        if(pid_mpu6050->actully_data > pid_mpu6050->target_data)
        {   
            left_flag_mpu6050 = 0;
            right_flag_mpu6050 = 1;
        }
        Mpu6050_Control();
}




