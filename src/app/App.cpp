#include "App.hpp"

#include "../commands/commands.hpp"
#include "../models/DataScope.hpp"

App::App(): env(core::Environment{ store, interface, display }){}

void App::init() {
	commands::registerCommands(env);
	store.add("exitPending", &exitPending);
	store.add("dataScopeState", models::DataScopeState{});
	initialized = true;
}

bool App::run() {
	if (!initialized) return false;
	interface.run("> ");
	return !exitPending;
}
