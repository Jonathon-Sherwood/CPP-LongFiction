#pragma once

#include <iostream> //Used to display messages to the console

using namespace std; //Global declaration to shorten many common commands throughout the code


//Classes		 
class Ship
{
protected:
	int startingHealth = 10;

public:
	Ship(int initializeHealth);
	virtual int TakeDamage(int damageTaken);
	int damage = 5;
	int* currentHealth = &startingHealth;
	bool isDead = false;
};

//Child Classe
class PlayerShip : public Ship 
{
private:
	int startingGold = 100;

public:
	PlayerShip(int health);
	int Loot(int lootGained);
	virtual int TakeDamage(int damageTaken);
	int* currentGold = &startingGold;
};

class EnemyShip : public Ship
{
public:
	EnemyShip(int health);
	void Greet();
};
					 

//Function prototypes
void Intro();
void FirstNameAsk(string startingName, string playerInput); //Converts the assume name without reference to player input
void SecondNameAsk(string& startingName, string playerInput); //Converts the assumed name's reference to the player's input
char Story(string story); //Adjustable function for different story elements
bool DeathCheck(int currentHealth); //Ends game on current health dropping to 0
void Scenario1(); //Holds all functions for the first scenario in the story
void Scenario2(); //Holds all functions for the second scenario in the story
void Scenario3(); //Holds all functions for the third scenario in the story
void Scenario4(); //Holds all functions for the fourth scenario in the story

