#ifndef MYNEWTASK_H_
#define MYNEWTASK_H_

/* Fwk */
#include "TimersManager.h"
#include "FunctionLib.h"
#include "LED.h"
/* KSDK */
#include "fsl_common.h"
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "MKW41Z4.h"

extern uint8_t counterto200;
/* Define the available Task's Events */
#define gMyNewTaskEvent1_c (1 << 0)
#define gMyNewTaskEvent2_c (1 << 1)
#define gMyNewTaskEvent3_c (1 << 2)

#define gMyTaskPriority_c 3
#define gMyTaskStackSize_c 400

#define BOARD_SW3_GPIO_PIN 4U
#define BOARD_SW3_GPIO GPIOC
#define BOARD_SW3_IRQ PORTB_PORTC_IRQn
#define SW_NVIC_PRIO 2

void MyTaskTimer_Start(void);
void MyTaskTimer_Stop(void);
void MyTask_Init(void);
static void myTaskTimerCallback(void *param);
void Counter_change(uint8_t N);
void My_Task(osaTaskParam_t argument);

#endif /* MYNEWTASK_H_ */
