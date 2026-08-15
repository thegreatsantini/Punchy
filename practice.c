// Header file for input output functions
#include <stdio.h>
#include <pigpio.h>

int LED_PINS[] = {18, 23, 24, 25, 12};
int BTN_PINS[] = {5, 6, 13, 19, 26};

int main()
{

    if (gpioInitialise() < 0)
        return 1;

    for (int i = 0; i < 5; i++)
    {
        int pin = LED_PINS[i];
        gpioSetMode(pin, PI_OUTPUT);
    }

    for (int i = 0; i < 5; i++)
    {
        int pin = BTN_PINS[i];
        gpioSetMode(pin, PI_INPUT);
        gpioSetPullUpDown(pin, PI_PUD_UP);
    }
    while (1)
    {
        for (int i = 0; i < 5; i++)
        {
            int btn_pressed = (gpioRead(BTN_PINS[i]) == 0);
            gpioWrite(LED_PINS[i], btn_pressed);
        }

        gpioDelay(20000);
    }
    gpioTerminate();
    return 0;
}