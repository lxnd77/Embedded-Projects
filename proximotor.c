int LED = 13; // Onboard LED pin
int proximityPin = 7;  // This is our input pin (IR LED at pin 7)
int sensorOut = HIGH;  // HIGH at No Obstacle

long interval = 10000;
long lastMilli = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(proximityPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();
  sensorOut = digitalRead(irPin);

  if (sensorOut == LOW){

    Serial.println("Switching Motor on for 10 more seconds");
    startEngine();
    lastMilli = currentMillis;
  }

  if (currentMillis >= lastMilli + interval){
    Serial.println("Stopping Motor");
    stopEngine();
  }

  delay(1000);
}

void startEngine(){
  digitalWrite(LED, HIGH);
}

void stopEngine(){
  digitalWrite(LED, LOW);
}