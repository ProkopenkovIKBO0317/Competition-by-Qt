#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <competition.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QVector>
#include <QtAlgorithms>
#include <QDebug>
#include <QIcon>
#include <QString>
#include <QFile>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Registration();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void Score_registration();
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_exit_button_clicked();

private:
    Competition c;
    QVector<Competition> vecComp;
    Ui::MainWindow *ui;
    QRegExpValidator name_validator;

};

#endif // MAINWINDOW_H
