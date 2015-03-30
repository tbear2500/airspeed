#include <Arduino.h>
#include "X25_360.h"

X25_360::X25_360(int pin0, int pin1, int pin2, int pin3) {
    pin[0] = pin0; 
    pin[1] = pin1;
    pin[2] = pin2;
    pin[3] = pin3;

    

    current_pos = 0;
    target_pos = 0;
}

void X25_360::write() {
    int out;
    for (int pin_num = 0; pin_num < NUM_PINS; pin_num++) {
        if (state_map[current_state][pin_num]) {
            out = HIGH;
        } else {
            out = LOW;
        }
        digitalWrite(pin[pin_num], out);
    }
}

void X25_360::update() {
    if (micros() >= last_update_micros + min_update_delay_micros && current_pos != target_pos) {
        last_update_micros = micros();
        if (clockwise) {
            current_state = (current_state + 1) % NUM_STATES;
            if (++current_pos == NUM_STEPS) {
                current_pos = 0;
            }
        } else {
            current_state = (current_state + 5) % NUM_STATES;
            if (--current_pos == -1) {
                current_pos = NUM_STEPS - 1;
            }
        }
        write();
    }

}

void X25_360::set_position(int pos) {
    target_pos = pos % NUM_STEPS;
    int diff = current_pos - target_pos;
    if (current_pos > target_pos || (diff < 0 && -diff > NUM_STEPS/2)) {
        clockwise = false;
    } else {
        clockwise = true;
    }
}

void X25_360::set_position(int pos, bool is_clockwise) {
    target_pos = pos % NUM_STEPS;
    clockwise = is_clockwise;
}

void X25_360::set_min_update_delay_micros(int min_delay_micros) {
    min_update_delay_micros = min_delay_micros;
}

