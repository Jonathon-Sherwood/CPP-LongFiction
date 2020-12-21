#include "LongFiction.h" //Allows us to define the prototypes of our header

#include <iostream> //Used to display messages to the console
#include <string> //Allows for using string functions

using namespace std; //Global declaration to shorten many common commands throughout the code

//Initializes the Ship class
Ship::Ship(int initializeHealth) : 
	startingHealth(initializeHealth)
{}

//Initializes the EnemyShip Class
EnemyShip::EnemyShip(int initializeHealth) :
	Ship(startingHealth = initializeHealth)
{}

//Initializes the PlayerShip class
PlayerShip::PlayerShip(int initializeHealth) :
	Ship(startingHealth = initializeHealth)
{}

//Creates the function for taking damage on all ships
int Ship::TakeDamage(int damage)
{
	//Returns the lost amount of health after taking damage
	int health = *currentHealth -= damage;

	//Sets the individual object's death to be true 
	if (*currentHealth <= 0)
	{
		isDead = true;
	}
	return health;
}

//Unique function for the player damage
int PlayerShip::TakeDamage(int damage)
{
	//Subtracts health, then runs the function to see if that killed the player
	int health = *currentHealth -= damage;
	DeathCheck(health);
	return health;
}

//Allows the player to loot gold
int PlayerShip::Loot(int loot)
{
	int gold = *currentGold += loot;
	return gold;
}

//Gives the enemy ships a common greeting
void EnemyShip::Greet()
{
	cout << "Yar! A vessel full o' booty!\n";
	cout << "Prepare to be boarded!\n";
}

//Objects created from classes with set health
PlayerShip playerShip(30);
EnemyShip enemyShip(10);
EnemyShip skeletonShip(15);
EnemyShip massiveShip(20);

//Introduces the game and asks for name
void Intro()
{
	cout << "Welcome to Scallywags!\n\n";
	cout << "This is an interactive fiction that will have you making various decisions.\n";
	cout << "You will often be given a scenario where you must choose between two decisions.\n";
	cout << "You will type either 'a' or 'b' depending on your choice.\n";
	cout << "Choose wisely! You will either become a pirate legend..\n";
	cout << "Or be sent to Davy Jones' locker!\n";

	char response = Story("\nDo you understand?\nA: Yes.\nB: No.\n");

	if (response == 'a' || response == 'A')
	{
		cout << "Excellent! I had a good feeling about you.\n";
	}
	if (response == 'b' || response == 'B')
	{
		cout << "Too late! You're shovin' off!\n";
	}

	cout << "\n\nThis be a big day for you, Sailor.. err.. sailor..\n";

	//Sets an initial name for the player
	string playerName = "Steve";
	cout << "What's yer name? You look like a " << playerName <<"\n";

	string playerInput; //Takes in player input
	cin >> playerInput;

	//Runs the function that swaps names without a reference
	FirstNameAsk(playerName, playerInput);
	cout << "Wuzzat? You say it's " << playerName << "?\n";

	cin >> playerInput;
	//Runs the function that swaps names with references
	SecondNameAsk(playerName, playerInput);
	cout << "\nEh, " <<  playerName << " Sh" << playerName << ".\n";
	cout << "What's important Sh" << playerName << " is that you go find gold!\n";
	cout << "Right now, you have " << playerShip.Loot(0) << " gold. Lets find some more!\n\n\n";
}

//Takes in the original name and the players input without being a reference
void FirstNameAsk(string playerName, string playerInput)
{
	string temp = playerName;
	playerName = playerInput;
}

//Takes in the reference to the players original and new names and alters them
void SecondNameAsk(string& playerName, string playerInput)
{
	string temp = playerName;
	playerName = playerInput;
}

void Scenario1() //Tells the first part of the story
{
	cout << "Quickly approaching is another vessel.\n";
	cout << "They are flying a pirate flag! The captain shouts his greeting:\n";
	enemyShip.Greet();

	do {
		char response = Story("\n\nIt looks like they mean trouble. What do you do?\nA: Fire Cannons\nB: Try to negotiate\n");
		if (response == 'a' || response == 'A') //Deals damage to the enemy if they choose A
		{
			cout << "You fire your cannons, dealing " << playerShip.damage << " damage. The pirate ship has "
				<< enemyShip.TakeDamage(playerShip.damage) << " health left.\n";

			if (!enemyShip.isDead) //Stops the enemy from firing on death
			{
				cout << "The enemy pirates are enraged, firing their cannons back for " << enemyShip.damage << " damage.";
				cout << "You have " << playerShip.TakeDamage(enemyShip.damage) << " health left.";
			}
		}
		if (response == 'b' || response == 'B') //Deals damage to the player if they choose B
		{
			cout << "You plead your case. Unfortunately, pirates don't seem the caring type.\n";
			cout << "The pirates fire their cannons, dealing " << enemyShip.damage << " damage."; 
			cout << "Your ship has " << playerShip.TakeDamage(enemyShip.damage) << " health left.\n";
		}
	} while (!enemyShip.isDead); //ends the battle on enemy death
}

void Scenario2() //Tells the second part of the story
{
	cout << "\nWith a massive crash of waves the enemy ship sinks, leaving 100 gold behind!\n";
	cout << "You now have " << playerShip.Loot(100) << " gold!\n";

	cout << "\n\nIn front of your ship lies a huge chest on an island. It must be full of gold!\n";
	char response = Story("What do you do?\nA: Go to the island.\nB: Ignore it. It's probably evil.\n");

	if (response == 'a' || response == 'A') //Begins the figh
	{
		cout << "\nYou approach the island, hoping to open the treasure chest.";
		cout << "\nSuddenly, a skeleton pirate ship pops up near you!";
		do {
			char response = Story("\nWhat do you do?\nA: Fire cannons!\nB: Flee without the gold.\n");
			if (response == 'a' || response == 'A') //Loops the battle
			{
				cout << "You fire your cannons, dealing " << playerShip.damage << " damage. The skeleton ship has "
					<< skeletonShip.TakeDamage(playerShip.damage) << " health left.\n";

				if (!skeletonShip.isDead) //Stops the enemy from firing back on death
				{
					cout << "The skeletons fire their cannons, dealing " << skeletonShip.damage << " damage.";
					cout << "You have " << playerShip.TakeDamage(skeletonShip.damage) << " health left.";
				}
			}

			if (response == 'b' || response == 'B') //Deals damage to the player if they choose B
			{
				cout << "\nThe fight is too much! You chart a course away from the battle and escape.\n";

				//Ends the battle if the player flees
				break;
			}
		} while (!skeletonShip.isDead); //Loops the fight until the enemy is dead
	}
	if (response == 'b' || response == 'B') //Ends the scenario successfully if the player chooses option B
	{
		cout << "\nYou sail off. Just in case.\n";
	}
}

void Scenario3() //Tells the third part of the story
{
	if (skeletonShip.isDead) //Adds loot if the player sank the enemy ship
	{
		cout << "With the skeletons taken care of, you are free to retrieve the gold!\n";
		cout << "You earn a whopping 200 gold, putting you at " << playerShip.Loot(200) << " gold!\n";
	}

	cout << "\n\nContinuing on your way, you see a thunderstorm approaching.\n";
	char response = Story("What do you do?\nA: Sail through it!\nB: Sail around it.\n");

	if (response == 'a' || response == 'A') //Takes damage
	{

		cout << "\nYour ship is battered and bashed about by the sea, taking 10 damage.";
		cout << "\nYour ship is down to " << playerShip.TakeDamage(10);
	}
	if (response == 'b' || response == 'B') //Heals player
	{

		cout << "\nTaking the time to go around, you lose considerable amount of time.\n";
		cout << "However, you did have time to repair 5 health, leaving your ship at " << playerShip.TakeDamage(-5) << " health.\n";
	}
}

void Scenario4() //Tells the fourth part of the story
{
	cout << "\n\nA massive ship is on the horizon.\n";
	char response = Story("What do you do?\nA: Chase it down.\nB: Go home, it's been a rough day.\n");

	if (response == 'a' || response == 'A') //Starts battle
	{
		cout << "\nThe ship seems to be carrying lots of gold!\n";
		cout << "It turns to defend itself, readying its cannons";
		do {
			char response = Story("\nWhat do you do?\nA: Fire cannons!\nB: Flee without the gold.\n");
			if (response == 'a' || response == 'A') //Loops battle
			{
				cout << "You fire your cannons, dealing " << playerShip.damage << " damage. The massive ship has "
					<< massiveShip.TakeDamage(playerShip.damage) << " health left.\n";

				if (!massiveShip.isDead) //Stops the enemy ship from dealing more damage on death
				{
					cout << "The massive ship fires its cannons, dealing " << massiveShip.damage << " damage.";
					cout << "You have " << playerShip.TakeDamage(massiveShip.damage) << " health left.";
				}
			}
			if (response == 'b' || response == 'B') //Flees from battle and ends loop
			{
				cout << "\nThe fight is too much! You chart a course away from the battle and escape.\n";
				break;
			}
		} while (!massiveShip.isDead); //Loops battle till enemy is sunk

		if (response == 'b' || response == 'B') //Ends the game successfully if the player chooses option B
		{
			cout << "\nYou go home and enjoy a peaceful life. Adventuring wasn't fun anyway.\n\n\n";
		}
	}

	if (massiveShip.isDead) //Earn extra gold for victory
	{
		cout << "Victory is yours! You loot 500 gold, putting you at " << playerShip.Loot(500) << " gold total!";
	}

	cout << "\n\nWith a day of sailing satisified, you go home with your treasures.";
}



/// <summary>
/// Type in story requiring choice A or B here. Awaits user input.
/// </summary>
/// <param name="story"></param>
/// <returns></returns>
char Story(string story)
{
	char response; //Creates a variable for the player's response
	do
	{
		cout << story; //Displays the story that the function is given
		cin >> response; //Awaits player response for only a or b
	} while (response != 'a' && response != 'A' && response != 'b' && response != 'B'); //Loops until proper input
	return response; //Returns the response the player gives from the function
}

/// <summary>
/// Checks for health being above 0. If not, it ends the narrative.
/// </summary>
/// <param name="currentHealth"></param>
/// <returns></returns>
bool DeathCheck(int currentHealth)
{
	if (currentHealth <= 0)
	{
		cout << "\n\nYour greed pushed your ship too far. It's wood shatters and you sink. The end.\n\n\n";
		exit(0);
		return true;
	}
	else
	{
		return false;
	}
}

