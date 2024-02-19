#include <thread>
#include <iostream>

void do_action_in_current_thread();
unsigned calculate_fib(unsigned);

class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :
		t(t_)
	{}
	~thread_guard() {
		if (t.joinable()) {
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

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
	thread_guard g(t);
	do_action_in_current_thread();
}

void do_action_in_current_thread() {
	std::cout << "Start action" << std::endl;
	//throw std::exception("exception");
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

int main(int argc, char** argv) {
	f();
	return 0;
}