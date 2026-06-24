#include "main.h"

//循迹环参数
int Place_Left_Pwm  = 30;
int Place_Right_Pwm = 30;

//角度环参数
int Angle_Left_Pwm  = 20;
int Angle_Right_Pwm = 20;


void Motor_Init(void)
{
    // 左电机
    DL_GPIO_setPins(AIN1_PORT, AIN1_PIN);
    DL_GPIO_clearPins(AIN2_PORT, AIN2_PIN);

    // 右电机
    DL_GPIO_setPins(BIN1_PORT, BIN1_PIN);
    DL_GPIO_clearPins(BIN2_PORT, BIN2_PIN);
    
}

void Motor_Control(void)
{
    if(left_flag == 1 && right_flag == 0)           //左边修正
        {
            Place_Left_Pwm = Place_Base_Speed - pid.pid_out;
            Place_Right_Pwm = Place_Base_Speed + pid.pid_out;
            if(Place_Left_Pwm < Place_Min_Speed)
            {
                Place_Left_Pwm = Place_Min_Speed;
            }
            if(Place_Left_Pwm > Place_Max_Speed)
            {
                Place_Left_Pwm = Place_Max_Speed;
            }
            if(Place_Right_Pwm > Place_Max_Speed)
            {
                Place_Right_Pwm = Place_Max_Speed;
            }
            if(Place_Right_Pwm < Place_Min_Speed)
            {
                Place_Right_Pwm = Place_Min_Speed;
            }
        }
        if(right_flag == 1 && left_flag == 0)//右边修正
        {
            Place_Left_Pwm = Place_Base_Speed + pid.pid_out;
            Place_Right_Pwm = Place_Base_Speed - pid.pid_out;
            if(Place_Left_Pwm < Place_Min_Speed)
            {
                Place_Left_Pwm = Place_Min_Speed;
            }
            if(Place_Left_Pwm > Place_Max_Speed)
            {
                Place_Left_Pwm = Place_Max_Speed;
            }
            if(Place_Right_Pwm > Place_Max_Speed)
            {
                Place_Right_Pwm = Place_Max_Speed;
            }
            if(Place_Right_Pwm < Place_Min_Speed)
            {
                Place_Right_Pwm = Place_Min_Speed;
            }
        }  
        DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, Place_Left_Pwm, DL_TIMER_CC_0_INDEX);
        DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, Place_Right_Pwm, DL_TIMER_CC_1_INDEX); 
}

void Mpu6050_Control(void)
{
        if(left_flag_mpu6050 == 1 && right_flag_mpu6050 == 0)           //向左修正
        {
            Angle_Left_Pwm = Angle_Base_Speed - pid_mpu6050.pid_out;
            Angle_Right_Pwm = Angle_Base_Speed + pid_mpu6050.pid_out;
            if(Angle_Left_Pwm < Angle_Min_Speed)
            {
                Angle_Left_Pwm = Angle_Min_Speed;
            }
            if(Angle_Left_Pwm > Angle_Max_Speed)
            {
                Angle_Left_Pwm = Angle_Max_Speed;
        }
            if(Angle_Right_Pwm > Angle_Max_Speed)
            {
                Angle_Right_Pwm = Angle_Max_Speed;
            }
            if(Angle_Right_Pwm < Angle_Min_Speed)
            {
                Angle_Right_Pwm = Angle_Min_Speed;
            }
        }
        if(right_flag_mpu6050 == 1 && left_flag_mpu6050 == 0)           //右边修正
        {
            Angle_Left_Pwm = Angle_Base_Speed + pid_mpu6050.pid_out;
            Angle_Right_Pwm = Angle_Base_Speed - pid_mpu6050.pid_out;
            if(Angle_Left_Pwm < Angle_Min_Speed)
            {
                Angle_Left_Pwm = Angle_Min_Speed;
            }
            if(Angle_Left_Pwm > Angle_Max_Speed)
            {
                Angle_Left_Pwm = Angle_Max_Speed;
            }
            if(Angle_Right_Pwm > Angle_Max_Speed)
            {
                Angle_Right_Pwm = Angle_Max_Speed;
            }
            if(Angle_Right_Pwm < Angle_Min_Speed)
            {
                Angle_Right_Pwm = Angle_Min_Speed;
            }
        }            
        DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, Angle_Left_Pwm, DL_TIMER_CC_0_INDEX);
        DL_TimerA_setCaptureCompareValue(PWM_MOTOR_INST, Angle_Right_Pwm, DL_TIMER_CC_1_INDEX); 
}


void Motor_show(PID_TypeDef *pid , PID_mpu6050_TypeDef *pid_mpu6050)
{   
//         uint8_t string[20] = {0};
//         sprintf((char*)string, "%.1f" , pitch);
//         OLED_ShowString(0, 0, string, 16);
//         sprintf((char*)string, "%.1f" , roll);
}

// //每50ms计算一次行驶的路程
// void s_calculate(void)
// {
//     s_right = (float)count_right / line * pi * diameter;    //行驶的路程,单位cm , 0.048cm
//     s_right_sum += s_right;                                 //计算路程累加和
//     count_right = 0;                                        //count计数值清零 
// }
