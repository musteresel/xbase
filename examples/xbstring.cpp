#include <xbase64/xbase64.h>

int main() {
	xbString s1;
	xbString s2;

	std::cout << "Xbstring sample program" << std::endl;
	std::cout << "This program demonstrates xbString class usage" << std::endl;

	s1 = "Some string data";
	s2 = "some more string data";

	std::cout << "s1 => " << s1 << std::endl;
	std::cout << "s2 => " << s2 << std::endl;

	s1 = "s1   ";
	s2 = "s2";
	s1 -= s2;

	std::cout << "-= operator => " << s1 << std::endl;

	s1 = "s1   ";
	s2 = "s2";
	s1 += s2;

	std::cout << "+= operator => " << s1 << std::endl;

	s1 = "some data";
	s2 = s1.mid(2, 3);
	std::cout << "mid() = " << s2 << std::endl;

	s1.setNum((xbLong)123456789);
	std::cout << "setNum(xbLong) = " << s1 << std::endl;

	s1.setNum("4.4", (xbDouble)1234.56789);
	std::cout << "setNum(xbDouble) = " << s1 << std::endl;

	return 0;
}
