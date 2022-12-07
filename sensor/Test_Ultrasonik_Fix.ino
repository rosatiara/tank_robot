const int trigPin[12] = {28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};
const int echoPin[12] = {29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};
int a, b, c;

long duration[5] = {0, 0, 0, 0, 0};
int distance[5] =  {0, 0, 0, 0, 0};
int sum[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int result[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  for (b = 0; b < 12; b++) {
    pinMode(trigPin[b], OUTPUT);
    pinMode(echoPin[b], INPUT);
  }
  a = 0;
  b = 0;
  c = 0;
  Serial.begin(115200);
}

void loop() {
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
