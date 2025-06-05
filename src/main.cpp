#include <iostream>

#include "core/Environment.hpp"
#include "models/TempTimeline.hpp"

int main(){
	
	core::Store store {};
	core::Environment env { store };

	models::TempReading reading { models::Timestamp {}, 4.32 };
	std::vector<models::TempReading> readings { reading };
	models::TempTimeline timeline { "FR", readings };

	env.store.add("test", timeline);
	std::cout << env.store.get<models::TempTimeline>("test").countryCode << std::endl;

	return 0;
}
