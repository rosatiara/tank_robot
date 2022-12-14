// motor kiri (oren)
const int motorDirPinL = 5; // done
const int motorPWMPinL = 6; // done
const int enablePinL = 7;
const int encoderPinAL = 2; // channel A & B motor kiri
const int encoderPinBL = 3;
const int powerPinL = A0;

// motor kanan (kuning)
const int motorDirPinR = 9; //
const int motorPWMPinR = 10; //
const int enablePinR = 8; //
const int encoderPinAR = 12;
const int encoderPinBR = 13;
const int powerPinR = A1;

int encoderPos = 0;

const float ratio = 360./188.611/48.;

float Kp = 30;
float targetDeg = 360;

void setup() {
  Serial.begin(1200);

  pinMode(powerPinL, OUTPUT);
  digitalWrite(powerPinL, HIGH);
  pinMode(powerPinR, OUTPUT);
  digitalWrite(powerPinR, HIGH);
  
  pinMode(encoderPinAL, INPUT_PULLUP);
  attachInterrupt(0, doEncoderAL, CHANGE);
  pinMode(encoderPinBL, INPUT_PULLUP);
  attachInterrupt(1, doEncoderBL, CHANGE);
  
  pinMode(encoderPinAR, INPUT_PULLUP);
  attachInterrupt(0, doEncoderAR, CHANGE);
  pinMode(encoderPinBR, INPUT_PULLUP);
  attachInterrupt(1, doEncoderBR, CHANGE);
  
  pinMode(motorDirPinL, OUTPUT);
  pinMode(motorDirPinR, OUTPUT);

}

void loop() {
  float motorDeg = float(encoderPos)*ratio;
  float error = targetDeg - motorDeg;
  float control = Kp*error;
  
  doMotor((control>=0)?HIGH:LOW, min(abs(control), 255));
  
  Serial.print("encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("   motorDeg : ");
  Serial.print(float(encoderPos)*ratio);
  Serial.print("   error : ");
  Serial.print(error);
  Serial.print("    control : ");
  Serial.print(control);
  Serial.print("    motorVel : ");
  Serial.println(min(abs(control), 255)); 
}

void doEncoderAL() {  
  encoderPos += (digitalRead(encoderPinAL)==digitalRead(encoderPinBL))?1:-1;
}
void doEncoderBL() {  
  encoderPos += (digitalRead(encoderPinAL)==digitalRead(encoderPinBL))?-1:1;
}

void doEncoderAR() {
  encoderPos += (digitalRead(encoderPinAR)==digitalRead(encoderPinBR))?1:-1;
}
void doEncoderBR(){
  encoderPos += (digitalRead(encoderPinAR)==digitalRead(encoderPinBR))?-1:1;
}

void doMotor(bool dir, int vel) {
  digitalWrite(motorDirPinL, dir);
  analogWrite(motorPWMPinL, dir?(255 - vel):vel);
  
  digitalWrite(motorDirPinR, dir);
  analogWrite(motorPWMPinR, dir?(255 - vel):vel);
}
