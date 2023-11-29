// könyvtárak
#include <AccelStepper.h>
#include <Servo.h>

Servo G; // G szervo objektum
Servo J6; // J6 szervo objektum
Servo J5; // J5 szervo objektum

Servo servos[] = { J6, J5, G }; // szervo objektumok tömbje

#define J1_STEP_PIN     54  // J1 lépés tű
#define J1_DIR_PIN      55  // J1 irány tű
#define J1_ENABLE_PIN   38  // J1 engedélyezés tű

#define J2_STEP_PIN     60  // J2 lépés tű
#define J2_DIR_PIN      61  // J2 irány tű
#define J2_ENABLE_PIN   56  // J2 engedélyezés tű

#define J3_STEP_PIN     26  // J3 lépés tű
#define J3_DIR_PIN      28  // J3 irány tű
#define J3_ENABLE_PIN   24  // J3 engedélyezés tű

#define J4_STEP_PIN     36  // J4 lépés tű
#define J4_DIR_PIN      34  // J4 irány tű
#define J4_ENABLE_PIN   30  // J4 engedélyezés tű

#define JOYSTICK_VRX_PIN A5   // analóg joystick X-tengely
#define JOYSTICK_VRY_PIN A10  // analóg joystick Y-tengely

#define JOYSTICK_THRESHOLD 50       // küszöbérték jostick-hoz
#define INCREMENT_THRESHOLD 1000    // inkrementálás küszöbértéke jostick-hoz
#define DECREMENT_THRESHOLD 20      // dekrementálás küszöbértéke jostick-hoz
unsigned long previousMillis = 0;   // előző időpont milliszekundumban jostick-hoz
const unsigned long interval = 500; // időköz milliszekundumban jostick-hoz
int previousY = 0;                  // előző jostick Y érték mentéséhez

int active = 0;  // aktív motor változó

#define STEP_MODE 1           // lépésmód
const float MAX_SPEED = 2000; // maximális sebesség
#define ACCELERATION 700      // gyorsulás
const int STEPS_PER_REV = 50; // lépések száma fordulatonként

AccelStepper stepperJ1(AccelStepper::DRIVER, J1_STEP_PIN, J1_DIR_PIN);  // J1 léptetőmotor
AccelStepper stepperJ2(AccelStepper::DRIVER, J2_STEP_PIN, J2_DIR_PIN);  // J2 léptetőmotor
AccelStepper stepperJ3(AccelStepper::DRIVER, J3_STEP_PIN, J3_DIR_PIN);  // J3 léptetőmotor
AccelStepper stepperJ4(AccelStepper::DRIVER, J4_STEP_PIN, J4_DIR_PIN);  // J4 léptetőmotor

AccelStepper* steppers[] = { &stepperJ1, &stepperJ2, &stepperJ3, &stepperJ4 }; // léptetőmotorok tömbje

bool moveToHome = false;  // HOME pozícióba mozgatás változó alapjáraton hamis értékkel

void setup() {

  for (int i = 0; i < 4; i++) {
    steppers[i]->setMaxSpeed(MAX_SPEED);        // léptetőmotorok maximális sebességének beállítása
    steppers[i]->setAcceleration(ACCELERATION); // léptetőmotorok gyorsulásának beállítása
  }

  J5.attach(5); // J5 szervo csatlakoztatása 5 pinre
  J6.attach(4); // J6 szervo csatlakoztatása 4 pinre
  G.attach(11); // G szervo csatlakoztatása 11 pinre

  // léptetőmotorok engedélyezési tű kimenetének beállítása
  // léptetőmotorok engedélyezési tű kimenetének alacsonyra állítása
  pinMode(J1_ENABLE_PIN, OUTPUT);
  digitalWrite(J1_ENABLE_PIN, LOW);
  pinMode(J2_ENABLE_PIN, OUTPUT);
  digitalWrite(J2_ENABLE_PIN, LOW);
  pinMode(J3_ENABLE_PIN, OUTPUT);
  digitalWrite(J3_ENABLE_PIN, LOW);
  pinMode(J4_ENABLE_PIN, OUTPUT);
  digitalWrite(J4_ENABLE_PIN, LOW);

  pinMode(JOYSTICK_VRX_PIN, INPUT);   // analóg joystick X-tengely bemenet beállítása
  pinMode(JOYSTICK_VRY_PIN, INPUT);   // analóg joystick Y-tengely bemenet beállítása

  pinMode(9, OUTPUT);         // 9-es pin kimenet beállítása (ventilátor)
  pinMode(44, INPUT_PULLUP);  // 44-es pin pull-up bemenet beállítása (joystick gomb)

  Serial.begin(9600);   // soros kommunikáció indítása 9600 baud sebességgel

  moveMotorsToHomePosition(); // motorok otthoni pozícióba mozgatása
}
void loop() {

  digitalWrite(9, HIGH);  // 9-es tű kimenetének magasra állítása (ventilátor)

  int x = analogRead(JOYSTICK_VRX_PIN); // joystick X-tengely analóg beolvasása
  int y = analogRead(JOYSTICK_VRY_PIN); // joystick Y-tengely analóg beolvasása

  Serial.print("Active: "); // "Active: " üzenet kiírása soros kommunikációra
  Serial.println(active);   // aktív érték kiírása soros kommunikációra

  //aktív változó értékét állítja a joystick értékei alapján
  if (y < DECREMENT_THRESHOLD && previousY >= DECREMENT_THRESHOLD && millis() - previousMillis >= interval) {
    if (active < 6) {  
      active++;
    } else {
      active = 0;
    }
    previousMillis = millis();
  }

  if (y > INCREMENT_THRESHOLD && previousY <= INCREMENT_THRESHOLD && millis() - previousMillis >= interval) {
    if (active > 0) {
      active--;
    } else {
      active = 6;
    }
    previousMillis = millis();
  }
  previousY = y;

  //reakció az SW gomb lenyomására moveToHome változót igazzá teszi
  if (digitalRead(44) == LOW) {
    moveToHome = true;
  }

  //ha moveToHome változó magas hívja a kiindulási pozícióra állásért felelős függvényt
  if (moveToHome) {
    moveMotorsToHomePosition();
    moveToHome = false;
  }

  //aktív változó alapján mozgatja a motorokat
  if (active >= 0 && active < 4) {
    while (x < (498 - JOYSTICK_THRESHOLD) || x > (498 + JOYSTICK_THRESHOLD)) {
      steppers[active]->setSpeed(map(x, 0, 1023, -MAX_SPEED, MAX_SPEED));
      steppers[active]->runSpeed();
      x = analogRead(JOYSTICK_VRX_PIN);
    }
  } else if (active >= 4 && active <= 6) {
    if (x < (498 - JOYSTICK_THRESHOLD) || x > (498 + JOYSTICK_THRESHOLD)) {
      int servoAngle = map(x, 0, 1023, -1, 1);
      servos[active - 4].write(servos[active - 4].read() + servoAngle);
      delay(10);
    }
  } else {
    steppers[active]->stop();
  }
}

//kiindulási pozícióra állásért felelős függvény
void moveMotorsToHomePosition() { 
  for (int i = 0; i < 4; i++) {
    steppers[i]->moveTo(0);
  }
  for (int i = 0; i < 3; i++) {
    servos[i].write(90);
  }
  while (steppers[0]->distanceToGo() != 0 || steppers[1]->distanceToGo() != 0 || steppers[2]->distanceToGo() != 0 || steppers[3]->distanceToGo() != 0) {
    for (int i = 0; i < 4; i++) {
      steppers[i]->run();
    }
  }
}
