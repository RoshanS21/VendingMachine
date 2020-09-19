// Roshan Shrestha

//adding include guards
#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

#include "VendingMachine.h"
#include <sstream>
#include <iostream>

class CokeMachine : public VendingMachine{
	private:
		int CokePrice;
		int inventoryLevel;
		int maxInventoryCapacity = 100;
	public:
		CokeMachine(std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100)
		:VendingMachine(name,change)		
			{
				CokePrice = cost;
				inventoryLevel = inventory;
			}
		
		~CokeMachine();	
		
		friend std::ostream& operator<<(std::ostream& oss, CokeMachine& MyCokeMachine);
		
		friend std::string CreateCokeOutputLine(CokeMachine& MyCokeMachine);
		
		bool buyACoke(int payment, std::string& change, int& action);
		
		int getInventoryLevel();
		
		int getMaxInventoryCapacity();
		
		bool incrementInventory(int amountToAdd);
		
		std::string getCokePrice();
		
		void setCokePrice(int newCokePrice);
};

#endif