#include "aliases.hpp"
#include <unordered_map>

static const std::unordered_map<std::string, std::string> aliases {
	{ "ls", "ls --color=auto" },
};

std::optional<std::string> get_alias(const std::string& command) {
	auto it = aliases.find(command);
	if (it != aliases.end()) {
		return it->second;
	}

	return std::nullopt;
}