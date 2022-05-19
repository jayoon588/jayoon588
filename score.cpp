/**
 * @file Score.cpp
 * @author Jacob Yoon (jyoon88@uwo.ca), Evan Goldrick (egoldric@uwo.ca), Calvin Nguyen (cnguy66@uwo.ca)
 * @brief This display the score of the player
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "score.h"
#include <QFont>

/**
 * @brief Construct a new Score object
 * 
 * @param x x position of the score
 * @param y y position of the score
 * @param parent parent object of the score
 */
Score::Score(double x, double y, QGraphicsItem *parent) : QGraphicsTextItem(parent){
    score = 0;
    wave = 0;
    setPlainText(QString("Score: ")+ QString::number(score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Times New Roman",14));
    setPos(x, y);
}

/**
 * @brief Destroy the Score:: Score object
 * 
 */
Score::~Score(){

}

/**
 * @brief function to increase the score value
 * 
 * @param amount amount to increase by
 */
void Score::increaseScore(int amount){
    score += amount;
    setPlainText(QString("Score: ")+ QString::number(score) + " Wave: " + QString::number(wave));
}

/**
 * @brief function increases wave
 * 
 */
void Score::increaseWave(){
    wave++;
    setPlainText(QString("Score: ")+ QString::number(score) + " Wave: " + QString::number(wave));
}

/**
 * @brief get the current score
 * 
 * @return int 
 */
int Score::getScore(){
    return score;
}

/**
 * @brief get the current wave
 * 
 * @return int 
 */
int Score::getWave(){
    return wave;
}