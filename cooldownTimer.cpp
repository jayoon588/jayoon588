/**
 * @file cooldownTimer.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of CooldownTimer
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "cooldownTimer.h"

/**
 * @brief Construct a new Cooldown Timer object
 * 
 * @param x x position of the timer
 * @param y y position of the timer
 * @param w width of the timer
 * @param h height of the timer
 * @param parent parent object
 */
CooldownTimer::CooldownTimer(double x, double y, double w, double h, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    pie = new QGraphicsEllipseItem(0, 0, w, h, this);
    pie->hide();
    this->setPos(x, y);
    pie->setStartAngle(0);
    pie->setSpanAngle(frac * 360 * 16);
}

/**
 * @brief Destroy the Cooldown Timer object
 * 
 */
CooldownTimer::~CooldownTimer() {
    delete pie;
}

/**
 * @brief set the amount that the pie should be filled
 * 
 * @param frac number between 0 and 1
 */
void CooldownTimer::setFraction(double frac)  {
    this->frac = frac;
    if (frac == 0) {
        pie->hide();
    } else {
        pie->setSpanAngle(frac * 360 * 16);
        pie->show();
    }
}

/**
 * @brief get the amoutn that the pie is filled
 * 
 * @return double 
 */
double CooldownTimer::getFraction() {
    return frac;
}

/**
 * @brief setting to hide the pie if the pie is not filled
 * 
 * @param h true means the pie will hide when fraction is zero, false means it is always visible
 */
void CooldownTimer::setHideOnZero(bool h) {
    hideOnZero = h;
}

/**
 * @brief set color of bullet
 * 
 * @param b 
 */
void CooldownTimer::setColor(QBrush b) {
    pie->setBrush(b);
}