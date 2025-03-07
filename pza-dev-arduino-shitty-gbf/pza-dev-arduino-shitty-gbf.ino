const int analogOutPin = 9; // Broche de sortie PWM
int dutyCycle = 50; // Valeur initiale du duty cycle en pourcentage
int period = 2000; // Période initiale en microsecondes (500 Hz)

void setup() {
  Serial.begin(9600); // Initialiser la communication série
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("PWM:DUTY")) {
      int newDutyCycle = command.substring(9).toInt();
      if (newDutyCycle >= 0 && newDutyCycle <= 100) {
        dutyCycle = newDutyCycle;
      }
    } else if (command == "PWM:DUTY?") {
      Serial.println(dutyCycle);
    } else if (command.startsWith("PWM:PERIOD")) {
      period = command.substring(11).toInt();
    } else if (command == "PWM:PERIOD?") {
      Serial.println(period);
    }
  }

  int pwmValue = map(dutyCycle, 0, 100, 0, 255); // Convertir le pourcentage en valeur PWM
  analogWrite(analogOutPin, pwmValue); // Écrire la valeur du duty cycle sur la broche PWM
  delayMicroseconds(period / 2); // Attendre la moitié de la période
  analogWrite(analogOutPin, 255 - pwmValue); // Inverser le duty cycle
  delayMicroseconds(period / 2); // Attendre l'autre moitié de la période
}
