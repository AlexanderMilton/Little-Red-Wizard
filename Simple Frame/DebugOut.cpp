#include "DebugOut.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string dbgo::debugOutFile = "";

namespace
{
	void outputText(std::string output)
	{
		if(dbgo::debugOutFile.empty())
		{
			std::cout << output;
		}
		else
		{
			/* This'll probably give totally rotten performance if many writes.
			 * But that is a later problem. */
			std::ofstream stream(dbgo::debugOutFile, std::ios::app);
			stream << output;
			stream.close();
		}
	}
}

void dbgo::print(std::string output)
{
#ifndef NDEBUG
	outputText(output);
#endif
}

void dbgo::println(std::string output)
{
#ifndef NDEBUG
	outputText(output+="\n");
#endif
}