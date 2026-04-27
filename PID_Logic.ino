#include<Wire.h>
#include<math.h>


float angle=0;
float dt;
float setpoint = -4.3;
unsigned long prevTime = 0;

float Kp = 15; // This is the part where we need to fine tune the code.
float Ki = 0;
float Kd = 0.5;

float prevError = 0;
float integral = 0;
float derivative;
float output;
float error=0;


// This are the pins which to be motor driver's pinss to be coonected to ardiuno.
int motorPWM =9 ; //controls the speed Motor Driverr PWM 
int clk = 8;
int aclk=7; //controls the direction Motor Driver Direction Pin

void setup() {
  Wire.begin();
  Serial.begin(115200);
   
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  pinMode(motorPWM, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(aclk, OUTPUT);

  prevTime = millis();
}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  
  Wire.requestFrom(0x68, 6, true);
  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  //Serial.print("This is the raw data");
  //Serial.print("/");
  //Serial.print(AcX);
  //Serial.print(" ");
  //Serial.print(AcY);
  //Serial.print(" ");
  //Serial.println(AcZ);

  float gX = AcX / 16384.0; // gX,gY,gZ are the acceleration in the X,Y<Z direction respectively.
  float gY = AcY / 16384.0;
  float gZ = AcZ / 16384.0;

  float accAngle=atan2(gY,gZ)*180/PI; //accAngle is the actual angle made by the pedulum.


  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2, true);

  int16_t GyX = Wire.read() << 8 | Wire.read();
  float gyroRate = GyX / 131.0;  // deg/sec this is angular velocity.

  unsigned long currentTime = millis();
  dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  angle = 0.98 * (angle + gyroRate * dt) + 0.02 * accAngle; // Chance to tune the pqarameters
  
  //if (angle<setpoint-30||angle>setpoint+30) {
    //analogWrite(motorPWM, 0);
    //return;
  //}
  Serial.println(angle);

  // Control system begins from here...............................
  error= setpoint-angle;
  
  integral += error * dt;
  if (dt > 0) {
    derivative = (error - prevError) / dt;
  }

  output = (Kp * error + Ki * integral + Kd * derivative);
  prevError = error;
  int pwm = constrain(abs(output), 0, 255);

  if (output > 0) {
    digitalWrite(clk, HIGH);
    digitalWrite(aclk, LOW);
  }else {
    digitalWrite(clk, LOW);
    digitalWrite(aclk, HIGH);
  }
  Serial.println(pwm);

  analogWrite(motorPWM, pwm);
  delay(10);
}
