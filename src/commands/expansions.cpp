#include "expansions.hpp"

void expand_args(std::vector<std::string>& args, int last_status) {
	for (auto& arg : args) {
		if (arg == "$?") {
			arg = std::to_string(last_status);
		}
		if (arg == "~") {
			arg = std::getenv("HOME");
		}
	}
}