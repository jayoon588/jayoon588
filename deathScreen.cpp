/**
 * @file deathScreen.cpp
 * @author Curtis Ackland (cacklan@uwo.ca)
 * @brief implementation of class that prompts window when player dies
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "deathScreen.h"

/**
 * @brief Construct a new Death Screen:: Death Screen object which creates a window
 * 
 * @param finalScore of the pkayer when they died
 */
DeathScreen::DeathScreen(int finalScore){

    QInputDialog *test = new QInputDialog();
    test->setLabelText(QString("Enter your name (One Word):"));
    
    int result = test->exec();
    if(result == 1){
        Leaderboard::instance().submitScore(finalScore, test->textValue().toStdString().c_str());
    }
    
}

/**
 * @brief Destroy the Death Screen:: Death Screen object
 * 
 */
DeathScreen::~DeathScreen(){

}
