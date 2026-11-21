#include "builtins.hpp"
#include "builtins/cd.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

using Builtin = std::function<int(const std::vector<std::string>&)>;

static const std::unordered_map<std::string, Builtin> builtins = {
	{ "cd", cd },
};

bool is_builtin(const std::string& command) {
	return builtins.contains(command);
}

int run_builtin(const std::vector<std::string>& args) {
	if (args.empty()) {
		return 1;
	}

	auto it = builtins.find(args[0]);
	if (it != builtins.end()) {
		return it->second(args);
	}

	return 1;
}