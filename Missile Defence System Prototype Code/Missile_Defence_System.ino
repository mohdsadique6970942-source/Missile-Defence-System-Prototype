#include <Servo.h>

// --- PINS ---
const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 2;
const int ledPin = 3;
const int launcherPin = 9;  // SG90
const int radarPin = 10;    // MG996R (360 Degree)

Servo launcherServo;
Servo radarServo;

// --- SPEED SETTINGS (SLOW KAR DIYA HAI) ---
// 90 = STOP. 
// Right jane ke liye: 80 (Pehle 70 tha, ab slow hai)
// Left jane ke liye: 100 (Pehle 110 tha, ab slow hai)
const int speedRight = 82;  
const int speedLeft = 98; 
const int stopMotor = 90; // Agar motor rukne par bhi vibrate kare to isko 89 ya 91 try karna

// --- TIMING TUNING (ISSE POSITION FIX HOGI) ---
// Isko change karke tum drift theek karoge
const long timeGoingRight = 2000; // 2000ms tak Right jayega
const long timeGoingLeft = 2150;  // 2150ms tak Left aayega (Thoda zyada time diya hai wapas aane ke liye)

// --- VARIABLES ---
unsigned long lastRadarSwitchTime = 0;
bool scanningRight = true;
bool targetDetected = false;
long duration;
int distance;
const int detectionDistance = 30;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  launcherServo.attach(launcherPin);
  launcherServo.write(90); // Ready

  radarServo.attach(radarPin);
  radarServo.write(stopMotor);
  
  Serial.println("System Ready. Adjust Timings in code if needed.");
  delay(1000);
  lastRadarSwitchTime = millis();
}

void loop() {
  moveRadar();
  distance = getDistance();
  
  // Debugging: Serial monitor pe dekho distance
  Serial.println(distance);

  if (distance > 0 && distance < detectionDistance) {
    if (!targetDetected) {
      targetDetected = true;
      fireSequence();
    }
  } else {
    targetDetected = false;
  }
  
  delay(30);
}

void moveRadar() {
  if (targetDetected) return;

  unsigned long currentTime = millis();
  unsigned long timePassed = currentTime - lastRadarSwitchTime;

  // Logic: Agar Right ja raha hai, to Right wala time check karo
  // Agar Left ja raha hai, to Left wala time check karo
  if (scanningRight) {
    if (timePassed >= timeGoingRight) {
      scanningRight = false; // Ab Left ghumo
      lastRadarSwitchTime = currentTime;
    } else {
      radarServo.write(speedRight);
    }
  } else {
    if (timePassed >= timeGoingLeft) {
      scanningRight = true; // Ab Right ghumo
      lastRadarSwitchTime = currentTime;
    } else {
      radarServo.write(speedLeft);
    }
  }
}

void fireSequence() {
  Serial.println("FIRING!");
  radarServo.write(stopMotor); // Radar Roko
  radarServo.detach(); // Power cut karo radar ki
  
  // Alarm
  for(int i=0; i<2; i++){
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    delay(200);
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(200);
  }
  
  // Fire
  for (int pos = 90; pos >= 0; pos--) { 
    launcherServo.write(pos);
    delay(6); 
  }
  delay(500);
  for (int pos = 0; pos <= 90; pos++) { 
    launcherServo.write(pos);
    delay(6);
  }
  
  // Resume
  radarServo.attach(radarPin);
  lastRadarSwitchTime = millis(); 
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}