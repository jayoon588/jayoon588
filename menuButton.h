/**
 * @file menuButton.h
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief File for MenuButton class
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MY_MENU_BUTTON_HEADER
#define MY_MENU_BUTTON_HEADER
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QFont>
#include <QFontMetrics>
#include <QRectF>
#include <iostream>
/**
 *  @class MenuButton
 *  @brief Class for making menu buttons for the main menu
 * 
 */
class MenuButton : public QGraphicsItemGroup {
    public:
    explicit MenuButton(double, double, double, double, QString, QGraphicsItem *parent = nullptr);
    ~MenuButton();
    void setText(QString);
    QRectF getRect();
    virtual void setRect(double, double, double, double);
    void setFont(QFont);
    bool pointCollision(double, double);
    private:
    QGraphicsRectItem *buttonBox;
    QGraphicsTextItem *buttonText;
    QFont font;
};

#endif