// motor kiri
const int motorDirPin = 5;
const int motorPWMPin = 6;
const int enablePin1 = 7;

// motor kanan 
const int enablePin2 = 8;
const int motorDirPin2 = 9; 
const int motorPWMPin2 = 10;
const int LED = 13;

const int encoderPinA = 2;
const int encoderPinB = 3;

// motor kanan
const int encoderPinA2 = 12;
const int encoderPinB2 = 13;
int encoderPos = 0;

const float ratio = 360./188.611/48.;

float Kp = 30;
float targetDeg = 360;

void doEncoderA() {  
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;
}
void doEncoderB() {  
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;
}

void doEncoderA2() {
  encoderPos += (digitalRead(encoderPinA2)==digitalRead(encoderPinB2))?1:-1;
}

void doEncoderB2(){
  encoderPos += (digitalRead(encoderPinA2)==digitalRead(encoderPinB2))?-1:1;
}

void doMotor(bool dir, int vel) {
  digitalWrite(motorDirPin, dir);
  digitalWrite(LED, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
  
  digitalWrite(motorDirPin2, dir);
  digitalWrite(LED, dir);
  analogWrite(motorPWMPin2, dir?(255 - vel):vel);
}

void setup() {
  Serial.begin(1200);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
  
  pinMode(encoderPinA2, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA2, CHANGE);
  
  pinMode(encoderPinB2, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB2, CHANGE);
  
  pinMode(LED, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
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
