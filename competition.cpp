#include "competition.h"
#include <QVector>
#include <ctime>
#include <QDateTime>
#include <iostream>

Competition::Competition(QString name,int number, int score)
{
    this->name = name;
    this->number = number;
    this->score = score;
}

Competition::Competition(){}

int Competition::Rand(int score) {
    score = qrand() % 30 + 0;
    return score;
}

int Competition::randomBetween(int low, int high, int score)
{
    //qsrand(seed); // Установка базового числа для отсчёта рандома в qrand
    score = (qrand() % ((high + 1) - low) + low);
    return score;
}


