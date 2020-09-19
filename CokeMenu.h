/*
	Roshan Shrestha
	
*/

#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <gtkmm.h>

class MyWindow : public Gtk::Window
{
    public:
        MyWindow();
        virtual ~MyWindow();
    protected:
//		void on_login_click(Gtk::Entry *euname, Gtk::Entry *epword);
		void on_login_click(Gtk::Entry *, Gtk::Entry *);
        void on_quit_click();
};
#endif // MYWINDOW_H