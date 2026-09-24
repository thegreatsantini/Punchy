# ============================================================
#  punchy_l2.py  —  Bacon Byte, Lesson 2: Functions
#
#  This code runs. It's also UGLY on purpose.
#  Your job tonight: find what's wrong with it, then fix
#  the ugliness using FUNCTIONS.
#
#  The puzzle: light all 5 LEDs.
#    - LED 1 can always be turned on.
#    - Every other LED is LOCKED until the one before it is lit.
#    - Pressing a lit LED's button turns it off.
#
#  Run it:   python3 punchy_l2.py      (Ctrl+C to quit)
# ============================================================

from gpiozero import LED, Button
from time import sleep

led1 = LED(17)
led2 = LED(18)
led3 = LED(27)
led4 = LED(22)
led5 = LED(23)

btn1 = Button(5)
btn2 = Button(6)
btn3 = Button(13)
btn4 = Button(19)
btn5 = Button(26)

# Was each button already down last time through the loop?
# (So holding a button doesn't count as 100 presses.)
was1 = False
was2 = False
was3 = False
was4 = False
was5 = False

print("Punchy is awake. Light all 5. Ctrl+C to quit.")

try:
    while True:

        # ----- Button 1 -----
        if btn1.is_pressed and not was1:
            if led1.is_lit:
                led1.off()
                print("LED 1 off")
            else:
                led1.on()
                print("LED 1 on")
        was1 = btn1.is_pressed

        # ----- Button 2 -----
        if btn2.is_pressed and not was2:
            if led2.is_lit:
                led2.off()
                print("LED 2 off")
            elif led1.is_lit:
                led2.on()
                print("LED 2 on")
            else:
                print("LED 2 is locked. Light LED 1 first.")
        was2 = btn2.is_pressed

        # ----- Button 3 -----
        if btn3.is_pressed and not was3:
            if led3.is_lit:
                led3.off()
                print("LED 3 off")
            elif led2.is_lit:
                led3.on()
                print("LED 3 on")
            else:
                print("LED 3 is locked. Light LED 2 first.")
        was3 = btn3.is_pressed

        # ----- Button 4 -----
        if btn4.is_pressed and not was4:
            if led4.is_lit:
                led4.off()
                print("LED 4 off")
            elif led3.is_lit:
                led5.on()
                print("LED 4 on")
            else:
                print("LED 4 is locked. Light LED 3 first.")
        was4 = btn4.is_pressed

        # ----- Button 5 -----
        if btn5.is_pressed and not was5:
            if led5.is_lit:
                led5.off()
                print("LED 5 off")
            elif led4.is_lit:
                led5.on()
                print("LED 5 on")
            else:
                print("LED 5 is locked. Light LED 4 first.")
        was5 = btn5.is_pressed

        # ----- Did they win? -----
        if led1.is_lit and led2.is_lit and led3.is_lit and led4.is_lit and led5.is_lit:
            print("PUZZLE SOLVED!")
            led1.off()
            led2.off()
            led3.off()
            led4.off()
            led5.off()
            sleep(0.3)
            led1.on()
            led2.on()
            led3.on()
            led4.on()
            led5.on()
            sleep(0.3)
            led1.off()
            led2.off()
            led3.off()
            led4.off()
            led5.off()
            sleep(0.3)
            led1.on()
            led2.on()
            led3.on()
            led4.on()
            led5.on()
            sleep(0.3)
            led1.off()
            led2.off()
            led3.off()
            led4.off()
            led5.off()

        sleep(0.02)

except KeyboardInterrupt:
    print("\nBye!")