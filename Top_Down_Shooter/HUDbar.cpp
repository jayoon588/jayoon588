/**
 * @file HUDbar.cpp
 * @author Jacob Yoon (jyoon88@uwo.ca), Evan Goldrick (egoldric@uwo.ca)
 * @brief This display the health
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "HUDbar.h"

/**
 * @brief Construct a new HUDbar::HUDbar object
 * 
 * @param x x position of the bar (left side) 
 * @param y y position of the bar (top)
 * @param length length of the bar
 * @param height height of the bar
 * @param startingValue the initial value that the bar should display
 * @param maxValue the maximum value the bar can hold
 * @param parent 
 */
HUDbar::HUDbar(double x, double y, double length, double height, double startingValue, double maxValue, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    setPos(x, y);
    this->length = length;
    max_value = maxValue;
    current_value = startingValue;
    backgroundBar = new QGraphicsRectItem(0, 0, length, height, this);
    backgroundBar->setBrush(QBrush(QColor(0,0,0,100)));
    bar = new QGraphicsRectItem(0, 0, 0, height, this);
    setCurrent(startingValue);
}

/**
 * @brief gets the current amount the bar is filled
 * 
 * @return int 
 */
int HUDbar::getCurrent(){
    return current_value;
}

/**
 * @brief Sets the brush used to show the bar itself
 * 
 * @param b 
 */
void HUDbar::setColor(QBrush b) {
    bar->setBrush(b);
}

/**
 * @brief Sets the brush used to paint the background bar
 * 
 * @param b 
 */
void HUDbar::setBackColor(QBrush b) {
    backgroundBar->setBrush(b);
}

/**
 * @brief Set a new current value for the bar
 * 
 * @param a 
 */
void HUDbar::setCurrent(double a){
    current_value = a;
    bar->setRect(0, 0, length*(std::min(max_value, std::max(0.0, current_value))/max_value), bar->rect().height());
}

/**
 * @brief Set a new maximum value that the bar can display
 * 
 * @param a 
 */
void HUDbar::setMax(double a){
    max_value = a;
}

/**
 * @brief method for resizing the HUD bar
 * 
 * @param width new width of HUD bar
 * @param height new height of HUD bar
 */
void HUDbar::resize(double width, double height) {
    length = width;
    backgroundBar->setRect(0, 0, width, height);
    bar->setRect(0, 0, length * (std::min(max_value, std::max(0.0, current_value))/max_value), height);
}