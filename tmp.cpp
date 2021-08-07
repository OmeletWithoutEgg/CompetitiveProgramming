#ifdef TAIL
}
#else
#ifndef HEAD
#define HEAD
#include <iostream>
int main() {
#include "tmp.cpp"
#else

#ifndef F1
#define F1
#include "tmp.cpp"
#include "tmp.cpp"
#define TAIL
#include "tmp.cpp"
#undef F1
#else
#ifndef F2
#define F2
#include "tmp.cpp"
#include "tmp.cpp"
#undef F2
#else
#ifndef F3
#define F3
#include "tmp.cpp"
#include "tmp.cpp"
#undef F3
#else
std::cout << "!!!" << std::endl;
#endif // !F3
#endif // !F2
#endif // !F1

#endif // !HEAD
#endif // TAIL
