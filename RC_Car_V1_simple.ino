// RC Car V1 - drugi - prosty 4x PWM bez 16-bit - L298N 78M05
const int pwmForward = 9;
const int pwmBackward = 6;
const int steerLeft = 11;
const int steerRight = 10;

const int rcPins[2] = {2, 3};
volatile uint16_t rcValue[2] = {1500, 1500};
volatile uint32_t lastRise[2] = {0, 0};

void rcISR0() {
  if (digitalRead(rcPins[0]) == HIGH) lastRise[0] = micros();
  else rcValue[0] = micros() - lastRise[0];
}
void rcISR1() {
  if (digitalRead(rcPins[1]) == HIGH) lastRise[1] = micros();
  else rcValue[1] = micros() - lastRise[1];
}

void setup() {
  Serial.begin(9600);
  pinMode(pwmForward, OUTPUT);
  pinMode(pwmBackward, OUTPUT);
  pinMode(steerLeft, OUTPUT);
  pinMode(steerRight, OUTPUT);
  for (int i=0;i<2;i++) pinMode(rcPins[i], INPUT);
  attachInterrupt(digitalPinToInterrupt(rcPins[0]), rcISR0, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rcPins[1]), rcISR1, CHANGE);
}

void loop() {
  int motorPWM = 0;
  int steerPWM = 0;
  bool rcActive = (rcValue[0] > 900 && rcValue[0] < 2100);
  if (rcActive) {
    if (rcValue[0] > 1550) motorPWM = map(rcValue[0], 1550, 2000, 0, 255);
    else if (rcValue[0] < 1450) motorPWM = -map(rcValue[0], 1450, 1000, 0, 255);
    if (rcValue[1] > 1550) steerPWM = map(rcValue[1], 1550, 2000, 0, 255);
    else if (rcValue[1] < 1450) steerPWM = -map(rcValue[1], 1450, 1000, 0, 255);
  }
  if (motorPWM > 0) {
    analogWrite(pwmForward, motorPWM);
    analogWrite(pwmBackward, 0);
  } else if (motorPWM < 0) {
    analogWrite(pwmForward, 0);
    analogWrite(pwmBackward, -motorPWM);
  } else {
    analogWrite(pwmForward, 0);
    analogWrite(pwmBackward, 0);
  }
  if (steerPWM > 0) {
    analogWrite(steerRight, steerPWM);
    analogWrite(steerLeft, 0);
  } else if (steerPWM < 0) {
    analogWrite(steerRight, 0);
    analogWrite(steerLeft, -steerPWM);
  } else {
    analogWrite(steerRight, 0);
    analogWrite(steerLeft, 0);
  }
}