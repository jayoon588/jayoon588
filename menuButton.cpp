/**
 * @file menuButton.cpp
 * @author Evan Goldrick (egoldric@uwo.ca)
 * @brief Implementation of MenuButton
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "menuButton.h"

/**
 * @brief Construct a new MenuButton object
 * 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @param text the text displayed on the button
 * @param parent the parent object (optional)
 */
MenuButton::MenuButton(double x, double y, double width, double height, QString text, QGraphicsItem *parent) : QGraphicsItemGroup(parent) {
    buttonBox = new QGraphicsRectItem(this);

    buttonText = new QGraphicsTextItem(text, this);
    font = QFont("Helvetica Neue", 40);
    buttonText->setFont(font);

    setRect(x, y, width, height);
}

/**
 * @brief Destroy the MenuButton object
 * 
 */
MenuButton::~MenuButton() {
    delete buttonBox;
    delete buttonText;
}

/**
 * @brief Change the text in the button
 * 
 * @param str New text
 */
void MenuButton::setText(QString str) {
    buttonText->setPlainText(str);
}

/**
 * @brief Get a QRectF that is the size and position of the button
 * 
 * @return QRectF 
 */
QRectF MenuButton::getRect() {
    return buttonBox->rect();
}

/**
 * @brief sets the rectangle surrounding the text for the button
 * 
 * @param x pos of button
 * @param y pos of button
 * @param w width of box
 * @param h height of box
 */
void MenuButton::setRect(double x, double y, double w, double h) {
    QFontMetrics fm(font);
    double textWidth = fm.horizontalAdvance(buttonText->toPlainText());
    double textHeight = fm.height();
    buttonBox->setRect(x, y, w, h);
    buttonText->setPos((x + (w / 2)) - (textWidth / 2), y + (h / 2) - (textHeight / 2));
}
/**
 * @brief Check if a point (usually the mouse) collides with the button
 * 
 * @param x 
 * @param y 
 * @return true Point inside button area
 * @return false Point outside button area
 */
bool MenuButton::pointCollision(double x, double y) {
    //printf("Button Pos: x%lf, y%lf, w%lf, h%lf Mouse Pos: x%lf, y%lf\n", getRect().x(), getRect().y(), getRect().width(), getRect().height(), x, y);
    return x > getRect().x() && x < getRect().x() + getRect().width() && y > getRect().y() && y < getRect().y() + getRect().height();
}
//isundermouse()
