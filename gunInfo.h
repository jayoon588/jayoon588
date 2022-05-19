/**
 * @file gunInfo.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Definition of GunInfo
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GUN_INFO_HEADER
#define GUN_INFO_HEADER
#include <QGraphicsItemGroup>
#include <QFont>
#include <QFontMetrics>
#include <string>
#include "player.h"
#include "gun.h"

/**
 * @class GunInfo
 * @brief Used to show information about the currently selected gun on the hud
 * 
 */
class GunInfo : public QGraphicsItemGroup {
    private:
    QFont *font = nullptr;
    QFontMetrics *fm = nullptr;
    QGraphicsTextItem *weaponType = nullptr;
    QGraphicsTextItem *ammoCount = nullptr;
    QGraphicsTextItem *healthPackCount = nullptr;
    QGraphicsTextItem *shieldPackCount = nullptr;
    
    public:
    GunInfo(double, double, QGraphicsItem *parent = nullptr);
    ~GunInfo();
    void updatePlayerInformation(Player *);
};
#endif