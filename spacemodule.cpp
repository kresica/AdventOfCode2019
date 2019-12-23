#include "spacemodule.h"

SpaceModule::SpaceModule(unsigned int mass)
{
	_mass = mass;
}

unsigned int SpaceModule::getMass()
{
	return _mass;
}
