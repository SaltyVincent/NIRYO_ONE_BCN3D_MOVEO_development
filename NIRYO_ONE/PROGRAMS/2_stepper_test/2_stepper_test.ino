//AccelStepper könyvtár
#include <AccelStepper.h> 
// Az adott motorhoz tartozó csatlakozó lábak definíciói
#define X_STEP_PIN         22
#define X_DIR_PIN          2
#define X_ENABLE_PIN       23

// AccelStepper objektum létrehozása a adott motorhoz
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);

void setup() {
  // stepperX maximális sebességének beállítása
  stepperX.setMaxSpeed(500);
  // stepperX gyorsulásának beállítása
  stepperX.setAcceleration(100);

  // X_ENABLE_PIN kimenetként történő inicializálása
  pinMode(X_ENABLE_PIN, OUTPUT);

  // X_ENABLE_PIN kimenet beállítása HIGH értékre
  // (alap esetben is tartó árammal tartja a motort)
  digitalWrite(X_ENABLE_PIN, HIGH);
}

void loop() {
  // Megadja a cél pozícióját a stepperX-nek 10000 lépéssel pozitív irányba
  stepperX.moveTo(10000);

  // Amíg stepperX nem érte el a célpontot, folyamatosan futtatja
  while (stepperX.distanceToGo() != 0)
    stepperX.run();

  // Megadja a kiindulási pozíciót cél pozíciónak
  stepperX.moveTo(0);

  // Amíg stepperX nem érte el a célpontot, folyamatosan futtatja
  while (stepperX.distanceToGo() != 0)
    stepperX.run();
}