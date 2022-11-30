const int motorDirPin = 5; // input 1, input 2
const int motorPWMPin = 6; // input 3, input 4

const int LED = 13;

const int encoderPinA = 2; // channel A kedua motor
const int encoderPinB = 3; // channel B kedua motor

int encoderPos = 0;

const float ratio = 360./188.611/48.;

float Kp = 30;
float targetDeg = 360;

void doEncoder() {
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderPos += 1;
  }
  else {
    encoderPos -= 1;
  }
}


void doMotor(bool dir, int vel) {
  digitalWrite(motorDirPin, dir);
  digitalWrite(LED, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoder, CHANGE);
  
  
  pinMode(LED, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
}

void loop() {
  float motorDeg = float(encoderPos)*ratio;
  
  float error = targetDeg - motorDeg;
  float control = Kp*error;

  doMotor((control>=0)?HIGH:LOW, min(abs(control), 255)); 
  
  // if control >= 0, doMotor()
  //	dir = min(abs(control)))
  //	vel = 255
  
  // debug encoder pin
  Serial.print("encoderPinA: ");
  Serial.print(digitalRead(encoderPinA));
  Serial.print("	encoderPinB: ");
  Serial.print(digitalRead(encoderPinB));
  //
  
  Serial.print("	encoderPos : ");
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
