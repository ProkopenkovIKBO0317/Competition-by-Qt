#ifndef COMPETITION_H
#define COMPETITION_H
#include <QString>
#include <string>
using namespace std;

class Competition
{
private:
    QString name;
    int number;
    int score;

public:
    Competition();
    Competition(QString name, int number, int score);
    int Rand(int score);
    int randomBetween(int low, int high,  int score);


    /* getters and setters */
    void setName(QString name) {
        this->name = name;
    }

    void setNumber(int number) {
        this->number = number;
    }

    void setScore(int score) {
        this->score = score;
    }

    QString getName() {
        return name;
    }

    int getNumber() {
        return number;
    }

    int getScore() {
        return score;
    }

};

struct compareCompByScore {
    bool operator()(Competition& a, Competition& b) {
        return a.getScore() > b.getScore();
    }
};

#endif // COMPETITION_H
