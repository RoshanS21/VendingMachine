// Roshan Shrestha

#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <string>

class VendingMachine{
	private:
		std::string machineName;
		int changeLevel;
		int maxChangeCapacity = 5000;
	public:
		VendingMachine(std::string name = "New Machine", int change = 500);
		~VendingMachine(){}
		
		std::string getMachineName();
		void setMachineName(std::string newMachineName);
		int getChangeLevel();
		bool incrementChangeLevel(int amountToAdd);
		std::string getMaxChangeCapacity();
		std::string displayMoney(int amount);
		
		virtual bool incrementInventory(int ){}
		virtual int getMaxInventoryCapacity(){}
		virtual int getInventoryLevel(){}
};

#endif