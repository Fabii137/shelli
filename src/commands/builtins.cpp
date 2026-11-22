#include "builtins.hpp"
#include "builtins/cd.hpp"
#include "commands/builtins/exit.hpp"
#include "commands/result.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

using Builtin = std::function<CommandResult(const std::vector<std::string>&)>;

static const std::unordered_map<std::string, Builtin> builtins = {
	{ "cd", cd },
	{ "exit", builtin_exit },
};

bool is_builtin(const std::string& command) {
	return builtins.contains(command);
}

CommandResult run_builtin(const std::vector<std::string>& args) {
	if (args.empty()) {
		return { .status = 1 };
	}

	auto it = builtins.find(args[0]);
	if (it != builtins.end()) {
		return it->second(args);
	}

	return { .status = 1 };
}