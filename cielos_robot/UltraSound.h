#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Servo.h>
#include <Arduino.h>

class UltraSound {
    public:

        UltraSound(int trigPin, int echoPin);
        UltraSound(int trigPin, int echoPin, Servo servo, int servoPin, int MIN_ANGLE, int MAX_ANGLE);
        ~UltraSound();

        void scan();
        void reset();
        void setup();
        void change_direction();
        void update_distances();
        int* get_distances();
        int get_angle();
        int set_angle(int new_angle);

        int trigPin;
        int echoPin;
        int distance;
        long duration;

    private:

        int *distances;
        int index;

        // Servo
        Servo servo;
        int servoPin;
        int angle;
        int MIN_ANGLE;
        int MAX_ANGLE;
        bool direction;
};

#endif
