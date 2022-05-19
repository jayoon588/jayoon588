/**
 * @file mainMenu.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Definition of MainMenu
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MAIN_MENU_HEADER
#define MAIN_MENU_HEADER
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <view.h>
#include "menuButton.h"
/**
 * @class MainMenu
 * @brief Creates a main menu screen
 * 
 */
class MainMenu : public QGraphicsItemGroup {
    public:
    explicit MainMenu(QGraphicsItem *parent = nullptr);
    ~MainMenu();
    int menuLoop();
    private:
    MenuButton *playGameButton;
    MenuButton *highScoresButton;
    MenuButton *quitButton;
    QGraphicsRectItem *background;
};

#endif