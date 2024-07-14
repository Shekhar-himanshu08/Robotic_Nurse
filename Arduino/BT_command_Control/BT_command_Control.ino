#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1);  //TX, RX respetively
String readtext;

void forward(int n) {
  // for (int i = 0; i < n; i++) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    delay(2000);
  // }
}

void stop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(2000);
}

void turn_left() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(1500);

  // digitalWrite(3, HIGH);
  // digitalWrite(4, LOW);
  // digitalWrite(5, HIGH);
  // digitalWrite(6, LOW);
  // delay(100);
}

void turn_right() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  delay(1500);
  // digitalWrite(3, HIGH);
  // digitalWrite(4, LOW);
  // digitalWrite(5, HIGH);
  // digitalWrite(6, LOW);
  // delay(100);
}
void reverse() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(2000);
}

void go_come(int n) {
  turn_right();
  forward(1);
  stop();
  reverse();
  // forward(1);
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

void loop() {
  while (BT.available()) {  //Check if there is an available byte to read
    delay(10);              //Delay added to make thing stable
    char c = BT.read();     //Conduct a serial read
    if (c == '#') { break; }
    readtext += c;  //build the string- "forward", "reverse", "left" and "right"
  }

  if (readtext.length() > 0) {

    BT.println(readtext);

    int n = 0;
    if (readtext == "bed one") {
      n = 1;
      forward(n);
      go_come(n);
    } else if (readtext == "bed two") {
      n = 2;
      forward(n);
      go_come(n);
    } else if (readtext == "*bed three#") {
      n = 3;
      forward(n);
      go_come(n);
    } else if (readtext == "*bed four") {
      n = 4;
      forward(n);
      go_come(n);
    }

    
    forward(1);
    forward(1);
    turn_right();
    forward(1);
     stop();    
     
    reverse();
    turn_right();
    forward(1);
    forward(1);
    stop();

    // // forward(n);

    if (readtext == "*forward#") {
      forward(n);
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

    // else if (readtext == "keep watch in all directions")
    // {
    //    digitalWrite (3, HIGH);
    //    digitalWrite (4, LOW);
    //    digitalWrite (5, LOW);
    //    digitalWrite (6, LOW);
    //    delay (100);
    // }

    readtext = "";
  }
}  //Reset the variable