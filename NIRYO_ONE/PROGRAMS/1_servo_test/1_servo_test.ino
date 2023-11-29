#include <Servo.h> //A Servo.h könyvtár

Servo G;   // G szervómotor objektum
Servo J6;  // J6 szervómotor objektum
Servo J5;  // J5 szervómotor objektum

void setup() {
  G.attach(11);   // G szervó csatlakoztatása 11-es lábra
  J6.attach(5);   // J6 szervó csatlakoztatása 5-ös lábra
  J5.attach(4);   // J5 szervó csatlakoztatása 4-es lábra
}

void loop() {
  // G szervó pozíció növelése 20 fokkal
  G.write(G.read() + 20);
  delay(200); //200 miliszekundumos késleltetés

  // J6 szervó pozíció növelése 20 fokkal
  J6.write(J6.read() + 20);
  delay(200);

  // J5 szervó pozíció növelése 20 fokkal
  J5.write(J5.read() + 20);
  delay(200);

  // G szervó pozíció csökkentése 20 fokkal
  G.write(G.read() - 20);
  delay(200);

  // J6 szervó pozíció csökkentése 20 fokkal
  J6.write(J6.read() - 20);
  delay(200);

  // J5 szervó pozíció csökkentése 20 fokkal
  J5.write(J5.read() - 20);
  delay(200);
}