/**
 * @file HUD.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of HUD
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "HUD.h"

/**
 * @brief Construct a new HUD object
 * 
 * @param parent 
 */
HUD::HUD(QGraphicsItem * parent) : QGraphicsItemGroup(parent) {
    healthBar = new HUDbar(20, 0, 0, 40, 50, 100, this);
    healthBar->setColor(QBrush(QColor(255, 0, 0, 200)));
    shieldBar = new HUDbar(20, 0, 0, 40, 50, 100, this);
    shieldBar->setColor(QBrush(QColor(0, 0, 255, 200)));
    score = new Score(0, 0, this);
    reloadTimer = new CooldownTimer(0, 0, 50, 50, this);
    reloadTimer->setColor(QBrush(QColor(255, 200, 0)));
    gunInfoBackground = new QGraphicsRectItem(0, 0, 250, 180, this);
    gunInfoBackground->setBrush(QBrush(QColor(0, 100, 150, 100)));
    gunInfoBackground->setZValue(0);
    gunInfo = new GunInfo(0, 0, this);
    gunInfo->setZValue(1);
}

/**
 * @brief Destroy the HUD object, delete all child objects
 * 
 */
HUD::~HUD() {
    delete healthBar;
    delete shieldBar;
    delete score;
    delete reloadTimer;
    delete gunInfo;
}

/**
 * @brief get health bar object
 * 
 * @return HUDbar* 
 */
HUDbar* HUD::getHealthBar() {
    return healthBar;
}

/**
 * @brief get shield bar object
 * 
 * @return HUDbar* 
 */
HUDbar* HUD::getShieldBar() {
    return shieldBar;
}

/**
 * @brief get score object
 * 
 * @return Score* 
 */
Score* HUD::getScore() {
    return score;
}

/**
 * @brief get reload timer object
 * 
 * @return CooldownTimer* 
 */
CooldownTimer* HUD::getReloadTimer() {
    return reloadTimer;
}

/**
 * @brief get gun info object
 * 
 * @return GunInfo* 
 */
GunInfo* HUD::getGunInfo() {
    return gunInfo;
}

/**
 * @brief resizing the game HUD
 * 
 * @param width new width of HUD
 * @param height new height of HUD
 */
void HUD::resizeHud(double width, double height) {
    double barWidth = width / 4;
    double barHeight = 40; //height / 20;
    healthBar->setPos(20, height - barHeight - 20);
    healthBar->resize(barWidth, barHeight);
    shieldBar->setPos(20, height - 2 * barHeight - 20);
    shieldBar->resize(barWidth, barHeight);

    reloadTimer->setPos(width - 100, height - 100);

    gunInfoBackground->setPos(width - 250, height - 200);
    gunInfo->setPos(width - 250, height - 200);
}