#pragma once

namespace Phantom {
template <typename T>
class Singleton {
public:
	static T& GetInstance() {
		static T s_Instance;
		return s_Instance;
	}

protected:
	Singleton() {};
	~Singleton() {};
private:
	Singleton(const Singleton& rhs) {}
	Singleton& operator = (const Singleton& rhs) {}
};
}
