#include <AccelStepper.h>
#include <Servo.h>

Servo G;

#define J1_STEP_PIN    22
#define J1_DIR_PIN     2
#define J1_ENABLE_PIN  23

#define J2_STEP_PIN    24
#define J2_DIR_PIN     3
#define J2_ENABLE_PIN  25

#define J3_STEP_PIN    26
#define J3_DIR_PIN     4
#define J3_ENABLE_PIN  27

#define J4_STEP_PIN    28
#define J4_DIR_PIN     5
#define J4_ENABLE_PIN  29

#define J5_STEP_PIN    30
#define J5_DIR_PIN     6
#define J5_ENABLE_PIN  31

#define J6_STEP_PIN    32
#define J6_DIR_PIN     7
#define J6_ENABLE_PIN  33

AccelStepper stepperJ1(AccelStepper::DRIVER, J1_STEP_PIN, J1_DIR_PIN);
AccelStepper stepperJ2(AccelStepper::DRIVER, J2_STEP_PIN, J2_DIR_PIN);
AccelStepper stepperJ3(AccelStepper::DRIVER, J3_STEP_PIN, J3_DIR_PIN);
AccelStepper stepperJ4(AccelStepper::DRIVER, J4_STEP_PIN, J4_DIR_PIN);
AccelStepper stepperJ5(AccelStepper::DRIVER, J5_STEP_PIN, J5_DIR_PIN);
AccelStepper stepperJ6(AccelStepper::DRIVER, J6_STEP_PIN, J6_DIR_PIN);

void setup() {

  G.attach(8);
  G.write(0);

  stepperJ1.setMaxSpeed(5000);
  stepperJ1.setAcceleration(1000);

  stepperJ2.setMaxSpeed(2000);
  stepperJ2.setAcceleration(500);
  
  stepperJ3.setMaxSpeed(10000);
  stepperJ3.setAcceleration(1000);

  stepperJ4.setMaxSpeed(4000);
  stepperJ4.setAcceleration(500);

  stepperJ5.setMaxSpeed(1000);
  stepperJ5.setAcceleration(300);

  stepperJ6.setMaxSpeed(300);
  stepperJ6.setAcceleration(50);

 
  pinMode(J1_ENABLE_PIN, OUTPUT);
  digitalWrite(J1_ENABLE_PIN, HIGH);

  pinMode(J2_ENABLE_PIN, OUTPUT);
  digitalWrite(J2_ENABLE_PIN, HIGH);

  pinMode(J3_ENABLE_PIN, OUTPUT);
  digitalWrite(J3_ENABLE_PIN, HIGH);
  
  pinMode(J4_ENABLE_PIN, OUTPUT);
  digitalWrite(J4_ENABLE_PIN, HIGH);

  pinMode(J5_ENABLE_PIN, OUTPUT);
  digitalWrite(J5_ENABLE_PIN, HIGH);

  pinMode(J6_ENABLE_PIN, OUTPUT);
  digitalWrite(J6_ENABLE_PIN, HIGH);
  
  //1. pont
  stepperJ1.moveTo(7500);
  stepperJ2.moveTo(3800);
  stepperJ3.moveTo(10750);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(2400);
  stepperJ6.moveTo(-1575);

  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }
  //felvétel
  delay(1000);
  G.write(95);
  delay(1000);
}

void loop() {
  delay(1000);
  //köztes pont
  stepperJ1.moveTo(3750);
  stepperJ2.moveTo(2500);
  stepperJ3.moveTo(8000);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(2400);
  stepperJ6.moveTo(-1575);

  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }
  delay(1000);

  //2. pont
  stepperJ1.moveTo(0);
  stepperJ2.moveTo(3800);
  stepperJ3.moveTo(10750);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(2400);
  stepperJ6.moveTo(-1575);

  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }

  //felvétel+lerakás
  delay(1000);
  G.write(0);
  delay(2000);
  G.write(95);
  delay(1000);

  //köztes pont
  stepperJ1.moveTo(3750);
  stepperJ2.moveTo(2500);
  stepperJ3.moveTo(8000);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(2400);
  stepperJ6.moveTo(-1575);

  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }
  delay(1000);

  //1. pont
  stepperJ1.moveTo(7500);
  stepperJ2.moveTo(3800);
  stepperJ3.moveTo(10750);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(2400);
  stepperJ6.moveTo(-1575);

  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }
  //felvétel+lerakás
  delay(1000);
  G.write(0);
  delay(2000);
  G.write(95);
  delay(1000);
}
