#include "StdString.h"
#include <iostream>

int main(int argc, char** argv)
{
	CStdString str;
	str.Format("%d %s", 12, "Hey!");
	std::cout << str.c_str() << std::endl;
	return 0;
}