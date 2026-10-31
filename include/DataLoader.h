#pragma once
#include "Title.h"
#include <string>
#include <vector>

std::vector<Title> loadTitles(const std::string& basicsPath,
                              const std::string& ratingsPath);