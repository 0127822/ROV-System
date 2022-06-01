#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QSerialPort>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include "Control.h"
#include <windows.h>
#include <QApplication>
#include <map>
#include <QSerialPortInfo>
#include <QDebug>

using namespace std;
void MotorReading(MainWindow* w);
void casting(MainWindow* w); //Fun. to Map the Final Speed and Casting it to Char[]
void setAxisArray(int ax, float position, float*axis);
//char CharSpeed [10];
string speedbuff;
int ax; //controller's axis
//int Final_speed[8];
char LL[2] = {'#' , '\0'} ;
char speed_mode = 0;
bool LL_buff[4] = {false,false,false,false};  //Laser, LGripper, RGripper,BGripper
float position; //controller's analog position
int servo_state = 2;
float axis[5]= {0,0,0,0,0};




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sf::RenderWindow Window;
    MainWindow w;
    w.show();
    Window.create(sf::VideoMode(600, 600), "My SFML project");
    Window.setPosition(sf::Vector2i(50,50));
    Window.setVisible(false);
    sf::Event Event;





        //std::cout << "Hello World!\n";


    w.control.setConfiguration();
    w.control.PIDController_Init();

    //Check for open COM ports and change it in combobox
    const auto infos = QSerialPortInfo::availablePorts();
    w.ui->comboBox->clear();
    for(const QSerialPortInfo &info : infos){
        w.arduino_is_available = true;
        if(w.ui->comboBox->findText(info.portName(),Qt::MatchContains) == -1)
            w.ui->comboBox->addItem(info.portName());
     }
     while(Window.isOpen())
     {


        if(w.ui->comboBox->count()<1)
        {
            w.arduino_is_available = false;
        }

        while(Window.pollEvent(Event))
        {
            switch(Event.type)
            {

            case sf::Event::Closed:
                Window.close();
                break;
            case sf::Event::JoystickConnected:
                cout<<"Joystick "<<Event.joystickConnect.joystickId<<" is connected."<<endl;
                break;
            case sf::Event::JoystickDisconnected:
                cout<<"Joystick "<<Event.joystickConnect.joystickId<<" is disconnected."<<endl;
                break;

            case sf::Event::JoystickButtonReleased:
                if(Event.joystickButton.button == 5){ //Slide Right
                    setAxisArray(0,0,axis);
                }

                if(Event.joystickButton.button == 4){ //Slide Left
                    setAxisArray(0,0,axis);
                }
                break;

            case sf::Event::JoystickButtonPressed:
//             cout<<Event.joystickButton.button<<endl;
                if (sf::Joystick::isButtonPressed(0,11))     //imu
                {
                    if(w.imu_state)
                    {
                        w.imu_state = false;
                        w.ui->IMU_state->setText("OFF");
                    }
                    else
                    {
                        w.imu_state = true;
                        w.ui->IMU_state->setText("ON");
                    }
                }
                else if (sf::Joystick::isButtonPressed(0,0))     //LGripper
                {
                    if(w.LL_state[1])
                    {
                        LL[1] &= ~(0x02);
                        w.LL_state[1] = false;
                        w.ui->LGripperState->setText("Closed");
                        w.ui->LGripperState_2->setText("Closed");
                    }
                    else
                    {
                        LL[1] |= 0x02;
                        w.LL_state[1] = true;
                        w.ui->LGripperState->setText("Open");
                        w.ui->LGripperState_2->setText("Open");
                    }
                    w.SendSerial(LL);
                }
                else if (sf::Joystick::isButtonPressed(0,2))     //RGripper
                {
                    if(w.LL_state[2])
                    {
                        LL[1] &= ~(0x04);
                        w.LL_state[2] = false;
                        w.ui->RGripperState->setText("Closed");
                        w.ui->RGripperState_2->setText("Closed");
                    }
                    else
                    {
                        LL[1] |= 0x04;
                        w.LL_state[2] = true;
                        w.ui->RGripperState->setText("Open");
                        w.ui->RGripperState_2->setText("Open");
                    }
                    w.SendSerial(LL);
                }
                else if (sf::Joystick::isButtonPressed(0,1))     //BGripper
                {
                    if(w.LL_state[3])
                    {
                        LL[1] &= ~(0x08);
                        w.LL_state[3] = false;
                        w.ui->BGripperState->setText("Closed");
                        w.ui->BGripperState_2->setText("Closed");
                    }
                    else
                    {
                        LL[1] |= 0x08;
                        w.LL_state[3] = true;
                        w.ui->BGripperState->setText("Open");
                        w.ui->BGripperState_2->setText("Open");
                    }
                    w.SendSerial(LL);
                }
                else if(sf::Joystick::isButtonPressed(0,5)){ //Slide Right
                    setAxisArray(0,1,axis);
                }

                else if(sf::Joystick::isButtonPressed(0,4)){ //Slide Left
                    setAxisArray(0,-1,axis);
                }

                else if(sf::Joystick::isButtonPressed(0,3))      //Laser
                {
                    if(w.LL_state[0])
                    {
                        LL[1] &= ~(0x01);
                        w.LL_state[0] = false;
                        w.ui->LaserState->setText("Closed");
                        w.ui->LaserState_2->setText("Closed");
                    }
                    else
                    {
                        LL[1] |= 0x01;
                        w.LL_state[0] = true;
                        w.ui->LaserState->setText("Open");
                        w.ui->LaserState_2->setText("Open");
                    }
                    w.SendSerial(LL);
                }

                break;

            case sf::Event::JoystickMoved:
                position=Event.joystickMove.position/100;
                ax=Event.joystickMove.axis;
//                cout << "axis: " <<ax;
//                cout<< "\tposition: " << position<<endl;


//            if(ax==0)
//                setAxisArray(ax,position,axis);//Up and Down

            if(ax==1)
                setAxisArray(ax,position,axis); //forword and back
            else if(ax==2)
                setAxisArray(ax,position,axis);//Pitch
            else if(ax==3)
                setAxisArray(ax,position,axis);//rotate
            else if((ax==4) | (ax==5))
            {
                if(ax==4)
                {
                    position = (-position-1)/2;
                    setAxisArray(ax,position,axis); //down
                }
                else if(ax==5)
                {
                    position = (position+1)/2;
                    setAxisArray(4,position,axis); //up
                }
            }

            else if(ax == 6){
                if(position == 1){
                switch(speed_mode){
                case 0:
                    speed_mode = 1;
                    w.max_speed = 100;
                    w.ui->SpeedMax->setText("100");
                    break;
                case 1:
                    speed_mode = 2;
                    w.max_speed = 150;
                    w.ui->SpeedMax->setText("150");
                    break;
                case 2:
                    speed_mode = 3;
                    w.max_speed = 200;
                    w.ui->SpeedMax->setText("200");
                    break;
                }
                }

                else if(position == -1){
                    switch(speed_mode){
                    case 1:
                        speed_mode = 0;
                        w.max_speed = 80;
                        w.ui->SpeedMax->setText("80");
                        break;
                    case 2:
                        speed_mode = 1;
                        w.max_speed = 100;
                        w.ui->SpeedMax->setText("100");
                        break;
                    case 3:
                        speed_mode = 2;
                        w.max_speed = 150;
                        w.ui->SpeedMax->setText("150");
                        break;
                    }
                }
                }
                break;

                default:
                    break;
            }


        }


        if(w.Quit)
        {
            Window.close();
            exit(EXIT_FAILURE);
        }

        //Calling motion function and giving it values of axes and the maximum speed of motors
        if(w.imu_state){
            w.readSerial();
            w.control.Set_setpoint(axis[3],w.orientations[0]);
            w.control.PIDController_Update();
        }
        w.Final_speed = w.control.motion(axis,w.max_speed,w.Final_speed,w.imu_state);

        w.casting();
        w.MotorReading();
        string sendSpeeds(w.CharSpeed);

        if(sendSpeeds.compare(speedbuff)!=0)
        {
        w.SendSerial(sendSpeeds);
        speedbuff.assign(sendSpeeds);
        }


        Sleep(50);

    }
    return a.exec();
}


void setAxisArray(int ax, float position, float*axis)
{
    if(abs(position)>0.1)
    {
        axis[ax]=position;
    }
    else
    {
        axis[ax]=0;
    }
}




