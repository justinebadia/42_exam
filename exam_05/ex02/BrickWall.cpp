#include "BrickWall.hpp"
#include <iostream>
#include "ASpell.hpp"

using std::cout;
using std::endl;
using std::string;

BrickWall::BrickWall() : ATarget("Inconspicuous Red-brick Wall")
{

}

BrickWall::~BrickWall()
{
}

BrickWall::BrickWall(const BrickWall& copy) : ATarget(copy)
{
	*this = copy;
}

BrickWall& BrickWall::operator=(const BrickWall& copy)
{
	if (this != &copy)
	{
		type = copy.type;
	}
	return *this;
}

ATarget* BrickWall::clone( void ) const { return (new BrickWall()); }