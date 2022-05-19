/**
 * @file mainMenu.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of MainMenu
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "mainMenu.h"
/**
 * @brief Construct a new MainMenu object, and create all menu buttons
 * 
 * @param parent 
 */
MainMenu::MainMenu(QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    playGameButton = new MenuButton(200, 100, 400, 100, QString("Play"), this);
    highScoresButton = new MenuButton(200, 300, 400, 100, QString("High Scores"), this);
	quitButton = new MenuButton(200, 500, 400, 100, QString("Quit"), this);
}

/**
 * @brief Destroy the MainMenu object
 * 
 */
MainMenu::~MainMenu() {
    delete playGameButton;
    delete highScoresButton;
    delete quitButton;
}

/**
 * @brief menu loop for checking user inputs
 * 
 * @return int value depending on which button is pressed
 */
int MainMenu::menuLoop(){
    View::instance().setSceneRect(QRectF(0, 0, View::instance().getAdjustedWindowWidth(), View::instance().getAdjustedWindowHeight()));
    
    playGameButton->setRect(View::instance().getAdjustedWindowWidth() / 4, View::instance().getAdjustedWindowHeight() / 7, (View::instance().getAdjustedWindowWidth() / 2), (View::instance().getAdjustedWindowHeight() / 7));
    highScoresButton->setRect(View::instance().getAdjustedWindowWidth() / 4, 3 * View::instance().getAdjustedWindowHeight() / 7, (View::instance().getAdjustedWindowWidth() / 2), (View::instance().getAdjustedWindowHeight() / 7));
    quitButton->setRect(View::instance().getAdjustedWindowWidth() / 4, 5 * View::instance().getAdjustedWindowHeight() / 7, (View::instance().getAdjustedWindowWidth() / 2), (View::instance().getAdjustedWindowHeight() / 7));
    
    if(View::instance().getMouseDown()){
        if (playGameButton->pointCollision(View::instance().getPos().x(), View::instance().getPos().y())) {
            //std::cerr << "Play button clicked" << std::endl;
            return 1;
        } else if (highScoresButton->pointCollision(View::instance().getPos().x(), View::instance().getPos().y())) {
            //std::cerr << "High Scores clicked" << std::endl;
            return 2;
        } else if (quitButton->pointCollision(View::instance().getPos().x(), View::instance().getPos().y())) {
            //std::cerr << "Quit button clicked" << std::endl;
            return 3;
            //qApp->quit();
        }
    }
    return 0;
}