#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value) {
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

struct func {
	int& i_;
	func(int i) : i_(i) {}
	void operator()() {
		std::cout << list_contains(i_);
	}
};

void f() {
	int some_local_state = 5;
	func my_func(some_local_state);
	
	std::thread t(my_func);

	add_to_list(5);

	t.join();
}


int main(int argc, char** argv) {
	f();

	return 0;
}