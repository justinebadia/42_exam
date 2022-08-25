#ifndef Fireball_HPP
#define Fireball_HPP

#include <string>
#include "ASpell.hpp"
using std::string;

class ATarget;

class Fireball : public ASpell
{
	public :
		Fireball();
		Fireball(const Fireball& copy);
		Fireball& operator=(const Fireball& copy);
		~Fireball();

		ASpell* clone( void ) const ;
};

#endif