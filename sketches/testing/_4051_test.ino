int potent = -1;
int tolerance = 4;

const int s0 = 10;
const int s1 = 9;
const int s2 = 8;

int pots[] = {-1,-1};

void setup() {
  Serial.begin(9600);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);  
  
}

void loop() {
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s1, LOW);
  int read =  analogRead(A1);
  if (pots[0] < read - tolerance || pots[0] > read + tolerance) {
    pots[0] = analogRead(A1);
    Serial.print("pot 0: ");
    Serial.print(pots[0]/8);
    Serial.println();
  }  
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s1, LOW);
  read =  analogRead(A1);
  if (pots[1] < read - tolerance || pots[1] > read + tolerance) {
    pots[1] = analogRead(A1);
    Serial.print("pot 1: ");
    Serial.print(pots[1]/8);
    Serial.println();
  }
}
