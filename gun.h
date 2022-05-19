/**
 * @file gun.h
 * @author Calvin Nguyen (cnguy66@uwo.ca), Curtis Ackland (cacklan@uwo.ca)
 * @brief header file for the gun class
 * @version 1.0
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GUN_H
#define GUN_H

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

/**
 * @class Gun
 * @brief Gun Class that stores characteristics and data about Gun objects
 */

class Gun{

    private:
        std::string gun_type;
        std::string ammo_type;
        int ammo_capacity;
        int max_ammo_capacity;
        int magazine_capacity;
        int max_magazine_capacity;
        double reloadSpeed;
        double reloadTimeLeft = 0;
        int fire_rate;
        int fire_rate_cd = 0;
        int damage;
        QGraphicsRectItem * gun_model;

    public:
        Gun(std::string gun, QRectF, QGraphicsItem* = nullptr);
        std::string getGunType();
        std::string getAmmoType();
        int getMaxMagazineCapacity();
        int getCurrentMagazineCapacity();
        void setCurrentMagazineCapacity(int);
        int getMaxAmmoCapacity();
        void setMaxAmmoCapacity(int);
        int getAmmoCount();
        void setAmmoCount(int);
        int getReloadSpeed();
        int getReloadTimeLeft();
        void setReloadTimeLeft(int);
        int getFireRate();
        int getFireRateCD();
        void setFireRateCD(int);
        int getGunDamage();
        QGraphicsRectItem* getGunModel();
        void hideGun();
        void showGun();
        ~Gun();


};

#endif
