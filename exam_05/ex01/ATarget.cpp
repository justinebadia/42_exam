#include "ATarget.hpp"
#include <iostream>
#include "ASpell.hpp"

using std::cout;
using std::endl;
using std::string;

ATarget::ATarget()
{

}

ATarget::ATarget(const string& T) : type(T)
{
}


ATarget::~ATarget()
{
}

ATarget::ATarget(const ATarget& copy)
{
	*this = copy;
}

ATarget& ATarget::operator=(const ATarget& copy)
{
	if (this != &copy)
	{
		type = copy.type;
	}
	return *this;
}

const string& ATarget::getType( void ) const { return type; }

void ATarget::getHitBySpell( const ASpell& spell) const
{
	cout << getType() << " has been " << spell.getEffects() << "!" << endl;
}