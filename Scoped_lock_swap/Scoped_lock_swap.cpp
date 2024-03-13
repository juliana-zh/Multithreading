#include <thread>
#include <vector>
#include <mutex>

class some_big_object {
	std::vector<int> some_big_data;
};

class X {
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(const some_big_object& sd) : some_detail(sd) {}
	friend void swap(X& lhs, X& rhs) {
		if (&lhs == &rhs) {
			return;
		}
		
		std::scoped_lock guard(lhs.m, rhs.m);
		std::swap(lhs.some_detail, rhs.some_detail);
	}
};