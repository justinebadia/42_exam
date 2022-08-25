#ifndef Polymorph_HPP
#define Polymorph_HPP

#include <string>
#include "ASpell.hpp"
using std::string;

class ATarget;

class Polymorph : public ASpell
{
	public :
		Polymorph();
		Polymorph(const Polymorph& copy);
		Polymorph& operator=(const Polymorph& copy);
		~Polymorph();

		ASpell* clone( void ) const ;
};

#endif