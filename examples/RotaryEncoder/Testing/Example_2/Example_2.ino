/**
 * Rotary Encoder Example 2
 *
 * Josh Kaplan <jk@joshkaplan.org>
 * November 9, 2014
 * 
 * Sources:
 *     https://www.youtube.com/watch?v=HQuLZHsGZdI 
 *     http://www.kevindarrah.com/download/arduino_code/Encoder.pde
 */

int pulses;
int A_SIG = 4, B_SIG = 3;

void setup()
{
    attachInterrupt(0, A_RISE, RISING);
    attachInterrupt(1, B_RISE, RISING);
    Serial.begin(115200);
}

void loop()
{
    
}

void A_RISE()
{
    detachInterrupt(0);
    A_SIG=1;

    if(B_SIG==0)
    pulses++;//moving forward
    if(B_SIG==1)
    pulses--;//moving reverse
    Serial.println(pulses);
    attachInterrupt(0, A_FALL, FALLING);
}

void A_FALL()
{
    detachInterrupt(0);
    A_SIG=0;

    if(B_SIG==1)
    pulses++;//moving forward
    if(B_SIG==0)
    pulses--;//moving reverse
    Serial.println(pulses);
    attachInterrupt(0, A_RISE, RISING);  
}

void B_RISE()
{
    detachInterrupt(1);
    B_SIG=1;

    if(A_SIG==1)
    pulses++;//moving forward
    if(A_SIG==0)
    pulses--;//moving reverse
    Serial.println(pulses);
    attachInterrupt(1, B_FALL, FALLING);
}

void B_FALL()
{
    detachInterrupt(1);
    B_SIG=0;

    if(A_SIG==0)
    pulses++;//moving forward
    if(A_SIG==1)
    pulses--;//moving reverse
    Serial.println(pulses);
    attachInterrupt(1, B_RISE, RISING);
}
