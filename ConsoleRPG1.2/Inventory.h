#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <string>
#include "Item.h"

class Inventory
{
	private:
		static constexpr int inventorySpace = 10;
		std::string inventory[inventorySpace] = {};
	public:
		bool addItem(std::string item);
		bool useItem(std::string item);


};
#endif

