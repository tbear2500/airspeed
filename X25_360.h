#define NUM_STEPS 1080
#define NUM_STATES 6
#define NUM_PINS 4
class X25_360 {
    int pin[4];
    int state_map[6][4] = {
      {1,0,0,1},
      {1,0,0,0},
      {1,1,1,0},
      {0,1,1,0},
      {0,1,1,1},
      {0,0,0,1}
    };
    int current_pos, target_pos;
    int current_state;
    unsigned long int last_update_micros;
    int min_update_delay_micros;
    bool clockwise;
    void write();
public:
    X25_360 (int pin1, int pin2, int pin3, int pin4);
    void update();
    void set_position(int);
    void set_position(int, bool);
    void set_min_update_delay_micros(int);
};

