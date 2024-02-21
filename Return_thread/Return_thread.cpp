#include <thread>
#include <iostream>

std::thread f()
{
	void some_function();
	return std::thread(some_function);
}
std::thread g()
{
	void some_other_function(unsigned);
	std::thread t(some_other_function, 42);
	return t;
}

void some_function() {
	std::cout << "Hello" << std::endl;
}

void some_other_function(unsigned n) {
	unsigned calculate_fib(unsigned);
	std::cout << calculate_fib(n) << std::endl;
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
	std::thread t1 = f();
	t1.join();

	std::thread t2 = g();
	t2.join();

	return 0;
}