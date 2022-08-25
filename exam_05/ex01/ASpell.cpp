#include "ASpell.hpp"
#include <iostream>
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

ASpell::ASpell()
{

}

ASpell::ASpell(const string& N, const string& E) : name(N), effects(E) 
{
}


ASpell::~ASpell()
{
}

ASpell::ASpell(const ASpell& copy)
{
	*this = copy;
}

ASpell& ASpell::operator=(const ASpell& copy)
{
	if (this != &copy)
	{
		name = copy.name;
		effects = copy.effects;
	}
	return *this;
}

const string& ASpell::getName( void ) const { return name; }
const string& ASpell::getEffects( void ) const { return effects; }

void ASpell::launch( const ATarget& target ) const
{
	target.getHitBySpell(*this);
}