#include "timer_setup.h"
#include "receive_public.h"
#include "send_public.h"
#include "debug.h"
#include "motor_control.h"


// Initializes timer to specified period in ms
void timer_initialize(int ms)
{
    TimerHandle_t myTimer1;
    myTimer1 = xTimerCreate("test",
                           (ms/portTICK_PERIOD_MS),
                           pdTRUE, 
                           (void *)0,
                           timerCallback);
    if (xTimerStart(myTimer1,10) == pdFAIL)
        error('a');
}



// Increments clock
bool greenDetect = false;
void timerCallback( TimerHandle_t myTimer )
{
    traces(TIMER_CALLBACK_ENTER);
    updateClock();
    PID_Controller(); 
    Turningtime(); 
    Distancetime();
    serverstuff();
    traces(TIMER_CALLBACK_EXIT);
    //slowQueue();  
    uint16_t num = getGreen();
    if(greenDetect)
    {
        if(num < 1<<13)
        {
            greenDetect = false;
            //lost token
        }
    }else
    {
        if(num > 1 << 13)
        {
            greenDetect = true;
            //found token
            addQSnd('~');
            addQSnd(0x21);
            addQSnd(0);
            addQSnd(0);
            addQSnd(0);
            addQSnd(0);
            addQSnd(0);
            addQSnd(')');
        }
    }

    
    
    
}



