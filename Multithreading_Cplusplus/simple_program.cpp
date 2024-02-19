#include <iostream>
#include <thread>
void hello()
{
	std::cout << "Hello Concurrent World\n";
}
void simple_program_func()
{
	std::thread t(hello);
	t.join();
}