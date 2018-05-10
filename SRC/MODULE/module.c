/**********************************************************************************************************
                                天穹飞控 —— 致力于打造中国最好的多旋翼开源飞控
                                Github: github.com/loveuav/BlueSkyFlightControl
                                技术讨论：bbs.loveuav.com/forum-68-1.html
 * @文件     module.c
 * @说明     提供通用的传感器数据输出接口
 * @版本  	 V1.0
 * @作者     BlueSky
 * @网站     bbs.loveuav.com
 * @日期     2018.05 
**********************************************************************************************************/

#include "module.h"
#include "mpu6000.h"

/**********************************************************************************************************
*函 数 名: GyroSensorInit
*功能说明: 陀螺仪传感器初始化
*形    参: 无
*返 回 值: 陀螺仪存在状态 
**********************************************************************************************************/
bool GyroSensorInit(void)
{
    #if (GYRO_TYPE == MPU6000)
    if(MPU6000_Detect())
    {
        MPU6000_Init();
        return true;
    }
    else
    {
        return false;
    }        
    #endif
}

/**********************************************************************************************************
*函 数 名: MagSensorInit
*功能说明: 磁力传感器初始化
*形    参: 无
*返 回 值: 磁力计存在状态 
**********************************************************************************************************/
bool MagSensorInit(void)
{
    return false;    
}

/**********************************************************************************************************
*函 数 名: BaroSensorInit
*功能说明: 气压传感器初始化
*形    参: 无
*返 回 值: 气压计存在状态
**********************************************************************************************************/
bool BaroSensorInit(void)
{
    return false;
}

/**********************************************************************************************************
*函 数 名: GyroSensorRead
*功能说明: 角速度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void GyroSensorRead(Vector3i_t* gyro)
{
    #if (GYRO_TYPE == MPU6000)
    MPU6000_ReadGyro(gyro);
    #endif    
}

/**********************************************************************************************************
*函 数 名: AccSensorRead
*功能说明: 加速度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void AccSensorRead(Vector3i_t* acc)
{
    #if (GYRO_TYPE == MPU6000)
    MPU6000_ReadAcc(acc);
    #endif    
}

/**********************************************************************************************************
*函 数 名: TempSensorRead
*功能说明: 陀螺仪温度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void TempSensorRead(float* temp)
{
    #if (GYRO_TYPE == MPU6000)
    MPU6000_ReadTemp(temp);
    #endif    
}

/**********************************************************************************************************
*函 数 名: MagSensorRead
*功能说明: 罗盘数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void MagSensorRead(Vector3i_t* mag)
{
    
}

/**********************************************************************************************************
*函 数 名: BaroSensorRead
*功能说明: 气压高度数据读取
*形    参: 读出数据指针
*返 回 值: 无
**********************************************************************************************************/
void BaroSensorRead(int32_t baroAlt)
{
    
}

/**********************************************************************************************************
*函 数 名: GyroDataNormalize
*功能说明: 陀螺仪数据单位化
*形    参: 原始数据
*返 回 值: 单位化后的数据
**********************************************************************************************************/
Vector3f_t GyroDataNormalize(Vector3i_t raw)
{
    #if (GYRO_TYPE == MPU6000)
    return MPU6000_GyroNormalize(raw);
    #endif     
}

/**********************************************************************************************************
*函 数 名: AccDataNormalize
*功能说明: 加速度数据单位化
*形    参: 原始数据
*返 回 值: 单位化后的数据
**********************************************************************************************************/
Vector3f_t AccDataNormalize(Vector3i_t raw)
{
    #if (GYRO_TYPE == MPU6000)
    return MPU6000_AccNormalize(raw);
    #endif     
}














