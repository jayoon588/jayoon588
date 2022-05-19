/**
 * @file mainGame.cpp
 * @author Evan Goldrick (egoldric@uwo.ca), Curtis Ackland (cacklan@uwo.ca), David Lin (dlin72@uwo.ca)
 * @brief Implementations of MainGame member functions
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "mainGame.h"
/**
 * @brief Construct a new MainGame object for storing everything about the game state
 * 
 * @param parent parent object (optional)
 */
MainGame::MainGame(QGraphicsItem* parent)
    : QGraphicsItemGroup(parent)
{
    map = new Map(102, 102, this);
    map->setZValue(-100);
    hud = new HUD(this);
    hud->setZValue(100);
    p1 = new Player(70, 70, 0, this);
    playerHitbox = p1->getPlayerHitBox()/2;
    p1->setZValue(1);

    p1->setSelectedGun(1);
    
    // Generate spawnable tiles
    spawnableTiles.clear();
    for (int x = 0; x < map->getMapWidth(); ++x) {
        for (int y = 0; y < map->getMapLength(); y++) {
            if (map->getMap()[x][y]->getWalkable()) {
                std::vector<int> *v = new std::vector<int>;
                v->push_back(x);
                v->push_back(y);
                spawnableTiles.push_back(v);
            }
        }
    }

    for (int i = 0; i < Drop::DropTypes::ENUM_END; ++i) {
        for (int j = 0; j < 4; ++j) {
            spawnDrop((Drop::DropTypes) i);
        }
    }
    
}
/**
 * @brief Destroy the MainGame object
 * 
 */
MainGame::~MainGame()
{
}

/**
 * @brief spawns enemies based on wave
 * 
 * @param wave current wave
 * @param enemies list to add enemies
 */
void MainGame::SpawnEnemies(int wave, std::list<Enemy*>& enemies){

    //perform some sort of algorithm with wave to produce number of enemies
    int enemyAmount = (4 * wave);

    //spawn locations of enemies
    int xLocation, yLocation;

    //radius in which the enemies will spawn from the player
    int radius = 400 + (200 * wave);

    //prevents radius from going beyond map size
    if (radius > 4800){
        radius = 4800;
    }

    //positions of the window borders
    int leftBorder = (p1->pos().x() - (View::instance().getAdjustedWindowWidth()/2));
    int rightBorder = (p1->pos().x() + (View::instance().getAdjustedWindowWidth()/2));
    int topBorder = (p1->pos().y() - (View::instance().getAdjustedWindowHeight()/2));
    int bottomBorder = (p1->pos().y() + (View::instance().getAdjustedWindowHeight()/2));

    for (int i = 0 ; i < enemyAmount ; i++){

        int location = std::experimental::randint(0, 7);

        if (location <= 2){
            xLocation = std::experimental::randint(leftBorder - radius, leftBorder);
            yLocation = std::experimental::randint(topBorder - radius, bottomBorder + radius);
        }
        else if ((location > 2) && (location <= 5)){
            xLocation = std::experimental::randint(rightBorder, rightBorder + radius);
            yLocation = std::experimental::randint(topBorder - radius, bottomBorder + radius);
        }
        else if (location == 6){
            xLocation = std::experimental::randint(leftBorder, rightBorder);
            yLocation = std::experimental::randint(topBorder - radius, topBorder);
        }
        else{
            xLocation = std::experimental::randint(leftBorder, rightBorder);
            yLocation = std::experimental::randint(bottomBorder, bottomBorder + radius);
        }

        //if enemy spawn location is outside map, flip the spawn location in reference to player location
        if (xLocation < 0){
            xLocation = xLocation + (2*radius) + 1280;
        }
        if (xLocation > 5000){
            xLocation = xLocation - (2*radius) - 1280;
        }
        if (yLocation < 0){
            yLocation = yLocation + (2*radius) + 720;
        }
        if (yLocation > 5000){
            yLocation = yLocation - (2*radius) - 720;
        }

        //spawns enemy
        
        if (i % 4 == 0) {
            enemies.push_back(new Enemy("Brute", xLocation, yLocation, -45, 500, 10, 2, 70, this));
        } else {
            enemies.push_back(new Enemy("Grunt", xLocation, yLocation, -45, 100, 5, 2, 50, this));
        }

    }

}

void MainGame::Explosion(double bulletX, double bulletY, std::list<Enemy*>& enemies){

    //radius of explosion
    double radius = 60;

    //range of explosion in respect of bullet position
    double leftRange = bulletX - radius;
    double rightRange = bulletX + radius;
    double topRange = bulletY - radius;
    double bottomRange = bulletY + radius;

    for (Enemy* e: enemies){

        double enemyX = e->pos().x();
        double enemyY = e->pos().y();

        if ((enemyX >= leftRange) && (enemyX <= rightRange) && (enemyY >= topRange) && (enemyY <= bottomRange)){

            e->hit(70);

        }

    }

}

void MainGame::spawnDrop(Drop::DropTypes dropType) {
    std::vector<int> *tileLocation = nullptr;
    int loops = 0;
    int maxLoops = map->getMapWidth() * map->getMapLength();
    bool itemCanSpawn = false;
    while (!itemCanSpawn && loops++ < maxLoops) {
        tileLocation = spawnableTiles[std::rand() % spawnableTiles.size()];
        itemCanSpawn = true;
        
        for (Drop *d : drops) {
            if ((int) d->pos().x() == (*tileLocation)[0] * 50 + 25 && (int) d->pos().y() == (*tileLocation)[1] * 50 + 25) {
                //std::cerr << "DROP SPAWN COLLISION";
                itemCanSpawn = false;
            }
        }
    };
    if (itemCanSpawn && tileLocation != nullptr) {
        drops.push_back(new Drop((*tileLocation)[0] * 50 + 25, (*tileLocation)[1] * 50 + 25, dropType, this));
    }
}

/**
 * @brief Game loop for doing calculations each "frame" of the game
 * 
 */
int MainGame::gameLoop()
{
    // Player rotation based on mouse coords
    p1->setRotation(180 - ((atan2(View::instance().getPos().x() - View::instance().getAdjustedWindowWidth()/2, View::instance().getPos().y() - View::instance().getAdjustedWindowHeight()/2) / M_PI) * 180));

    // Shooting bullets based on mouse clicks
    if (View::instance().getMouseDown()) {
        if (p1->getSelectedGun()->getCurrentMagazineCapacity() != 0 && p1->getSelectedGun()->getReloadTimeLeft() == 0 && p1->getSelectedGun()->getFireRateCD() == 0) {
            double hyp = sqrt(pow(p1->getSelectedGun()->getGunModel()->boundingRect().size().width()/2 - playerHitbox, 2) + pow(-p1->getSelectedGun()->getGunModel()->boundingRect().size().height() - playerHitbox, 2));
            double angle = 180 - (atan2(p1->getSelectedGun()->getGunModel()->boundingRect().size().width()/2 - playerHitbox, -p1->getSelectedGun()->getGunModel()->boundingRect().size().height() - playerHitbox)/M_PI) * 180;
            double newX = p1->pos().x() + (hyp * sin(((p1->rotation() + angle)*M_PI)/180));
            double newY = p1->pos().y() - (hyp * cos(((p1->rotation() + angle)*M_PI)/180));
            bullets.push_back(new Bullet(newX, newY, View::instance().getPos().x() - View::instance().getAdjustedWindowWidth()/2, View::instance().getPos().y() - View::instance().getAdjustedWindowHeight()/2, p1->getSelectedGun()->getGunType(), p1->getSelectedGun()->getGunDamage(), this));
            p1->getSelectedGun()->setCurrentMagazineCapacity(p1->getSelectedGun()->getCurrentMagazineCapacity() - 1);
            p1->getSelectedGun()->setFireRateCD(p1->getSelectedGun()->getFireRate());
            //QSound::play("resources/sounds/pew.wav");
        }
    }

    // Player movement using WASD
    // TODO - make movement speed based on player class
    double xVel = 0;
    double yVel = 0;
    if (View::instance().getKey().count(Qt::Key_W)) {
        yVel--;
    }
    if (View::instance().getKey().count(Qt::Key_A)) {
        xVel--;
    }
    if (View::instance().getKey().count(Qt::Key_S)) {
        yVel++;
    }
    if (View::instance().getKey().count(Qt::Key_D)) {
        xVel++;
    }
    if(xVel != 0 || yVel != 0){
        int px = round(p1->pos().x() + p1->getSpeed() * xVel/sqrt(xVel * xVel + yVel * yVel));
        int py = round(p1->pos().y() + p1->getSpeed() * yVel/sqrt(xVel * xVel + yVel * yVel));

        if((!map->getMap()[(int) floor(( (px) + playerHitbox)/50)][(int) floor(((py) + playerHitbox)/50)]->getWalkable()
         || !map->getMap()[(int) floor(( (px) + -playerHitbox)/50)][(int) floor(((py) + playerHitbox)/50)]->getWalkable()
         || !map->getMap()[(int) floor(( (px) + playerHitbox)/50)][(int) floor(((py) + -playerHitbox)/50)]->getWalkable()
         || !map->getMap()[(int) floor(( (px) + -playerHitbox)/50)][(int) floor(((py) + -playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(((int) (px) + -playerHitbox)/50)][(int) floor(((int) (py) + -playerHitbox)/50)]){
            if(xVel < 0 && yVel < 0){ // player travelling up-left
                if((!map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor((p1->pos().y() - playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor((p1->pos().y() + playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(p1->pos().x()/50)][(int) floor(((int) (py) - playerHitbox)/50)]->getWalkable()){
                    p1->setPos(p1->pos().x(), py);
                } else if((!map->getMap()[(int) floor((p1->pos().x() + playerHitbox)/50)][(int) floor(((int) (py) - playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor((p1->pos().x() - playerHitbox)/50)][(int) floor(((int) (py) - playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor(p1->pos().y()/50)]->getWalkable()){
                    p1->setPos(px, p1->pos().y());
                }
            } else if(xVel > 0 && yVel < 0){ // player travelling up-right
                if((!map->getMap()[(int) floor(((int) (px) + playerHitbox)/50)][(int) floor((p1->pos().y() - playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor(((int) (px) + playerHitbox)/50)][(int) floor((p1->pos().y() + playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(p1->pos().x()/50)][(int) floor(((int) (py) - playerHitbox)/50)]->getWalkable()){
                    p1->setPos(p1->pos().x(), py);
                } else if((!map->getMap()[(int) floor((p1->pos().x() + playerHitbox)/50)][(int) floor(((int) (py) - playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor((p1->pos().x() - playerHitbox)/50)][(int) floor(((int) (py) - playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor(p1->pos().y()/50)]->getWalkable()){
                    p1->setPos(px, p1->pos().y());
                }
            } else if(xVel < 0 && yVel > 0){ // player travelling down-left
                if((!map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor((p1->pos().y() - playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor((p1->pos().y() + playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(p1->pos().x()/50)][(int) floor(((int) (py) + playerHitbox)/50)]->getWalkable()){
                    p1->setPos(p1->pos().x(), py);
                } else if((!map->getMap()[(int) floor((p1->pos().x() + playerHitbox)/50)][(int) floor(((int) (py) + playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor((p1->pos().x() - playerHitbox)/50)][(int) floor(((int) (py) + playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(((int) (px) - playerHitbox)/50)][(int) floor(p1->pos().y()/50)]->getWalkable()){
                    p1->setPos(px, p1->pos().y());
                }
            } else if(xVel > 0 && yVel > 0){ // player travelling down-right
                if((!map->getMap()[(int) floor(((int) (px) + playerHitbox)/50)][(int) floor((p1->pos().y() - playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor(((int) (px) + playerHitbox)/50)][(int) floor((p1->pos().y() + playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(p1->pos().x()/50)][(int) floor(((int) (py) + playerHitbox)/50)]->getWalkable()){
                    p1->setPos(p1->pos().x(), py);
                } else if((!map->getMap()[(int) floor((p1->pos().x() + playerHitbox)/50)][(int) floor(((int) (py) + playerHitbox)/50)]->getWalkable() || !map->getMap()[(int) floor((p1->pos().x() - playerHitbox)/50)][(int) floor(((int) (py) + playerHitbox)/50)]->getWalkable()) && map->getMap()[(int) floor(((int) (px) + playerHitbox)/50)][(int) floor(p1->pos().y()/50)]->getWalkable()){
                    p1->setPos(px, p1->pos().y());
                }
            } 
        } else {
            p1->setPos(px, py);
        }
        
        
    }

    if (View::instance().getKey().count(Qt::Key_1)) {
        p1->setSelectedGun(1);
    }
    if (View::instance().getKey().count(Qt::Key_2)) {
        p1->setSelectedGun(2);
    }

    if (View::instance().getKey().count(Qt::Key_3) && !consumedKeys.count(Qt::Key_3) && p1->getInventory()->getHealthAmount() > 0) {
        consumedKeys.insert(Qt::Key_3);
        p1->setHealth(p1->getHealth() + 50); // TODO make the values not hard coded
        p1->getInventory()->setHealthAmount(p1->getInventory()->getHealthAmount() - 1);
    } else if (!View::instance().getKey().count(Qt::Key_3) && consumedKeys.count(Qt::Key_3)) {
        consumedKeys.erase(Qt::Key_3);
    }

    if (View::instance().getKey().count(Qt::Key_4) && !consumedKeys.count(Qt::Key_4) && p1->getInventory()->getShieldAmount() > 0) {
        consumedKeys.insert(Qt::Key_4);
        p1->setShield(p1->getShield() + 50);
        p1->getInventory()->setShieldAmount(p1->getInventory()->getShieldAmount() - 1);
    } else if (!View::instance().getKey().count(Qt::Key_4) && consumedKeys.count(Qt::Key_3)) {
        consumedKeys.erase(Qt::Key_4);
    }

    if ((View::instance().getKey().count(Qt::Key_R) || p1->getSelectedGun()->getCurrentMagazineCapacity() == 0)
        && p1->getSelectedGun()->getCurrentMagazineCapacity() != p1->getSelectedGun()->getMaxMagazineCapacity()
        && p1->getSelectedGun()->getReloadTimeLeft() == 0
        && p1->getSelectedGun()->getAmmoCount() != 0) {
        p1->getSelectedGun()->setReloadTimeLeft(p1->getSelectedGun()->getReloadSpeed());
    }

    // Drop pickup logic

    if (View::instance().getKey().count(Qt::Key_F)) {
        for (Drop* d : drops) {
            if (p1->collidesWithItem(d)) {
                drops.remove(d);
                spawnDrop(d->getDropType());
                if (d->getDropType() == Drop::DropTypes::Shield) {
                    p1->getInventory()->setShieldAmount(p1->getInventory()->getShieldAmount() + 1);
                } else if (d->getDropType() == Drop::DropTypes::Health) {
                    p1->getInventory()->setHealthAmount(p1->getInventory()->getHealthAmount() + 1);
                } else if (d->getDropType() == Drop::DropTypes::Pistol) {
                    Gun *oldGun = p1->getSelectedGun();
                    p1->setSelectedGunObj(new Gun("Pistol", p1->getPlayerHitBoxRect(), p1));
                    delete oldGun;
                } else if (d->getDropType() == Drop::DropTypes::AR) {
                    Gun *oldGun = p1->getSelectedGun();
                    p1->setSelectedGunObj(new Gun("AR", p1->getPlayerHitBoxRect(), p1));
                    delete oldGun;
                } else if (d->getDropType() == Drop::DropTypes::Laser) {
                    Gun *oldGun = p1->getSelectedGun();
                    p1->setSelectedGunObj(new Gun("Laser", p1->getPlayerHitBoxRect(), p1));
                    delete oldGun;
                } else if (d->getDropType() == Drop::DropTypes::RocketLauncher) {
                    Gun *oldGun = p1->getSelectedGun();
                    p1->setSelectedGunObj(new Gun("RL", p1->getPlayerHitBoxRect(), p1));
                    delete oldGun;
                } else if (d->getDropType() == Drop::DropTypes::PistolAmmo) { // TODO set ammo amount
                    if (p1->hasGunType("Pistol") == 1) {
                        p1->getInventory()->getGunPrim()->setAmmoCount(std::min(p1->getInventory()->getGunPrim()->getAmmoCount() + p1->getInventory()->getGunPrim()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunPrim()->getMaxAmmoCapacity()));
                    } else if (p1->hasGunType("Pistol") == 2) {
                        p1->getInventory()->getGunSec()->setAmmoCount(std::min(p1->getInventory()->getGunSec()->getAmmoCount() + p1->getInventory()->getGunSec()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunSec()->getMaxAmmoCapacity()));
                    }
                } else if (d->getDropType() == Drop::DropTypes::ARAmmo) {
                    if (p1->hasGunType("AR") == 1) {
                        p1->getInventory()->getGunPrim()->setAmmoCount(std::min(p1->getInventory()->getGunPrim()->getAmmoCount() + p1->getInventory()->getGunPrim()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunPrim()->getMaxAmmoCapacity()));
                    } else if (p1->hasGunType("AR") == 2) {
                        p1->getInventory()->getGunSec()->setAmmoCount(std::min(p1->getInventory()->getGunSec()->getAmmoCount() + p1->getInventory()->getGunSec()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunSec()->getMaxAmmoCapacity()));
                    }
                } else if (d->getDropType() == Drop::DropTypes::LaserAmmo) {
                    if (p1->hasGunType("Laser") == 1) {
                        p1->getInventory()->getGunPrim()->setAmmoCount(std::min(p1->getInventory()->getGunPrim()->getAmmoCount() + p1->getInventory()->getGunPrim()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunPrim()->getMaxAmmoCapacity()));
                    } else if (p1->hasGunType("Laser") == 2) {
                        p1->getInventory()->getGunSec()->setAmmoCount(std::min(p1->getInventory()->getGunSec()->getAmmoCount() + p1->getInventory()->getGunSec()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunSec()->getMaxAmmoCapacity()));
                    }
                } else if (d->getDropType() == Drop::DropTypes::RocketAmmo) {
                    if (p1->hasGunType("RL") == 1) {
                        p1->getInventory()->getGunPrim()->setAmmoCount(std::min(p1->getInventory()->getGunPrim()->getAmmoCount() + p1->getInventory()->getGunPrim()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunPrim()->getMaxAmmoCapacity()));
                    } else if (p1->hasGunType("RL") == 2) {
                        p1->getInventory()->getGunSec()->setAmmoCount(std::min(p1->getInventory()->getGunSec()->getAmmoCount() + p1->getInventory()->getGunSec()->getMaxAmmoCapacity() / 2, p1->getInventory()->getGunSec()->getMaxAmmoCapacity()));
                    }
                }
                delete d;
                break;
            }
        }
    }

    p1->cooldown();

    // Move enemies and perform collisions
    {
        std::list<Enemy*> deadEnemies;
        for (Enemy* e : enemies) {
            e->move(p1);
            e->attack(p1);
            
            
            if (p1->isDead()){
                return hud->getScore()->getScore();
            }

            e->cooldown();

            std::list<Bullet*> deadBullets;

            // collision of bullets with enemies
            for (Bullet* b : bullets) {
                if (b->collidesWithItem(e)) {
                    e->hit(b->getDamage());
                    if (b->getGunType() == "RL")
                        Explosion(b->pos().x(), b->pos().y(), enemies);
                    deadBullets.push_back(b);
                }
            }
            // delete collided bullets
            for (Bullet* b : deadBullets) {
                bullets.remove(b);
                delete b;
            }
            // check for dead enemies
            if (e->isDead()) {
                hud->getScore()->increaseScore(100);
                deadEnemies.push_back(e);
            }
        }

        
        // remove dead enemies
        for (Enemy* e : deadEnemies) {
            enemies.remove(e);
            delete e;
        }

    }

    //Bullet collisions with obstacles
    std::list<Bullet*> obstacleBullets;
    for (Bullet* b : bullets) {
        if(!map->getMap()[(int) floor(b->pos().x()/50)][(int) floor(b->pos().y()/50)]->getWalkable()){
            if (b->getGunType() == "RL")
                Explosion(b->pos().x(), b->pos().y(), enemies);
            obstacleBullets.push_back(b);
        }
    }
    for (Bullet* b : obstacleBullets) {
        bullets.remove(b);
        delete b;
    }
    
    for (Bullet* i : bullets) {
        i->moveBullet();
    }

    
    hud->getHealthBar()->setCurrent(p1->getHealth());
    hud->getShieldBar()->setCurrent(p1->getShield());
    hud->getReloadTimer()->setFraction((double)p1->getSelectedGun()->getReloadTimeLeft() / (double)p1->getSelectedGun()->getReloadSpeed());
    hud->getGunInfo()->updatePlayerInformation(p1);
    hud->setPos(p1->pos().x() - View::instance().getAdjustedWindowWidth()/2, p1->pos().y() - View::instance().getAdjustedWindowHeight()/2);
    View::instance().setSceneRect(QRectF(p1->pos().x() - View::instance().getAdjustedWindowWidth()/2, p1->pos().y() - View::instance().getAdjustedWindowHeight()/2, View::instance().getAdjustedWindowWidth(), View::instance().getAdjustedWindowHeight()));
    hud->resizeHud(View::instance().getAdjustedWindowWidth(), View::instance().getAdjustedWindowHeight()); // TODO check if this can be moved to a resize event handler function

    //execute when wave is cleared
    if (enemies.empty()){
        hud->getScore()->increaseWave();
        SpawnEnemies(hud->getScore()->getWave(), enemies);
    }

    return -1;

}
