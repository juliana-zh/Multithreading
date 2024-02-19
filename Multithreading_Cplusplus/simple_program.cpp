#include <iostream>
#include <thread>
void hello()
{
	std::cout << "Hello Concurrent World\n";
}
void f()
{
	std::thread t(hello);
	t.join();
}

int main(int argc, char** argv) {
	f();
}