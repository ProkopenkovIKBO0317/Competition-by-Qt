#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow),
    name_validator(QRegExp("^[а-яА-Я]{20}$")),
    score_validator(QRegExp("^[0-9]{3}$"))

{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->lineScore->hide();
    ui->pushButton_5->hide();
    ui->label_4->hide();
    ui->label_score->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->lineText->hide();
    ui->lineText->setValidator(&name_validator);
    ui->lineScore->setValidator(&score_validator);
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

void MainWindow::Registration()
{
    c.setName(ui->lineText->text());
    if(ui->lineText->text().isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Вы ничего не ввели!");
    } else {
        QMessageBox::information(this, "Диалоговое окно", "Участник успешно зарегистрирован");
    }

        vecComp.push_back(c);
        if(vecComp.size() >= 10) {
            QMessageBox::about(this, "Диалоговое окно", "Зарегистрировано максимальное количество участников!");
            ui->pushButton_2->setEnabled(false);
            ui->lineText->setReadOnly(true);
        }
        qDebug() << vecComp.size();
        ui->lineText->clear();
        for(int i = 0; i < vecComp.size(); i++) {
            vecComp[i].setNumber(i+1);
        }

}

void MainWindow::on_pushButton_3_clicked()
{
    if(vecComp.size() == 0) {
        QMessageBox::critical(this, "Ошибка", "Отсутствуют зарегистрированные участники!");
    } else {
        QString s = QString::number(1);
        ui->label_4->setText("     Участник #" + s);
        ui->label_score->setVisible(true);
        ui->pushButton_3->hide();
        ui->lineText->hide();
        ui->label_2->hide();
        ui->pushButton_2->hide();
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->pushButton_4->setVisible(true);
        ui->lineScore->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton_5->setEnabled(false);
    }
}

void MainWindow::Score_registration()
{
    c.setScore(ui->lineScore->text().toInt());
    if(c.getScore() > 100 || ui->lineScore->text().isEmpty()) {
        QMessageBox::critical(this, "Недопустимое значение", "Максимально возможный балл - 100, а минимально возможный - 0");
    } else {
        QMessageBox::information(this, "Диалоговое окно", "Балл успешно зарегистрирован");
        QString s = QString::number(j);
        j++;
        vecScore.push_back(c.getScore());
        if(vecScore.size() >= vecComp.size()) {
            QMessageBox::about(this, "Диалоговое окно", "Все баллы зарегистрированы!");
            ui->pushButton_4->setEnabled(false);
            ui->lineScore->setReadOnly(true);
            ui->pushButton_5->setEnabled(true);
            ui->label_4->hide();
        }
        ui->label_4->setText("     Участник #" + s);
    }
    ui->lineScore->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->exit_button->setVisible(true);
    ui->pushButton_5->hide();
    ui->label_score->hide();
    ui->lineScore->hide();

    for(int i = 0; i < vecScore.size(); i++) {
        vecComp[i].setScore(vecScore[i]);
    }

}

void MainWindow::on_exit_button_clicked()
{
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->lineScore->hide();
    ui->pushButton_5->hide();
    ui->label_4->hide();
    ui->label_score->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->lineText->hide();
    ui->exit_button->hide();

    QString str ="";
    QString begin = "Начало сеанса";
    QString end = "Конец сеанса";
    QString score = "Очки: ";
    QFile file("CompetitionResult.txt");
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
               out << "#" << (vecComp[i].getNumber()) << " | " << vecComp[i].getName()<< " | " << score << vecComp[i].getScore() << "\n";
               file.close();
          }
        str += "#";
        str += QString::number(vecComp[i].getNumber()) +" | ";
        str += vecComp[i].getName() + " | ";
        str += score;
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
