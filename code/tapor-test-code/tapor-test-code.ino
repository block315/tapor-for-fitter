int MainSensorPin = A0;   // Linear potentimeter
int CalibrateSensorPin = A1; // Knob
int ledPin = LED_BUILTIN;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
float correct_dist = 100;
int tolerance = 100;
int main_sensor_top = 1023;
int main_sensor_bot = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  calibrate_main_sensor();
}

void calibrate_main_sensor() {
  Serial.println("Move linear sensor to top and press something.");
  while(!Serial.available());
  main_sensor_top = analogRead(MainSensorPin);
  Serial.println("Move linear sensor to bottom and press something.");
  while(!Serial.available());
  main_sensor_bot = analogRead(MainSensorPin);
  if (main_sensor_top > main_sensor_bot){
    Serial.println("Calibration finished");
  }
  
}

void loop() {
  sensorValue = analogRead(MainSensorPin);
  Serial.print("Linear sensor : ");
  Serial.print(sensorValue);
  correct_dist = map(main_sensor_bot, main_sensor_top, 0, 1023, analogRead(CalibrateSensorPin));
  Serial.print(",\t Knob : ");
  Serial.println(correct_dist);
  if (sensorValue > (correct_dist - tolerance) || sensorValue < (correct_dist + tolerance)){
    digitalWrite(ledPin, HIGH); // ok to fitting
  }
  else {
    digitalWrite(ledPin, LOW); // something worng
  }
  delay(1000);
}
