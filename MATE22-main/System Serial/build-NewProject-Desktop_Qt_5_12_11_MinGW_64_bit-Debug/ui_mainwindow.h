/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QGridLayout *gridLayout_3;
    QLabel *Pitchlabe_2;
    QLabel *Yawlabel_2;
    QLabel *PitchReading_2;
    QLabel *YawReading_2;
    QLabel *RollLabel;
    QLabel *RollReading;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QGridLayout *gridLayout_4;
    QLabel *BFRlabel_2;
    QLabel *TFLlabel_2;
    QLabel *TBRlabel_2;
    QLabel *BFLlabel_2;
    QLabel *BBRlabel_2;
    QLabel *BBLlabel_2;
    QLabel *TFRlabel_2;
    QLabel *TBLlabel_2;
    QLabel *BFRreading_2;
    QLabel *BFLreading_2;
    QLabel *BBRreading_2;
    QLabel *BBLreading_2;
    QLabel *TFRreading_2;
    QLabel *TFLreading_2;
    QLabel *TBRreading_2;
    QLabel *TBLreading_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1337, 702);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(980, 420, 321, 201));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        Pitchlabe_2 = new QLabel(layoutWidget);
        Pitchlabe_2->setObjectName(QString::fromUtf8("Pitchlabe_2"));
        Pitchlabe_2->setFont(font);

        gridLayout_3->addWidget(Pitchlabe_2, 2, 0, 1, 1);

        Yawlabel_2 = new QLabel(layoutWidget);
        Yawlabel_2->setObjectName(QString::fromUtf8("Yawlabel_2"));
        Yawlabel_2->setFont(font);

        gridLayout_3->addWidget(Yawlabel_2, 1, 0, 1, 1);

        PitchReading_2 = new QLabel(layoutWidget);
        PitchReading_2->setObjectName(QString::fromUtf8("PitchReading_2"));
        PitchReading_2->setFont(font);

        gridLayout_3->addWidget(PitchReading_2, 2, 1, 1, 1);

        YawReading_2 = new QLabel(layoutWidget);
        YawReading_2->setObjectName(QString::fromUtf8("YawReading_2"));
        YawReading_2->setFont(font);

        gridLayout_3->addWidget(YawReading_2, 1, 1, 1, 1);

        RollLabel = new QLabel(layoutWidget);
        RollLabel->setObjectName(QString::fromUtf8("RollLabel"));
        RollLabel->setFont(font);

        gridLayout_3->addWidget(RollLabel, 3, 0, 1, 1);

        RollReading = new QLabel(layoutWidget);
        RollReading->setObjectName(QString::fromUtf8("RollReading"));
        RollReading->setFont(font);

        gridLayout_3->addWidget(RollReading, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 430, 511, 191));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_4);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        BFRlabel_2 = new QLabel(layoutWidget_2);
        BFRlabel_2->setObjectName(QString::fromUtf8("BFRlabel_2"));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        BFRlabel_2->setFont(font1);

        gridLayout_4->addWidget(BFRlabel_2, 1, 0, 1, 1);

        TFLlabel_2 = new QLabel(layoutWidget_2);
        TFLlabel_2->setObjectName(QString::fromUtf8("TFLlabel_2"));
        TFLlabel_2->setFont(font1);

        gridLayout_4->addWidget(TFLlabel_2, 2, 3, 1, 1);

        TBRlabel_2 = new QLabel(layoutWidget_2);
        TBRlabel_2->setObjectName(QString::fromUtf8("TBRlabel_2"));
        TBRlabel_2->setFont(font1);

        gridLayout_4->addWidget(TBRlabel_2, 3, 3, 1, 1);

        BFLlabel_2 = new QLabel(layoutWidget_2);
        BFLlabel_2->setObjectName(QString::fromUtf8("BFLlabel_2"));
        BFLlabel_2->setFont(font1);

        gridLayout_4->addWidget(BFLlabel_2, 2, 0, 1, 1);

        BBRlabel_2 = new QLabel(layoutWidget_2);
        BBRlabel_2->setObjectName(QString::fromUtf8("BBRlabel_2"));
        BBRlabel_2->setFont(font1);

        gridLayout_4->addWidget(BBRlabel_2, 3, 0, 1, 1);

        BBLlabel_2 = new QLabel(layoutWidget_2);
        BBLlabel_2->setObjectName(QString::fromUtf8("BBLlabel_2"));
        BBLlabel_2->setFont(font1);

        gridLayout_4->addWidget(BBLlabel_2, 4, 0, 1, 1);

        TFRlabel_2 = new QLabel(layoutWidget_2);
        TFRlabel_2->setObjectName(QString::fromUtf8("TFRlabel_2"));
        TFRlabel_2->setFont(font1);

        gridLayout_4->addWidget(TFRlabel_2, 1, 3, 1, 1);

        TBLlabel_2 = new QLabel(layoutWidget_2);
        TBLlabel_2->setObjectName(QString::fromUtf8("TBLlabel_2"));
        TBLlabel_2->setFont(font1);

        gridLayout_4->addWidget(TBLlabel_2, 4, 3, 1, 1);

        BFRreading_2 = new QLabel(layoutWidget_2);
        BFRreading_2->setObjectName(QString::fromUtf8("BFRreading_2"));
        BFRreading_2->setFont(font1);

        gridLayout_4->addWidget(BFRreading_2, 1, 1, 1, 1);

        BFLreading_2 = new QLabel(layoutWidget_2);
        BFLreading_2->setObjectName(QString::fromUtf8("BFLreading_2"));
        BFLreading_2->setFont(font1);

        gridLayout_4->addWidget(BFLreading_2, 2, 1, 1, 1);

        BBRreading_2 = new QLabel(layoutWidget_2);
        BBRreading_2->setObjectName(QString::fromUtf8("BBRreading_2"));
        BBRreading_2->setFont(font1);

        gridLayout_4->addWidget(BBRreading_2, 3, 1, 1, 1);

        BBLreading_2 = new QLabel(layoutWidget_2);
        BBLreading_2->setObjectName(QString::fromUtf8("BBLreading_2"));
        BBLreading_2->setFont(font1);

        gridLayout_4->addWidget(BBLreading_2, 4, 1, 1, 1);

        TFRreading_2 = new QLabel(layoutWidget_2);
        TFRreading_2->setObjectName(QString::fromUtf8("TFRreading_2"));
        TFRreading_2->setFont(font1);

        gridLayout_4->addWidget(TFRreading_2, 1, 4, 1, 1);

        TFLreading_2 = new QLabel(layoutWidget_2);
        TFLreading_2->setObjectName(QString::fromUtf8("TFLreading_2"));
        TFLreading_2->setFont(font1);

        gridLayout_4->addWidget(TFLreading_2, 2, 4, 1, 1);

        TBRreading_2 = new QLabel(layoutWidget_2);
        TBRreading_2->setObjectName(QString::fromUtf8("TBRreading_2"));
        TBRreading_2->setFont(font1);

        gridLayout_4->addWidget(TBRreading_2, 3, 4, 1, 1);

        TBLreading_2 = new QLabel(layoutWidget_2);
        TBLreading_2->setObjectName(QString::fromUtf8("TBLreading_2"));
        TBLreading_2->setFont(font1);

        gridLayout_4->addWidget(TBLreading_2, 4, 4, 1, 1);


        verticalLayout_4->addLayout(gridLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1337, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "IMU Reading", nullptr));
        Pitchlabe_2->setText(QApplication::translate("MainWindow", "PITCH:", nullptr));
        Yawlabel_2->setText(QApplication::translate("MainWindow", "YAW:", nullptr));
        PitchReading_2->setText(QString());
        YawReading_2->setText(QString());
        RollLabel->setText(QApplication::translate("MainWindow", "Roll:", nullptr));
        RollReading->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Motors' Speed Readings ", nullptr));
        BFRlabel_2->setText(QApplication::translate("MainWindow", "BFR", nullptr));
        TFLlabel_2->setText(QApplication::translate("MainWindow", "TFL", nullptr));
        TBRlabel_2->setText(QApplication::translate("MainWindow", "TBR", nullptr));
        BFLlabel_2->setText(QApplication::translate("MainWindow", "BFL", nullptr));
        BBRlabel_2->setText(QApplication::translate("MainWindow", "BBR", nullptr));
        BBLlabel_2->setText(QApplication::translate("MainWindow", "BBL", nullptr));
        TFRlabel_2->setText(QApplication::translate("MainWindow", "TFR", nullptr));
        TBLlabel_2->setText(QApplication::translate("MainWindow", "TBL", nullptr));
        BFRreading_2->setText(QString());
        BFLreading_2->setText(QString());
        BBRreading_2->setText(QString());
        BBLreading_2->setText(QString());
        TFRreading_2->setText(QString());
        TFLreading_2->setText(QString());
        TBRreading_2->setText(QString());
        TBLreading_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
