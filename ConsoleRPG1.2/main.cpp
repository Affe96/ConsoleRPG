#include "Enemy.h"
#include "Item.h"
#include "HealthPotion.h"
#include "Inventory.h"

#include <string>
#include <iostream>

int validInput(int firstChoice, int lastChoice);

void setPlayerName();
void getPlayerHero();

void setWarriorValues();
void setMageValues();

void warriorTooltips();
void mageTooltips();

void setHealth(int heal);
void setMana(int manaCost);
int applyDamage(int characterHealth, int characterDamage);

int combatPhaseWarrior(int enemyHealth, int enemyDamage);
int combatPhaseMage(int enemyHealth, int enemyDamage);

void roomSelection();
void roomA();
void roomB();
void roomC();
void roomD();
void roomE();

Inventory Inventory;

Enemy Enemy1;
HealthPotion HealthPotion1;

std::string playerName;

int playerHeroChoice;
int playerInput;

int maxHealth;
int health;

int mana;
int warriorResistance;

char currentRoom = 'A';

struct ability
{
	std::string id;
	std::string description;
	int power = 0;
	int special = 0;
};

ability shieldSlam;
ability swordLunge;
ability shieldBlock;

ability fireball;
ability icebolt;
ability greaterHeal;

int validInput(int firstChoice, int lastChoice)
{
	int input;
	while (!(std::cin >> input) || input < firstChoice || input > lastChoice)
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Invalid input.  Try again: ";

	}
	return input;
}

void setPlayerName()
{
	std::cout << "Hi! What's your name? ";
	std::getline(std::cin, playerName);
}

void getPlayerHero()
{
	std::cout << "Hello " << playerName << "! Are you a warrior or a mage?" << std::endl;
	std::cout << "1: Warrior, 2: Mage: ";

	//Check if the input is valid
	playerHeroChoice = validInput(1, 2);

	switch (playerHeroChoice)
	{
	case 1:
		std::cout << "Ok, " << playerName << " the warrior!" << std::endl;
		setWarriorValues();
		break;

	case 2:
		std::cout << "Ok, " << playerName << " the mage!" << std::endl;
		setMageValues();
		break;

	default:
		break;
	}
}

void setWarriorValues()
{
	maxHealth = 120;
	health = maxHealth;

	warriorResistance = 0;

	shieldSlam.id = "Shieldslam";
	shieldSlam.description = "A weak attack, but you take less damage next attack.";
	shieldSlam.power = 10;
	shieldSlam.special = 5; //blockvalue

	swordLunge.id = "Sword-lunge";
	swordLunge.description = "A strong attack";
	swordLunge.power = 15;
	swordLunge.special = 0;

	shieldBlock.id = "Shieldblock";
	shieldBlock.description = "Raise your shield and block some damage.";
	shieldBlock.power = 0;
	shieldBlock.special = 15;
}

void setMageValues()
{
	maxHealth = 70;
	health = maxHealth;

	mana = 100;

	fireball.id = "Fireball";
	fireball.description = "A weak but cheap attack.";
	fireball.power = 10;
	fireball.special = 5; //manacost

	icebolt.id = "Icebolt";
	icebolt.description = "A strong but expensive attack.";
	icebolt.power = 40;
	icebolt.special = 40;

	greaterHeal.id = "Greater heal";
	greaterHeal.description = "Heal yourself.";
	greaterHeal.power = 40;
	greaterHeal.special = 30;
}

void warriorTooltips()
{
	std::cout << shieldSlam.id << ": " << shieldSlam.description << "\n";
	std::cout << swordLunge.id << ": " << swordLunge.description << "\n";
	std::cout << shieldBlock.id << ": " << shieldBlock.description << "\n";
}

void mageTooltips()
{
	std::cout << fireball.id << ": " << fireball.description << "\n";
	std::cout << icebolt.id << ": " << icebolt.description << "\n";
	std::cout << greaterHeal.id << ": " << greaterHeal.description << "\n";
}

void setHealth(int heal)
{
	health = health + heal;
	if (health > maxHealth)
		health = maxHealth;
}

void setMana(int manaCost)
{
	mana = mana - manaCost;
}

int applyDamage(int characterHealth, int characterDamage)
{
	characterHealth = characterHealth - characterDamage;
	return characterHealth;
}

int combatPhaseWarrior(int enemyHealth,int enemyDamage)
{
	while (true)
	{
		std::cout << "The enemy health is " << enemyHealth << "\n";
		std::cout << "Your health is " << health << "\n";
		std::cout << "1: Use " << shieldSlam.id << ", 2: Use " << swordLunge.id << ", 3: Use " << shieldBlock.id;
		std::cout << ", 4: Drink " << HealthPotion1.getItemName() << ", 5: Flee" << ", 6: Show tooltips ";

		playerInput = validInput(1, 6);
		switch (playerInput)
		{
		case 1:
			enemyHealth = applyDamage(enemyHealth, shieldSlam.power);
			warriorResistance = shieldSlam.special;
			break;
		case 2:
			enemyHealth = applyDamage(enemyHealth, swordLunge.power);
			warriorResistance = swordLunge.special;
			break;
		case 3:
			enemyHealth = applyDamage(enemyHealth, shieldBlock.power);
			warriorResistance = shieldBlock.special;
			break;
		case 4:
			if (useItem(HealthPotion1.getItemName()))
				setHealth(HealthPotion1.getHealthPotionHeal());
			break;
		case 5:
			return enemyHealth;
		case 6:
			warriorTooltips();
			break;
		default:
			break;
		}
		if (enemyHealth <= 0)
		{
			std::cout << "You win!\n";
			std::cout << "Press Enter to Continue!";
			std::cin;
			exit(0);
		}
		std::cout << "You get hit by the monster!\n";
		std::cout << "\n\n\n";
		health = applyDamage(health, (enemyDamage - warriorResistance));
		warriorResistance = 0;
		if (health <= 0)
		{
			std::cout << "You lose!\n";
			std::cout << "Press Enter to Continue!";
			std::cin;
			exit(0);
		}
	}
}

int combatPhaseMage(int enemyHealth, int enemyDamage)
{
	while (true)
	{

		std::cout << "The enemy health is " << enemyHealth << "\n";
		std::cout << "Your health is " << health << "\n";
		std::cout << "Your mana is " << mana << "\n";
		std::cout << "1: Cast " << fireball.id << ", 2: Cast " << icebolt.id << ", 3: Cast " << greaterHeal.id;
		std::cout << ", 4: Drink " << HealthPotion1.getItemName() << ", 5: Flee" << ", 6: Show tooltips ";

		playerInput = validInput(1, 6);
		switch (playerInput)
		{
		case 1:
			if (mana >= fireball.special)
			{
				enemyHealth = applyDamage(enemyHealth, fireball.power);
				setMana(fireball.special);
			}
			else
			{
				std::cout << "You need more mana!\n";
			}
			break;
		case 2:
			if (mana >= icebolt.special)
			{
				enemyHealth = applyDamage(enemyHealth, icebolt.power);
				setMana(icebolt.special);
			}
			else
			{
				std::cout << "You need more mana!\n";
			}
			break;
		case 3:
			if (mana >= greaterHeal.special)
			{
				setHealth(greaterHeal.power);
				setMana(greaterHeal.special);
			}
			else
			{
				std::cout << "You need more mana!\n";
			}
			break;
		case 4:
			if (useItem(HealthPotion1.getItemName()))
				setHealth(HealthPotion1.getHealthPotionHeal());
			break;
		case 5:
			return enemyHealth;
		case 6:
			mageTooltips();
			break;
		default:
			break;
		}
		if (enemyHealth <= 0)
		{
			std::cout << "You win!\n";
			std::cout << "Press Enter to Continue!";
			std::cin;
			exit(0);
		}
		std::cout << "You get hit by the monster!\n";
		std::cout << "\n\n\n";
		health = applyDamage(health, enemyDamage);
		if (health <= 0)
		{
			std::cout << "You lose!\n";
			std::cout << "Press Enter to Continue";
			std::cin;
			exit(0);
		}
	}
}

//Layout
///////////
// A-C-E //
// | |   //
// B-D   //
///////////
void roomA()
{
	std::cout << "Do you want to go 1: East or 2: South? ";
	playerInput = validInput(1, 2);

	switch (playerInput)
	{
	case 1:
		currentRoom = 'C';
		break;
	case 2:
		currentRoom = 'B';
		break;
	default:
		break;
	}
}

void roomB()
{
	std::cout << "Do you want to go 1: North or 2: East? ";
	playerInput = validInput(1, 2);

	switch (playerInput)
	{
	case 1:
		currentRoom = 'A';
		break;
	case 2:
		currentRoom = 'D';
		break;
	default:
		break;
	}
}

void roomC()
{
	std::cout << "Do you want to go 1: East, 2: South or 3: West? ";
	playerInput = validInput(1, 3);

	switch (playerInput)
	{
	case 1:
		currentRoom = 'E';
		break;
	case 2:
		currentRoom = 'D';
		break;
	case 3:
		currentRoom = 'A';
		break;
	default:
		break;
	}
}

void roomD() //healthpot-room
{
	if (HealthPotion1.isPickedUp == false)
	{
		std::cout << "You find a Health-potion on the floor!\n";
		std::cout << "Do you want to pick it up? 1: Yes, 2: No: ";
		playerInput = validInput(1, 2);
		switch (playerInput)
		{
		case 1:
			if (!(addItem(HealthPotion1.getItemName()) == true))
				std::cout << "Inventory is full! ";
			else
				HealthPotion1.isPickedUp = true;
			break;
		case 2:
			break;
		default:
			break;
		}
	}

	std::cout << "Do you want to go 1: North or 2: West? ";
	playerInput = validInput(1, 2);

	switch (playerInput)
	{
	case 1:
		currentRoom = 'C';
		break;
	case 2:
		currentRoom = 'B';
		break;
	default:
		break;
	}
}

void roomE() //monster-room
{
	std::cout << "You encounter a monster! What do you want to do?\n";
	switch (playerHeroChoice)
	{
	case 1:
		Enemy1.enemyHealth = combatPhaseWarrior(Enemy1.enemyHealth, Enemy1.enemyDamage);
		break;

	case 2:
		Enemy1.enemyHealth = combatPhaseMage(Enemy1.enemyHealth, Enemy1.enemyDamage);
		break;

	default:
		break;
	}
	currentRoom = 'C';
}

void roomSelection()
{
	while(true)
	{
		switch(currentRoom)
		{
		case 'A':
			roomA();
			break;
		case 'B':
			roomB();
			break;
		case 'C':
			roomC();
			break;
		case 'D':
			roomD();
			break;
		case 'E':
			roomE();
			break;
		default:
			break;
		}
	}
}

int main()
{
	setPlayerName();
	getPlayerHero();

	roomSelection();

	return 0;
}