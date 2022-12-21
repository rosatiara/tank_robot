boolean normal = true; // normal = true;
int testVal = 1;
const int motorDirPinL = 5; // done
const int motorPWMPinL = 6; // done
const int enablePinL = 7;
const int channelPinAL = 2; // channel A & B motor kiri
const int channelPinBL = 3;
const int powerPinL = A0;

const int motorDirPinR = 9;//done
const int motorPWMPinR = 10;//done
const int enablePinR = 8; 
const int channelPinAR = 12;
const int channelPinBR = 13;
const int powerPinR = A1;

int encoderPos = 0;

const float ratio = 360./188.611/48.;

float Kp = 30;
float targetDeg = 360;

void setup() {
  Serial.begin(115200);

  pinMode(powerPinL, OUTPUT);
  digitalWrite(powerPinL, HIGH);
  pinMode(powerPinR, OUTPUT);
  digitalWrite(powerPinR, HIGH);
  
  pinMode(channelPinAL, INPUT_PULLUP);
  attachInterrupt(0, doEncoderAL, CHANGE);
  pinMode(channelPinBL, INPUT_PULLUP);
  attachInterrupt(1, doEncoderBL, CHANGE);
  
  pinMode(channelPinAR, INPUT_PULLUP);
  attachInterrupt(0, doEncoderAR, CHANGE);
  pinMode(channelPinBR, INPUT_PULLUP);
  attachInterrupt(1, doEncoderBR, CHANGE);
  
  pinMode(motorDirPinL, OUTPUT);

  pinMode(motorDirPinR, OUTPUT);
  digitalWrite(enablePinL, HIGH);
  digitalWrite(enablePinR, HIGH);
}

void loop() {
  float motorDeg = float(encoderPos)*ratio;
  float error = targetDeg - motorDeg;
  float control = Kp*error;
  
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
  
  while (normal) {
    doMotor((control>=0)?HIGH:LOW, min(abs(control), 255)); 
    if (testVal == 1) // check if front sensor is detected
    normal = !normal;
    doMotor((control>=0)?LOW:HIGH, min(abs(control), 255)); 
    }
}

void doEncoderAL() {  
  encoderPos += (digitalRead(channelPinAL)==digitalRead(channelPinBL))?1:-1;
}
void doEncoderBL() {  
  encoderPos += (digitalRead(channelPinAL)==digitalRead(channelPinBL))?-1:1;
}

void doEncoderAR() {
  encoderPos += (digitalRead(channelPinAR)==digitalRead(channelPinBR))?1:-1;
}
void doEncoderBR(){
  encoderPos += (digitalRead(channelPinAR)==digitalRead(channelPinBR))?-1:1;
}

void doMotor(bool dir, int vel) {
  digitalWrite(motorDirPinL, dir);
  analogWrite(motorPWMPinL, dir?(255 - vel):vel);
  digitalWrite(motorDirPinR, dir);
  analogWrite(motorPWMPinR, dir?(255 - vel):vel);
}
