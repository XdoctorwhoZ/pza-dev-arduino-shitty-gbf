const int analogOutPin = 9; // Broche de sortie PWM
int dutyCycle = 50; // Valeur initiale du duty cycle en pourcentage
int signal_duration_ms = 50;
unsigned long signal_enable = 0;

void setup() {
  Serial.begin(9600); // Initialiser la communication série

  analogWrite(analogOutPin, 127);
  delay(1000);
  analogWrite(analogOutPin, 0);
  // Serial.println("ready!");
}

void loop() {
  
  
  //
  //
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "PWM:DUTY?") {
      Serial.println(dutyCycle);
    } else if (command.startsWith("PWM:DUTY")) {
      int newDutyCycle = command.substring(9).toInt();
      if (newDutyCycle >= 0 && newDutyCycle <= 100) {
        dutyCycle = newDutyCycle;
      }
    } 

    else if (command.startsWith("SIG:DUR?")) {
      Serial.println(signal_duration_ms);
    } else if (command.startsWith("SIG:DUR")) {
      int newDuration = command.substring(8).toInt();
      if (newDuration >= 0 && newDuration <= 1000) {
        signal_duration_ms = newDuration;
      }
    }

    else if (command.startsWith("SIG:TRIG")) {
      signal_enable = millis();
      int pwmValue = map(dutyCycle, 0, 100, 0, 255); // Convertir le pourcentage en valeur PWM
      analogWrite(analogOutPin, pwmValue); // Écrire la valeur du duty cycle sur la broche PWM
    }
  }

  //
  //
  if (signal_enable > 0) {
    if ( (millis() - signal_enable) >= signal_duration_ms )
    {
      analogWrite(analogOutPin, 0);
      signal_enable = 0;
    }
  }

}
