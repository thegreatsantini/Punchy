// Header file for input output functions
#include <stdio.h>
#include <pigpio.h>

int LED_PINS[] = {17, 18, 27, 22, 23};
int BUTTON_PINS[] = {5, 6, 13, 19, 26};

int activated[] = {0, 0, 0, 0, 0, 0};
int prev_btn[] = {1, 1, 1, 1, 1}; // pull-up so default is 1
int btn3_latch = 0;
int solved = 0;

int main(void)
{
    gpioInitialise();

    for (int i = 0; i < 5; i++)
    {
        int pin = LED_PINS[i];
        gpioSetMode(pin, PI_OUTPUT);
    }

    for (int i = 0; i < 5; i++)
    {
        int pin = BUTTON_PINS[i];
        gpioSetMode(pin, PI_INPUT);
        gpioSetPullUpDown(pin, PI_PUD_UP);
    }

    while (solved == 0)
    {
        // Button 1
        if (gpioRead(BUTTON_PINS[0]) == 0)
        {
            gpioWrite(LED_PINS[0], 1);
        } // Button 2
        if (gpioRead(BUTTON_PINS[1]) == 0)
        {
            gpioWrite(LED_PINS[1], 1);
        } // Button 3
        if (gpioRead(BUTTON_PINS[2]) == 0)
        {

            if (solved == 1)
            {
                printf("Run solved sequence");
            }
            else
            {
                int curr = gpioRead(BUTTON_PINS[2]);
                if (curr == 0 && prev_btn[2] == 1)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (i == 2)
                        {
                            activated[2] = !activated[2];
                            gpioWrite(LED_PINS[2], activated[2]);
                        }
                        else
                        {
                            activated[i] = 0;
                            gpioWrite(LED_PINS[i], 0);
                        }
                    }
                }
                prev_btn[2] = curr;
            }
        } // Button 4
        if (gpioRead(BUTTON_PINS[3]) == 0)
        {
            gpioWrite(LED_PINS[3], 1);
        } // Button 5
        if (gpioRead(BUTTON_PINS[4]) == 0)
        {
            gpioWrite(LED_PINS[4], 1);
        }

        gpioDelay(10000);
    }

    return 0;
}
