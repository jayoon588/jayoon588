#include "scene.h"
#include <chrono>
/**
 * @brief Construct a new Scene object, and set the game state to 0 (main menu)
 * 
 * @param parent Parent object (optional)
 */
Scene::Scene(QObject *parent) : QGraphicsScene(parent) {
    startTimer(17);
    switchGameState(0);
}

/**
 * @brief Destroy the Scene object
 * 
 */
Scene::~Scene() {
    if (gameState == 0) {
        delete mainMenu;
    } else if (gameState == 1) {
        delete mainGame;
    } else if (gameState == 2) {
        delete LBMenu;
    } else if (gameState == 3) {
        delete deadScreen;
    }
}

/**
 * @brief Change the game state between game and main menu
 * 
 * @param state Number of the state you want to switch to 0=main menu, 1=game
 */
void Scene::switchGameState(int state) {
    gameState = state;
    if (state == 0) {
        mainMenu = new MainMenu();
        this->addItem(mainMenu);
        if (mainGame != nullptr) {
            this->removeItem(mainGame);
            delete mainGame;
            mainGame = nullptr;
        }
        if (LBMenu != nullptr) {
            this->removeItem(LBMenu);
            delete LBMenu;
            LBMenu = nullptr;
        }
        
    } else if (state == 1) {
        mainGame = new MainGame();
        this->addItem(mainGame);
        if (mainMenu != nullptr) {
            this->removeItem(mainMenu);
            delete mainMenu;
            mainMenu = nullptr;
        }
        if (LBMenu != nullptr) {
            this->removeItem(LBMenu);
            delete LBMenu;
            LBMenu = nullptr;
        }
        
    } else if (state == 2) {
        LBMenu = new LeaderboardMenu();
        this->addItem(LBMenu);
        if (mainGame != nullptr) {
            this->removeItem(mainGame);
            delete mainGame;
            mainGame = nullptr;
        }
        if (mainMenu != nullptr) {
            this->removeItem(mainMenu);
            delete mainMenu;
            mainMenu = nullptr;
        }
        
    } else if (state == 3) {
        deadScreen = new DeathScreen(finalScore);
        if (mainGame != nullptr) {
            this->removeItem(mainGame);
            delete mainGame;
            mainGame = nullptr;
        }
        if (mainMenu != nullptr) {
            this->removeItem(mainMenu);
            delete mainMenu;
            mainMenu = nullptr;
        }
        if (LBMenu != nullptr) {
            this->removeItem(LBMenu);
            delete LBMenu;
            LBMenu = nullptr;
        }
        switchGameState(0);
    }

}

/**
 * @brief Timer for running the game loop at a regular interval
 * 
 * @param event Event provided by Qt
 */
void Scene::timerEvent(QTimerEvent *event) {
    bool debugTime = false;
    auto start = std::chrono::high_resolution_clock::now();
    if (debugTime) {
        std::cerr << "Loop start: " << ((double)((std::chrono::duration_cast<std::chrono::microseconds>(start.time_since_epoch()).count()) % 100000)) / 1000 << "ms ";
    }
    if (gameState == 1) {
        finalScore = mainGame->gameLoop();
        //after player dies, switch state to death screen
        if (finalScore >= 0){
            switchGameState(3);
        }
    } else if(gameState == 0){
        int temp = 0;
        temp = mainMenu->menuLoop();
        if (temp == 1 || temp == 2){
            switchGameState(temp);
        } else if (temp == 3) {
            qApp->quit();
        }
    } else if (gameState == 2){
        int temp = 2;
        temp = LBMenu->leaderboardLoop();
        if (temp == 0){
            switchGameState(temp);
        }
    } 
    QGraphicsScene::timerEvent(event);
    auto stop = std::chrono::high_resolution_clock::now();
    if (debugTime) {
        std::cerr << "Loop took: " << (double) (std::chrono::duration_cast<std::chrono::microseconds>(stop - start)).count()/1000 << "ms" << std::endl;
    }
}