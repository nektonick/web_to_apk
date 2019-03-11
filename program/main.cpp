#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

bool internet = true;
bool local_files = true;
bool camera = true;
bool geodata = true;

void on_button_clicked (){

    cout << "Hello World" << std::endl;
	system("make -C .. apk");
}

void on_check1_toggled (){
	internet = !internet;
	cout<<internet<<endl;
}

void on_check2_toggled (){
	local_files = !local_files;
	cout<<local_files<<endl;
}

void on_check3_toggled (){
	camera = !camera;
	cout<<camera<<endl;
}

void on_check4_toggled (){
	 geodata= !geodata;
	 cout<<geodata<<endl;
}

void buildAndroidManifest (){
	string line;
	ifstream file("../app/AndroidManifestStart.xml");
	ofstream out;
	out.open("../app/AndroidManifest.xml");
	if (file.is_open()){
        while (getline(file, line)){
			if (out.is_open())
            	out << line << endl;
        }
    }
    file.close();

	if (internet == true){
		ifstream p1file("../app/AndroidManifestPermission1.xml");
		if (p1file.is_open()){
        	while (getline(p1file, line)){
            	if (out.is_open())
            		out << line << endl;        
			}
    	}
		p1file.close();
	}

	if (local_files == true){
		ifstream p2file("../app/AndroidManifestPermission2.xml");
		if (p2file.is_open()){
        	while (getline(p2file, line)){
            	if (out.is_open())
            		out << line << endl;
        	}
    	}
		p2file.close();
	}

	if (camera == true){
		ifstream p3file("../app/AndroidManifestPermission3.xml");
		if (p3file.is_open()){
        	while (getline(p3file, line)){
            	if (out.is_open())
            		out << line << endl;
        	}
    	}
		p3file.close();
	}

	if (geodata== true){
		ifstream p4file("../app/AndroidManifestPermission4.xml");
		if (p4file.is_open()){
        	while (getline(p4file, line)){
            	if (out.is_open())
            		out << line << endl;
        	}
    	}
		p4file.close();
	}


	ifstream lastFile ("../app/AndroidManifestEnd.xml");
		if (lastFile.is_open()){
        	while (getline(lastFile, line)){
            	if (out.is_open())
            		out << line << endl;  
        	}
    	}
    lastFile.close();
	out.close();
}


int main(int argc, char *argv[]){

	buildAndroidManifest();

	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
	auto builder = Gtk::Builder::create_from_file("app.glade");
	Gtk::Window *window = nullptr;
	builder->get_widget("window", window);

	Gtk::Button *button = nullptr;
	builder->get_widget("button", button);
	button->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));

	Gtk::CheckButton *check1 = nullptr;
	builder->get_widget("check1", check1);
	check1->signal_toggled().connect(sigc::ptr_fun(on_check1_toggled));
	
	Gtk::CheckButton *check2 = nullptr;
	builder->get_widget("check2", check2);
	check2->signal_toggled().connect(sigc::ptr_fun(on_check2_toggled));
	
	Gtk::CheckButton *check3 = nullptr;
	builder->get_widget("check3", check3);
	check3->signal_toggled().connect(sigc::ptr_fun(on_check3_toggled));
	
	Gtk::CheckButton *check4 = nullptr;
	builder->get_widget("check4", check4);
	check4->signal_toggled().connect(sigc::ptr_fun(on_check4_toggled));

	app->run(*window);
}
