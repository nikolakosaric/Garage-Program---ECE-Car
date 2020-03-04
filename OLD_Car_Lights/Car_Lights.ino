 // Buttons
#define lights_in 2
#define left_turn_signal_in 4
#define brake_in 7
#define right_turn_signal_in 8

// LEDs
#define left_turn_signal 10
#define right_turn_signal 11
#define front_left 3
#define front_right 5
#define rear_left 6
#define rear_right 12

unsigned long debounce = 200;
// currentMillis;
const long interval = 500;

// LIGHT CONTROL
/// button debouncing for change state
bool lights = false;
int previous_lights = LOW;
unsigned long time_lights = 0;

// LEFT TURN SIGNAL CONTROL
bool left_turn = false;
// button debouncing for change state
int previous_left = LOW;
unsigned long time_left = 0;
// delay w/out delay
unsigned long previousMillis = 0;
int leftState = LOW;

// RIGHT TURN SIGNAL CONTROL
bool right_turn = false;
// button debouncing for change state
int previous_right = LOW;
unsigned long time_right = 0;
// delay w/out delay
int rightState = LOW;

void setup() {
  pinMode(lights_in, INPUT);
  pinMode(left_turn_signal_in, INPUT);
  pinMode(brake_in, INPUT);
  pinMode(right_turn_signal_in, INPUT);
  pinMode(left_turn_signal, OUTPUT);
  pinMode(right_turn_signal, OUTPUT);
  pinMode(front_left, OUTPUT);
  pinMode(front_right, OUTPUT);
  pinMode(rear_left, OUTPUT);
  pinMode(rear_right, OUTPUT);
}

void loop() {
  if (digitalRead(brake_in)) {
    brakes_on();
  } else {
    brakes_off();
  }

  if (digitalRead(lights_in) && previous_lights == LOW && millis() - time_lights > debounce) {
    if (lights) {
      lights = false;
    } else {
      lights = true;
    }
    time_lights = millis();
  }

  if (digitalRead(left_turn_signal_in) && previous_left == LOW && millis() - time_left > debounce) {
    if (left_turn) {
      left_turn = false;
    } else {
      left_turn = true;
    }
    time_left = millis();
  }

  if (digitalRead(right_turn_signal_in) && previous_right == LOW && millis() - time_right > debounce) {
    if (right_turn) {
      right_turn = false;
    } else {
      right_turn = true;
    }
    time_right = millis();
  }
  
  if (lights) {
    lights_on();
  } else if (!lights) {
    lights_off();
  }

  if (left_turn) {
    left_turn_on();
  } else {
    digitalWrite(left_turn_signal, LOW);
  }

  if (right_turn) {
    right_turn_on();
  } else {
    digitalWrite(right_turn_signal, LOW);
  }
}

void lights_on(){
  analogWrite(front_left, 64);
  analogWrite(front_right, 64);
  analogWrite(rear_left, 128);
  analogWrite(rear_right, 128);
}
void lights_off(){
  analogWrite(front_left, 0);
  analogWrite(front_right, 0);
  analogWrite(rear_left, 0);
  analogWrite(rear_right, 0);
}

void brakes_on() {
  digitalWrite(rear_left, HIGH);
  digitalWrite(rear_right, HIGH);
}

void brakes_off() {
  digitalWrite(rear_left, LOW);
  digitalWrite(rear_right, LOW);
}

void left_turn_on() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (leftState == LOW) {
      leftState = HIGH;
    } else {
      leftState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(left_turn_signal, leftState);
  }
}

void right_turn_on() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (rightState == LOW) {
      rightState = HIGH;
    } else {
      rightState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(right_turn_signal, rightState);
  }
}
