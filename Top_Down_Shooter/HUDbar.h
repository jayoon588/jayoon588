/**
 * @file HUDbar.h
 * @author Jacob Yoon (jyoon88@uwo.ca), Evan Goldrick (egoldric@uwo.ca)
 * @brief This display the HUD
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef HUDBAR_H
#define HUDBAR_H
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QBrush>
#include <QColor>
#include <algorithm>

/**
 * @class HUDbar
 * @brief A progress bar style bar implemented in QGraphics
 * 
 */
class HUDbar: public QGraphicsItemGroup {
    public: HUDbar(double, double, double, double, double, double, QGraphicsItem * parent = nullptr);

    int getCurrent();

    void setCurrent(double a);

    void setMax(double a);

    void setColor(QBrush);

    void setBackColor(QBrush);

    void resize(double, double);

    private:
    double max_value;
    double current_value;
    double length;
    QGraphicsRectItem *bar;
    QGraphicsRectItem *backgroundBar;
};
#endif