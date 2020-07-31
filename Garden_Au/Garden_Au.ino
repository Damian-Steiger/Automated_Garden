/* Damian Steiger - Summer Garden Gold V - 31/05/2020
 * This is the final version of the Automated Garden 
 * Watering and monitoring system.
 */

 #include <math.h>

//Pin Declaration
  //relay
  const int relay_pin = 1;
  
  //screen
  const int pinA = 2;
  const int pinB = 3;
  const int pinC = 4;
  const int pinD = 5;
  const int pinE = 6;
  const int pinF = 7;
  const int pinG = 8;
  const int D1 = 9;
  const int D2 = 10;
  const int D3 = 11;
  const int D4 = 12;
  const int DOT = 13;
  
  //thermometer
  const int thermometer_pin = A5;   //thermometer pin

//Variables
  String temperatureString;         //string version of temperature for easy screen output
  float vout;                       //store temperature in degree celcius
  float tempc;                      //temporary variable for sensor readings
  int count;                        //holds the program counter
  const int HighDelay = 77650;      //delay for high pressure watering cycle
  const int MedDelay = 85400;       //delay for medium pressure watering cycle
  const int LowDelay = 191800;      //delay for low pressure watering cycle
  float temperatureArray[100] = {}; //array to hold daily temperature data

//Functions
  void setup();                                 //setup
  void loop();                                  //main loop
  void counter();                               //program counter, schedules events
  void tempUpdate();                            //updates temperature, prints to serial monitor
  void screenOutput(char, char, char);          //sepcifies screen output
  boolean relayCtrl();                          //controls the watering cycle
  boolean waterCheck();                         //determines if 2nd watering is necessary
  float integration();                          //find area under temperature curve  
  float calcMax();                              //find max value in a array
  float calcMin();                              //find min value in a array    
  void screen0();                               //screen 0 - 9 and C are functions to set the screen...            
  void screen1();                               //... to those outputs, preventing code repetition
  void screen2();
  void screen3();
  void screen4();
  void screen5();
  void screen6();
  void screen7();
  void screen8();
  void screen9();
  void screenC();

void setup() {
  
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
  pinMode(thermometer_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  delay(1);
  
  counter();

}

void counter(){

  count++;
  //if count is multiple of 864000, aka every 14.4 mins, then update temp
  if(count % 864000 == 0){
      tempUpdate();      
    }
    
  //if count equals 39600000 or 0, the watering times, then start watering cycle
  if(count == 39600000 | count == 0){
      if(relayCtrl()){
          count += LowDelay;
        }
    } 
    
  //resets counter at te begining of new day cycle
  if(count >= 86400000){
      count = 0;
    }
    
}

boolean relayCtrl(){

  //water at begining of day cycle
  if(count == 0){
      digitalWrite(relay_pin, HIGH);
      delay(LowDelay);
      digitalWrite(relay_pin, LOW);
      return true;
    }
    
  //water if 2nd watering time and its necessary
  if(count == 39600000 & waterCheck()){
      digitalWrite(relay_pin, HIGH);
      delay(LowDelay);
      digitalWrite(relay_pin, LOW);
      return true;
    }
    
  return false;
  
}

boolean waterCheck(){

  if(integration() > 500) return true; //500 may not be a good number, review later

  return false;
    
}

float integration(){

  float arr [5000]; //5000 elements for higher integration resolution  
  float SUM;
  double max = calcMax();
  double min = calcMin();
  for(int j=0; j < 2500; j++){
      arr[j] = max / (1 + exp(-((max - min)/50) * (j - 25)));
    }
  for(int j=2501; j < 5000; j++){
      arr[j] = max / (1 + exp(-((min - max)/50) * (j - 75)));
    }
  for(int i=0; i < sizeof(arr); i++){
     SUM += arr[i];
    }
  return SUM;

}

float calcMax(){

  double max = temperatureArray[0];
  for(int i=1; i < sizeof(temperatureArray); i++){
    if(temperatureArray[i] > max) {
        max = temperatureArray[i];
    }
  }
  return max;
    
} 

float calcMin(){
  
  double min = temperatureArray[0];
  for(int i=1; i < sizeof(temperatureArray); i++){
    if(temperatureArray[i] < min) {
        min = temperatureArray[i];
    }
  }
  return min;

} 

void tempUpdate(){

  vout = analogRead(thermometer_pin); //Reading the value from sensor
  vout = (vout * 500) / 1023;
  tempc = vout; // Storing value in Degree Celsius
  temperatureString = String(tempc);
  screenOutput(temperatureString[0], temperatureString[1], temperatureString[3]);
  
  Serial.print("Temp = ");
  Serial.print(tempc);
  Serial.print("°C");
  Serial.println();

  //add temperature measurement to array
  for(int i=0; i < sizeof(temperatureArray); i++){
    if(temperatureArray[i] == 0) {
        temperatureArray[i] = tempc;
        break;
    }
  }
}

void screenOutput(char DEKA, char UNIT, char DECI) {

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
