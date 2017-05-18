#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Servo.h>
#include <Arduino.h>

class UltraSound {
    public:

        UltraSound(int trigPin, int echoPin);
        UltraSound(int trigPin, int echoPin, Servo servo, int servoPin);
        ~UltraSound();

        void scan();
        void reset();
        void setup();
        void change_direction();
        void update_distances();
        int* get_distances();

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
        bool direction;
};

#endif
