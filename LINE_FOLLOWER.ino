#include <Arduino_APDS9960.h>

// IRs Sensors
int RightSensor = 7;
int MiddleSensor = 6;
int LeftSensor = 3;
//

//Left Motor
int LEFT_MOTOR = 10;
int FORWARD_L = 4;
int BACKWARD_L = 5;
//

//Right Motor
int RIGHT_MOTOR = 11;
int FORWARD_R = 8;
int BACKWARD_R = 9;

//LEDs
int Green = 13;
int Red = A1;
int Blue = 12;
//


//RETURNED VALUES PROXIMITY SENSOR
int proximity;

//RETURNED VALUES COLOR SENSOR
int r, g, b;
//

//Obstacle Functions 
void stop_F(); // Stop when faces an obstacle 
void continue_F(); // Ride when obstacle is removed
void proximity_F(); // Read the proximity
void color_F(); // Read the color
//


  
void setup()
{
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  // DECLARE ALL PINS
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(RightSensor, INPUT);
  pinMode(MiddleSensor, INPUT);
  pinMode(LeftSensor, INPUT);
  pinMode(FORWARD_R, OUTPUT);
  pinMode(BACKWARD_R, OUTPUT);
  pinMode(FORWARD_L, OUTPUT);
  pinMode(BACKWARD_L, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Blue, OUTPUT);

    digitalWrite(Green,1);
  delay(1000);
  digitalWrite(Green,0);
  digitalWrite(Red,1);
    delay(1000);
  digitalWrite(Red,0);
  digitalWrite(Blue, 1);
    delay(1000);
  digitalWrite(Blue, 0);

analogWrite(LEFT_MOTOR,119);
analogWrite(RIGHT_MOTOR,125);
}
void loop()
{
  proximity_F();
  color_F();
    
  if (digitalRead(RightSensor) == HIGH && digitalRead(MiddleSensor) == HIGH && digitalRead(LeftSensor) == HIGH) //Tsomet
  {
    
    digitalWrite(FORWARD_L, HIGH);
    digitalWrite(BACKWARD_L, LOW);
    digitalWrite(FORWARD_R, HIGH);
    digitalWrite(BACKWARD_R, LOW);
    analogWrite (LEFT_MOTOR, 194);
    analogWrite (RIGHT_MOTOR, 200);

  }
  
  else if (digitalRead(RightSensor) == LOW && digitalRead(MiddleSensor) == LOW && digitalRead(LeftSensor) == LOW) // Interrupted line
  {
    // Don't change
  }
  else if (digitalRead(RightSensor) == LOW && digitalRead(MiddleSensor) == HIGH && digitalRead(LeftSensor) == LOW) //Over the line
  {
    //Move both the Motors
    digitalWrite(FORWARD_L, HIGH);
    digitalWrite(BACKWARD_L, LOW);
    digitalWrite(FORWARD_R, HIGH);
    digitalWrite(BACKWARD_R, LOW);
    analogWrite (LEFT_MOTOR, 194);
    analogWrite (RIGHT_MOTOR,200);

  }

  else if (digitalRead(RightSensor) == LOW && digitalRead(LeftSensor) == HIGH)
  {
    //Tilt robot towards left by stop_Fing the left wheel and moving the right one
    digitalWrite(FORWARD_L, HIGH);
    digitalWrite(BACKWARD_L, LOW);
    digitalWrite(FORWARD_R, LOW);
    digitalWrite(BACKWARD_R, HIGH);
    analogWrite (LEFT_MOTOR, 150);
    analogWrite (RIGHT_MOTOR, 150);
    delay(100);
  }

    else if (digitalRead(RightSensor) == HIGH && digitalRead(LeftSensor) == LOW)
  {
    //Tilt robot towards right by stop_Fing the right wheel and moving the left one
    digitalWrite(FORWARD_L, LOW);    // If I want to turn right then the speed of the right wheel should be less than that of the left wheel, here, let a be the right wheel
    digitalWrite(BACKWARD_L, HIGH);
    digitalWrite(FORWARD_R, HIGH);
    digitalWrite(BACKWARD_R, LOW);
    analogWrite (LEFT_MOTOR, 150);
    analogWrite (RIGHT_MOTOR, 150);
    delay(100);
  }
}  
void stop_F(){
    digitalWrite(FORWARD_L, LOW);
    digitalWrite(BACKWARD_L, HIGH);
    digitalWrite(FORWARD_R, LOW);
    digitalWrite(BACKWARD_R, HIGH);
    analogWrite (LEFT_MOTOR, 100);
    analogWrite (RIGHT_MOTOR, 100);
    delay(50);
    analogWrite (LEFT_MOTOR, 0);
    analogWrite (RIGHT_MOTOR, 0);
    
    if(r > g && r > b){
      digitalWrite(Red,1);
      digitalWrite(Blue,0);
      digitalWrite(Green,0);
    }
    else if(b > g && b > r){
      digitalWrite(Red,0);
      digitalWrite(Blue,1);
      digitalWrite(Green,0);
    }
    else if(g > r && g > b){
      digitalWrite(Red,0);
      digitalWrite(Blue,0);
      digitalWrite(Green,1);
    }
}


void continuee_F(){
    digitalWrite(FORWARD_L, HIGH);
    digitalWrite(BACKWARD_L, LOW);
    digitalWrite(FORWARD_R, HIGH);
    digitalWrite(BACKWARD_R, LOW);
    analogWrite (LEFT_MOTOR, 150);
    analogWrite (RIGHT_MOTOR, 150);

    digitalWrite(Red,0);
    digitalWrite(Green,0);
    digitalWrite(Blue,0);
}


void proximity_F(){
  if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    proximity = APDS.readProximity();
//    Serial.print("   distance: ");
//    Serial.println(proximity);
      if (proximity < 240){
        stop_F();
        delay(500);
      }
      else if (proximity > 240){
        continuee_F();
      }
      else if  (proximity == -1){
        analogWrite(LEFT_MOTOR,0);
        analogWrite(RIGHT_MOTOR,0);
      }
    }
}



void color_F(){
    while (! APDS.colorAvailable()) {
    delay(5);
  }

  // read the color
  APDS.readColor(r, g, b);
}
