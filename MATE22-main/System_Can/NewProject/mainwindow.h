#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTcpServer>
#include <QTcpSocket>
#include "Control.h"
#include<stdlib.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    bool Quit  = false;
    void SendSerial(std::string command);
    void readSerial();
    int pitch, yaw, roll;
    QString arduino_port_name;
    char LL[2] = {'#','\0'};
    bool LL_state[4] = {false,false,false,false}; //laser, LGripper, RGripper, BGripper
//    unsigned char servo_state = 2;
    bool arduino_is_available;
    bool imu_state = false;
    array<int,8> Final_speed;
    char CharSpeed[9];
    Control control;
    int max_speed = 80;
    int orientations[3]={0,0,0};

    int PWM[201] = { 1100,1104,1108,1112,1116,1120,1124,1128,1132,1136,1140,1144,1148,1152,1156,1160,1164,1168,1172,1176,1180,1184,
            1188,1192,1196,1200,1204,1208,1212,1216,1220,1224,1228,1232,1236,1240,1244,1248,1252,1256,1260,1264,1268,1272,1276,1280,1284
            ,1288,1292,1296,1300,1304,1308,1312,1316,1320,1324,1328,1332,1336,1340,1344,1348,1352,1356,1360,1364,1368,1372,1376,1380
           ,1384,1388,1392,1396,1400,1404,1408,1412,1416,1420,1424,1428,1432,1436,1440,1444,1448,1452,1456,1460,1464,1468,1472,1476,1480,1484,1488
           ,1492,1496,1500,1504,1508,1512,1516,1520,1524,1528,1532,1536,1540,1544,1548,1552,1556,1560,1564,1568,1572,1576,1580,1584,1588,1592
           ,1596,1600,1604,1608,1612,1616,1620,1624,1628,1632,1636,1640,1644,1648,1652,1656,1660,1664,1668,1672,1676,1680,1684,1688,1692,1696
           ,1700,1704,1708,1712,1716,1720,1724,1728,1732,1736,1740,1744,1748,1752,1756,1760,1764,1768,1772,1776,1780,1784,1788,1792,1796,1800
           ,1804,1808,1812,1816,1820,1824,1828,1832,1836,1840,1844,1848,1852,1856,1860,1864,1868,1872,1876,1880,1884,1888,1892,1896,1900   };
        float Force[201] = { -2.90,-2.92,-2.89,-2.83,-2.79,-2.76,-2.72,-2.67,-2.60,-2.59,-2.56,-2.49,-2.44,-2.43,-2.39
                ,-2.34,-2.30,-2.25,-2.23,-2.18,-2.14,-2.10,-2.07,-2.01,-1.98,-1.95,-1.88,-1.85,-1.81,-1.78,-1.73
                ,-1.66,-1.65,-1.61,-1.56,-1.53,-1.49,-1.47,-1.44,-1.40,-1.37,-1.33,-1.29,-1.28,-1.22,-1.19,-1.15,-1.12
                ,-1.08,-1.04,-1.02,-0.99,-0.96,-0.93,-0.90,-0.87,-0.83,-0.79,-0.77,-0.74,-0.72,-0.69,-0.66,-0.64,-0.60,-0.57
                ,-0.54,-0.52,-0.49,-0.47,-0.44,-0.42,-0.39,-0.37,-0.34,-0.32,-0.29,-0.27,-0.24,-0.23,-0.20,-0.18,-0.16,-0.15
                ,-0.12,-0.11,-0.09,-0.07,-0.06,-0.05,-0.04, 0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00
                ,0.00,0.00,0.00,0.04,0.05,0.07,0.10,0.11,0.13,0.15,0.18,0.20,0.22,0.25,0.28,0.31,0.33,0.37,0.39,0.43,0.46,0.49,0.52,0.55,0.59
                ,0.63,0.65,0.68,0.71,0.76,0.79,0.83,0.86,0.89,0.93,0.97,1.00,1.04,1.08,1.14,1.16,1.20,1.23,1.28,1.31,1.35,1.40,1.43,1.48,1.53
                ,1.56,1.63,1.67,1.71,1.77,1.82,1.85,1.91,1.92,1.96,2.03,2.09,2.13,2.18,2.24,2.27,2.33,2.40,2.46,2.51,2.56,2.62,2.65,2.71,2.78
                ,2.84,2.87,2.93,3.01,3.04,3.08,3.16,3.23,3.26,3.32,3.38,3.40,3.45,3.50,3.57,3.64,3.71,3.69,3.71};
        map<int, int> PmwToForce;
        map<int, int> ForceToPwm;
        double getPWM(int x);
        void MotorReading();
        void casting();

protected:
    void closeEvent(QCloseEvent *event) override;


signals:
    void newMessage(QString);

private slots:
    // Tabs
    void on_comboBox_currentIndexChanged(const QString &arg1);

    // Developer Tab
    void on_Laser_btn_clicked();
    void on_MotorsTest_btn_clicked();

    void on_Forward_btn_pressed();
    void on_Forward_btn_released();
    void on_SlideR_btn_pressed();
    void on_SlideR_btn_released();
    void on_Reverse_btn_pressed();
    void on_Reverse_btn_released();
    void on_SlideL_btn_pressed();
    void on_SlideL_btn_released();
    void on_PitchU_btn_pressed();
    void on_PitchU_btn_released();
    void on_PitchD_btn_released();
    void on_PitchD_btn_pressed();
    void on_RollR_btn_pressed();
    void on_pushButton_clicked();
    void on_LGripper_btn_clicked();
    void on_RGripper_btn_clicked();
    void on_BGripper_btn_clicked();

//    // Socket
//    void newConnection();
//    void appendToSocketList(QTcpSocket* socket);

//    void readSocket();
//    void discardSocket();

private:
    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;

    QSerialPort *arduino;
//    static const quint16 arduino_uno_vendor_id = 9025;
//    static const quint16 arduino_nano_vendor_id = 6790;
//    static const quint16 arduino_nano_vendor_id = 1A86;
//    static const quint16 arduino_uno_product_id = 67;
//    static const quint16 arduino_nano_product_id = 29987;
    static const quint16 arduino_nano_product_id = 7523;
    //QString arduino_port_name;

    QByteArray serialData;
    QString serialBuffer;
    string temp;

    unsigned char y[8]={0,0,0,0,0,0,0,0};



};
#endif // MAINWINDOW_H
