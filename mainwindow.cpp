#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow),
    name_validator(QRegExp("^[а-яА-Я]{20}$"))

{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->label_4->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->lineText->hide();
    ui->lineText->setValidator(&name_validator);
    ui->exit_button->hide();
    ui->out_result->hide();

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Registration()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(Score_registration()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label_2->setVisible(true);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->lineText->setVisible(true);
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::Registration()
{
    c.setName(ui->lineText->text());
    if(c.getName() == "") {
        QMessageBox::critical(this, "Ошибка", "Вы ничего не ввели!");
    } else {
        QMessageBox::information(this, "Диалоговое окно", "Участник успешно зарегистрирован");

        //ui->statusBar->showMessage("Участник успешно зарегистрирован");
        vecComp.push_back(c);
        if(vecComp.size() >= 10) {
            QMessageBox::about(this, "Диалоговое окно", "Зарегистрировано максимальное количество участников!");
            ui->pushButton_2->setEnabled(false);
            ui->lineText->setReadOnly(true);
        }
        qDebug() << vecComp.size();
        ui->lineText->clear();
    };
}

void MainWindow::on_pushButton_3_clicked()
{
    if(vecComp.size() == 0) {
        QMessageBox::critical(this, "Ошибка", "Отсутствуют зарегистрированные участники!");
    } else {
        ui->pushButton_3->hide();
        ui->lineText->hide();
        ui->label_2->hide();
        ui->pushButton_2->hide();
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton_5->setEnabled(false);
    }
}

void MainWindow::Score_registration()
{
    for(int i = 0; i < vecComp.size(); i++) {
        vecComp[i].setScore(qrand() % 30 + 1);
        vecComp[i].setNumber(i+1);
    }
    /*
    for(int i = 0; i < vecComp.size(); i++) {
        QFile file("D:/Result.txt");
                if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
                {
                     QTextStream out(&file);
                     out << "#" << vecComp[i].getNumber() << "  " << vecComp[i].getName()<< "\n" <<  "Score: " << vecComp[i].getScore() << "\n\n";
                     file.close();
                }
    }
    */
    QMessageBox::information(this, "Диалоговое окно", "Баллы успешно зарегистрированы");
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(true);
}



void MainWindow::on_pushButton_5_clicked()
{
    ui->exit_button->setVisible(true);

}

void MainWindow::on_exit_button_clicked()
{
    QString str ="";
    QString begin = "Начало сеанса";
    QString end = "Конец сеанса";
    QFile file("ываыррварв.txt");
    QTextStream out(&file);
    out << begin << "\n";
    sort(vecComp.begin(),vecComp.end(), compareCompByScore());

    for(int j = 0; j < 1; j++) {
        if(vecComp.size() == 1) {
            vecComp[0].setName(vecComp[0].getName()+" | 1 МЕСТО");
        } else if(vecComp.size() == 2) {
            vecComp[0].setName(vecComp[0].getName()+" | 1 МЕСТО");
            vecComp[1].setName(vecComp[1].getName()+" | 2 МЕСТО");
        } else if(vecComp.size() >= 3) {
            vecComp[0].setName(vecComp[0].getName()+" | 1 МЕСТО");
            vecComp[1].setName(vecComp[1].getName()+" | 2 МЕСТО");
            vecComp[2].setName(vecComp[2].getName()+" | 3 МЕСТО");
        }

    }
    for(int i = 0; i < vecComp.size(); i++) {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
          {
               out << "#" << (vecComp[i].getNumber()) << "  " << vecComp[i].getName()<< " | " <<  "Score: " << vecComp[i].getScore() << "\n";
               file.close();
          }
        str += "#";
        str += QString::number(vecComp[i].getNumber()) +" ";
        str += vecComp[i].getName() + " | ";
        str += "Score: ";
        str += QString::number(vecComp[i].getScore()) + "\n";
    }
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
      {
        out << end + "\n\n\n";
        file.close();
      }
    ui->out_result->setVisible(true);
    ui->out_result->setText(str);
}
