#include "MY_Camera.h"
#include "ANO_DT_LX.h"
#include "Drv_Uart.h"
#include "MY_fly_fun.h"
#include "MY_PID.h"
#include "ANO_LX.h"

//飞机Y对应摄像头X


#define X_POSITION 320 
#define Y_POSITION 240 
#define Z_POSITION 0

#define R_num 30
#define G_num 29

char camera_data[20] = {0};
u8 camera_flag = 0, len = 0, count_data = 0;

u16 R_location = 0, G_location = 0;
s16 R_l_error = 0, G_l_error = 0;
u16 R_distance = 0, G_distance = 0;
s16 R_r_error = 0, G_r_error = 0;

void Camera_Data(void) //处理接收的数据              
{	
	R_location = camera_data[0] * 100 + camera_data[1] * 10 + camera_data[2];
    R_distance = camera_data[3] * 100 + camera_data[4] * 10 + camera_data[5];
    R_l_error = R_location - X_POSITION;   //飞机Y轴对应摄像头X轴
    R_r_error = R_distance - R_num;   

    G_location = camera_data[6] * 100 + camera_data[7] * 10 + camera_data[8];
    G_distance = camera_data[9] * 100 + camera_data[10] * 10 + camera_data[11];
    G_l_error = G_location - X_POSITION;
    G_r_error = G_distance - G_num;

    if(R_location == 0 && R_distance == 0)
    {
        R_l_error = 0;
        R_r_error = 0;
    }
    if(G_location == 0 && G_distance == 0)
    {
        G_l_error = 0;
        G_r_error = 0;
    }

	ANO_DT_Send_MY_DATA(0xF2,4,R_location,R_distance,G_l_error,G_r_error);
}

/*接收Camera传过来的数据（转移寄存器）*/
void Camera_Receive_Data(uint8_t data) 
{
    static u8 state = 0;
    static u8 sum_data = 0;
    // DrvUart2SendBuf(&data,1);
    if (state == 0 && data == 0xFE)     //帧头1
    {
        state = 1;
    }
    
	else if (state == 1)                //数据长度      
    {
        sum_data = 0;
        len = data;
        count_data = 0;
        state = 2;
    }

    else if (state == 2)                //数据内容
    {	            
        camera_data[count_data] = data; 
        sum_data += data;
        count_data++;       
        if(count_data >= len)
            state = 3;
    }                 

	else if (state == 3)               //校验和      
    {
        if(data == sum_data)
            state = 4;
        else
            state = 0;
    }
    else if (state == 4 && data == 0xEF)
    {
        // MY_Camera_print("ok\n");

        Camera_Data();
        state = 0;
    }
	else 
	{		
		state = 0;	
	}
}
