#include <Servo.h>

Servo leftShoulder;
Servo leftElbow;
Servo rightShoulder;
Servo rightElbow;
Servo faceServo;

// ---------------- PINS ----------------
#define LS_PIN    3
#define LE_PIN    5
#define RS_PIN    6
#define RE_PIN    9
#define FACE_PIN 10

// ---------------- ARM POSITIONS ----------------
int LS = 90;
int LE = 90;
int RS = 90;
int RE = 90;

// Arm speed
// Smaller number = faster
int armSpeed = 3;


// =====================================================
// FACE SETTINGS
// =====================================================

int faceAngle = 0;
int faceDirection = 1;

unsigned long lastFaceMove = 0;

// Smaller = faster face movement
int faceSpeed = 8;


// =====================================================
// SETUP
// =====================================================

void setup()
{
  leftShoulder.attach(LS_PIN);
  leftElbow.attach(LE_PIN);
  rightShoulder.attach(RS_PIN);
  rightElbow.attach(RE_PIN);
  faceServo.attach(FACE_PIN);

  leftShoulder.write(90);
  leftElbow.write(90);
  rightShoulder.write(90);
  rightElbow.write(90);

  faceServo.write(0);

  delay(500);
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
  // ==================================================
  // EFFECT 1
  // ALL 4 TOGETHER
  // ==================================================

  moveArms(65, 65, 65, 65);
  waitFace(100);

  moveArms(115, 115, 115, 115);
  waitFace(100);

  moveArms(65, 65, 65, 65);
  waitFace(100);

  moveArms(115, 115, 115, 115);
  waitFace(150);


  // ==================================================
  // EFFECT 2
  // ELBOWS OPPOSITE
  // ==================================================

  moveArms(90, 60, 90, 120);
  waitFace(100);

  moveArms(90, 120, 90, 60);
  waitFace(100);

  moveArms(90, 60, 90, 120);
  waitFace(100);

  moveArms(90, 120, 90, 60);
  waitFace(150);


  // ==================================================
  // EFFECT 3
  // SHOULDERS OPPOSITE
  // ==================================================

  moveArms(60, 90, 120, 90);
  waitFace(100);

  moveArms(120, 90, 60, 90);
  waitFace(100);

  moveArms(60, 90, 120, 90);
  waitFace(100);

  moveArms(120, 90, 60, 90);
  waitFace(150);


  // ==================================================
  // EFFECT 4
  // CROSS MOVEMENT
  // ==================================================

  moveArms(65, 115, 115, 65);
  waitFace(100);

  moveArms(115, 65, 65, 115);
  waitFace(100);

  moveArms(65, 115, 115, 65);
  waitFace(100);

  moveArms(115, 65, 65, 115);
  waitFace(150);


  // ==================================================
  // EFFECT 5
  // FAST DANCE
  // ==================================================

  moveArms(65, 110, 105, 70);
  waitFace(70);

  moveArms(110, 70, 70, 110);
  waitFace(70);

  moveArms(75, 65, 115, 105);
  waitFace(70);

  moveArms(105, 115, 65, 75);
  waitFace(70);

  moveArms(60, 120, 120, 60);
  waitFace(70);

  moveArms(120, 60, 60, 120);
  waitFace(150);
}


// =====================================================
// CONTINUOUS FACE MOVEMENT
//
// 0° -> 90° -> 0° -> 90° continuously
// =====================================================

void updateFace()
{
  unsigned long currentTime = millis();

  if (currentTime - lastFaceMove >= faceSpeed)
  {
    lastFaceMove = currentTime;

    faceAngle += faceDirection;

    // Reached 90 degrees
    if (faceAngle >= 90)
    {
      faceAngle = 90;
      faceDirection = -1;
    }

    // Reached 0 degrees
    if (faceAngle <= 0)
    {
      faceAngle = 0;
      faceDirection = 1;
    }

    faceServo.write(faceAngle);
  }
}


// =====================================================
// FAST + SMOOTH ARM MOVEMENT
// Face continues moving during this function
// =====================================================

void moveArms(int targetLS,
              int targetLE,
              int targetRS,
              int targetRE)
{
  while (
    LS != targetLS ||
    LE != targetLE ||
    RS != targetRS ||
    RE != targetRE
  )
  {

    if (LS < targetLS) LS++;
    else if (LS > targetLS) LS--;

    if (LE < targetLE) LE++;
    else if (LE > targetLE) LE--;

    if (RS < targetRS) RS++;
    else if (RS > targetRS) RS--;

    if (RE < targetRE) RE++;
    else if (RE > targetRE) RE--;

    leftShoulder.write(LS);
    leftElbow.write(LE);
    rightShoulder.write(RS);
    rightElbow.write(RE);

    // Keep face moving
    updateFace();

    delay(armSpeed);
  }
}


// =====================================================
// REPLACEMENT FOR delay()
//
// Face keeps moving while waiting
// =====================================================

void waitFace(unsigned long waitTime)
{
  unsigned long startTime = millis();

  while (millis() - startTime < waitTime)
  {
    updateFace();
  }
}
