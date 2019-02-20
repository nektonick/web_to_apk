#include <gtkmm.h>
#include <iostream>
#include <cstdlib>

void on_button_clicked ()
{
    std::cout << "Hello World" << std::endl;
	system("make -C .. apk");
}

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
	auto builder = Gtk::Builder::create_from_file("app.glade");
	Gtk::ApplicationWindow *window = nullptr;
	builder->get_widget("window", window);

	Gtk::Button *button = nullptr;
	builder->get_widget("button", button);
	button->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));

	app->run(*window);
}
