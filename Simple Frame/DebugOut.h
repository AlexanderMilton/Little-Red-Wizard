#ifndef _DEBUG_OUT_
#define _DEBUG_OUT_

#include <string>

struct dbgo
{
public:
	static void print(std::string output);
	static void println(std::string output);
	static std::string debugOutFile;
};
#endif