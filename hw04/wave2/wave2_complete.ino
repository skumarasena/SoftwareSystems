/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;

void setup() 
{  
    Serial.begin(9600);

    pinMode(buttonPin1, INPUT_PULLUP);  
    pinMode(buttonPin2, INPUT_PULLUP);  

    pinMode(ledPin, OUTPUT);

    DDRD = B11000000;
    DDRB = B00111111;

    pinMode(13, OUTPUT);  
    pinMode(12, OUTPUT);  
    pinMode(11, OUTPUT);  
    pinMode(10, OUTPUT);  
    pinMode(9, OUTPUT);  
    pinMode(8, OUTPUT);  
    pinMode(7, OUTPUT);  
    pinMode(6, OUTPUT); 

    cli();

    //set timer0 interrupt at 2kHz
    TCCR0A = 0;// set entire TCCR0A register to 0
    TCCR0B = 0;// same for TCCR0B

    TCNT0  = 0;//initialize counter value to 0

    // set compare match register for 2khz increments: [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
    OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)

    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);   
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);

    sei();

 

}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

ISR(TIMER0_COMPA_vect) {
    int button1 = digitalRead(buttonPin1);
    if (button1) return;

    counter += stride;
    if (counter > high) {
        counter = low;
        // Serial.println(counter);
    }

    // write to the digital pins  
    writeByte(counter);

}

void writeByte(int x) {
    // int pin;

    // for (pin=13; pin>=6; pin--) {
    //     digitalWrite(pin, x&1);
    //     x >>= 1;
    // }

    // reverse!

    int y = reverse(x);

    int d = B11000000;
    int b = B00111111;

    PORTD = (y << 6) & b;
    PORTB = (y >> 2) & d;

}

int reverse(int b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}



void loop() {

}

