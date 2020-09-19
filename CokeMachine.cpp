// Roshan Shrestha

#include "CokeMachine.h"

CokeMachine::~CokeMachine()
{}

std::ostream& operator<<(std::ostream& oss, CokeMachine& MyCokeMachine){
	oss << "Machine Name: " << MyCokeMachine.getMachineName() << "\n\n";
	oss << "Current Inventory Level " << MyCokeMachine.inventoryLevel << "\n";
	oss << "Max Inventory Capacity " << MyCokeMachine.maxInventoryCapacity << "\n\n";
	oss << "Current Change Level " << MyCokeMachine.getChangeLevel() << "\n";
	//converting maxchangecapacity : string to int
	std::string a = MyCokeMachine.getMaxChangeCapacity();
	int x = std::stoi(a.substr(a.find("$")+1,a.length())) * 100;
	oss << "Max Change Capacity " << x << "\n\n";
	
	oss << "Current Coke Price is " << MyCokeMachine.CokePrice << "\n\n";
	return oss;
}

std::string CreateCokeOutputLine(CokeMachine& MyCokeMachine){
	std::ostringstream oss;
	oss << MyCokeMachine.getMachineName() << "|" 
	<< MyCokeMachine.CokePrice << "|" << MyCokeMachine.getChangeLevel()
	<< "|" << MyCokeMachine.inventoryLevel;
	return oss.str();
}

bool CokeMachine::buyACoke(int payment, std::string& change, int& action){
	
	int cl = getChangeLevel();
	
	std::string a = getMaxChangeCapacity();
	int mcc = std::stoi(a.substr(a.find("$")+1,a.length())) * 100;
	
	if(payment < CokePrice){
		action = 0;
		return true;
	}else if(payment == CokePrice && (cl + CokePrice) <= mcc){
		action = 1;
		--inventoryLevel;
		return incrementChangeLevel(CokePrice);
	}else if(payment > CokePrice && cl > (payment - CokePrice) && (cl + CokePrice) <= mcc){
		action = 2;
		--inventoryLevel;
		change = displayMoney(payment - CokePrice);
		return incrementChangeLevel(CokePrice);
	}else{
		action = 3;
		return true;
	}
	return false;
}

int CokeMachine::getInventoryLevel(){
	return inventoryLevel;
}

int CokeMachine::getMaxInventoryCapacity(){
	return maxInventoryCapacity;
}

bool CokeMachine::incrementInventory(int amountToAdd){
	if(inventoryLevel < maxInventoryCapacity){
		if(amountToAdd + inventoryLevel <= maxInventoryCapacity){
			inventoryLevel += amountToAdd;
			return true;
		}
	}
	return false;
}

std::string CokeMachine::getCokePrice(){
	return displayMoney(CokePrice);
}

void CokeMachine::setCokePrice(int newCokePrice){
	CokePrice = newCokePrice;
}