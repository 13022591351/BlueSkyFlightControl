/**********************************************************************************************************
                                天穹飞控 —— 致力于打造中国最好的多旋翼开源飞控
                                Github: github.com/loveuav/BlueSkyFlightControl
                                技术讨论：bbs.loveuav.com/forum-68-1.html
 * @文件     module_task.c
 * @说明     传感器及外设等相关任务
 * @版本  	 V1.0
 * @作者     BlueSky
 * @网站     bbs.loveuav.com
 * @日期     2018.05 
**********************************************************************************************************/
#include "TaskConfig.h"

#include "module.h"

//声明任务句柄
xTaskHandle imuSensorReadTask;

/**********************************************************************************************************
*函 数 名: vImuSensorReadTask
*功能说明: IMU传感器数据读取任务，此任务具有最高优先级，运行频率为1KHz
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
portTASK_FUNCTION(vImuSensorReadTask, pvParameters) 
{
	portTickType xLastWakeTime;

	Vector3i_t* accRawData = pvPortMalloc(sizeof(Vector3i_t));
	Vector3i_t* gyroRawData = pvPortMalloc(sizeof(Vector3i_t));
	float* tempRawData = pvPortMalloc(sizeof(float));

	//挂起调度器
	vTaskSuspendAll();
	
	//陀螺仪传感器初始化
	GyroSensorInit();
	
	//唤醒调度器
	xTaskResumeAll();

	xLastWakeTime = xTaskGetTickCount();
	for(;;) 
	{
		//读取加速度传感器
		AccSensorRead(accRawData);
		//读取陀螺仪传感器
		GyroSensorRead(gyroRawData);
		//读取温度传感器
		TempSensorRead(tempRawData);		
		
		//往消息队列中填充数据
		xQueueSendToBack(messageQueue[ACC_SENSOR_READ],  (void *)&accRawData, 0); 		
		xQueueSendToBack(messageQueue[GYRO_SENSOR_READ],  (void *)&gyroRawData, 0); 
		xQueueSendToBack(messageQueue[TEMP_SENSOR_READ],  (void *)&tempRawData, 0); 

        //睡眠1ms
		vTaskDelayUntil(&xLastWakeTime, (1 / portTICK_RATE_MS));
	}
}

/**********************************************************************************************************
*函 数 名: ModuleTaskCreate
*功能说明: 传感器组件相关任务创建
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void ModuleTaskCreate(void)
{
	xTaskCreate(vImuSensorReadTask, "imuSensorReadTask", IMU_SENSOR_READ_TASK_STACK, NULL, IMU_SENSOR_READ_TASK_PRIORITY, &imuSensorReadTask); 
}


/**********************************************************************************************************
*函 数 名: GetImuSensorReadTaskStackUse
*功能说明: 获取任务堆栈使用情况
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
int16_t	GetImuSensorReadTaskStackUse(void)
{
	return uxTaskGetStackHighWaterMark(imuSensorReadTask);
}





