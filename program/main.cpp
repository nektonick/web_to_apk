#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;
using namespace Gtk;

bool internet = true;
bool local_files = true;
bool camera = true;
bool geodata = true;
bool islink = true; //приложению передана ссылка на сайт или папка с ресурсами (пока ни с чем не связана)
string URL = "https://example.com"; //ссылка на сайт
string name = "Example app";


void on_check1_toggled (){
	internet = !internet;
//	cout<<internet<<endl;
}

void on_check2_toggled (){
	local_files = !local_files;
//	cout<<local_files<<endl;
}

void on_check3_toggled (){
	camera = !camera;
//	cout<<camera<<endl;
}

void on_check4_toggled (){
	 geodata= !geodata;
//	 cout<<geodata<<endl;
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

void buildMainActivity(){
	if (islink == true){ //если передана ссылка
		string line;
		ifstream res1("../app/src/com/example/MainActivityStart.java");
		ofstream out;
		out.open("../app/src/com/example/helloandroid/MainActivity.java");
		if (res1.is_open()){
        	while (getline(res1, line)){
				if (out.is_open())
            		out << line << endl;
        	}
    	}
    	res1.close();
		
		string s="        webView.loadUrl(\"" ;
		string ss="\");";
	
		s=s+URL+ss;	
		out << s << endl;

		ifstream res2("../app/src/com/example/MainActivityEnd.java");
		if (res2.is_open()){
        	while (getline(res2, line)){
				if (out.is_open())
            		out << line << endl;
        	}
    	}
    	res2.close();
	}

}
void buildStrings(){
	string line;
	ifstream strings1("../app/strings1.txt");
	ofstream out;
	out.open("../app/res/values/strings.xml");
	if (strings1.is_open()){
        while (getline(strings1, line)){
			if (out.is_open())
            	out << line << endl;
        }
    }
    strings1.close();
		
	string s="  <string name=\"app_name\">";
	string ss="</string>";
	
	s=s+name+ss;	
	out << s << endl;

	ifstream string2("../app/strings2.txt");
	if (string2.is_open()){
        while (getline(string2, line)){
			if (out.is_open())
            	out << line << endl;
        }
    }
    string2.close();
}

void f(Entry* entry){
	cout<<entry->get_text()<<" "<<endl;
	URL = entry->get_text();
}
void v (Entry* entry){
	cout<<entry->get_text()<<" "<<endl;
	name = entry->get_text();
}


void on_button_clicked (){

 // cout << "Hello World" << std::endl;
 	buildStrings();
	buildAndroidManifest();
	buildMainActivity();
 
	system("make -C .. apk");
}


int main(int argc, char *argv[]){


//	buildAndroidManifest();
//	buildMainActivity(link);

	auto app = Application::create(argc, argv, "org.gtkmm.examples.base");
	auto builder = Builder::create_from_file("app.glade");

	Window *window = nullptr;
	builder->get_widget("window", window);

	Button *button = nullptr;
	builder->get_widget("button", button);
	button->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
/*
	EntryBuffer *entrybuffer1 = nullptr;//его нужно связать с буфером из глейда
	builder->get_widget("entrybuffer1", entrybuffer1);
*/
	CheckButton *check1 = nullptr;
	builder->get_widget("check1", check1);
	check1->signal_toggled().connect(sigc::ptr_fun(on_check1_toggled));
	
	CheckButton *check2 = nullptr;
	builder->get_widget("check2", check2);
	check2->signal_toggled().connect(sigc::ptr_fun(on_check2_toggled));
	
	CheckButton *check3 = nullptr;
	builder->get_widget("check3", check3);
	check3->signal_toggled().connect(sigc::ptr_fun(on_check3_toggled));
	
	CheckButton *check4 = nullptr;
	builder->get_widget("check4", check4);
	check4->signal_toggled().connect(sigc::ptr_fun(on_check4_toggled));


	Entry *entry1 = nullptr;
	builder->get_widget("entry1", entry1);

	entry1->signal_changed().connect(sigc::bind<Gtk::Entry*>(sigc::ptr_fun(f), entry1));
	
	Entry *entry2 = nullptr;
	builder->get_widget("entry2", entry2);

	entry2->signal_changed().connect(sigc::bind<Gtk::Entry*>(sigc::ptr_fun(v), entry2));

	app->run(*window);
}
