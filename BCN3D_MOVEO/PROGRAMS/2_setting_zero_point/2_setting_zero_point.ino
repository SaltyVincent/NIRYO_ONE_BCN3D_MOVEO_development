// Könyvtárak importálása
#include <AccelStepper.h>
#include <Servo.h>

#define MICROSWITCH_PIN 35

//int MAX_SPEED = (4000);
int MAX_ACC = (5000000);
// szervómotorok definíciói
Servo G;

// léptetőmotorokhoz csatlakozó lábak definíciói
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

// AccelStepper objektumok létrehozása a léptetőmotorokhoz
AccelStepper stepperJ1(AccelStepper::DRIVER, J1_STEP_PIN, J1_DIR_PIN);
AccelStepper stepperJ2(AccelStepper::DRIVER, J2_STEP_PIN, J2_DIR_PIN);
AccelStepper stepperJ3(AccelStepper::DRIVER, J3_STEP_PIN, J3_DIR_PIN);
AccelStepper stepperJ4(AccelStepper::DRIVER, J4_STEP_PIN, J4_DIR_PIN);
AccelStepper stepperJ5(AccelStepper::DRIVER, J5_STEP_PIN, J5_DIR_PIN);
AccelStepper stepperJ6(AccelStepper::DRIVER, J6_STEP_PIN, J6_DIR_PIN);

void setup() {
  pinMode(MICROSWITCH_PIN, INPUT_PULLUP);
// léptetőmotorok max sebességének és gyorsulásának beállítása
  stepperJ1.setMaxSpeed(700);
  stepperJ1.setAcceleration(MAX_ACC);

  stepperJ2.setMaxSpeed(1500);
  stepperJ2.setAcceleration(MAX_ACC);
  
  stepperJ3.setMaxSpeed(1500);
  stepperJ3.setAcceleration(MAX_ACC);

  stepperJ4.setMaxSpeed(1500);
  stepperJ4.setAcceleration(MAX_ACC);

  stepperJ5.setMaxSpeed(1500);
  stepperJ5.setAcceleration(MAX_ACC);

  stepperJ6.setMaxSpeed(1500);
  stepperJ6.setAcceleration(MAX_ACC);


  // szervómotorokhoz csatlakozó lábak definíciói
  G.attach(8);
  G.write(0);

  // léptetőmotorok engedélyezési lábainak inicializálása
  // léptetőmotorok engedélyezési lábainak beállítása LOW értékre

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

  stepperJ6.moveTo(-100000000); // Large move towards the microswitch
  while (stepperJ6.distanceToGo() != 0) {
    stepperJ6.run();
    if (digitalRead(MICROSWITCH_PIN) == HIGH) {
      stepperJ6.stop();
      delay(300); // Add a delay here to allow things to settle
      break;
    }
  }
  stepperJ6.move(300); // Move back 600 steps
  while (stepperJ6.distanceToGo() != 0) {
    stepperJ6.run();
  }
  stepperJ6.setCurrentPosition(0); // Set this as the new 0 position*/
  delay(200);

  stepperJ5.moveTo(100000000); // Large move towards the microswitch
  while (stepperJ5.distanceToGo() != 0) {
    stepperJ5.run();
    if (digitalRead(MICROSWITCH_PIN) == HIGH) {
      stepperJ5.stop();
      delay(300); // Add a delay here to allow things to settle
      break;
    }
  }
  stepperJ5.move(-6500); // Move back 600 steps
  while (stepperJ5.distanceToGo() != 0) {
    stepperJ5.run();
  }
  stepperJ5.setCurrentPosition(0); // Set this as the new 0 position
  delay(200);

  stepperJ4.moveTo(-100000000); // Large move towards the microswitch
  while (stepperJ4.distanceToGo() != 0) {
    stepperJ4.run();
    if (digitalRead(MICROSWITCH_PIN) == HIGH) {
      stepperJ4.stop();
      delay(300); // Add a delay here to allow things to settle
      break;
    }
  }
  stepperJ4.move(10700); // Move back 600 steps
  while (stepperJ4.distanceToGo() != 0) {
    stepperJ4.run();
  }
  stepperJ4.setCurrentPosition(0); // Set this as the new 0 position
  delay(200);

  stepperJ3.moveTo(100000000); // Large move towards the microswitch
  while (stepperJ3.distanceToGo() != 0) {
    stepperJ3.run();
    if (digitalRead(MICROSWITCH_PIN) == HIGH) {
      stepperJ3.stop();
      delay(300); // Add a delay here to allow things to settle
      break;
    }
  }
  stepperJ3.move(-800); // Move back 600 steps
  while (stepperJ3.distanceToGo() != 0) {
    stepperJ3.run();
  }
  delay(200);

  stepperJ2.moveTo(-100000000); // Large move towards the microswitch
  while (stepperJ2.distanceToGo() != 0) {
    stepperJ2.run();
    if (digitalRead(MICROSWITCH_PIN) == HIGH) {
      stepperJ2.stop();
      delay(300); // Add a delay here to allow things to settle
      break;
    }
  }
  stepperJ2.move(8000);
  stepperJ3.move(-8100); // Move back 600 steps
  while (stepperJ2.distanceToGo() != 0 && stepperJ3.distanceToGo() != 0) {
    stepperJ2.run();
    stepperJ3.run();
  }
  stepperJ2.setCurrentPosition(0); // Set this as the new 0 position
  stepperJ3.setCurrentPosition(0);
  delay(200);

  stepperJ1.moveTo(100000000); // Large move towards the microswitch
  while (stepperJ1.distanceToGo() != 0) {
    stepperJ1.run();
    if (digitalRead(MICROSWITCH_PIN) == HIGH) {
      stepperJ1.stop();
      delay(300); // Add a delay here to allow things to settle
      break;
    }
  }
  stepperJ1.move(-7400); // Move back 600 steps
  while (stepperJ1.distanceToGo() != 0) {
    stepperJ1.run();
  }
  stepperJ1.setCurrentPosition(0); // Set this as the new 0 position
  delay(200);
}

void loop() {
  // Mozgatja a léptetőmotorokat adott pozíció felé
  stepperJ1.moveTo(0);
  stepperJ2.moveTo(0);
  stepperJ3.moveTo(0);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(0);
  stepperJ6.moveTo(0);

  // Amíg legalább egy léptetőmotornak van még távolsága hátra folyamatosan futtatja a léptetőmotorokat
  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }
  delay(1000);
  // szervómotorok pozíciójának növelése 20 fokkal
  // Kis várakozás köztük (200 ms)
  G.write(75);
  delay(200);
  

  // Mozgatja a léptetőmotorokat alap pozíció felé
  stepperJ1.moveTo(0);
  stepperJ2.moveTo(0);
  stepperJ3.moveTo(0);
  stepperJ4.moveTo(0);
  stepperJ5.moveTo(0);
  stepperJ6.moveTo(0);

  // Amíg legalább egy léptetőmotornak van még távolsága hátra folyamatosan futtatja a léptetőmotorokat
  while (stepperJ1.distanceToGo() != 0 || stepperJ2.distanceToGo() != 0 || stepperJ3.distanceToGo() != 0 || stepperJ4.distanceToGo() != 0) {
    stepperJ1.run();
    stepperJ2.run();
    stepperJ3.run();
    stepperJ4.run();
    stepperJ5.run();
    stepperJ6.run();
  }
  delay(1000);

  // szervómotorok pozíciójának csökkentése 20 fokkal
  // Kis várakozás köztük (200 ms)
  G.write(0);
  delay(200);
}