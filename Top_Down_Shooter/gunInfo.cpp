/**
 * @file gunInfo.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of GunInfo
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "gunInfo.h"
/**
 * @brief Construct a new Gun Info object
 * 
 * @param x x position of the text (right aligned)
 * @param y y position of the text (top aligned)
 * @param parent parent graphics object
 */
GunInfo::GunInfo(double x, double y, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    this->setPos(x, y);
    font = new QFont("Helvetica Neue", 20);
    fm = new QFontMetrics(*font);
    weaponType = new QGraphicsTextItem(this);
    weaponType->setFont(*font);
    
    ammoCount = new QGraphicsTextItem(this);
    ammoCount->setFont(*font);

    healthPackCount = new QGraphicsTextItem(this);
    healthPackCount->setFont(*font);
    healthPackCount->setDefaultTextColor(QColor(255, 0, 0));

    shieldPackCount = new QGraphicsTextItem(this);
    shieldPackCount->setFont(*font);
    shieldPackCount->setDefaultTextColor(QColor(0, 0, 255));
}

/**
 * @brief Destroy the Gun Info object
 * 
 */
GunInfo::~GunInfo() {
    delete font;
    delete fm;
    delete weaponType;
    delete ammoCount;
}

/**
 * @brief update the text to reflect the gun stats
 * 
 * @param gun 
 */
void GunInfo::updatePlayerInformation(Player *p) {
    QString type = QString::fromStdString(p->getSelectedGun()->getGunType());
    weaponType->setPlainText(type);
    weaponType->setPos(200 - fm->horizontalAdvance(type), 0);

    QString count("");
    count.append(QString::number(p->getSelectedGun()->getCurrentMagazineCapacity()));
    count.append("/");
    count.append(QString::number(p->getSelectedGun()->getAmmoCount()));
    ammoCount->setPlainText(count);
    ammoCount->setPos(200 - fm->horizontalAdvance(count), fm->height() + 10);

    QString numHealthPacks = QString::number(p->getInventory()->getHealthAmount());
    numHealthPacks.append(" Medkit");    
    healthPackCount->setPlainText(numHealthPacks);
    healthPackCount->setPos(10, 2 * fm->height() + 10);

    QString numShieldPacks = QString::number(p->getInventory()->getShieldAmount());
    numShieldPacks.append(" Shield");
    shieldPackCount->setPlainText(numShieldPacks);
    shieldPackCount->setPos(10, 3 * fm->height() + 10);
    
}

