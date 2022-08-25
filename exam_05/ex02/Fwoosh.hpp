#ifndef Fwoosh_HPP
#define Fwoosh_HPP

#include <string>
#include "ASpell.hpp"
using std::string;

class ATarget;

class Fwoosh : public ASpell
{
	public :
		Fwoosh();
		Fwoosh(const Fwoosh& copy);
		Fwoosh& operator=(const Fwoosh& copy);
		~Fwoosh();

		ASpell* clone( void ) const ;
};

#endif