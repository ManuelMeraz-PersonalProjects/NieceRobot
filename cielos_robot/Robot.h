#ifndef ROBOT_H
#define ROBOT_H

#include <AFMotor.h>
#include <Servo.h>
#include <Arduino.h>
#include <limits.h>
#include "UltraSound.h"

class Robot {
    public:
        Robot(int SPEED, int OBSTACLE_DISTANCE);
        ~Robot();
        void setup();

        void stop();
        void reverse(int ms);
        void forwards(int ms);
        void right(int ms);
        void left(int ms);
        void scan();
        void reset();
        void set_left_angle(int new_angle);
        void set_right_angle(int new_angle);
        void scan_left();
        void scan_right();

        int obstacle_detected();

    private:
        AF_DCMotor *motorLeft; // M3 on shield
        AF_DCMotor *motorRight; // M4 on shield

        UltraSound *ultraSoundLeft;
        UltraSound *ultraSoundRight;
        UltraSound *ultraSoundCenter;
        
        int OBSTACLE_DISTANCE;
        int SPEED;

        void update();
        int get_distance(UltraSound *ultraSound);
        int repeat(int *numbers, int length);
        int check_angle(UltraSound *ultraSound);

        void motor_left_reverse(int speed);
        void motor_left_forward(int speed);
        void motor_right_reverse(int speed);
        void motor_right_forward(int speed);
};

#endif
