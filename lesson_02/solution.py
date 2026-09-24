# ============================================================
#  punchy_l2_solution.py  —  Bacon Byte, Lesson 2: Functions
#  MENTOR COPY. Don't put this on the Pi before class.
#
#  Same puzzle, same behavior, bug fixed.
#  Every rule now lives in exactly ONE place.
# ============================================================

from gpiozero import LED, Button
from time import sleep

# A list is a numbered shelf of things. leds[0] is the first one.
leds    = [LED(17), LED(18), LED(27), LED(22), LED(23)]
buttons = [Button(5), Button(6), Button(13), Button(19), Button(26)]
was_down = [False, False, False, False, False]


# ---------- Functions: each one does ONE job ----------

def set_led(n, on):
    """Turn LED n (1-5) on or off, and say so."""
    if on:
        leds[n - 1].on()   # humans count from 1, Python counts from 0.
    else:                  # The function hides that so nobody else has to care.
        leds[n - 1].off()
    state = "on" if on else "off"
    print(f"LED {n} {state}")


def is_lit(n):
    """Return True if LED n is on."""
    return leds[n - 1].is_lit


def just_pressed(n):
    """Return True only at the moment button n goes down (not while held)."""
    down = buttons[n - 1].is_pressed
    pressed_now = down and not was_down[n - 1]
    was_down[n - 1] = down
    return pressed_now


def can_light(n):
    """THE PUZZLE RULE. LED 1 is free; every other LED needs the one before it lit."""
    if n == 1:
        return True
    return is_lit(n - 1)


def handle_button(n):
    """What happens when button n is pressed."""
    if is_lit(n):
        set_led(n, False)
    elif can_light(n):
        set_led(n, True)
    else:
        print(f"LED {n} is locked. Light LED {n - 1} first.")


def all_lit():
    """Return True if every LED is on."""
    for n in range(1, 6):
        if not is_lit(n):
            return False
    return True


def blink_all(times):
    """Flash every LED together, then leave them off."""
    for _ in range(times):
        for led in leds:
            led.off()
        sleep(0.3)
        for led in leds:
            led.on()
        sleep(0.3)
    for led in leds:
        led.off()


# ---------- The main loop now reads like English ----------

print("Punchy is awake. Light all 5. Ctrl+C to quit.")

try:
    while True:
        for n in range(1, 6):
            if just_pressed(n):
                handle_button(n)

        if all_lit():
            print("PUZZLE SOLVED!")
            blink_all(2)

        sleep(0.02)

except KeyboardInterrupt:
    print("\nBye!")