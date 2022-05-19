/**
 * @file inventory.h
 * @author Curtis Ackland (cacklan@uwo.ca), Calvin Nguyen
 * @brief Implementation of the inventory
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string.h>
#include <stdio.h>
#include <QGraphicsItemGroup>

#include "gun.h"

/**
 * @class Inventory
 * @brief Inventory that holds the items and item data possessed by a player
 */
class Inventory{

    private:
        Gun *gun_primary = nullptr;
        Gun *gun_secondary = nullptr;
        int amount_health = 0;
        int amount_shield = 0;

    public:
        Inventory(QRectF player, QGraphicsItem* = nullptr);
        void setGunPrim(Gun *newGun);
        Gun* getGunPrim();
        void setGunSec(Gun *newGun);
        Gun* getGunSec();
        void setHealthAmount(int amount);
        int getHealthAmount();
        void setShieldAmount(int amount);
        int getShieldAmount();
        ~Inventory();


};

#endif