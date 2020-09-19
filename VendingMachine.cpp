// Roshan Shrestha

#include "VendingMachine.h"
#include <string>

VendingMachine::VendingMachine(std::string name, int change):
	machineName{name},changeLevel{change}
{}

std::string VendingMachine::getMachineName(){
	return machineName;
}

void VendingMachine::setMachineName(std::string newMachineName){
	machineName = newMachineName;
}

int VendingMachine::getChangeLevel(){
	return changeLevel;
}

bool VendingMachine::incrementChangeLevel(int amountToAdd){
	if(changeLevel < maxChangeCapacity){
		if(amountToAdd + changeLevel <= maxChangeCapacity){
			changeLevel += amountToAdd;
			return true;
		}
	}
	return false;
}

std::string VendingMachine::getMaxChangeCapacity(){
	return displayMoney(maxChangeCapacity);
}

std::string VendingMachine::displayMoney(int amount){
	std::string dollars = std::to_string(amount/100);
	std::string cents = std::to_string(amount%100);
	return ("$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents);
}