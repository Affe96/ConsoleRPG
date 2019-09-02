#ifndef __HEALTHPOTION_H__
#define __HEALTHPOTION_H__



#include "Item.h"

class HealthPotion: public Item
{
private:
	int healthPotionHeal;
public:
	int getHealthPotionHeal()
	{
		return healthPotionHeal;
	}
	
	HealthPotion();
};

#endif