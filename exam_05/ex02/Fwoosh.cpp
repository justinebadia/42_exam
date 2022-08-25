#include "Fwoosh.hpp"
#include <iostream>
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

Fwoosh::Fwoosh() : ASpell("Fwoosh", "fwooshed")
{

}

Fwoosh::~Fwoosh()
{
}

Fwoosh::Fwoosh(const Fwoosh& copy) : ASpell(copy)
{
	*this = copy;
}

Fwoosh& Fwoosh::operator=(const Fwoosh& copy)
{
	if (this != &copy)
	{
		name = copy.name;
		effects = copy.effects;
	}
	return *this;
}

ASpell* Fwoosh::clone( void ) const { return (new Fwoosh()); }
