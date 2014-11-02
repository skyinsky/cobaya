/*OJ PIR Motion Sensor
 www.openjumper.com
 */
int Sensor = 4;
void setup() {
  Serial.begin(9600);
  pinMode(Sensor, INPUT);
}
void loop() {
  int SensorState = digitalRead(Sensor);
  if (SensorState)
    Serial.println(1);
  else
    Serial.println(0);
  delay(5000);
}


