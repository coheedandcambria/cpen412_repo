/*
 * EXAMPLE_1.C
 *
 * This is a minimal program to verify multitasking.
 *
 */

#include <stdio.h>
#include <Bios.h>
#include <ucos_ii.h>

#define STACKSIZE  256

/*
** Stacks for each task are allocated here in the application in this case = 256 bytes
** but you can change size to suit
*/

OS_STK Task1Stk[STACKSIZE];
OS_STK Task2Stk[STACKSIZE];
OS_STK Task3Stk[STACKSIZE];
OS_STK Task4Stk[STACKSIZE];

/* Prototypes for our threads*/
void Task1(void *);
void Task2(void *);
void Task3(void *);
void Task4(void *);

// Canbus Prototypes
void Init_CanBus_Controller0(void);
void Init_CanBus_Controller1(void);
void CanBus0_Transmit(void);
void CanBus1_Receive(void);
void CanBus0_Receive(void);
void CanBus1_Transmit(void);

/*
** Our main application which has to
** 1) Initialise any peripherals on the board, e.g. RS232 for hyperterminal + LCD
** 2) Call OSInit() to initialise the OS
** 3) Create our application task/threads
** 4) Call OSStart()
*/

void main(void)
{
    // initialise board hardware by calling our routines from the BIOS.C source file

    Init_RS232();
    Init_LCD();

/* display welcome message on LCD display */

    Oline0("Altera DE1/68K");
    Oline1("Micrium uC/OS-II RTOS");

    OSInit();		// call to initialise the OS

    Init_CanBus_Controller0();
    Init_CanBus_Controller1();

/* the smaller the numerical priority value, the higher the task priority */

    OSTaskCreate(Task1, OS_NULL, &Task1Stk[STACKSIZE], 12);
    OSTaskCreate(Task2, OS_NULL, &Task2Stk[STACKSIZE], 11);     // highest priority task
    OSTaskCreate(Task3, OS_NULL, &Task3Stk[STACKSIZE], 13);
    OSTaskCreate(Task4, OS_NULL, &Task4Stk[STACKSIZE], 14);

    OSStart();  // call to start the OS scheduler, (never returns from this)
}

/*
** IMPORTANT : ticker interrupts must be started within the highest priority task
** that runs which is Task2
*/

void Task1(void *pdata)
{

    for (;;) {
       //printf("This is Task #1\n");
       OSTimeDly(200);
       printf("Canbus0 Transmit  Canbus0 Receive\n");
       CanBus0_Transmit();
       CanBus1_Receive();
       printf("\n");

       printf("Canbus1 Transmit  Canbus0 Receive\n");
       CanBus1_Transmit();
       CanBus0_Receive();
       printf("\n");
    }
}

/*
** Task 2 below was created with the highest priority so it must start timer1
** so that it produces interrupts for the 100hz context switches
*/

void Task2(void *pdata)
{
    // must start timer ticker here

    Timer1_Init() ;      // this function is in BIOS.C and written by us to start timer

    for (;;) {
       //printf("....This is Task #2\n");
       OSTimeDly(10);
    }
}

void Task3(void *pdata)
{
    for (;;) {
       //printf("........This is Task #3\n");
       OSTimeDly(40);
    }
}

void Task4(void *pdata)
{

    for (;;) {
       //printf("............This is Task #4\n");
       OSTimeDly(50);
    }
}
