#ifndef ROBOT_H
#define ROBOT_H

#include <AFMotor.h>
#include <Servo.h>
#include <Arduino.h>
#include <limits.h>
#include "UltraSound.h"

class Robot {
    public:
        Robot();
        ~Robot();
        void setup();

        void stop();
        void reverse(int ms, int speed);
        void forwards(int ms, int speed);
        void right(int ms, int speed);
        void left(int ms, int speed);
        void scan();
        void reset();

        int obstacle_detected();

    private:
        AF_DCMotor *motorLeft; // M3 on shield
        AF_DCMotor *motorRight; // M4 on shield

        UltraSound *ultraSoundLeft;
        UltraSound *ultraSoundRight;
        UltraSound *ultraSoundCenter;
        
        int obstacle_threshold;

        void update();
        int get_distance(UltraSound *ultraSound);
        int repeat(int *numbers, int length);

        void motor_left_reverse(int speed);
        void motor_left_forward(int speed);
        void motor_right_reverse(int speed);
        void motor_right_forward(int speed);
};

#endif
