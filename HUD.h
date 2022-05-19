/**
 * @file HUD.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Definition of HUD class
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef HUD_HEADER
#define HUD_HEADER
#include "HUDbar.h"
#include "score.h"
#include "cooldownTimer.h"
#include "gunInfo.h"
#include "view.h"
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>


/**
 * @class HUD
 * @brief HUD contains all items that should be shown on the player's screen at all times
 * 
 */
class HUD : public QGraphicsItemGroup {
    private:
    HUDbar *healthBar;
    HUDbar *shieldBar;
    Score *score;
    CooldownTimer *reloadTimer;
    GunInfo *gunInfo;
    QGraphicsRectItem *gunInfoBackground;
    
    public:
    HUD(QGraphicsItem *parent = nullptr);
    ~HUD();
    HUDbar* getHealthBar();
    HUDbar* getShieldBar();
    Score* getScore();
    CooldownTimer* getReloadTimer();
    GunInfo* getGunInfo();
    void resizeHud(double, double);
};

#endif