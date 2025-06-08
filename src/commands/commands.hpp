#pragma once

#include "../core/Environment.hpp"

namespace commands {

void registerExit(core::Environment&);
void registerHelp(core::Environment&);
void registerList(core::Environment&);
void registerLoad(core::Environment&);
void registerShow(core::Environment&);
void registerSelect(core::Environment&);
void registerScope(core::Environment&);

inline void registerCommands(core::Environment& env) {
	registerExit(env);
	registerHelp(env);
	registerList(env);
	registerLoad(env);
	registerShow(env);
	registerSelect(env);
	registerScope(env);
}

} // namespace commands
