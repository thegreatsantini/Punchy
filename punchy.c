// Header file for input output functions
#include <stdio.h>
#include <pigpio.h>

int LED_PINS[] = {18, 23, 24, 25, 12};
int BTN_PINS[] = {2, 3, 4, 17, 27};
int activated[] = {0, 0, 0, 0, 0};
int btn1_latched = 0;
int game_won = 0;

void evaluate(int btn1_held, int *on)
{
    on[0] = btn1_held || btn1_latched;
    on[2] = activated[2];
    on[1] = activated[1] && on[2];
    on[4] = activated[4] && on[1] && on[2];
    on[3] = activated[3] && on[0] && on[1] && on[2] && on[4];
}

void handle_press(int i, int *on)
{
    if (i == 2)
    {
        activated[2] = !activated[2];
        activated[1] = 0;
        activated[4] = 0;
        activated[3] = 0;
    }

    // btn 2
    else if (i == 1)
    {
        if (on[2] == 1)
        {
            activated[1] = 1;
        }
    }

    // btn 5
    else if (i == 4)
    {
        if (on[1] && on[2])
        {
            activated[4] = 1;
        }
    }
    // btn 4
    else if (i == 3)
    {
        if (on[0] && on[1] && on[2] && on[4])
        {
            activated[3] = 1;
            btn1_latched = 1;
        }
    }
}
void win_sequence()
{
    for (int i = 0; i < 5; i++)
    {
        gpioWrite(LED_PINS[i], 1);
        gpioDelay(150000);
    }

    for (int f = 0; f < 3; f++)
    {
        for (int i = 0; i < 5; i++)
            gpioWrite(LED_PINS[i], 0);
        gpioDelay(200000);
        for (int i = 0; i < 5; i++)
            gpioWrite(LED_PINS[i], 1);
        gpioDelay(200000);
    }
    while (gpioRead(BTN_PINS[0]) != 0)
    {
    }

    for (int i = 0; i < 5; i++)
        gpioWrite(LED_PINS[i], 0);
    activated[0] = 0;
    activated[1] = 0;
    activated[2] = 0;
    activated[3] = 0;
    activated[4] = 0;
    btn1_latched = 0;
    game_won = 0;
}

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
    int prev_state[5] = {0, 0, 0, 0, 0};
    while (!game_won)
    {
        int btn1_held = (gpioRead(BTN_PINS[0]) == 0);
        int btn_state[5];
        for (int i = 0; i < 5; i++)
        {
            int btn_pressed = (gpioRead(BTN_PINS[i]) == 0);
            btn_state[i] = btn_pressed;
        }
        int on[5];
        evaluate(btn1_held, on);
        for (int i = 0; i < 5; i++)
        {
            int pin = LED_PINS[i];
            int value = on[i];
            gpioWrite(pin, value);
        }
        for (int i = 0; i < 5; i++)
        {
            if (btn_state[i] == 1 && prev_state[i] == 0)
            {
                handle_press(i, on);
            }
            prev_state[i] = btn_state[i];
        }
        if (btn1_latched == 1 && prev_state[0] == 1 && btn_state[0] == 0 && on[0] && on[1] && on[2] && on[3] && on[4])
        {
            game_won = 1;
        }
        gpioDelay(20000);
    }
    win_sequence();
    gpioTerminate();
    return 0;
}