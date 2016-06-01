#define DEBUG

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("running...");
  #endif
}

void loop() {

}
