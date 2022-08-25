#include "Dummy.hpp"
#include <iostream>
#include "ASpell.hpp"

using std::cout;
using std::endl;
using std::string;

Dummy::Dummy() : ATarget("Target Practice Dummy")
{

}

Dummy::~Dummy()
{
}

Dummy::Dummy(const Dummy& copy) : ATarget(copy)
{
	*this = copy;
}

Dummy& Dummy::operator=(const Dummy& copy)
{
	if (this != &copy)
	{
		type = copy.type;
	}
	return *this;
}

ATarget* Dummy::clone( void ) const { return (new Dummy()); }