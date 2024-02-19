#include <iostream>
#include <string>
#include <thread>
#include <chrono>

struct user_command {
	enum TType { open_new_document, close_new_document };
	TType type;
};

void open_document_and_display_gui(const std::string&);
user_command get_user_input();
std::string get_filename_from_user();
void process_user_input(const user_command&); 
bool done_editing();


void edit_document(const std::string& filename) {
	open_document_and_display_gui(filename);
	while (!done_editing()) {
		std::cout << "Try to get user input"  << std::endl;
		user_command cmd = get_user_input();
		if (cmd.type == user_command::open_new_document) {
			const std::string new_name = get_filename_from_user();
			std::thread t(edit_document, new_name);
			t.detach();
		}
		else {
			process_user_input(cmd);
		}
	}
}

void open_document_and_display_gui(const std::string& filename) {
	std::cout << "Document " << filename <<" has been opened and display has been shown" << std::endl;
}

user_command get_user_input() {
	user_command res;
	char letter;
	std::cout << "Open document - P, close document - C" << std::endl;
	std::cin >> letter;
	if (letter == 'P') {
		res.type = user_command::open_new_document;
	}
	else if (letter == 'C') {
		res.type = user_command::close_new_document;
	}
	else {
		throw std::exception("Wrong input");
	}
	return res;
}

std::string get_filename_from_user() {
	std::string filename;
	std::cout << "Input filename" << std::endl;
	std::cin >> filename;
	return filename;
}

void process_user_input(const user_command& cmd) {
	std::cout << "Process user input" << std::endl;
}

bool done_editing() {	
	return false;
}

int main(int argc, char** argv) {
	edit_document("abc.txt");
}