
#ifndef URLENCODE_HPP
#define URLENCODE_HPP

#include <string>
#include <stdlib.h>

std::string urlencode(const std::string &s);
void htmlspecialchars(std::string& data);
bool replace(std::string& str, const std::string& from, const std::string& to);

#endif
