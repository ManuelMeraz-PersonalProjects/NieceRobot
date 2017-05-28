#include "Robot.h"

Robot::Robot(int SPEED, int OBSTACLE_DISTANCE) {
    Servo servoLeft, servoRight;

    ultraSoundLeft = new UltraSound(18, 19, servoLeft, 10, 55, 165);
    ultraSoundRight = new UltraSound(14, 15, servoRight, 9, 15, 125);
    ultraSoundCenter = new UltraSound(17, 16);
    motorLeft = new AF_DCMotor(3);
    motorRight = new AF_DCMotor(2);
    this->OBSTACLE_DISTANCE = 15;
    this->SPEED = SPEED;
}

Robot::~Robot() {
    delete ultraSoundLeft;
    delete ultraSoundRight;
    delete ultraSoundCenter;
    delete motorLeft;
    delete motorRight;
}

void Robot::setup() {
    ultraSoundLeft->setup();
    ultraSoundRight->setup();
    ultraSoundLeft->change_direction();
    ultraSoundCenter->setup();

    for(int i = 0; i < 3; i++) {
        update();
    }
}

void Robot::motor_left_reverse(int speed) {
    motorLeft->setSpeed(speed);
    motorLeft->run(BACKWARD);
}

void Robot::motor_right_reverse(int speed) {
    motorRight->setSpeed(speed);
    motorRight->run(BACKWARD);
}

void Robot::motor_left_forward(int speed) {
    motorLeft->setSpeed(SPEED);
    motorLeft->run(FORWARD);
}

void Robot::motor_right_forward(int speed) {
    motorRight->setSpeed(speed);
    motorRight->run(FORWARD);
}

void Robot::stop() {
    motorLeft->run(RELEASE);
    motorRight->run(RELEASE);
    delay(250);
}

void Robot::forwards(int ms) {
    motor_left_forward(SPEED);
    motor_right_forward(SPEED);
    delay(ms);
    update();
}

void Robot::reverse(int ms) {
    stop();
    motor_left_reverse(SPEED);
    motor_right_reverse(SPEED);
    delay(ms);
    update();
}

void Robot::right(int ms) {
    stop();
    motor_left_forward(SPEED);
    motor_right_reverse(SPEED);
    delay(ms);
    stop();
    update();
}

void Robot::left(int ms) {
    stop();
    motor_left_reverse(SPEED);
    motor_right_forward(SPEED);
    delay(ms);
    stop();
    update();
}

void Robot::update() {
    ultraSoundLeft->update_distances();
    ultraSoundRight->update_distances();
    ultraSoundCenter->update_distances();
}

int Robot::get_distance(UltraSound *ultraSound) {
    return repeat(ultraSound->get_distances(), 3);
}

int Robot::repeat(int *numbers, int length) {
  int max_dist = 0;

  for(int i = 0; i < length; i++) {
    if (numbers[i] > max_dist) {
      max_dist = numbers[i];
    }
  }
  
  int count[max_dist + 1];
  memset (count, 0, max_dist*sizeof(int));

  for(int i = 0; i < length; i++) {
        Serial.print(numbers[i]);
    Serial.print(" ");
    count[numbers[i]]++;
  }
    Serial.println(" ");  


  int most_repeated_value = 0;
  int most_repeated_count = 0;

  for(int i = 0; i < max_dist + 1; i++) {
    Serial.print(count[i]);
    Serial.print(" ");
    if (count[i] > most_repeated_count) {
      most_repeated_value = i;
      most_repeated_count = count[i];
    }
  }
  Serial.println(" ");  

  if (most_repeated_count > 1) {
    return most_repeated_value;
  }

  return -1;
}

int Robot::obstacle_detected() {
  update();
  
  int distance_left = get_distance(ultraSoundLeft);
  int angle_left = ultraSoundLeft->get_angle();

  int distance_right = get_distance(ultraSoundRight);
  int angle_right = ultraSoundRight->get_angle();

  int distance_center = get_distance(ultraSoundCenter);
  
  if (distance_center <= 0.75 * OBSTACLE_DISTANCE && distance_center != -1){
    return 0;
  }

  if (distance_left < OBSTACLE_DISTANCE && distance_right < OBSTACLE_DISTANCE && distance_left != -1 && distance_right != -1) {

      if(distance_left < distance_right) {
          return check_angle(ultraSoundLeft);
      } else {
          return check_angle(ultraSoundRight);
      }

  }
  
  if (distance_left < OBSTACLE_DISTANCE && distance_left != -1) {
    return check_angle(ultraSoundLeft);
  }

  if (distance_right < OBSTACLE_DISTANCE && distance_right != -1) {
    return check_angle(ultraSoundLeft);
  }

  return -1;
}

void Robot::scan() {
    this->ultraSoundLeft->scan();
    this->ultraSoundRight->scan();
}

void Robot::scan_left() {
      this->ultraSoundLeft->scan();
}

void Robot::scan_right() {
  this->ultraSoundRight->scan();
}

void Robot::reset() {
    this->ultraSoundLeft->reset();
    this->ultraSoundRight->reset();
}

int Robot::check_angle(UltraSound *ultraSound) {
    if(ultraSound->get_angle()  > 90) {
        return 1;
    }

    return 2;
}

void Robot::set_left_angle(int new_angle) {
  ultraSoundLeft->set_angle(new_angle);
}

void Robot::set_right_angle(int new_angle) {
    ultraSoundRight->set_angle(new_angle);
}

