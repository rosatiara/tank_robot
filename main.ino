boolean normal = true;
int dist = 0;

// motor pins
const int motorDirPinL = 5;
const int motorPWMPinL = 6; 
const int enablePinL = 7;
const int channelPinAL = 2; 
const int channelPinBL = 3;
const int powerPinL = A0;
const int motorDirPinR = 9;
const int motorPWMPinR = 10;
const int enablePinR = 8; 
const int channelPinAR = 12;
const int channelPinBR = 13;
const int powerPinR = A1;

// motor properties
int encoderPos = 0;
const float ratio = 360./188.611/48.;
float Kp = 30;
float targetDeg = 360;

// sensor pins
const int trigPin[12] = {28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};
const int echoPin[12] = {29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};

// sensor properties
int a, b, c;
long duration[5] = {0, 0, 0, 0, 0};
int distance[5] =  {0, 0, 0, 0, 0};
int sum[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int result[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

  for (b = 0; b < 12; b++) {
    pinMode(trigPin[b], OUTPUT);
    pinMode(echoPin[b], INPUT);
  }
  a = 0;
  b = 0;
  c = 0;
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


  // checkABC();
  while (normal) {
    doMotor((control>=0)?HIGH:LOW, min(abs(control), 255)); 
  }
    // if (front sensor detected)
    // normal = !normal;
    doMotor((control>=0)?LOW:HIGH, min(abs(control), 255)); 
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

void checkABC(){
  if (a < 5) {
    digitalWrite(trigPin[c], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[c], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[c], LOW);
    duration[a] = pulseIn(echoPin[c], HIGH);
    distance[a] = duration[a] * 0.034 / 2;
    sum[c] += distance[a];
    a++;
  }

  if (a == 5) {
    result[c] = sum[c] / 5;
    if (result[c] > 300) {
      Serial.print("NaN");
      Serial.print("\t");
    }
    else {
      Serial.print(result[c]);
      Serial.print("\t");
    }
    sum[c] = 0;
    a = 0;
    c++;
  }

  if (c == 12) {
    c = 0;
    Serial.println();
  }
}
