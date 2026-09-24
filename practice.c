/* buttontest.c — Punchy hardware check.
 * Press a button, its LED toggles. That's it.
 * Build: gcc buttontest.c -o buttontest -lpigpio && sudo ./buttontest
 */

#include <pigpio.h>
#include <stdio.h>
#include <signal.h>

#define N 5

static const int leds[N]    = {18, 23, 24, 25, 12};
static const int buttons[N] = { 5,  6, 13, 19, 26};

static volatile sig_atomic_t running = 1;

static void stop(int signum) { running = 0; }

int main(void) {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio init failed (are you root?)\n");
        return 1;
    }
    gpioSetSignalFunc(SIGINT, stop);

    int state[N] = {0};
    int last[N];

    for (int i = 0; i < N; i++) {
        gpioSetMode(leds[i], PI_OUTPUT);
        gpioWrite(leds[i], 0);

        gpioSetMode(buttons[i], PI_INPUT);
        gpioSetPullUpDown(buttons[i], PI_PUD_UP);  /* pressed == LOW */
        last[i] = gpioRead(buttons[i]);
    }

    printf("Button test live. Press each one — matching LED should toggle.\n");
    printf("Ctrl-C to quit (GPIO gets cleaned up).\n\n");

    while (running) {
        for (int i = 0; i < N; i++) {
            int now = gpioRead(buttons[i]);

            if (last[i] == 1 && now == 0) {        /* falling edge = press */
                state[i] = !state[i];
                gpioWrite(leds[i], state[i]);
                printf("BTN %d (BCM %2d)  ->  LED (BCM %2d)  %s\n",
                       i + 1, buttons[i], leds[i], state[i] ? "ON " : "OFF");
                fflush(stdout);
                gpioDelay(25000);                  /* 25ms debounce */
                now = gpioRead(buttons[i]);
            }
            last[i] = now;
        }
        gpioDelay(2000);
    }

    for (int i = 0; i < N; i++) gpioWrite(leds[i], 0);
    gpioTerminate();
    printf("\nClean exit.\n");
    return 0;
}