
GPIO assignments (LEDs):

LED 1 → GPIO17 ✅
LED 2 → GPIO18
LED 3 → GPIO27
LED 4 → GPIO22
LED 5 → GPIO23

GPIO assignments (buttons):

BTN 1 → GPIO5
BTN 2 → GPIO6
BTN 3 → GPIO13
BTN 4 → GPIO19
BTN 5 → GPIO26


python3 -c "
import RPi.GPIO as GPIO; 
GPIO.setmode(GPIO.BCM); 
GPIO.setup(17, GPIO.OUT); 
GPIO.output(17, True); 
input('Press enter to turn off'); 
GPIO.output(17, False); 
GPIO.cleanup()"


import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(5, GPIO.IN, pull_up_down=GPIO.PUD_UP)
print('Press the button...')
while True:
    if GPIO.input(5) == 0:
        print('PRESSED')
        break
GPIO.cleanup()
