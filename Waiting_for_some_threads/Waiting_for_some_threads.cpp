#include <thread>
#include <vector>
#include <iostream>

void do_work(unsigned id);
void f() {
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; ++i) {
		threads.emplace_back(do_work, i);
	}
	for (auto& entry : threads) {
		entry.join();
	}
}

void do_work(unsigned id) {
	std::cout << "Hello from " << id << std::endl;
}

int main(int argc, char** argv) {
	f();
}