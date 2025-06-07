#pragma once

#include "../core/Environment.hpp"

class App {

public:
	App();
	void init();
	bool run();

private:
	bool initialized = false;
	bool exitPending = false;

	core::Display display;
	core::Interface interface;
	core::Store store;
	core::Environment env;
};
