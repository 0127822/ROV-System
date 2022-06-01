#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <stdlib.h>
#include <mainwindow.h>
using namespace std;

class Control
{
  public:
    float Kp;
    float Ki;
    float Kd;
    float axis;
    /* Derivative low-pass filter time constant */
    float tau = 1;

    /* Output limits */
    float limMin = -100;
    float limMax = 100;

    /* Integrator limits */
    float limMinInt = -100;
    float limMaxInt = 100;

    /* Sample time (in seconds) */
    float T = 0.01;

    /* Controller "memory" */
    float integrator;
    float prevError;			/* Required for integrator */
    float differentiator;
    float prevMeasurement;		/* Required for differentiator */

    /* Controller output */
    float out;

    int SETPOINT;
    int IMU_READING;
    int imu_out;

    bool enable = false;
    bool state  = false;

    void PIDController_Init();
    void PIDController_Update();
    void Set_setpoint(float axis,int actual);

    //Motion
    array<int,8> F,S,R,P,U;

    array<int,8> motion(float axis[5],int max_speed,array<int,8> Final_speed,bool imu_state);
    array<int,8> normalize(int max_speed,array<int,8> Final_speed);
    void setConfiguration();



};

#endif // CONTROL_H
