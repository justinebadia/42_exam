#ifndef BrickWall_HPP
#define BrickWall_HPP

#include <string>
#include "ATarget.hpp"
using std::string;

class ASpell;

class BrickWall : public ATarget
{
	public :
	 	BrickWall();
		BrickWall(const BrickWall& copy);
		BrickWall& operator=(const BrickWall& copy);
		~BrickWall();

		ATarget* clone( void ) const;
		
};

#endif