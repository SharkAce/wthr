#include "app/App.hpp"

int main() {
	App app {};
	app.init();
	while (app.run());
	return 0;
}
