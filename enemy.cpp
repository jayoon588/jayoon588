/**
 * @file enemy.cpp
 * @author David Lin (dlin72@uwo.ca) Evan Goldrick (egoldric@uwo.ca)
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "enemy.h"

/**
 * @brief constructor initializes position and direction of enemy
 * @param name name of enemy
 * @param initialX initial x pos
 * @param initialY initial y pos
 * @param initialD initial direction in radians
 * @param hp enemy health
 * @param dmg enemy damage
 * @param speed enemy movement speed
 * @param target Player class
 */
Enemy::Enemy(std::string name, double initialX, double initialY, double initialD, int hp, int damage, double speed, double attackRadius, QGraphicsItem * parent) : QGraphicsItemGroup (parent){
    if (name == "Grunt" || name == "Tank"){
        hitbox_size = 30;
    } else if (name == "Brute"){
        hitbox_size = 50;
    }
    enemy = new QGraphicsRectItem (-(hitbox_size/2), -(hitbox_size/2), hitbox_size, hitbox_size, this);
    this->setPos(initialX, initialY);
    enemy->setRotation(initialD);
    QPen outline;
    outline.setStyle(Qt::NoPen);
    enemy->setPen(outline);

    QTransform transform;
    transform.translate(-(hitbox_size/2), -(hitbox_size/2));

    QBrush brush;
    if (name == "Grunt"){
        brush.setTextureImage(QImage("resources/Grunt.png"));
    } else if (name == "Brute"){
        brush.setTextureImage(QImage("resources/Brute.png")); 
    } else if (name == "Tank"){
        brush.setTextureImage(QImage("resources/Tank.png")); 
    }
    brush.setTransform(transform);
    enemy->setBrush(brush);

    attackRange = new QGraphicsEllipseItem (-attackRadius, -attackRadius, attackRadius * 2, attackRadius * 2, this);
    attackRange->setPen(Qt::NoPen);

    maxHealth = hp;
    health = hp;
    this->damage = damage;
    movementSpeed = speed;
    this->attackRadius = attackRadius;
    healthBar = new HUDbar(-30, 25, 60, 10, 50, 100, this);
    healthBar->setColor(QBrush(QColor(255,0,0,200)));
    healthBar->setMax(maxHealth);
}
/**
 * @brief destructor
 */
Enemy::~Enemy(){

}

/**
 * @brief changes enemy location to chase the player
 * @param target player class that contains the player's location
 */
void Enemy::move(Player * target) {
    if (!isDead()) {
        double horizontal = target->pos().x() - pos().x(); 
        double vertical = target->pos().y() - pos().y();
        
        double normalization = 1/sqrt(horizontal * horizontal + vertical * vertical);
        
        horizontal = horizontal * normalization;
        vertical = vertical * normalization;

        enemy->setRotation(-180 * atan2(horizontal, vertical) / M_PI);
        setPos(pos().x() + horizontal * movementSpeed, pos().y() + vertical * movementSpeed);
    }
}

/**
 * @brief determines collision with player
 * @param target player
 */
bool Enemy::inRange(Player* target){
    return target->collidesWithItem(attackRange);
}

/**
 * @brief function for the enemy to attack player 
 * @param target player
 */
void Enemy::attack(Player *target){
    if (attackCdTimeleft == 0){
        if (inRange(target)){
            target->hit(damage);
            attackCdTimeleft = attackCdFullTime;
        }
    }
}

/**
 * @brief checks if the enemy is colliding with the passed object
 * @param other object that is checking collision with
 * @param mode specifies the type of collision
 * @return true if there is a collision
 * @return false if there is no collision
 */
bool Enemy::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    return enemy->collidesWithItem(other, mode);
}

/**
 * @brief takes away from enemy's health when called, dies when health reaches 0
 * @param dmg the amount that is taken away
 */
void Enemy::hit(int dmg){
    health = health - dmg;
}


/**
 * @brief gets the enemy's health
 * @return the enemy's health
 */
int Enemy::getHealth(){
    return health;
}

/**
 * @brief Function to check if the enemy is dead based on its current health
 * 
 * @return true the enemy's health is less than or equal to 0
 * @return false the enemy's health is greater than 0
 */
bool Enemy::isDead() {
    return health <= 0;
}

/**
 * @brief change the time it takes to cool down an attack
 * 
 * @param cd new cooldown value
 */
void Enemy::setCooldownLength(int cd) {
    attackCdFullTime = cd;
}

/**
 * @brief cools down abilities
 * 
 */
void Enemy::cooldown() {
    // Cooldown timers
    if (attackCdTimeleft > 0) {
        --attackCdTimeleft;
    } else {
        attackCdTimeleft = 0;
    }

    // 
    healthBar->setCurrent(health);
}

QPainterPath Enemy::shape() const {
    return enemy->shape();
}