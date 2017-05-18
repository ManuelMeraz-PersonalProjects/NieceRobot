#include "Robot.h"

Robot::Robot() {
    Servo servoLeft, servoRight;

    ultraSoundLeft = new UltraSound(18, 19, servoLeft, 9);
    ultraSoundRight = new UltraSound(14, 15, servoRight, 10);
    ultraSoundCenter = new UltraSound(17, 16);
    motorLeft = new AF_DCMotor(3);
    motorRight = new AF_DCMotor(2);
    this->obstacle_threshold = 30;
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
    ultraSoundRight->change_direction();
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
    motorLeft->setSpeed(speed);
    motorLeft->run(FORWARD);
}

void Robot::motor_right_forward(int speed) {
    motorRight->setSpeed(speed);
    motorRight->run(FORWARD);
}

void Robot::stop() {
    motorLeft->run(RELEASE);
    motorRight->run(RELEASE);
    delay(500);
    update();
}

void Robot::forwards(int ms, int speed) {
    motor_left_forward(speed);
    motor_right_forward(speed);
    delay(ms);
    update();
}

void Robot::reverse(int ms, int speed) {
    stop();
    motor_left_reverse(speed);
    motor_right_reverse(speed);
    delay(ms);
    update();
}

void Robot::right(int ms, int speed) {
    stop();
    motor_left_forward(speed);
    motor_right_reverse(speed);
    delay(ms);
    update();
}

void Robot::left(int ms, int speed) {
    stop();
    motor_left_reverse(speed);
    motor_right_forward(speed);
    delay(ms);
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
  
  int count[max_dist + 1] = {0};

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
  int distance_right = get_distance(ultraSoundRight);
  int distance_center = get_distance(ultraSoundCenter);
  
  Serial.print("Center: ");
  Serial.println(distance_center);
  Serial.println("");
  
  if (distance_center <= obstacle_threshold && distance_center != -1){
    return 0;
  }

  if (distance_left < obstacle_threshold && distance_right < obstacle_threshold && distance_left != -1 && distance_right != -1) {

    if(distance_left < distance_right) {
      return 1;
    } else {
      return 2;
    }
    
  }
  
  if (distance_left < obstacle_threshold && distance_left != -1) {
    return 1;
  }

  if (distance_right < obstacle_threshold && distance_right != -1) {
    return 2;
  }

  return -1;
}

void Robot::scan() {
    this->ultraSoundLeft->scan();
    this->ultraSoundRight->scan();
}

void Robot::reset() {
    this->ultraSoundLeft->reset();
    this->ultraSoundRight->reset();
}
