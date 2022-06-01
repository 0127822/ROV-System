#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
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
    void SendSerial(char* command);
    void readSerial();
    int pitch, yaw, roll;

protected:
    void closeEvent(QCloseEvent *event) override;




private:
    QSerialPort *arduino;
//    static const quint16 arduino_uno_vendor_id = 9025;
//    static const quint16 arduino_nano_vendor_id = 6790;
    static const quint16 arduino_nano_vendor_id = 0403;
//    static const quint16 arduino_uno_product_id = 67;
//    static const quint16 arduino_nano_product_id = 29987;
    static const quint16 arduino_nano_product_id = 6001;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray serialData;
    QString serialBuffer;
    string temp;
    int x[3]={0,0,0};
    unsigned char y[8]={0,0,0,0,0,0,0,0};



};
#endif // MAINWINDOW_H
