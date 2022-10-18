void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // delay(1000);
  // digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Hola");
  if (Serial.available() > 0)
  {
    Serial.flush();
    String msg = Serial.readString();
    const char *ptrMsg = msg.c_str();
    Serial.println(ptrMsg);
    if (strncmp("encendido", ptrMsg, 9) == 0)
    {
      Serial.println("Led Encendido!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (strncmp("apagado", ptrMsg, 7) == 0)
    {
      Serial.println("Led Apagado!");
      digitalWrite(LED_BUILTIN, LOW);
    }
  }œ
}
