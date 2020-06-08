#define POT_IN 0
#define PWM_MOTOR 2

int val_pot = 0;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM_MOTOR, OUTPUT);
  //val = 255 / 1023;
}

void loop() {
  // put your main code here, to run repeatedly:
  val_pot = analogRead(POT_IN);   //Lee el valor del potenciometro.
  val = map(val_pot, 0, 1023, 0, 255);
  analogWrite(PWM_MOTOR, val); //Escribe el valor analogico del potenciometro como duty cycle del PWM.
}   
