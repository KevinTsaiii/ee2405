#include "mbed.h"
#include "parallax.h"
#include "uLCD_4DGL.h"
#include "math.h"

DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
DigitalOut blueLED(LED3);

DigitalIn speech_IO7(D5);
DigitalIn speech_IO8(D6);
DigitalIn speech_IO9(D8);

PwmOut pin12(D12), pin11(D11), buzzer(D3);

uLCD_4DGL uLCD(D1, D0, D2);

Serial xbee(D9, D7);

I2C i2c( D14, D15 );

void FXOS8700CQ_enable();
float FXOS8700CQ_read_X();
float FXOS8700CQ_read_Y();
float FXOS8700CQ_read_Z();

//parallax_servo *servo0_ptr, *servo1_ptr;

int main()
{
    parallax_servo servo_left(pin11);   //Left wheel
    parallax_servo servo_right(pin12);   //Right wheel
    servo_ticker.attach(&servo_control, .5);

    FXOS8700CQ_enable();
    int slope;

    while(1)
    {
        //go 0001
        if (speech_IO7 == 1 && speech_IO8 == 0 && speech_IO9 == 0)
        {
            //Red
            redLED = 0;
            greenLED = 1;
            blueLED = 1;

            //Move forward
            servo_left = 100;
            servo_right = -100;

            uLCD.cls();
            uLCD.printf("\nMoving forward\n");

            xbee.printf("Moving forward \n");

            wait(1);
        }

        //back 0010
        else if (speech_IO7 == 0 && speech_IO8 == 1 && speech_IO9 == 0)
        {
            //Green
            redLED = 1;
            greenLED = 0;
            blueLED = 1;

            //Move backward
            servo_left = -100;
            servo_right = 100;

            uLCD.cls();
            uLCD.printf("\nMoving backward\n");

            xbee.printf("Moving backward\n");

            wait(1);
        }

        //left 0011
        else if (speech_IO7 == 1 && speech_IO8 == 1 && speech_IO9 == 0)
        {
            //Blue
            redLED = 1;
            greenLED = 1;
            blueLED = 0;

            //Turn left
            servo_left = -5;
            servo_right = -100;

            uLCD.cls();
            uLCD.printf("\nTurning left\n");

            xbee.printf("Turning left   \n");

            wait(1);
        }

        //right 0100
        else if (speech_IO7 == 0 && speech_IO8 == 0 && speech_IO9 == 1)
        {
            //Green + red
            redLED = 0;
            greenLED = 0;
            blueLED = 1;

            //Turn right
            servo_left = 100;
            servo_right = 5;

            uLCD.cls();
            uLCD.printf("\nTurning right\n");

            xbee.printf("Turning right  \n");

            wait(1);
        }

        else if (speech_IO7 == 0 && speech_IO8 == 0 && speech_IO9 == 0)
        {
            redLED = 1;
            greenLED = 1;
            blueLED = 1;

            //Stop
            servo_left = 0;
            servo_right = 0;

            uLCD.cls();
            uLCD.printf("\nStanding by\n");

            xbee.printf("Standing by    \n");
            slope = acos(FXOS8700CQ_read_Z())*180/3.14159;
            xbee.printf("Slope: %02d deg  \n", slope);

            wait(0.3);
        }
    }
}