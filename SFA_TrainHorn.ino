/* Simple code to take signal from PIR Sensor
    and subsequently activate a 5V relay, to then
    trigger a 12V automotive grade relay

    Eventually should be upgraded to utilize a
    logic level 3.3V MOSFET to drive the automotive
    relay directly, but this will work fine.
*/


// Assign output pin number to a variable - any digital pin will do!
const int relay = D8;

// Set the initial timer to ZERO
unsigned long lastRun = 0;

// Set the minimum delay between effect triggers in milliseconds
const long minDelay = 10000;
const long maxDelay = 600000;
const long runTime = 1250;

void setup() {
  Serial.begin(9600);
  // Set the pin connected to the sensor as an INPUT
  //pinMode(motionPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(D2, INPUT);
  // Set the output HIGH, the light activates when it is LOW
  digitalWrite(relay, LOW);

}

void loop() {
  //Serial.println("MAIN LOOP");
  unsigned long currentMillis = millis();
  //Serial.println(currentMillis - lastRun);
  //unsigned long motion = analogRead(A1);
  //Serial.println(motion);
  //Serial.println(digitalRead(2));
  if (currentMillis - lastRun > minDelay) {
    if (digitalRead(D2) == HIGH) {
      lastRun = currentMillis;
      Serial.println("TRIG by PIN");
      
      while (currentMillis - lastRun < runTime) {
        digitalWrite(relay, HIGH);
        currentMillis = millis();
        Serial.println("looping");
      }
      digitalWrite(relay, LOW);
      lastRun = millis();
      exit;
    }
    else if (currentMillis - lastRun > maxDelay) {
      lastRun = currentMillis;
      Serial.println("TRIG by TIMEOUT");
      digitalWrite(relay, HIGH);
      while (currentMillis - lastRun < runTime) {
        currentMillis = millis();
      }
      digitalWrite(relay, LOW);
      lastRun = millis();
      exit;
    }
  }
  /*
    if (analogRead(motionPin) >= 600) {
    digitalWrite(13, HIGH);
    digitalWrite(relayPin, LOW);
    delay(random(1250));
    digitalWrite(13, LOW);
    digitalWrite(relayPin, HIGH);
    delay(minDelay);
    }
  */
}
