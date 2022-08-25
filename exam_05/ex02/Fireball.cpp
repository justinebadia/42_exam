#include "Fireball.hpp"
#include <iostream>
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

Fireball::Fireball() : ASpell("Fireball", "burnt to a crisp")
{

}

Fireball::~Fireball()
{
}

Fireball::Fireball(const Fireball& copy) : ASpell(copy)
{
	*this = copy;
}

Fireball& Fireball::operator=(const Fireball& copy)
{
	if (this != &copy)
	{
		name = copy.name;
		effects = copy.effects;
	}
	return *this;
}

ASpell* Fireball::clone( void ) const { return (new Fireball()); }
