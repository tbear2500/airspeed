#define _360

#ifdef _360
#include "X25_360.h"
#else
#include "SwitecX25.h"
#endif

#ifdef _360
X25_360 airspeed(2,3,4,5);
#else
#define NUM_STEPS 945
SwitecX25 airspeed(NUM_STEPS, 2, 3, 4, 5);
#endif
int prev_pos, pos;
int pos_inc;

void setup() {
#ifdef _360
    airspeed.set_min_update_delay_micros(700);
#endif
    Serial.begin(9600);
    Serial.println("Go!");
    
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

    prev_pos = 1;
    pos = 0;
    pos_inc = 200;
}

void loop(void) {
    prev_pos = pos;
    if (Serial.available()) {
        pos = Serial.parseInt();
    }
    if (prev_pos != pos) {
        Serial.println(pos);
    }
#ifdef _360
    airspeed.set_position(pos);
#else
    airspeed.setPosition(pos);
#endif
    airspeed.update();
    //pos += pos_inc;
    if (pos >= NUM_STEPS || pos <= 0) {
        pos_inc *= -1;
    }
    delay(0);
}
