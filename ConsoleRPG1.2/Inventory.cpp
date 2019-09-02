#include "Inventory.h"

//Check for empty space and add item
bool Inventory::addItem(std::string item)
{
	for (int i = 0; i < inventorySpace - 1; i++)
	{
		if (inventory[i].compare("") == 0)
		{
			inventory[i] = item;
			return true;
		}
	}
	return false;
}

//Check for item and use item
bool Inventory::useItem(std::string item)
{
	for (int i = 0; i < inventorySpace - 1; i++)
	{
		if (inventory[i].compare(item) == 0)
		{
			inventory[i] = "";
			return true;
		}
	}
	return false;
}