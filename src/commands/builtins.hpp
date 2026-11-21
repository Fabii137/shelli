#pragma once

#include <string>
#include <vector>

bool is_builtin(const std::string& command);
int run_builtin(const std::vector<std::string>& args);