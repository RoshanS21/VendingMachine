/*
	Roshan Shrestha
	
*/

#include "MyWindow.h"

MyWindow::MyWindow()
{
    set_default_size(400, 200);
    set_title("My App - Part 3");

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &MyWindow::on_quit_click));
    filemenu->append(*menuitem_quit);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
	grid->set_row_spacing(5);
    vbox->add(*grid);

	Gtk::Label *lusername = Gtk::manage(new Gtk::Label("Username: "));
    grid->attach(*lusername, 0, 0, 1, 1);

    Gtk::Label *lpassword = Gtk::manage(new Gtk::Label("Password: "));
    grid->attach(*lpassword, 0, 1, 1, 1);

    Gtk::Entry *eusername = Gtk::manage(new Gtk::Entry());
    eusername->set_hexpand(true);
    grid->attach(*eusername, 1, 0, 2, 1);

    Gtk::Entry *epassword = Gtk::manage(new Gtk::Entry());
    epassword->set_hexpand(true);
    epassword->set_visibility(false);
    grid->attach(*epassword, 1, 1, 2, 1);

    Gtk::Button *blogin = Gtk::manage(new Gtk::Button("Login"));
    blogin->signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::mem_fun(*this, &MyWindow::on_login_click), eusername, epassword));                                   
    grid->attach(*blogin, 2, 2, 1, 1);

    vbox->show_all();
}

MyWindow::~MyWindow()
{
}

void MyWindow::on_login_click(Gtk::Entry *euname, Gtk::Entry *epword)
{
    if(euname->get_text().compare("admin") == 0 && epword->get_text().compare("password") == 0)
    {
        Gtk::MessageDialog dlg("You are now logged in.", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
        dlg.set_title("My App - Part 4");
        dlg.run();
    }
	else
    {
        Gtk::MessageDialog dlg("Unknown username or password.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dlg.set_title("My App - Part 4");
		dlg.run();
    }
}

void MyWindow::on_quit_click()
{
    hide();
}