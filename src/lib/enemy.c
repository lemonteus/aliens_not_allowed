#include <stdbool.h>
#include <stdlib.h>

#include "enemy.h"

Vector2D *enemy_projectiles;

Enemy *enemy_enemiesLvl01;
Enemy *enemy_enemiesLvl02;

bool enemy_reset = true;
unsigned int numberOfEnemiesCreated;

enum enemy_stage {stage01 = 1, stage02, final};
enum enemy_stage enemy_currentStage;

void enemy_update(){
    if(enemy_reset)
        enemy_internal_initialize();

    enemy_internal_organizeEnemiesByID();

    //(re)desenhar inimigos
    enemy_internal_updateProjectiles();

    // calcular chance de realziar tiro e atirar
    // enemy_internal_shoot(unsigned int enemyID);

    enemy_intenal_updateEnemiesPositions();
}

Vector2D* enemy_getProjectiles(){
    return enemy_projectiles;
}

// update enemies health Points
void enemy_gotHit(unsigned int enemyID, unsigned int attackPoints);

// Concat all enemies' arrays in ascending order and return it
Enemy* enemy_getEnemies(){
    int sizeArrayEnemiesLvl01 = sizeof(enemy_enemiesLvl01);
    int sizeArrayEnemiesLvl02 = sizeof(enemy_enemiesLvl02);
    int numberOfEnemies = sizeArrayEnemiesLvl01 + sizeArrayEnemiesLvl02;

    Enemy *enemies = (Enemy *) malloc(sizeof(Enemy) * numberOfEnemies);

    for(int i = 0, indexLvl02 = 0; i < numberOfEnemies; i++){
        if (i < sizeArrayEnemiesLvl01)
            *(enemies + i) = *(enemy_enemiesLvl01 + i);
        else{
            *(enemies + i) = *(enemy_enemiesLvl02 + indexLvl02);
            indexLvl02++;
        }
    }
    return enemies;
}

void enemy_internal_initialize(){
    enemy_enemiesLvl01 = (Enemy *) realloc(enemy_enemiesLvl01, 0);
    enemy_enemiesLvl02 = (Enemy *) realloc(enemy_enemiesLvl02, 0);
    numberOfEnemiesCreated = 0;

    enum enemy_stage enemy_currentStage = stage01;

    enemy_internal_spawn();

    enemy_reset = false;
}

// necessário definir melhor método de ordenação para o caso
void enemy_internal_organizeEnemiesByID(); 

void enemy_internal_spawn();

//necessário definir padrões de movimento
void enemy_intenal_updateEnemiesPositions();

void enemy_internal_shoot(unsigned int enemyID);

//necessário definir padrões de movimento
void enemy_internal_updateProjectiles();
