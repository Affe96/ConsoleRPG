#ifndef __ITEM_H__
#define __ITEM_H__



#include <string>

namespace Items {
	class Item
	{
	private:

	protected:
		std::string itemName;
	public:
		std::string getItemName()
		{
			return itemName;
		}

		bool isPickedUp;
	};
}
#endif
