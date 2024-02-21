#include <thread>
#include <stdexcept>
#include <iostream>

class scoped_thread {
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :
		t(std::move(t_)) {
		if (!t.joinable()) {
			throw std::logic_error("No thread");
		}
	}
	~scoped_thread() {
		t.join();
	}
	scoped_thread(const scoped_thread&) = delete;
	scoped_thread& operator=(const scoped_thread&) = delete;
};

struct func {
	int& i;
	func(int& i_) : i(i_) {}
	void operator()() {
		unsigned calculate_fib(unsigned);
		std::cout << "Calculating process" << std::endl;
		for (unsigned j = 0; j < 1000000; ++j) {
			calculate_fib(j);
		}
	}
};

void f() {
	int some_local_state;
	scoped_thread{ std::thread(func(some_local_state)) };
	std::cout << "Hello" << std::endl;
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