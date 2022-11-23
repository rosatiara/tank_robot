// motor kiri
const int motorDirPin = 5;//4//5 
const int motorPWMPin =6 ;//12 //6

// motor kanan 
const int motorDirPin2 = 9;//4//5 
const int motorPWMPin2 =10 ;//12 //6
//const int EnablePin1 = 9;//8//9
//const int EnablePin2 = 7;
const int LED = 13;

const int encoderPinA = 2;//10///2 //Channel A motor kiri
const int encoderPinB = 3;//11//3  //Channel B motor kiri

// motor kanan
const int encoderPinA2 = 12;//10///2 //Channel A motor kanan
const int encoderPinB2 = 13;//11//3 //  Channel B motor kanan
int encoderPos = 0;

const float ratio = 360./188.611/48.;

float Kp = 30;
float targetDeg = 360;

void doEncoderA()
{  
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;
}
void doEncoderB()
{  
  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;
}

void doMotor(bool dir, int vel)
{
  digitalWrite(motorDirPin, dir);
  digitalWrite(LED, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
  
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
  
  pinMode(LED, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
 // pinMode(EnablePin1, OUTPUT);
 // pinMode(EnablePin2, OUTPUT);
}

void loop()
{
  float motorDeg = float(encoderPos)*ratio;
  
  float error = targetDeg - motorDeg;
  float control = Kp*error;
  
  //digitalWrite(EnablePin1, 255);
  //digitalWrite(EnablePin2, 255);

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
