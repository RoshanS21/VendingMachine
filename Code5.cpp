// Roshan Shrestha

#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <map>
#include "CokeMachine.h"
#include "CokeLib.h"
#include <gtkmm.h>

using namespace std;

int menu(string machineName){
	/*cout << "\n\n" << machineName << endl;
	cout << "\n" << "0. Walk away\n"
		<< "1. Buy a coke\n"
		<< "2. Restock machine\n"
		<< "3. Add change\n"
		<< "4. Display Machine Info\n"
		<< "5. Update Machine Name\n"
		<< "6. Update Coke Price\n"
		<< endl;
	*/
	Gtk::Dialog *menuDialog = Gtk::manage(new Gtk::Dialog());
	menuDialog->set_title(machineName);
	Gtk::Label *menuLabel = Gtk::manage(new Gtk::Label("What do you want to do?"));
	menuDialog->get_content_area()->pack_start(*menuLabel);
	menuLabel->show();
	std::vector<std::string> buttons = {"Walk away", "Buy a Coke", "Restock Machine", "Add Change", "Display Machine Info", "Update Machine Name", "Update Coke Price"};
	for(int i=0; i<buttons.size(); i++){
		menuDialog->add_button(buttons[i],i);
	}
	menuDialog->set_default_response(0);
	int result = menuDialog->run();
	menuDialog->close();
	delete menuDialog;
	return result;
}

void get_command_line_params(int& argc, char* argv[], string& INPUTFILENAME, string& OUTPUTFILENAME){
	for(int i = 1; i < argc; i++){
		try{
			string cla = argv[i];
			if(cla.substr(0,cla.find("=")) == "INPUTFILENAME"){
				INPUTFILENAME = cla.substr(cla.find("=")+1,cla.length());
			}
			else if(cla.substr(0,cla.find("=")) == "OUTPUTFILENAME"){
				OUTPUTFILENAME = cla.substr(cla.find("=")+1,cla.length());
			}else{
				throw std::invalid_argument ("Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME= \n");
			}
		}
		catch(invalid_argument& say){
			cerr << say.what() << endl;
			exit(1);
		}
	}
}

void updateReceipt(map<string, int>& CokeReceipt, const string& machineName){
	if(CokeReceipt.find(machineName) == CokeReceipt.end()){
		CokeReceipt.insert(make_pair(machineName,1));
	}else{
		CokeReceipt.at(machineName)++;
	}
}
//Function to get payment
int getPayment(){
	Gtk::Dialog *paymentDialog = Gtk::manage(new Gtk::Dialog());
	paymentDialog->set_title("Payment");
	Gtk::Label *paymentLabel = Gtk::manage(new Gtk::Label("Insert payment: "));
	paymentDialog->get_content_area()->pack_start(*paymentLabel);
	paymentLabel->show();
	Gtk::Entry *paymentEntry = Gtk::manage(new Gtk::Entry());
	paymentEntry->set_text("Insert Payment");
	paymentEntry->set_max_length(20);
	paymentEntry->show();
	paymentDialog->get_content_area()->pack_start(*paymentEntry);
	std::vector<std::string> buttons = {"OK","CANCEL"};
	for(int i=0; i<buttons.size(); i++){
		paymentDialog->add_button(buttons[i],i);
	}
	paymentDialog->set_default_response(0);
	int payment = paymentDialog->run();
	payment = std::stoi(paymentEntry->get_text());
	paymentDialog->close();
	delete paymentDialog;
	return payment;
}
//Function to get restock amount
int restockMachine(){
	Gtk::Dialog *inputDialog = Gtk::manage(new Gtk::Dialog());
	inputDialog->set_title("Input");
	Gtk::Label *inputLabel = Gtk::manage(new Gtk::Label("How much product are you adding to the machine?"));
	inputDialog->get_content_area()->pack_start(*inputLabel);
	inputLabel->show();
	Gtk::Entry *inputEntry = Gtk::manage(new Gtk::Entry());
	inputEntry->set_text("0000");
	inputEntry->set_max_length(10);
	inputEntry->show();
	inputDialog->get_content_area()->pack_start(*inputEntry);
	std::vector<std::string> buttons = {"OK","CANCEL"};
	for(int i=0; i<buttons.size(); i++){
		inputDialog->add_button(buttons[i],i);
	}
	inputDialog->set_default_response(0);
	int input = inputDialog->run();
	input = std::stoi(inputEntry->get_text());
	inputDialog->close();
	delete inputDialog;
	return input;
}
//Function to get change amount to be incremented
int addChange(){
	Gtk::Dialog *inputDialog = Gtk::manage(new Gtk::Dialog());
	inputDialog->set_title("Input");
	Gtk::Label *inputLabel = Gtk::manage(new Gtk::Label("How much change are you adding to the machine?"));
	inputDialog->get_content_area()->pack_start(*inputLabel);
	inputLabel->show();
	Gtk::Entry *inputEntry = Gtk::manage(new Gtk::Entry());
	inputEntry->set_text("0000");
	inputEntry->set_max_length(10);
	inputEntry->show();
	inputDialog->get_content_area()->pack_start(*inputEntry);
	std::vector<std::string> buttons = {"OK","CANCEL"};
	for(int i=0; i<buttons.size(); i++){
		inputDialog->add_button(buttons[i],i);
	}
	inputDialog->set_default_response(0);
	int change = inputDialog->run();
	change = std::stoi(inputEntry->get_text());
	inputDialog->close();
	delete inputDialog;
	return change;
}
//Function to get new machine name
string newName(){
	Gtk::Dialog *inputDialog = Gtk::manage(new Gtk::Dialog());
	inputDialog->set_title("Input");
	Gtk::Label *inputLabel = Gtk::manage(new Gtk::Label("Enter a new machine name"));
	inputDialog->get_content_area()->pack_start(*inputLabel);
	inputLabel->show();
	Gtk::Entry *inputEntry = Gtk::manage(new Gtk::Entry());
	inputEntry->set_text("Enter new name");
	inputEntry->set_max_length(30);
	inputEntry->show();
	inputDialog->get_content_area()->pack_start(*inputEntry);
	std::vector<std::string> buttons = {"OK","CANCEL"};
	for(int i=0; i<buttons.size(); i++){
		inputDialog->add_button(buttons[i],i);
	}
	inputDialog->set_default_response(0);
	int p = inputDialog->run();
	string newMachineName = inputEntry->get_text();
	inputDialog->close();
	delete inputDialog;
	return newMachineName;
}
//Function to get new Coke Price
int newPrice(){
	Gtk::Dialog *inputDialog = Gtk::manage(new Gtk::Dialog());
	inputDialog->set_title("Input");
	Gtk::Label *inputLabel = Gtk::manage(new Gtk::Label("Enter a new Coke price"));
	inputDialog->get_content_area()->pack_start(*inputLabel);
	inputLabel->show();
	Gtk::Entry *inputEntry = Gtk::manage(new Gtk::Entry());
	inputEntry->set_text("0000");
	inputEntry->set_max_length(10);
	inputEntry->show();
	inputDialog->get_content_area()->pack_start(*inputEntry);
	std::vector<std::string> buttons = {"OK","CANCEL"};
	for(int i=0; i<buttons.size(); i++){
		inputDialog->add_button(buttons[i],i);
	}
	inputDialog->set_default_response(0);
	int newCokePrice = inputDialog->run();
	newCokePrice = std::stoi(inputEntry->get_text());
	inputDialog->close();
	delete inputDialog;
	return newCokePrice;
}

int main(int argc, char* argv[]){
	
	Gtk::Main kit(argc, argv);
	
	//Creating a map
	map <string, int> CokeReceipt;
	
	int choiceMachine;
	int action = 0;
	int payment;
	int newCokePrice;
	int input = 0;
	ostringstream oss;
	string message = "";
	string change = "";
	string newMachineName;
	string INPUTFILENAME, OUTPUTFILENAME;
	
	get_command_line_params(argc,argv,INPUTFILENAME,OUTPUTFILENAME);
	
	vector <CokeMachine> SetOfCokeMachines; // vector of Coke Machines;
	
	ifstream CokeInputFile{INPUTFILENAME};
	ofstream CokeOutputFile{OUTPUTFILENAME, ios::out};
	
	if(CokeInputFile.is_open()){
		string CokeMachineLine;
		vector<string> ConstructorValues(4);
		
		while(CokeInputFile.good()){ //Checking the good bit
			getline(CokeInputFile,CokeMachineLine);
			if(ParseCokeLine(CokeMachineLine,ConstructorValues)){
				//temporary CokeMachine object;
				CokeMachine MyCokeMachine{ConstructorValues[0],stoi(ConstructorValues[1]),stoi(ConstructorValues[2]),stoi(ConstructorValues[3])};
				SetOfCokeMachines.push_back(MyCokeMachine);
			}
		}
	}else{
		cout << "Unable to open file.\n\n";
		exit(1);
	}
	// Pick a Coke Machine;
	do{
		int i=0;
		
		cout << "\n\nPick a Coke Machine\n\n" << endl;
		
		cout << "0. Exit\n\n";
		//Using range based for loop to print out the machine menu.
		for(auto it : SetOfCokeMachines){
			cout << i+1 << ". " << it.getMachineName() << "\n\n";
			i++;
		}
		cout << i+1 << ". Add a new machine\n\n";
		
		cout << "Enter choice ";
		cin >> choiceMachine;
		/*
		//Dialog for Coke Machines
		Gtk::Dialog *machineDialog = Gtk::manage(new Gtk::Dialog());
		machineDialog->set_title("Coke Machines");
		Gtk::Label *machineLabel = Gtk::manage(new Gtk::Label("Pick a Coke Machine"));
		machineDialog->get_content_area()->pack_start(*machineLabel);
		machineLabel->show();
		i=0;
		machineDialog->add_button("Exit",i);
		i++;
		for(auto it : SetOfCokeMachines){
			machineDialog->add_button(it.getMachineName(),i);
			i++;
		}
		machineDialog->set_default_response(0);
		choiceMachine = machineDialog->run();
		machineDialog->close();
		delete machineDialog;
		*/
		if(choiceMachine == 0){
			//write to output file.
			for(int i=0; i<SetOfCokeMachines.size(); i++){
				if(i != SetOfCokeMachines.size()-1){
					CokeOutputFile << CreateCokeOutputLine(SetOfCokeMachines[i]);
					CokeOutputFile << "\n";
				}else{
					CokeOutputFile << CreateCokeOutputLine(SetOfCokeMachines[i]);
				}
			}
			//print Coke Receipt
			cout << "\n\n" << "Your Coke Receipt\n" << endl;
			for(auto it : CokeReceipt){
				cout << it.first << " : " << it.second << endl;
			}
			cout << "\n\n" << endl;
			break;
		}
		
		int choice = 1;
		
		while(choice){
			
			choice = menu(SetOfCokeMachines[choiceMachine-1].getMachineName());
			
			//cin >> choice;
			
			switch(choice){
				case 0:
					//cout << "\nAre you sure you aren't really TRHIRSTY and need a Coke?\n\n" << endl;
					Gtk::MessageDialog *myMessageDialog;
					myMessageDialog = new Gtk::MessageDialog{"Are you sure you aren't really TRHIRSTY and need a Coke?"};
					myMessageDialog->run();
					myMessageDialog->close();
					delete myMessageDialog;
					break;
				
				case 1:
					//cout << "Insert payment: ";
					//cin >> payment;
					
					payment = getPayment();
					
					if(SetOfCokeMachines[choiceMachine-1].buyACoke(payment, change, action)){
						switch(action){
							case 0:
								//cout << "\n\nInsufficient payment...returning your payment\n\n" << endl;
								Gtk::MessageDialog *m0;
								m0 = new Gtk::MessageDialog{"Insufficient payment...returning your payment"};
								m0->run();
								m0->close();
								delete m0;
								break;
							case 1:
								//cout << "\n\nThank you for exact change\n\n" << endl;
								Gtk::MessageDialog *m1;
								m1 = new Gtk::MessageDialog{"Thank you for exact change"};
								m1->run();
								m1->close();
								delete m1;
								updateReceipt(CokeReceipt,SetOfCokeMachines[choiceMachine-1].getMachineName());
								break;
							case 2:
								//cout << "\n\nHere's your coke and your change of " << change << "\n\n" << endl;
								message = "Here's your coke and your change of";
								message = message + change;
								Gtk::MessageDialog *m2;
								m2 = new Gtk::MessageDialog{message};//,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
								m2->run();
								m2->close();
								delete m2;
								updateReceipt(CokeReceipt,SetOfCokeMachines[choiceMachine-1].getMachineName());
								break;
							case 3:
								//cout << "\n\nUnable to give change at this time...returning your payment\n\n" << endl;
								Gtk::MessageDialog *m3;
								m3 = new Gtk::MessageDialog{"Unable to give change at this time...returning your payment"};
								m3->run();
								m3->close();
								delete m3;
								break;
							default:
								break;
						}
					}
					
					break;
					
				case 2:
					//cout << "How much product are you adding to the machine? ";
					input = restockMachine();
					//cin >> input;
					if(SetOfCokeMachines[choiceMachine-1].incrementInventory(input)){
						//cout << "\n\nYour machine has been restocked.\n\n" << endl;
						Gtk::MessageDialog *m4;
						m4 = new Gtk::MessageDialog{"Youe machine has been restocked"};
						m4->run();
						m4->close();
						delete m4;
					}else{
						//cout << "\n\nYou have exceeded your machine's max capacity.\n\n" << endl;
						Gtk::MessageDialog *m5;
						m5 = new Gtk::MessageDialog{"You have exceeded your machine's max capacity"};
						m5->run();
						m5->close();
						delete m5;
					}
					message = "Your inventory level is now ";
					message = message + std::to_string(SetOfCokeMachines[choiceMachine-1].getInventoryLevel());
					//cout << "Your inventory level is now " << SetOfCokeMachines[choiceMachine-1].getInventoryLevel() << "\n\n\n" << endl;
					Gtk::MessageDialog *m6;
					m6 = new Gtk::MessageDialog{message};//,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
					m6->run();
					m6->close();
					delete m6;
					break;
					
				case 3:
					//cout << "How much change are you adding to the machine? ";
					//cin >> change;
										
					input = addChange();
					
					if(SetOfCokeMachines[choiceMachine-1].incrementChangeLevel(input)){
						//cout << "\n\nYour change has been updated\n\n" << endl;
						Gtk::MessageDialog *m7;
						m7 = new Gtk::MessageDialog{"Your change has been updated."};
						m7->run();
						m7->close();
						delete m7;
					}else{
						//cout << "\n\nYou have exceeded your machine's max change capacity\n\n\n" << endl;
						Gtk::MessageDialog *m8;
						m8 = new Gtk::MessageDialog{"You have exceeded your machine's max change capacity"};
						m8->run();
						m8->close();
						delete m8;
					}
					//cout << "Your change level is now " << SetOfCokeMachines[choiceMachine-1].getChangeLevel() << "\n\n" << endl;
					message = "Your change level is now ";
					message = message + std::to_string(SetOfCokeMachines[choiceMachine-1].getChangeLevel());
					Gtk::MessageDialog *m9;
					m9 = new Gtk::MessageDialog{message};//,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
					m9->run();
					m9->close();
					delete m9;					
					break;
					
				case 4:
					oss << SetOfCokeMachines[choiceMachine-1]; //using overloaded stream insertion opeartor.
					message = oss.str();
					Gtk::MessageDialog *m10;
					m10 = new Gtk::MessageDialog{message};//,Gtk::MESSAGE_INFO,Gtk::BUTTONS_OK,false};
					m10->run();
					m10->close();
					delete m10;
					//clearing outputstringstream such that it doesn't pile up.
					oss.str(std::string());
					break;
					
				case 5:
					//cout << "Enter a new machine name: ";
					//cin.ignore(10,'\n');
					//getline(cin,newMachineName);
					newMachineName = newName();
					SetOfCokeMachines[choiceMachine-1].setMachineName(newMachineName);
					//cout << "\nMachine name has been updated.\n" << endl;
					Gtk::MessageDialog *m11;
					m11 = new Gtk::MessageDialog{"Machine name has been updated."};
					m11->run();
					m11->close();
					delete m11;	
					break;
					
				case 6:
					//cout << "Enter a new Coke price: ";
					//cin >> newCokePrice;
					newCokePrice = newPrice();
					SetOfCokeMachines[choiceMachine-1].setCokePrice(newCokePrice);
					//cout << "\nCoke price has been updated.\n" << endl;
					Gtk::MessageDialog *m12;
					m12 = new Gtk::MessageDialog{"Coke price has been updated."};
					m12->run();
					m12->close();
					delete m12;	
					break;
					
				default:
					break;
					
			}
		}
		
		if(choiceMachine == (SetOfCokeMachines.size()+1)){
			CokeMachine MyCokeMachine;
			SetOfCokeMachines.push_back(MyCokeMachine);
			
			//cout << "New Machine Added\n\n" << endl;
			Gtk::MessageDialog *m13;
			m13 = new Gtk::MessageDialog{"New Machine Added."};
			m13->run();
			m13->close();
			delete m13;	
		}
		
	}while(choiceMachine != 0);
	
	CokeInputFile.close();
	CokeOutputFile.close();
	return 0;
}