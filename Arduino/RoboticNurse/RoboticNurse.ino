



#include <SoftwareSerial.h>


SoftwareSerial BT(0, 1); // TX, RX respectively
String readtext;


const int maxBeds = 4; // Maximum number of beds
int bedSequence[maxBeds]; // Array to store the bed sequence


void forward(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    delay(2000);
  }
}


void stop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(200);
}


void turn_right() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(800);


  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  delay(100);
}


void turn_left() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  delay(800);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  delay(100);
}


void reverse() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(100);
}


void go_come(int n) {
  turn_right();
  forward(1);
  stop();
  reverse();
  turn_right();
  forward(n);
}


void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}


void sortBedSequence() {
  for (int i = 0; i < maxBeds - 1; i++) {
    for (int j = 0; j < maxBeds - i - 1; j++) {
      if (bedSequence[j] > bedSequence[j + 1]) {
        int temp = bedSequence[j];
        bedSequence[j] = bedSequence[j + 1];
        bedSequence[j + 1] = temp;
      }
    }
  }
}


void visitBeds() {
  for (int i = 0; i < maxBeds; i++) {
    int n = bedSequence[i];
    forward(n);
    go_come(n);
  }
}


void loop() {
  while (BT.available()) {
    delay(10);
    char c = BT.read();
    if (c == '#') {
      break;
    }
    readtext += c;
  }


  if (readtext.length() > 0) {
    BT.println(readtext);


    if (readtext.startsWith("bed")) {
      int bedIndex = readtext.charAt(4) - '1';
      if (bedIndex >= 0 && bedIndex < maxBeds) {
        bedSequence[bedIndex] = bedIndex + 1;
      }
    }


    else if (readtext == "*forward#") {
      forward(2);
    }


    else if (readtext == "back") {
      reverse();
    }


    else if (readtext == "left") {
      turn_left();
    }


    else if (readtext == "*right#") {
      turn_right();
    }


    else if (readtext == "*stop#") {
      stop();
    }


    readtext = "";
  }
}






