#include "MyNewTask.h"
#include "router_eligible_device_app.h"
osaEventId_t mMyEvents;
/* Global Variable to store our TimerID */
tmrTimerID_t myTimerID = gTmrInvalidTimerID_c;
/* Handler ID for task */
osaTaskId_t gMyTaskHandler_ID;
/* Local variable to store the current state of the LEDs */
static uint8_t ledsState = 0;


/* OSA Task Definition*/
OSA_TASK_DEFINE(My_Task, gMyTaskPriority_c, 1, gMyTaskStackSize_c, FALSE );


//void Counter_change(uint8_t N)
//{
//	led_count = N--;
//}
/* Main custom task */
void My_Task(osaTaskParam_t argument)
{
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();

	while(1)
	{
		OSA_EventWait(mMyEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c, &customEvent);

		if( !gUseRtos_c && !customEvent)
		{
			break;
		}

		/* Depending on the received event */
		switch(customEvent){
			case gMyNewTaskEvent1_c:
				TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
				5000, /* Timer's Timeout */
				myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
				NULL);
				TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
//			case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
//				switch(led_count)
//				{
//					case 0:
//						TurnOffLeds();
//						Led2On();		//RED
//						//App_SendSensorStatus(led_count);
//						led_count++;
//					break;
//					case 1:
//						TurnOffLeds();
//						Led3On();		//GREEN
//						//App_SendSensorStatus(led_count);
//						led_count++;
//					break;
//					case 2:
//						TurnOffLeds();
//						Led4On();		//BLUE
//						//App_SendSensorStatus(led_count);
//						led_count++;
//					break;
//					case 3:
//						TurnOffLeds();
//						Led3On();		//GREEN
//						Led4On();		//BLUE
//						//App_SendSensorStatus(led_count);
//						led_count++;
//					break;
//					case 4:
//						TurnOffLeds();
//						Led2On();		//RED
//						Led4On();		//BLUE
//						//App_SendSensorStatus(led_count);
//						led_count++;
//					break;
//					case 5:
//						TurnOnLeds();
//						//App_SendSensorStatus(led_count);
//						led_count = 0;
//					break;
//					//Porque no existe endcase en C :(((
//				}
//
//			break;
			case gMyNewTaskEvent3_c: /* Event to stop the timer */
				ledsState = 0;
				TurnOffLeds();
				TMR_StopTimer(myTimerID);
			break;
			default:
			break;
	  }
	}
}

/* Function to init the task */
void MyTask_Init(void)
{
	mMyEvents = OSA_EventCreate(TRUE);
	/* The instance of the MAC is passed at task creaton */
	gMyTaskHandler_ID = OSA_TaskCreate(OSA_TASK(My_Task), NULL);
}

void MyTaskTimer_Start(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent1_c);

}

/* This is the function called by the Timer each time it expires */
void myTaskTimerCallback(void *param)
{
	//uint16_t led_count = 0;
	OSA_EventSet(mMyEvents, gMyNewTaskEvent2_c);
	Ip_view();
}



/* Public function to send an event to stop the timer */
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent3_c);
}

