#include <thread>
#include <vector>
#include <iostream>
#include <sstream>  

void do_work();
void f() {
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; ++i) {
		threads.emplace_back(do_work);
	}
	for (auto& entry : threads) {
		entry.join();
	}
}

void do_work() {
	std::stringstream ss;
	ss << "Hello from " << std::this_thread::get_id() << std::endl;
	std::cout << ss.str();
}

int main(int argc, char** argv) {
	f();
}