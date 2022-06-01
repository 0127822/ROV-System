#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include<QtWidgets>
#include"Motion.h"
#include <sstream>
using namespace std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "COM13";
    arduino = new QSerialPort;
    serialBuffer = "";



//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
//                if(serialPortInfo.vendorIdentifier() == arduino_nano_vendor_id){
//                    if(serialPortInfo.productIdentifier() == arduino_nano_product_id){
//                        arduino_port_name = serialPortInfo.portName();
//                        arduino_is_available = true;
//                    }
//                }
//            }
//        }
    arduino_is_available = true;
    if(arduino_is_available){
          // open and configure the serialport
          arduino->setPortName(arduino_port_name);
          arduino->open(QSerialPort::ReadWrite);
          arduino->setBaudRate(QSerialPort::Baud115200);
          arduino->setDataBits(QSerialPort::Data8);
          arduino->setParity(QSerialPort::NoParity);
          arduino->setStopBits(QSerialPort::OneStop);
          arduino->setFlowControl(QSerialPort::NoFlowControl);
          QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
      }else{
          // give error message if not available
        cout<<"Port error, Couldn't find the Arduino!"<<endl;
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
      }



}

MainWindow::~MainWindow()
{
    delete ui;
    if(arduino->isOpen()){  //close arduino port if window is closed
       arduino->close();
    }
}


void MainWindow::SendSerial(char* command)
{
    if(arduino->isWritable()){
//        char charArray[11];
//        char *charArray = new char[command.size() + 1 ];
//        copy(command.begin() , command.end() , charArray);

//        charArray[10] = '\0';
                for (int i = 0 ; i < 10 ; i ++)
                {
                    cout<<command[i]<<" ";
                }
                cout<<endl;

        arduino->write(command,11);

//        for (int i = 0 ; i < 8 ; i ++)
//        {
//            cout<<(int)charArray[i]*2<<" ";
//        }
//        cout<<endl;
//        for (int i = 8 ; i < 10 ; i ++)
//        {
//            cout<<charArray[i]<<" ";
//        }
//        cout<<endl;



         ui->TFRreading_2->setText(QString::number(((int) command[0])*2));
         ui->TFLreading_2->setText(QString::number(((int) command[1])*2));
         ui->TBRreading_2->setText(QString::number(((int) command[2])*2));
         ui->TBLreading_2->setText(QString::number(((int) command[3])*2));
         ui->BFRreading_2->setText(QString::number(((int) command[4])*2));
         ui->BFLreading_2->setText(QString::number(((int) command[5])*2));
         ui->BBRreading_2->setText(QString::number(((int) command[6])*2));
         ui->BBLreading_2->setText(QString::number(((int) command[7])*2));

//        delete [] charArray;

        //Sleep(2);
        //arduino->clear();




    }else{
        qDebug() << "Couldn't write to serial!";
    }

}

void MainWindow::readSerial()
{
    if(arduino->bytesAvailable()>0){
    serialData = arduino->readAll();
    arduino->clear();
//    qDebug()<<serialData<<endl;

//    for(int  i = 1 ; i < 8 ; i ++)
//    {
//       y[i-1] =  (unsigned char)serialData[i];

//    }

//    if((serialData[0]=='s') && (serialData[5]=='a')){
////    x[0]= (y[0] << 8) | (y[1]&0xFF);
////    x[1]= ((y[2] << 8) | (y[3]&0xFF)) - 180;
////    x[2]= ((y[4] << 8) | (y[5]&0xFF)) - 180;
//    x[0] = y[0] | (y[3] & ((1<<0))<<8);
//    x[1] = (y[1] | (y[3] & ((1<<1))<<7))-180;
//    x[2] = (y[2] | (y[3] & ((1<<2))<<6))-180;

//    ui->YawReading_2->setText(QString::number(x[0]));
//    ui->PitchReading_2->setText(QString::number(x[1]));
//    ui->RollReading->setText(QString::number(x[2]));
//}
}
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this,"Quit" ,
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                              QMessageBox::Yes );
    if (resBtn != QMessageBox::Yes)
    {
        event->ignore();

    }
    else
    {
        Quit = true ;
        event->accept();
    }
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




