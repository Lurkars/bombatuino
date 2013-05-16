#define encoder0PinA  2
#define encoder0PinB  4

#define encoder1PinA  3
#define encoder1PinB  5

void setup() {  
  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor
  pinMode(encoder1PinA, INPUT); 
  digitalWrite(encoder1PinA, HIGH);       // turn on pullup resistor
  pinMode(encoder1PinB, INPUT); 
  digitalWrite(encoder1PinB, HIGH);       // turn on pullup resistor
  
  attachInterrupt(0, doEncoder0, CHANGE);
  attachInterrupt(1, doEncoder1, CHANGE);
  
  Serial.begin(9600);
}

void doEncoder0() {
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    rotary_encoder_jogwheel_right_inc();
  } else {
    rotary_encoder_jogwheel_right_dec();
  }
}

void doEncoder1() {
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   *
   * For more information on speeding up this process, see
   * [Reference/PortManipulation], specifically the PIND register.
   */
  if (digitalRead(encoder1PinA) == digitalRead(encoder1PinB)) {
    rotary_encoder_jogwheel_left_inc();
  } else {
    rotary_encoder_jogwheel_left_dec();
  }
}


void loop() {
  delay(1000);
  Serial.println("sleep");
}

//left jogwheel
void rotary_encoder_jogwheel_left_inc() {
    Serial.println("jogwheel_left_inc");
}

void rotary_encoder_jogwheel_left_dec() {
    Serial.println("jogwheel_left_dec");
}

//right jogwheel
void rotary_encoder_jogwheel_right_inc() {
    Serial.println("jogwheel_right_inc");
}

void rotary_encoder_jogwheel_right_dec() {
    Serial.println("jogwheel_right_dec");
}
