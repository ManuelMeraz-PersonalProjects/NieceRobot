#include <AFMotor.h>
#include <Servo.h> 
#include "Robot.h"

#define CENTER 0
#define LEFT 1
#define RIGHT 2

Robot robot;

const int SLOW = 100;
const int NORMAL = 130;
const int FAST = 200;


void setup() {
    //Start up serial connection
    Serial.begin(115200); // baud rate
    Serial.flush();

    delay(2000);
    robot.setup();
}

void loop() {

    int obstacle = robot.obstacle_detected();

    if(obstacle != -1) {
        robot.reset();
    }

    if (obstacle == CENTER) {

        robot.reverse(500, NORMAL);
        robot.left(300, NORMAL);

    } else if (obstacle == LEFT) {
        robot.reverse(200, NORMAL);
        robot.right(600, NORMAL);

    } else if (obstacle == RIGHT) {
        robot.reverse(200, NORMAL);
        robot.left(300, NORMAL);

    } else {
        robot.scan();
        robot.forwards(100, NORMAL);

    }

}


