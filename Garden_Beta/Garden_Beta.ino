// Damian Steiger - Summer Garden - 18/5/2020

void tempFunction();

void screenControl(int, int, int);

const int sensor = A5; // Assigning analog pin A5 to variable 'sensor'

float tempc; //variable to store temperature in degree Celsius

float vout; //temporary variable to hold sensor reading

// Pin 2-8 is connected to the 7 segments of the display.

int pinA = 2;

int pinB = 3;

int pinC = 4;

int pinD = 5;

int pinE = 6;

int pinF = 7;

int pinG = 8;

int D1 = 9;

int D2 = 10;

int D3 = 11;

int D4 = 12;

int DOT = 13;

int count = 15000; // start the count to update on reset

String tempString;

void setup() {

  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);

  pinMode(pinB, OUTPUT);

  pinMode(pinC, OUTPUT);

  pinMode(pinD, OUTPUT);

  pinMode(pinE, OUTPUT);

  pinMode(pinF, OUTPUT);

  pinMode(pinG, OUTPUT);

  pinMode(D1, OUTPUT);

  pinMode(D2, OUTPUT);

  pinMode(D3, OUTPUT);

  pinMode(D4, OUTPUT);

  pinMode(DOT, OUTPUT);

  pinMode(sensor, INPUT); // Configuring sensor pin as input

  Serial.begin(9600);

}

void loop() {

  //update temp once a minute
  if (count == 15000) {
    tempFunction();
    count = 0;
  }
  
  //convert float to string, send it to the screen output function
  tempString = String(tempc);
  screenControl(tempString[0], tempString[1], tempString[3]);

  count++;

}

void tempFunction() {
  vout = analogRead(sensor); //Reading the value from sensor

  vout = (vout * 500) / 1023;

  tempc = vout; // Storing value in Degree Celsius


  Serial.print("Temp = ");

  Serial.print(tempc);

  Serial.print("°C");

  Serial.print("\t");

  Serial.print("Water = Good");

  Serial.println();

}

void screenControl(char DEKA, char UNIT, char DECI) {

  //D1 - D4 are opposite (High is low and low is high)
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  if (DEKA == '0') {
    screen0();
  } else if (DEKA == '1') {
    screen1();
  } else if (DEKA == '2') {
    screen2();
  } else if (DEKA == '3') {
    screen3();
  } else if (DEKA == '4') {
    screen4();
  } else if (DEKA == '5') {
    screen5();
  } else if (DEKA == '6') {
    screen6();
  } else if (DEKA == '7') {
    screen7();
  } else if (DEKA == '8') {
    screen8();
  } else if (DEKA == '9') {
    screen9();
  }
  delay(1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(DOT, HIGH);
  if (UNIT == '0') {
    screen0();
  } else if (UNIT == '1') {
    screen1();
  } else if (UNIT == '2') {
    screen2();
  } else if (UNIT == '3') {
    screen3();
  } else if (UNIT == '4') {
    screen4();
  } else if (UNIT == '5') {
    screen5();
  } else if (UNIT == '6') {
    screen6();
  } else if (UNIT == '7') {
    screen7();
  } else if (UNIT == '8') {
    screen8();
  } else if (UNIT == '9') {
    screen9();
  }
  delay(1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(DOT, LOW);
 if (DECI == '0') {
    screen0();
  } else if (DECI == '1') {
    screen1();
  } else if (DECI == '2') {
    screen2();
  } else if (DECI == '3') {
    screen3();
  } else if (DECI == '4') {
    screen4();
  } else if (DECI == '5') {
    screen5();
  } else if (DECI == '6') {
    screen6();
  } else if (DECI == '7') {
    screen7();
  } else if (DECI == '8') {
    screen8();
  } else if (DECI == '9') {
    screen9();
  }
  delay(1);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  screenC();
  delay(1);

}

void screen0() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);

}

void screen1() {

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);

}

void screen2() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);

}

void screen3() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);

}

void screen4() {

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);

}

void screen5() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);

}

void screen6() {

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);

}

void screen7() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);

}

void screen8() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);

}

void screen9() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);

}

void screenC() {

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);

}

void screenDotON() {

  digitalWrite(DOT, HIGH);

}

void screenDotOFF() {

  digitalWrite(DOT, LOW);

}
