#ifndef FUNCTIONS
#define FUNCTIONS 1

#include <fstream>
#include <sstream>
#include <string>

std::string loadfile(const char* name);
inline bool checkChar(const char& ch);
void stripComments(std::string& str);

#endif
