/**
 * @file Score.h
 * @author Jacob Yoon (jyoon88@uwo.ca), Evan Goldrick (egoldric@uwo.ca), Calvin Nguyen (cnguy66@uwo.ca)
 * @brief This display the score of the player
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
/**
 * @class Score
 * @brief Displays the player's score
 * 
 */
class Score : public QGraphicsTextItem {
    public: 
    Score(double, double, QGraphicsItem *parent = nullptr);
    ~Score();

    void increaseScore(int);
    void increaseWave();

    int getScore();
    int getWave();

    private: 
    int score;
    int wave;
};

#endif