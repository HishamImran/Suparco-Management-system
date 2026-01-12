#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn0_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btnAdd_clicked();

    void on_btnSub_clicked();

    void on_btnMul_clicked();

    void on_btnDiv_clicked();

    void on_btnMod_clicked();

    void on_btnEqual_clicked();

    void on_btnClear_clicked();

    void on_btnDot_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
