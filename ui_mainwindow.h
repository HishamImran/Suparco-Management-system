/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *display;
    QPushButton *btn0;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn7;
    QPushButton *btn5;
    QPushButton *btn8;
    QPushButton *btn6;
    QPushButton *btn9;
    QPushButton *btnMod;
    QPushButton *btnClear;
    QPushButton *btnEqual;
    QPushButton *btnDiv;
    QPushButton *btnMul;
    QPushButton *btnSub;
    QPushButton *btnAdd;
    QPushButton *btnDot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(380, 360);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #d9e2e8;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        display = new QLineEdit(centralwidget);
        display->setObjectName("display");
        display->setGeometry(QRect(2, 21, 371, 41));
        QFont font;
        font.setPointSize(18);
        display->setFont(font);
        display->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        display->setReadOnly(true);
        btn0 = new QPushButton(centralwidget);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(20, 210, 51, 24));
        btn0->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn1 = new QPushButton(centralwidget);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(20, 170, 51, 24));
        btn1->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn2 = new QPushButton(centralwidget);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(110, 170, 51, 24));
        btn2->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn3 = new QPushButton(centralwidget);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(210, 170, 51, 24));
        btn3->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn4 = new QPushButton(centralwidget);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(20, 130, 51, 24));
        btn4->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn7 = new QPushButton(centralwidget);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(20, 80, 51, 24));
        btn7->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn5 = new QPushButton(centralwidget);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(110, 130, 51, 24));
        btn5->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn8 = new QPushButton(centralwidget);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(110, 80, 51, 24));
        btn8->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn6 = new QPushButton(centralwidget);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(210, 130, 51, 24));
        btn6->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btn9 = new QPushButton(centralwidget);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(210, 80, 51, 24));
        btn9->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btnMod = new QPushButton(centralwidget);
        btnMod->setObjectName("btnMod");
        btnMod->setGeometry(QRect(110, 210, 51, 24));
        btnMod->setStyleSheet(QString::fromUtf8("background-color: lightgray;\n"
"font-size: 14px;\n"
""));
        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(210, 210, 51, 24));
        btnClear->setStyleSheet(QString::fromUtf8("background-color: lightgreen;\n"
"font-size: 14px;\n"
""));
        btnEqual = new QPushButton(centralwidget);
        btnEqual->setObjectName("btnEqual");
        btnEqual->setGeometry(QRect(210, 260, 51, 24));
        btnEqual->setStyleSheet(QString::fromUtf8("background-color: pink;\n"
"font-size: 14px;\n"
""));
        btnDiv = new QPushButton(centralwidget);
        btnDiv->setObjectName("btnDiv");
        btnDiv->setGeometry(QRect(310, 80, 41, 24));
        QFont font1;
        btnDiv->setFont(font1);
        btnDiv->setStyleSheet(QString::fromUtf8("background-color: orange;\n"
"font-size: 14px;"));
        btnMul = new QPushButton(centralwidget);
        btnMul->setObjectName("btnMul");
        btnMul->setGeometry(QRect(310, 130, 41, 24));
        btnMul->setFont(font1);
        btnMul->setStyleSheet(QString::fromUtf8("background-color: orange;\n"
"font-size: 14px;"));
        btnSub = new QPushButton(centralwidget);
        btnSub->setObjectName("btnSub");
        btnSub->setGeometry(QRect(310, 170, 41, 24));
        btnSub->setFont(font1);
        btnSub->setStyleSheet(QString::fromUtf8("background-color: orange;\n"
"font-size: 14px;"));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(310, 210, 41, 24));
        btnAdd->setFont(font1);
        btnAdd->setStyleSheet(QString::fromUtf8("background-color: orange;\n"
"font-size: 14px;"));
        btnDot = new QPushButton(centralwidget);
        btnDot->setObjectName("btnDot");
        btnDot->setGeometry(QRect(110, 260, 51, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 380, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnMod->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "c", nullptr));
        btnEqual->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnDiv->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        btnSub->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnDot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
