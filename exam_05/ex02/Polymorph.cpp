#include "Polymorph.hpp"
#include <iostream>
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

Polymorph::Polymorph() : ASpell("Polymorph", "turned into a critter")
{

}

Polymorph::~Polymorph()
{
}

Polymorph::Polymorph(const Polymorph& copy) : ASpell(copy)
{
	*this = copy;
}

Polymorph& Polymorph::operator=(const Polymorph& copy)
{
	if (this != &copy)
	{
		name = copy.name;
		effects = copy.effects;
	}
	return *this;
}

ASpell* Polymorph::clone( void ) const { return (new Polymorph()); }
