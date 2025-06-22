#pragma once

#include "../core/Environment.hpp"

class App {

public:
	App();
	~App();
	void init();
	bool run();

private:
	bool initialized = false;
	bool exitPending = false;

	core::Interface interface;
	core::Store store;
	core::Environment env;
};
