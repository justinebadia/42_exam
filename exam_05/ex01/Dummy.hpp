#ifndef Dummy_HPP
#define Dummy_HPP

#include <string>
#include "ATarget.hpp"
using std::string;

class ASpell;

class Dummy : public ATarget
{
	public :
	 	Dummy();
		Dummy(const Dummy& copy);
		Dummy& operator=(const Dummy& copy);
		~Dummy();

		ATarget* clone( void ) const;
		
};

#endif