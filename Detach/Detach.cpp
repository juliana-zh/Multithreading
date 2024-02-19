#include <thread>
#include <iostream>

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
		std::cerr << prev << std::endl;
	}
	
	return prev;
}

int main(int argc, char **argv) {
	std::thread t(calculate_fib, 5);
	calculate_fib(100);
	t.detach();
}