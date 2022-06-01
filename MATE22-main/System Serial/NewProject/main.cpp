#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QSerialPort>
#include <SFML/Graphics.hpp>
#include<stdlib.h>
#include<iostream>
#include"Motion.h"
#include <windows.h>
#include <QApplication>

using namespace std;
void MotorReading(MainWindow* w);
void casting(); //Fun. to Map the Final Speed and Casting it to Char[]
void setAxisArray(int ax, float position, float*axis);
char CharSpeed [11];
string checkbuff;
int maxspeed = 100;
int ax; //controller's axis
int Final_speed[8];
float position; //controller's analog position
float axis[5]= {0,0,0,0,0};
char buff[10];
char laser='f',lighting='f';

string convertToString(char* a)
{
    string s = a;
    return s;
}

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
    w.SendSerial("start\0");
    while(Window.isOpen())
        {
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

            case sf::Event::JoystickButtonPressed:
//                cout<<Event.joystickButton.button<<endl;
                if (sf::Joystick::isButtonPressed(0,4))
                {
                    if(maxspeed==100)
                    {
                        maxspeed=100;
//                        cout<<maxspeed<<endl;
                    }
                    else
                    {
                        maxspeed-=50;
//                        cout<<maxspeed<<endl;
                    }
                }

                if (sf::Joystick::isButtonPressed(0,5))
                {
                    if(maxspeed==200)
                    {
                        maxspeed=200;
//                        cout<<maxspeed<<endl;
                    }
                    else
                    {
                        maxspeed+=50;
//                        cout<<maxspeed<<endl;
                    }
                }
                if (sf::Joystick::isButtonPressed(0,1))
                {
                    if(laser=='f')
                    {
                        laser='o';
                      // cout<<"laser On"<<endl;
                    }
                    else
                    {
                        laser='f';
                       // cout<<"laser Off"<<endl;
                    }
                }
                if (sf::Joystick::isButtonPressed(0,2))
                {
                    if(lighting=='f')
                    {
                        lighting='o';
//                        cout<<"lighting On"<<endl;
                    }
                    else
                    {
                        lighting='f';
//                        cout<<"lighting Off"<<endl;
                    }
                }
                break;
            case sf::Event::JoystickMoved:
                position=Event.joystickMove.position/100;
                ax=Event.joystickMove.axis;
//                cout<<ax<<endl;


            if(ax==0)
                setAxisArray(ax,position,axis);//Up and Down

            else if(ax==1)
                setAxisArray(ax,position,axis); //forword and back
            else if(ax==2)
                setAxisArray(ax,position,axis);//Pitch
            else if(ax==3)
                setAxisArray(ax,position,axis);//rotate
            else if(ax==4 |ax==5)
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


                break;
            }

        }
        if(w.Quit)
        {
            Window.close();
            exit(EXIT_FAILURE);
        }
        motion(axis,maxspeed);
//        MotorReading(&w);
        casting();

//        string sendSpeeds = convertToString(CharSpeed);
//        cout << CharSpeed[8] << endl;
        //string sendSpeeds(CharSpeed);

//        cout << sendSpeeds[8] << endl;
//        if(sendSpeeds.compare(checkbuff)!=0)
//        {
        for(int i = 0 ; i < 10; i ++)
        {
            if(buff[i] !=CharSpeed[i] )
            {
                w.SendSerial(CharSpeed);
            }
            buff[i]=CharSpeed[i];

        }

//        checkbuff.assign(sendSpeeds);
//        }
        Sleep(50);
        w.readSerial();


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

void casting()
{
    for(int i = 0 ; i < 8 ; i ++)
            {
//                Final_speed[i]+=202;
                Final_speed[i]/=2;

                CharSpeed[i] = (char)Final_speed[i];
//                    for(int i = 0 ; i < 8 ; i++ )
//                    {
//                        cout<<(int)CharSpeed[i]<<" ";
//                    }

//                    cout<<endl;

            }
    CharSpeed[8] = laser;
    CharSpeed[9] = lighting;
    CharSpeed[10] = '\0';

//    for(int i = 8 ; i < 10 ; i++ )
//    {
//        cout<<CharSpeed[i]<<" ";
//    }

//    cout<<endl;
}

//void MotorReading(MainWindow* w)
//{
//    w->ui->BFRreading_2->setText(QString::number(Final_speed[0]));
//    w->ui->BFLreading_2->setText(QString::number(Final_speed[1]));
//    w->ui->BBRreading_2->setText(QString::number(Final_speed[2]));
//    w->ui->BBLreading_2->setText(QString::number(Final_speed[3]));
//    w->ui->TFRreading_2->setText(QString::number(Final_speed[4]));
//    w->ui->TFLreading_2->setText(QString::number(Final_speed[5]));
//    w->ui->TBRreading_2->setText(QString::number(Final_speed[6]));
//    w->ui->TBLreading_2->setText(QString::number(Final_speed[7]));
//}

