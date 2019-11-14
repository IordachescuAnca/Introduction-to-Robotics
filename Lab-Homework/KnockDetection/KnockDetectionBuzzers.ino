const int passiveBuzzerPin = A0;
const int activeBuzzerPin = 10;
const int pushButton = 2;

int buttonState = 0;
int lastButtonState = 0;

const int knockDetectorLimit = 5;
int knockValue = 0;

const int interval = 5000;
unsigned long startMusicTime = 0;

int isMusicOn = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(passiveBuzzerPin, INPUT);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(isMusicOn){
    playMusic();
    IsButtonPushed();
  }
  else{
    waitTillKnock();
  }
}

void waitTillKnock(){
  knockValue = analogRead(passiveBuzzerPin);
  if (knockValue >= knockDetectorLimit){
    isMusicOn = 1;
    startMusicTime = millis();
    //Serial.println("Knock!");
  }
}

void playMusic(){
  if (millis() - startMusicTime >= interval){
    tone(activeBuzzerPin, knockValue);
  }
}

void IsButtonPushed(){
  buttonState = digitalRead(pushButton);
  if (buttonState == 0 && lastButtonState == 1){
    isMusicOn = 0;
    noTone(activeBuzzerPin);
  }
  lastButtonState = buttonState;
}
