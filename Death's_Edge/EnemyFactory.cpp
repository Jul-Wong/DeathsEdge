#include "EnemyFactory.hpp"




Enemy* EnemyFactory::create(const std::string& type) {
    if (type == "Goblin") {
        Enemy* enemy = new Enemy("Goblin", 30, 10, 5, 1, 15);
        //enemy->setSpritePath()
        enemy->setMaxHealth(30);
        enemy->setMaxMana(10);
        return enemy;
    }
    else if (type == "Skeleton") {
        Enemy* enemy = new Enemy("Skeleton", 40, 0, 7, 2, 25);
        enemy->setSpritePath("Sprites/Entities/Skeleton_Mob.png");
        enemy->setMaxHealth(40);
        enemy->setMaxMana(0);
        return enemy;
    }
    else if (type == "Slime") {
        Enemy* enemy = new Enemy("The Elusive Pink Slime", 45, 20, 9, 4, 30);
        enemy->setSpritePath("Sprites/Entities/Pink_Slime.png");
        enemy->setMaxHealth(45);
        enemy->setMaxMana(20);
        return enemy;
    }

    return nullptr;
}

Enemy* EnemyFactory::createRandom() {
    return nullptr;
}
