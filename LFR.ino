const int pingPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor

int LDR1, LDR2, LDR3;
int MLF = 3, MLB = 5 ,MRF = 6 , MRB = 10;
int leftHigh = analogRead(2),leftLow = analogRead(2),rightHigh = analogRead(4),rightLow = analogRead(4),centreHigh = analogRead(3),centreLow = analogRead(3);
int leftAverage,rightAverage,centreAverage;

void calibrate() {
  
    for (int x = 0; x < 100; x++) {
      LDR1 = analogRead(2);
      LDR2 = analogRead(3);
      LDR3 = analogRead(4);
      if (LDR1 < leftLow) {
        leftLow = LDR1;
      } else if (LDR1 > leftHigh) {
        leftHigh = LDR1;
      }
      if (LDR2 < centreLow) {
        centreLow = LDR2;
      } else if (LDR2 > centreHigh) {
        centreHigh = LDR2;
      }
      if (LDR3 < rightLow) {
        rightLow = LDR3;
      } else if (LDR3 > rightHigh) {
        rightHigh = LDR3;
      }
      delay(50);
    }
    leftAverage = (leftHigh - leftLow)/2;
    rightAverage = (rightHigh - rightLow)/2;
    centreAverage = (centreHigh - centreLow)/2;
  }
void setup() {
  // put your setup code here, to run once:
  pinMode(MLF, OUTPUT);
  pinMode(MLB, OUTPUT);
  pinMode(MRB, OUTPUT);
  pinMode(MRF, OUTPUT);
  Serial.begin(9600);
  calibrate();
  delay(2000);
  analogWrite(MLF,190);
  analogWrite(MRF,190);
  analogWrite(MLB,0);
  analogWrite(MRB,0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  LDR1 = analogRead(2);
  LDR2 = analogRead(3);
  LDR3 = analogRead(4);
  int LDR1Value = 0; // 0 means white
  int LDR2Value = 0;
  int LDR3Value = 0;
  if (LDR1 > leftAverage) {
    LDR1Value = 1;//means black
  } else {
    LDR1Value = 0;
  }
  if (LDR2 > centreAverage) {
    LDR2Value = 1;//means black
  } else {
    LDR2Value = 0;
  }
  if (LDR3 > rightAverage) {
    LDR3Value = 1;//means black
  } else {
    LDR3Value = 0;
  } 
  if (ULsensorReadingInCM() < 13) {
    stop();
  }
  move(LDR1Value,LDR2Value,LDR3Value); 
  Serial.print(LDR1Value);
  Serial.print(" ");
  Serial.print(leftAverage);
  Serial.print(" ");
  Serial.print(LDR2Value);
  Serial.print(" ");
  Serial.println(LDR3Value);
}
//////////////////////////////////////////
long ULsensorReadingInCM() {
  long duration, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
   return (cm);
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
/////////////////////UL sensor code

void move (int a, int b, int c) {
  if (a == 0 && b ==0 && c ==0 ) { // all white
      //do nothing let the previous move function continue
  }
  if (a == 0 && b ==0 && c ==1 ) {
    moveRight();
  }
  if (a == 0 && b == 1&& c == 0) {
    moveForward();
  }
  if (a == 0 && b ==1 && c == 1) {
    hardRight();
  }
  if (a == 1 && b == 0&& c == 0) {
    moveLeft();   
  }
  if (a == 1 && b == 0&& c == 1) {
    moveLeft();
  }
  if (a == 1 && b == 1&& c == 0) {
    hardLeft();
  }
  if (a == 1 && b == 1&& c == 1) { //all black
      moveForward();

  }
}
void moveLeft() {
analogWrite(MLF,190);
analogWrite(MRF,200);
Serial.println("Turning Left");
}
void moveRight() {
analogWrite(MLF,200);
analogWrite(MRF,190);
Serial.println("Turning right");
}
void moveForward() {
analogWrite(MLF,190);
analogWrite(MRF,190);
Serial.println("Forward");
}
void hardLeft(){
analogWrite(MLF,190);
analogWrite(MRF,0);
Serial.println("hard Left");
}
void hardRight(){
analogWrite(MLF,0);
analogWrite(MRF,190);
Serial.println("Hard Right");
}
void stop() {
analogWrite(MLF,0);
analogWrite(MRF,0);  
Serial.println("Stop!");
}


