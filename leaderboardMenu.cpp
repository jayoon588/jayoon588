/**
 * @file leaderboardMenu.cpp
 * @author Calvin Nguyen (cnguy66@uwo.ca)
 * @brief Implementation of the leaderboard menu page
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "leaderboardMenu.h"

using namespace std;

/**
 * @brief Construct a new Leaderboard Menu object and generates back button and scores 
 * 
 * @param parent 
 */
LeaderboardMenu::LeaderboardMenu(QGraphicsItem *parent) : QGraphicsItemGroup(parent){

    backButton = new MenuButton(50, 600, 200, 75, QString("Back"), this);

    display = new QGraphicsTextItem(this->generateEntries(), this);
    display->setDefaultTextColor(Qt::black);
    display->setFont(QFont("Times New Roman",35));
    display->setPos(30, 30);

}

/**
 * @brief Destroy the Leaderboard Menu:: Leaderboard Menu object
 * 
 */
LeaderboardMenu::~LeaderboardMenu(){

    delete backButton;
    delete display;

}

/**
 * @brief checks for button press
 * 
 * @return int 0 if button is pressed to go back to main menu, 2 otherwise to stay on page
 */
int LeaderboardMenu::leaderboardLoop(){

    if(View::instance().getMouseDown()){
        if (backButton->pointCollision(View::instance().getPos().x(), View::instance().getPos().y())) {
            //std::cerr << "Back button clicked" << std::endl;
            return 0;
        }
    }
    return 2;

}

/**
 * @brief method that receives vector of strings from leaderboard class and constrcuts formatted string to display in constructor
 * 
 * @return const QString of scores
 */
const QString LeaderboardMenu::generateEntries(){

    vector<string> entriesVector = Leaderboard::instance().getLeaderboard();

    QString entries;

    for (string entry : entriesVector){

        entries = entries + QString::fromStdString(entry) + QString("\n");

    }

    return entries;

}