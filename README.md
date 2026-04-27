# Robotics-ControlSystem
<p align="center">
  <img src="bot.png" width="500">
</p>
This project implements a PID-controlled inverted pendulum using an MPU6050 sensor for angle estimation. Accelerometer and gyroscope data are fused to compute tilt, compared with a setpoint, and corrected using PID output. The motor driver adjusts direction and speed via PWM, enabling continuous feedback control to stabilize the system.<br>

# Features<br>
Real-time angle estimation (MPU6050)<br>
Complementary filter for stability<br>
PID control (Kp, Ki, Kd tuning)<br>
PWM motor control<br>
Direction control using driver<br>
Continuous feedback loop<br>
# Hardware Required<br>
Arduino (Uno)<br>
MPU6050 Sensor<br>
Motor Driver (L298N)<br>
DC Motor<br>
Power Supply<br>
Connecting wires<br>
# Working Principle<br>
Sensor reads tilt angle<br>
Complementary filter calculates stable angle<br>
Error = Setpoint − Angle<br>
PID computes correction<br>
Motor adjusts position<br>
# Control Algorithm<br>
The flowchart:<br>
<p align="center">
  <img src="flowchart.png" width="500">
</p>

# Circuit Connections<br>
1.MPU(Gyroscope)->Ardiuno<br>
SDA->SDA<br>
SCL->SCL<br>
VCC->5V<br>
GND->GND<br>

2.Ardiuno->Motor Driver
GND->GND<br><br>
5V->5V<br>
PWM pin (in our case its A9)->ENA<br>
Direction pin1 (in our case its A8)->IN1<br>
Direction pin1 (in our case its A7)->IN2<br>

3.Motor Driver->Motor<br>
OUT1->Terminal1<br>
OOT2->Terminal2<br>

# How to Run <br>
Upload code to Arduino<br>
Connect hardware properly<br>
Open Serial Monitor<br>
Tune Kp, Ki, Kd<br>

# Demo
🎥 Demo Video: [Watch Here]([https://drive.google.com/your-link](https://drive.google.com/file/d/131b9_4uZ-IpVv0CsWT5Alv41JCA6dMJ3/view?usp=sharing))
