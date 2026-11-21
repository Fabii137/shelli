#include "alias.hpp"
#include <unordered_map>

static const std::unordered_map<std::string, std::string> alias_map {
	{ "ls", "ls --color=auto" },
};

std::optional<std::string> get_alias(const std::string& command) {
	auto it = alias_map.find(command);
	if (it != alias_map.end()) {
		return it->second;
	}

	return std::nullopt;
}