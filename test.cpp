#include<iostream>
#include<gtkmm.h>

int main(){
	Gtk::Main kit(argc, argv);
	Gtk::Window MyWindow;
	Gtk::Main::run(MyWindow);
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
	cout << "The result is :" << result << endl;
	return 0;
}