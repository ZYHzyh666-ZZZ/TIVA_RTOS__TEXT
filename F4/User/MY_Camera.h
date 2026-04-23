#ifndef _MY_CAMERA_H_
#define _MY_CAMERA_H_

#include "SysConfig.h"

extern s16 R_l_error, G_l_error;
extern s16 R_r_error, G_r_error;
extern u16 R_location, G_location;

extern u8 camera_flag;

void Camera_Data(void); //处理接收的数据              
void Camera_Receive_Data(uint8_t data); 



#endif
