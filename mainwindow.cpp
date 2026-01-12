#include "mainwindow.h"
#include "ui_mainwindow.h"
double firstNum = 0;
QString operation = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn0_clicked()
{
   ui->display->setText(ui->display->text() + "0");
}


void MainWindow::on_btn1_clicked()
{
    ui->display->setText(ui->display->text() + "1");
}


void MainWindow::on_btn2_clicked()
{
    ui->display->setText(ui->display->text() + "2");
}


void MainWindow::on_btn3_clicked()
{
    ui->display->setText(ui->display->text() + "3");
}


void MainWindow::on_btn4_clicked()
{
    ui->display->setText(ui->display->text() + "4");
}


void MainWindow::on_btn5_clicked()
{
    ui->display->setText(ui->display->text() + "5");
}


void MainWindow::on_btn6_clicked()
{
    ui->display->setText(ui->display->text() + "6");
}


void MainWindow::on_btn7_clicked()
{
    ui->display->setText(ui->display->text() + "7");
}


void MainWindow::on_btn8_clicked()
{
    ui->display->setText(ui->display->text() + "8");
}


void MainWindow::on_btn9_clicked()
{
    ui->display->setText(ui->display->text() + "9");
}


void MainWindow::on_btnAdd_clicked()
{


        firstNum = ui->display->text().toDouble();
        operation = "+";
        ui->display->clear();


}


void MainWindow::on_btnSub_clicked()
{


        firstNum = ui->display->text().toDouble();
        operation = "-";
        ui->display->clear();


}


void MainWindow::on_btnMul_clicked()
{


        firstNum = ui->display->text().toDouble();
        operation = "*";
        ui->display->clear();


}


void MainWindow::on_btnDiv_clicked()
{


        firstNum = ui->display->text().toDouble();
        operation = "/";
        ui->display->clear();


}


void MainWindow::on_btnMod_clicked()
{


        firstNum = ui->display->text().toDouble();
        operation = "%";
        ui->display->clear();


}


void MainWindow::on_btnEqual_clicked()
{
    double secondNum = ui->display->text().toDouble();
    double result = 0;

    if (operation == "+")
        result = firstNum + secondNum;
    else if (operation == "-")
        result = firstNum - secondNum;
    else if (operation == "*")
        result = firstNum * secondNum;
    else if (operation == "/")
        result = (secondNum != 0) ? firstNum / secondNum : 0;
    else if (operation == "%")
        result = (int)firstNum % (int)secondNum;

    ui->display->setText(QString::number(result));
}


void MainWindow::on_btnClear_clicked()
{


        ui->display->clear();
        firstNum = 0;
        operation = "";


}


void MainWindow::on_btnDot_clicked()
{
    if (!ui->display->text().contains("."))
        ui->display->setText(ui->display->text() + ".");
}

