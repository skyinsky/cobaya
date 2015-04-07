int Sensor= 2;
void setup() {
   Serial.begin(9600);
   pinMode(Sensor, INPUT);
}
void loop() {
   int SensorState = digitalRead(Sensor);
   Serial.println(SensorState);
   delay(100);
}
