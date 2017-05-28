#include <AFMotor.h>
#include <Servo.h> 
#include "Robot.h"

#define NONE -1
#define CENTER 0
#define LEFT 1
#define RIGHT 2


// How fast the robot goes
const int SPEED = 150;

// The distance at which obstacles get detected
const int OBSTACLE_DISTANCE = 27;

Robot robot(SPEED, OBSTACLE_DISTANCE);


/* AVAILABLE COMMANDS
 *  
 *  These will make the robot move for the given time
 *  robot.forwards(time); 
 *  robot.reverse(time);
 *  robot.right(time)
 *  robot.left(time);
 *  
 *  robot.scan(); This will make the robot scan with both scanners and move them by 5 degrees
 *  robot.scan_left(); This will move only the left scanner by 5 degrees
 *  robot.scan_right(); This will move only the right scanner by 5 degrees
 *  
 * robot.reset(); This will set the scanners back to the default position of 90 degrees
 *  
 *  These will set the angle of the scanners to the position you want
 *  robot.set_left_angle(angle); 
 *  robot.set_right_angle(angle);
 */


void setup() {
    delay(2000);
    robot.setup();
}

void loop() {

    // This will tell you whether the robot sees an obstacle
    int obstacle = robot.obstacle_detected();

    // If an obstacle is detected
    if (obstacle != NONE) {
        robot.reset();
        robot.reverse(300);
    }

    // If the obstacle is on the left side or at the center
    if (obstacle == LEFT || obstacle == CENTER) {
        
        robot.right(400);

    // if the obstacle is on the right
    } else if (obstacle == RIGHT) {

        robot.left(400);
        
    } else {
        robot.scan();
        robot.forwards(50);
    }

}


