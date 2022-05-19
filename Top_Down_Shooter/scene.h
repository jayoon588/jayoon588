/**
 * @file scene.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Scene class definition
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SCENE_HEADER
#define SCENE_HEADER
#include <QObject>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QTimerEvent>

#include "mainMenu.h"
#include "mainGame.h"
#include "leaderboardMenu.h"
#include "deathScreen.h"
/**
 * @class Scene
 * @brief Scene class for holding all graphics objects
 * 
 */
class Scene : public QGraphicsScene {
    public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
    void switchGameState(int);
    virtual void timerEvent(QTimerEvent *);
    private:
    int gameState;
    int finalScore;
    MainMenu *mainMenu = nullptr;
    MainGame *mainGame = nullptr;
    LeaderboardMenu *LBMenu = nullptr;
    DeathScreen *deadScreen = nullptr;
};

#endif