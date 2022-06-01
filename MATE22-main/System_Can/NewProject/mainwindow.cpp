#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QtWidgets>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <map>

using namespace std;

QString arduino_port_name;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

//    m_server = new QTcpServer();

//    if(m_server->listen(QHostAddress::Any, 8000))
//    {
////       connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
//       connect(m_server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
//       qDebug() << "Server is listening on" << "127.0.0.1";
//    }
//    else
//    {
//        QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
//        exit(EXIT_FAILURE);
//    }


    ui->setupUi(this);
    QPixmap background_image = QPixmap(":/new/prefix1/background.jpg");
    QPixmap logo_image = QPixmap(":/new/prefix1/Croco_logo_white.png");
    ui->label->setPixmap(background_image);
    ui->label_11->setPixmap(logo_image);
//
    for (int i = 0; i < 201; i++) {
        PmwToForce.insert({ PWM[i],Force[i]*100 });
        ForceToPwm.insert({ Force[i]*100,PWM[i] });
    }
    ui->tabWidget->setCurrentIndex(0);
    arduino_is_available = false;
    arduino_port_name = "COM9";
    arduino = new QSerialPort;
    serialBuffer = "";

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
      }
    else{
          // give error message if not available
        cout<<"Port error, Couldn't find the Arduino!"<<endl;
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}


MainWindow::~MainWindow()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();
    delete ui;
    if(arduino->isOpen()){  //close arduino port if window is closed
       arduino->close();
    }
}

//void MainWindow::newConnection()
//{
//    while (m_server->hasPendingConnections())
//        appendToSocketList(m_server->nextPendingConnection());
//}

//void MainWindow::appendToSocketList(QTcpSocket* socket)
//{
//    connection_set.insert(socket);
//    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
//    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
//    qDebug() << "INFO :: Client with sockd:" << socket->socketDescriptor() << " has just entered the room" ;
//}

//void MainWindow::readSocket()
//{

//    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

//    QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString(socket->readAll()));
//    emit newMessage(message);
//    qDebug() << message;
//    return;

//}

//void MainWindow::discardSocket()
//{
//    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
//    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
//    if (it != connection_set.end()){
//        qDebug() << QString("INFO :: A client has just left the room").arg(socket->socketDescriptor());
//        connection_set.remove(*it);
//    }

//    socket->deleteLater();
//}

double MainWindow::getPWM(int x){

    int tempForce =  0;

    if (PmwToForce.count(x)) {
        tempForce = PmwToForce[x];
    }
    else{
        int tempForceNegative = 0;
        int tempForcePositive = 0;
        int i = 1;
        while (true) {

            if (PmwToForce.count(x - i)) {

                tempForceNegative = PmwToForce[x - i];
                break;
            }
            i++;
        }
        i = 1;
        while (true) {
            if (PmwToForce.count(x +  i)) {

                tempForcePositive = PmwToForce[x + i];
                break;
            }
            i++;
        }
        tempForce = (tempForceNegative + tempForcePositive) / 2;
    }
    tempForce = -1 * tempForce;
    int tempPWM = 0;

    if (ForceToPwm.count(tempForce)) {

        tempPWM = ForceToPwm[tempForce];
    }
    else {
        int tempPWMNegative = 0;
        int tempPWMPositive = 0;
        int i = 1;
        while (true) {

            if (ForceToPwm.count(tempForce - i)) {

                tempPWMNegative = ForceToPwm[tempForce - i];
                break;
            }
            i++;
        }
        i = 1;
        while (true) {
            if (ForceToPwm.count(tempForce + i)) {

                tempPWMPositive = ForceToPwm[tempForce + i];
                break;
            }
            i++;
        }
        tempPWM = (tempPWMNegative + tempPWMPositive) / 2;
    }
    return tempPWM;
}

void MainWindow::MotorReading()
{
    ui->BFRreading->setText(QString::number(Final_speed[0]*2-202));
    ui->BFLreading->setText(QString::number(Final_speed[1]*2-202));
    ui->BBRreading->setText(QString::number(Final_speed[2]*2-202));
    ui->BBLreading->setText(QString::number(Final_speed[3]*2-202));
    ui->TFRreading->setText(QString::number(Final_speed[4]*2-202));
    ui->TFLreading->setText(QString::number(Final_speed[5]*2-202));
    ui->TBRreading->setText(QString::number(Final_speed[6]*2-202));
    ui->TBLreading->setText(QString::number(Final_speed[7]*2-202));
}

void MainWindow::casting()
{
    CharSpeed[0] = '*';
    for(int i = 1 ; i < 9 ; i ++)
    {

        if(Final_speed[i-1] > 0 )
            Final_speed[i-1] = getPWM(1500 - Final_speed[i-1]) - 1500;

        Final_speed[i-1]+=202;
        Final_speed[i-1]/=2;
        CharSpeed[i] = (char)Final_speed[i-1];
                //cout<<CharSpeed[i]<<" ";


    }
    //cout<<endl;

}

void MainWindow::SendSerial(string command)
{
    if(arduino->isWritable()){
        if(command[0] == '*')
        {
        char charArray[10];
        copy(command.begin() , command.end() , charArray);

        charArray[command.size()] = '\0';
        arduino->write(charArray,10);
        }
        else if(command[0] == '#')
        {
            char charArray[3];
            copy(command.begin() , command.end() , charArray);

            charArray[command.size()] = '\0';
            arduino->write(charArray,3);
        }
    }
    else{
        qDebug() << "Couldn't write to serial!";
    }
}


void MainWindow::readSerial()
{
    if(arduino->bytesAvailable()>0){
        serialData = arduino->readAll();
        arduino->clear();
        for(int  i = 1 ; i < 9 ; i ++)
        {
           y[i-1] =  (unsigned char)(serialData[i]);
        }

        // IMU Data
        if((serialData[0]=='s') && (serialData[5]=='a')){
//            x[0]= (y[0] << 8) | (y[1]&0xFF);
//            x[1]= ((y[2] << 8) | (y[3]&0xFF)) - 180;
//            x[2]= ((y[4] << 8) | (y[5]&0xFF)) - 180;
            orientations[0] = (y[0] | ((y[3] & (1<<0))<<8))-180;
            orientations[1] = (y[1] | ((y[3] & (1<<1))<<7))-180;
            orientations[2] = (y[2] | ((y[3] & (1<<2))<<6))-180;
            ui->YawOrientation->setText(QString::number(orientations[0]));
            ui->PitchOrientation->setText(QString::number(orientations[1]));
            ui->RollOrientation->setText(QString::number(orientations[2]));
        }

        // Current Sensor Data
        else if((serialData[0]=='s') && (serialData[9]=='a')){
            for(int i=0; i<8;i++){
                qDebug() << "Motor " << i << ": " << y[i]/10;
            }
        }
    }
}




void MainWindow::closeEvent(QCloseEvent *)
{
    arduino->close();
    Quit = true;
//    QMessageBox::StandardButton resBtn = QMessageBox::question( this,"Quit" ,
//                                                                tr("Are you sure?\n"),
//                                                                QMessageBox::No | QMessageBox::Yes,
//                                                              QMessageBox::Yes );
//    if (resBtn != QMessageBox::Yes)
//    {
//        event->ignore();

//    }
//    else
//    {
//        Quit = true ;
//        event->accept();
//    }
}

int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//Change the COM port used for serial when selection changed in combo box
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arduino_is_available){
        arduino->close();                       //Close previous serial connection
        arduino->setPortName(arg1);             //set the current selected COM port
        arduino->open(QSerialPort::ReadWrite);  //open new serial connection
    }
}


//testing motors
void MainWindow::on_MotorsTest_btn_clicked()
{
    if(arduino_is_available){
        int speed = ui->Speeds->text().split(" ")[0].toInt();
        if(ui->comboBox_motors->currentText() == "All")
        {
            qDebug() << "All Motors Running...";
            Final_speed[0]= speed;
            Final_speed[1]= speed;
            Final_speed[2]= speed;
            Final_speed[3]= speed;
            Final_speed[4]= speed;
            Final_speed[5]= speed;
            Final_speed[6]= speed;
            Final_speed[7]= speed;
        }
        else if(ui->comboBox_motors->currentText() == "TFR")
        {
            qDebug() << "TFR Running...";
            Final_speed[0]= speed;
            Final_speed[1]= 0;
            Final_speed[2]= 0;
            Final_speed[3]= 0;
            Final_speed[4]= 0;
            Final_speed[5]= 0;
            Final_speed[6]= 0;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "TFL")
        {
            qDebug() << "TFL Running...";
            Final_speed[0]= 0;
            Final_speed[1]= speed;
            Final_speed[2]= 0;
            Final_speed[3]= 0;
            Final_speed[4]= 0;
            Final_speed[5]= 0;
            Final_speed[6]= 0;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "TBR")
        {
            qDebug() << "TBR Running...";
            Final_speed[0]= 0;
            Final_speed[1]= 0;
            Final_speed[2]= speed;
            Final_speed[3]= 0;
            Final_speed[4]= 0;
            Final_speed[5]= 0;
            Final_speed[6]= 0;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "TBL")
        {
            qDebug() << "TBL Running...";
            Final_speed[0]= 0;
            Final_speed[1]= 0;
            Final_speed[2]= 0;
            Final_speed[3]= speed;
            Final_speed[4]= 0;
            Final_speed[5]= 0;
            Final_speed[6]= 0;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "BFR")
        {
            qDebug() << "BFR Running...";
            Final_speed[0]= 0;
            Final_speed[1]= 0;
            Final_speed[2]= 0;
            Final_speed[3]= 0;
            Final_speed[4]= speed;
            Final_speed[5]= 0;
            Final_speed[6]= 0;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "BFL")
        {
            qDebug() << "BFL Running...";
            Final_speed[0]= 0;
            Final_speed[1]= 0;
            Final_speed[2]= 0;
            Final_speed[3]= 0;
            Final_speed[4]= 0;
            Final_speed[5]= speed;
            Final_speed[6]= 0;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "BBR")
        {
            qDebug() << "BBR Running...";
            Final_speed[0]= 0;
            Final_speed[1]= 0;
            Final_speed[2]= 0;
            Final_speed[3]= 0;
            Final_speed[4]= 0;
            Final_speed[5]= 0;
            Final_speed[6]= speed;
            Final_speed[7]= 0;
        }
        else if(ui->comboBox_motors->currentText() == "BBL")
        {
            qDebug() << "BBL Running...";
            Final_speed[0]= 0;
            Final_speed[1]= 0;
            Final_speed[2]= 0;
            Final_speed[3]= 0;
            Final_speed[4]= 0;
            Final_speed[5]= 0;
            Final_speed[6]= 0;
            Final_speed[7]= speed;
        }

        casting();
        SendSerial(CharSpeed);

        Sleep((ui->Delays->text().split(" ")[0].toInt())*1000); //delay with time in secs

        //stopping motors after test
        Final_speed[0]= 0;
        Final_speed[1]= 0;
        Final_speed[2]= 0;
        Final_speed[3]= 0;
        Final_speed[4]= 0;
        Final_speed[5]= 0;
        Final_speed[6]= 0;
        Final_speed[7]= 0;

        casting();
        SendSerial(CharSpeed);
    }
}


//testing lights
//void MainWindow::on_Lighting_btn_clicked()
//{
//    if(arduino_is_available){
//        if(LL_state[0])
//        {
//            LL[1] &= ~(0x01);
//            LL_state[0] = false;
//            ui->LightingState->setText("OFF");
//            ui->LightingState_2->setText("OFF");
//        }
//        else{
//            LL[1] |= 0x01;
//            LL_state[0] = true;
//            ui->LightingState->setText("ON");
//            ui->LightingState_2->setText("ON");
//        }
//        SendSerial(LL);
//    }
//}

//testing laser
void MainWindow::on_Laser_btn_clicked()
{
    if(arduino_is_available){
        if(LL_state[1])
        {
            LL[1] &= ~(0x02);
            LL_state[1] = false;
            ui->LaserState->setText("OFF");
            ui->LaserState_2->setText("OFF");
        }
        else{
            LL[1] |= 0x02;
            LL_state[1] = true;
            ui->LaserState->setText("ON");
            ui->LaserState_2->setText("ON");
        }
        SendSerial(LL);
    }
}


////testing servo up case
//void MainWindow::on_ServoUp_btn_clicked()
//{
//    if(arduino_is_available){
//        switch(servo_state){
//            case 0:
//                servo_state =1;
//                LL[1] &= ~(0x10);
//                LL[1] &= ~(0x08);
//                LL[1] |= 0x04;
//                ui->ServoState->setText("1");
//                ui->ServoState_2->setText("1");
//                break;
//            case 1:
//                servo_state =2;
//                LL[1] &= ~(0x10);
//                LL[1] |= 0x08;
//                LL[1] &= ~(0x04);
//                ui->ServoState->setText("2");
//                ui->ServoState_2->setText("2");
//                break;
//            case 2:
//                servo_state =3;
//                LL[1] &= ~(0x10);
//                LL[1] |= 0x08;
//                LL[1] |= 0x04;
//                ui->ServoState->setText("3");
//                ui->ServoState_2->setText("3");
//                break;
//            case 3:
//                servo_state =4;
//                LL[1] |= 0x10;
//                LL[1] &= ~(0x08);
//                LL[1] &= ~(0x04);
//                ui->ServoState->setText("4");
//                ui->ServoState_2->setText("4");
//                break;
//        }

//        SendSerial(LL);
//    }
//}


//testing servo down case
//void MainWindow::on_ServoDown_btn_clicked()
//{
//    if(arduino_is_available){
//        switch(servo_state){
//            case 1:
//                servo_state =0;
//                LL[1] &= ~(0x10);
//                LL[1] &= ~(0x08);
//                LL[1] &= ~(0x04);
//                ui->ServoState->setText("0");
//                ui->ServoState_2->setText("0");
//                break;
//            case 2:
//                servo_state =1;
//                LL[1] &= ~(0x10);
//                LL[1] &= ~(0x08);
//                LL[1] |= 0x04;
//                ui->ServoState->setText("1");
//                ui->ServoState_2->setText("1");
//                break;
//            case 3:
//                servo_state =2;
//                LL[1] &= ~(0x10);
//                LL[1] |= 0x08;
//                LL[1] &= ~(0x04);
//                ui->ServoState->setText("2");
//                ui->ServoState_2->setText("2");
//                break;
//            case 4:
//                servo_state =3;
//                LL[1] &= ~(0x10);
//                LL[1] |= 0x08;
//                LL[1] |= 0x04;
//                ui->ServoState->setText("3");
//                ui->ServoState_2->setText("3");
//                break;
//        }
//        SendSerial(LL);
//    }
//}

void MainWindow::on_Forward_btn_pressed()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,0,1};
        control.motion(ax,max_speed,Final_speed,false);

        casting();
        SendSerial(CharSpeed);
        qDebug() << "Forward";

    }

}

void MainWindow::on_Forward_btn_released()
{

    if(arduino_is_available){
        float ax[5] = {0,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Stop";
    }


}

void MainWindow::on_Reverse_btn_pressed()
{

    if(arduino_is_available){
        float ax[5] = {0,0,0,0,-1};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Reverse";
    }
}

void MainWindow::on_Reverse_btn_released()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Stop";
    }
}


void MainWindow::on_SlideR_btn_pressed()
{

    if(arduino_is_available){
        float ax[5] = {1,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Slide Right";
    }

}


void MainWindow::on_SlideR_btn_released()
{

    if(arduino_is_available){
        float ax[5] = {0,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Stop";
    }
}


void MainWindow::on_SlideL_btn_pressed()
{
    if(arduino_is_available){
        float ax[5] = {-1,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Slide Left";
    }
}


void MainWindow::on_SlideL_btn_released()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Stop";
    }
}




void MainWindow::on_PitchU_btn_pressed()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,-1,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Pitch Up";
    }
}


void MainWindow::on_PitchU_btn_released()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Stop";
    }
}

void MainWindow::on_PitchD_btn_pressed()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,1,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Pitch Down";
    }
}


void MainWindow::on_PitchD_btn_released()
{
    if(arduino_is_available){
        float ax[5] = {0,0,0,0,0};
        control.motion(ax,max_speed,Final_speed,false);
        casting();
        SendSerial(CharSpeed);
        qDebug() << "Stop";
    }
}

void MainWindow::on_RollR_btn_pressed()
{
    qDebug() << "Roll Right";
}


void MainWindow::on_pushButton_clicked()
{
    control.setConfiguration();
}


void MainWindow::on_LGripper_btn_clicked()
{
    if(arduino_is_available){
        if(LL_state[1])
        {
            LL[1] &= ~(0x02);
            LL_state[2] = false;
            ui->LGripperState->setText("Closed");
            ui->LGripperState_2->setText("Closed");
        }
        else{
            LL[1] |= 0x02;
            LL_state[1] = true;
            ui->LGripperState->setText("Open");
            ui->LGripperState_2->setText("Open");
        }
        SendSerial(LL);
    }
}


void MainWindow::on_RGripper_btn_clicked()
{
    if(arduino_is_available){
        if(LL_state[2])
        {
            LL[1] &= ~(0x04);
            LL_state[2] = false;
            ui->RGripperState->setText("Closed");
            ui->RGripperState_2->setText("Closed");
        }
        else{
            LL[1] |= 0x04;
            LL_state[2] = true;
            ui->RGripperState->setText("Open");
            ui->RGripperState_2->setText("Open");
        }
        SendSerial(LL);
    }
}


void MainWindow::on_BGripper_btn_clicked()
{
    if(arduino_is_available){
        if(LL_state[3])
        {
            LL[1] &= ~(0x08);
            LL_state[3] = false;
            ui->BGripperState->setText("Closed");
            ui->BGripperState_2->setText("Closed");
        }
        else{
            LL[1] |= 0x08;
            LL_state[3] = true;
            ui->BGripperState->setText("Open");
            ui->BGripperState_2->setText("Open");
        }
        SendSerial(LL);
    }
}

