/**
 * @file mainGame.h
 * @author Evan Goldrick (egoldric@uwo.ca), Curtis Ackland (cacklan@uwo.ca), David Lin (dlin72@uwo.ca)
 * @brief MainGame class definition
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MAIN_GAME_HEADER
#define MAIN_GAME_HEADER

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QKeyEvent>
#include <QWindow>
#include <QSound>
#include <math.h>

#include <iostream>
#include <stdio.h>
#include <list>
#include <set>
#include <experimental/random>
#include <QRectF>
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "drop.h"
#include "HUD.h"
#include "view.h"
#include "inventory.h"
#include "gun.h"
#include "map.h"
/**
 * @class MainGame
 * @brief MainGame stores everything about current game state
 * 
 */
class MainGame : public QGraphicsItemGroup {
    public:
    explicit MainGame(QGraphicsItem *parent = nullptr);
    ~MainGame();
    int gameLoop();
    private: 
        Map * map;
        std::list<Enemy*> enemies;
        std::list<Bullet*> bullets;
        std::list<Drop*> drops;
        std::vector<std::vector<int>*> spawnableTiles;
        std::set<Qt::Key> consumedKeys;
        QGraphicsRectItem * tempRect;
        QGraphicsRectItem * mapBorder;
        Player *p1;
        int playerHitbox;
        Gun *currentGun;
        HUD *hud;
        void SpawnEnemies(int wave, std::list<Enemy*>& enemies);
        void Explosion (double bulletX, double bulletY, std::list<Enemy*>& enemies);
        void spawnDrop(Drop::DropTypes);
};

#endif