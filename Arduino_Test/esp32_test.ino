byte sbus_pin = 11;
byte tx_pin = 10;
byte rx_pin = 12;

int incomingByte;
String inputString;
boolean newLineReceived;

void setup() {
  Serial.begin(250000);
  pinMode(sbus_pin, OUTPUT);
  pinMode(tx_pin, OUTPUT);
  pinMode(rx_pin, INPUT);
  digitalWrite(sbus_pin, LOW);
  digitalWrite(tx_pin, HIGH);
}

void loop() {
  if (newLineReceived) {
    int data = inputString.toInt();
    inputString = "";
    newLineReceived = false;
    digitalWrite(sbus_pin, data / 10);
    digitalWrite(tx_pin, data % 10);
  }
  bool sbus_signal = digitalRead(sbus_pin);
  bool tx_signal = digitalRead(tx_pin);
  bool rx_signal = digitalRead(rx_pin);
  char str[100];
  Serial.println(
    "Sbus = " + bool2str(sbus_signal) + ", " +
    "Tx = " + bool2str(tx_signal) + ", " +
    "Rx = " + bool2str(rx_signal)
  );
  delay(1000);
}

void serialEvent() {
  while (Serial.available()) {
    incomingByte = Serial.read();
    inputString += (char) incomingByte;
    if (incomingByte == '\n') newLineReceived = true;
  }
}

String bool2str(bool b) {
  if (b)
    return "High";
  else
    return "Low";
}
