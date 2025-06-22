#include <ncurses.h>
#include "App.hpp"
#include "../commands/commands.hpp"
#include "../models/models.hpp"

App::App(): env(core::Environment{ store, interface }){}

// Properly terminate the ncurses context
App::~App() { endwin(); }

void App::init() {
	commands::registerCommands(env);
	store.add("exitPending", &exitPending);
	store.add("dataScopeState", models::DataScopeState{});
	store.add("timelines", models::TimelineMap{});
	initialized = true;
}

bool App::run() {
	if (!initialized) return false;
	interface.run("> ");
	return !exitPending;
}
