const int TOUCH_PIN = A0;  // Your purple wire stays in A0
const int LED_PIN = 3;     // Your red wire pin
const int BUZZER_PIN = 2;  // Your buzzer pin

int currentHour = 12;      
bool rushHourHandled = false; 

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("--- Smart AI Lift Routing System Active ---");
}

void loop() {
  // 1. AUTOMATIC RUSH HOUR (Runs once at start)
  if (currentHour == 12 && !rushHourHandled) {
    Serial.println("AI Prediction: It is 12:00 PM (Lunch Peak Time). Sending empty lift to Cafeteria floor automatically!");
    
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW); 
    delay(1500);                   
    digitalWrite(LED_PIN, LOW);
    
    rushHourHandled = true; 
    Serial.println("System Ready. Waiting for manual passenger touch...");
  }

  // 2. LIVE PASSENGER TOUCH CHECK
  int sensorValue = analogRead(TOUCH_PIN);
  
  // Triggers when the pin gets a solid voltage jump
  if (sensorValue > 800) { 
    Serial.println("Manual passenger request received!");
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    
    while(analogRead(TOUCH_PIN) > 800) {
      delay(10); // Wait until wire is removed to prevent spamming
    }
  }

  delay(50); 
}
