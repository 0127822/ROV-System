#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <mainwindow.h>
#include <array>
#include "Control.h"
using namespace std;
//extern int Final_speed[8] ;



void Control::PIDController_Init()
{
    /* Clear controller variables */
    integrator = 0.0f;
    prevError  = 0.0f;

    differentiator  = 0.0f;
    prevMeasurement = 0.0f;

    out = 0.0f;
}

void Control::PIDController_Update()
{

    /*
    * Error signal
    */
    float error = SETPOINT - IMU_READING;

    /*
    * Proportional
    */
    float proportional = Kp * error;

    /*
    * Derivative (band-limited differentiator)
    */

    differentiator = -(2.0f * Kd * (IMU_READING - prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
                             + (2.0f * tau - T) * differentiator)
                             / (2.0f * tau + T);
    /*
    * Integral
    */

    integrator = integrator + 0.5f * Ki * T * (error + prevError);
    /* Anti-wind-up via integrator clamping */
    if (integrator > limMaxInt)
    {
        integrator = limMaxInt;
    }

    else if (integrator < limMinInt) {
        integrator = limMinInt;
    }

    /*
    * Compute output and apply limits
    */
    out = proportional + integrator + differentiator;

    if (out > limMax)
    {
        out = limMax;
    }

    else if (out < limMin) {
        out = limMin;
    }

    /* Store error and measurement for later use */
    prevMeasurement = IMU_READING;
    prevError       = error;

    /* Return controller output */
    imu_out = (int) out;
}

void Control::Set_setpoint(float axis,int actual)
{
    IMU_READING = actual;
    if (axis != 0)        //axis={yaw,pitch,roll}
    {
        enable = true;
    }

    else
    {
        enable = false;
    }

    if(enable == true)    //if ROV ROLLING FROM CONTROLLER CHANGE ROLL SET POINT
    {
      state = false;      //pause roll control
      SETPOINT = IMU_READING;
    }

    else
    {
        state = 1;
    }
}

array<int,8> Control::motion(float axis[5],int max_speed,array<int,8> Final_speed,bool imu_state)
{
    if(!imu_state){
        imu_out = 0;
    }
    float a=1;
       if (max_speed == 100)
       a=0.8;
       else
       a=1;
        float Forward=a*axis[4];
        float Slide=-axis[0];
        float Rotate=-a*axis[2];
        float Pitch=a*axis[3]*-1;
        float Up=a*axis[1]*-1;
//        float Roll=0;

//       int TFR=(-Forward-Slide+Up-Rotate+Roll-Pitch)*max_speed;
//       int TFL=(Forward-Slide-Up-Rotate+Roll+Pitch)*max_speed;
//       int TBR=(Forward-b*Slide+Up+Rotate-Roll+Pitch)*max_speed;
//       int TBL=(-Forward-Slide-Up+Rotate+Roll-Pitch)*max_speed;
//       int BFR=(Forward+Slide+Up+Rotate+Roll-Pitch)*max_speed;
//       int BFL=(-Forward+Slide-Up+Rotate+Roll+Pitch)*max_speed;
//       int BBR=(-Forward+Slide+Up-Rotate+Roll+Pitch)*max_speed;
//       int BBL=(-Forward-b*Slide+Up+Rotate+Roll+Pitch)*max_speed;

//       int TFR = (F[0]*Forward+S[0]*Slide+U[0]*Up+R[0]*Rotate+P[0]*Pitch)*max_speed;
//       int TFL = (F[1]*Forward+S[1]*Slide+U[1]*Up+R[1]*Rotate+P[1]*Pitch)*max_speed;
//       int TBR = (F[2]*Forward+S[2]*Slide+U[2]*Up+R[2]*Rotate+P[2]*Pitch)*max_speed;
//       int TBL = (F[3]*Forward+S[3]*Slide+U[3]*Up+R[3]*Rotate+P[3]*Pitch)*max_speed;
//       int BFR = (F[4]*Forward+S[4]*Slide+U[4]*Up+R[4]*Rotate+P[4]*Pitch)*max_speed;
//       int BFL = (F[5]*Forward+S[5]*Slide+U[5]*Up+R[5]*Rotate+P[5]*Pitch)*max_speed;
//       int BBR = (F[6]*Forward+S[6]*Slide+U[6]*Up+R[6]*Rotate+P[6]*Pitch)*max_speed;
//       int BBL = (F[7]*Forward+S[7]*Slide+U[7]*Up+R[7]*Rotate+P[7]*Pitch)*max_speed;
//        Final_speed[0]=TFR;
//        Final_speed[1]=TFL;
//        Final_speed[2]=TBR;
//        Final_speed[3]=TBL;
//        Final_speed[4]=BFR;
//        Final_speed[5]=BFL;
//        Final_speed[6]=BBR;
//        Final_speed[7]=BBL;

       for(int i=0; i<8; i++){
           Final_speed[i] = (F[i]*Forward+S[i]*Slide+U[i]*Up+R[i]*(Rotate+imu_out)+P[i]*Pitch)*max_speed;
       }

       return normalize(max_speed,Final_speed);
}

array<int,8> Control::normalize(int max_speed,array<int,8> Final_speed)
{
    float MAX =0;
    float scale;
    float max_speedF=max_speed;


    for(int i=0;i<8;i++)
    {
        if(abs(Final_speed[i])>MAX)
            MAX=abs(Final_speed[i]);
    }
    if(MAX>max_speed)
    {
        scale=float(max_speedF/MAX);
        for(int i=0;i<8;i++)
            Final_speed[i]*=scale;
    }
    return Final_speed;
}
void Control::setConfiguration()
{
    QFile mFile(":/new/prefix1/Configuration.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Couldn't open file";
        return;
    }

    QTextStream in(&mFile);
    QString mText = in.readAll();

    QStringList data = mText.split("\n");
    QStringList dataSlice;
    dataSlice = data[0].split(":");
    if(dataSlice[0] == QString("forward"))
    {
        for(int j = 1; j<9; j++){
        if(dataSlice[1][j] == QString("+"))
            F[j-1] = 1;
        else
            F[j-1] = -1;
        }
    }
//    for(int i = 0;i<data.count(); i++){
//        dataSlice = data[i].split(":");
//        if(dataSlice[0] == QString("forward")){
//            for(int j = 1; j<9; j++){
//                if(dataSlice[1][j] == QString("+"))
//                    F[j-1] = 1;
//                else
//                    F[j-1] = -1;
//            }
//        }
//        else if(dataSlice[0] == QString("up")){
//            for(int j = 1; j<9; j++){
//                if(dataSlice[1][j] == QString("+"))
//                    U[j-1] = 1;
//                else
//                    U[j-1] = -1;
//            }
//        }
//        else if(dataSlice[0] == QString("slide")){
//            for(int j = 1; j<9; j++){
//                if(dataSlice[1][j] == QString("+"))
//                    S[j-1] = 1;
//                else
//                    S[j-1] = -1;
//            }
//        }
//        else if(dataSlice[0] == QString("rotate")){
//            for(int j = 1; j<9; j++){
//                if(dataSlice[1][j] == QString("+"))
//                    R[j-1] = 1;
//                else
//                    R[j-1] = -1;
//            }
//        }
//        else if(dataSlice[0] == QString("pitch")){
//            for(int j = 1; j<9; j++){
//                if(dataSlice[1][j] == QString("+"))
//                    P[j-1] = 1;
//                else
//                    P[j-1] = -1;
//            }
//        }
//    }
    U = {-F[0],-F[1],F[2],F[3],F[4],F[5],-F[6],-F[7]};
    S = {F[0],-F[1],-F[2],F[3],F[4],-F[5],-F[6],F[7]};
    R = {F[0],-F[1],F[2],-F[3],F[4],-F[5],F[6],-F[7]};
    P = {-U[0],-U[1],U[2],U[3],-U[4],-U[5],U[6],U[7]};

    mFile.close();

}
