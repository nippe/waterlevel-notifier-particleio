// This #include statement was automatically added by the Particle IDE.

const char webhook_name[] = "cellar-climate";
int sendSms(String command);
const int DELAY_IN_SECONDS = 10*60; // 10 minutes
bool isMessageSent = false;
int waterThreshold = 2880;
int waterLevelPin = A1;
int waterLevel = 0;

void setup() {

    Particle.variable("waterLevel", waterLevel);
    Particle.function("sendSms", sendSms);

    pinMode(waterLevelPin, INPUT);
    delay(1000);
}

void loop() {
    getWaterLevel();
    checkWaterLevel();
    delay(DELAY_IN_SECONDS * 1000);
}

int getWaterLevel() {
  waterLevel = analogRead(waterLevelPin);
  return waterLevel;
}

int sendSms(String command) {
  if(command.length() > 0){
    Particle.publish("twilio", command, 60, PRIVATE);
  }
  return 0;
}

void checkWaterLevel() {
  int currentLevel = analogRead(waterLevelPin);
  if(currentLevel > waterThreshold) {
    if(!isMessageSent){
      char msg[255];
      snprintf(msg, sizeof(msg), "Dags att tömma vatten i källarn! Nivå: %d", waterLevel);
      sendSms(msg);
      isMessageSent = true;
    }
  }

  if(isMessageSent && (currentLevel < waterThreshold)) {
    isMessageSent = false;
    sendSms("Du har tömt ser jag, lysande polarn!");
  }
}
