#include <thread>
#include <iostream>
#include <random>

unsigned calculate_fib(unsigned n);
void action_in_current_thread();

struct func {
	int& i;
	func(int& i_) : i(i_) {}
	void operator()() {
		std::cout << "Calculating process" << std::endl;
		for (unsigned j = 0; j < 1000000; ++j) {
			calculate_fib(j);
		}
	}
};

void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);

	try {
		action_in_current_thread();
	}
	catch (...) {
		t.join();
		throw;
	}
	t.join();
}

unsigned calculate_fib(unsigned n) {
	if (n <= 0) {
		return 0;
	}
	if (n == 1 || n == 2) {
		return 1;
	}

	unsigned prev = 1;
	unsigned prevprev = 1;

	for (unsigned i = 2; i < n; ++i) {
		unsigned t = prev + prevprev;
		prevprev = prev;
		prev = t;
	}

	return prev;
}

void action_in_current_thread() {	
	throw std::exception("Exception");
}

int waiting_for_finishing_a_thread() {
	
	try {
		f();
	}
	catch (...) {
		std::cerr << "An exception has been caught" << std::endl;
	}

	return 0;
}