#include "Warlock.hpp"
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

Warlock::Warlock()
{

}

Warlock::Warlock(const string& N, const string& T) : name(N), title(T)
{
	cout << getName() << ": This looks like another boring day." << endl;
}


Warlock::~Warlock()
{
	cout << getName() << ": My job here is done!" << endl;

}

Warlock::Warlock(const Warlock& copy)
{
	*this = copy;
}

Warlock& Warlock::operator=(const Warlock& copy)
{
	if (this != &copy)
	{
		name = copy.name;
		title = copy.title;
	}
	return *this;
}

const string& Warlock::getName( void ) const { return name; }
const string& Warlock::getTitle( void ) const { return title; }
void Warlock::setTitle( const string& new_title) { title = new_title; }

void Warlock::introduce( void ) const 
{
	cout << getName() << ": I am " << getName() << ", " << getTitle() << "!" << endl;
}

void Warlock::learnSpell(ASpell* spell)
{
	if (spell)
		book.learnSpell(spell);
	return;
}

void Warlock::forgetSpell(const string& spell_name)
{
	book.forgetSpell(spell_name);
}

void Warlock::launchSpell(const string& spell_name, const ATarget& target)
{
	const ATarget *temp = 0;
	if (temp == &target)
		return;
	ASpell* spell = book.createSpell(spell_name);
	if (spell)
		spell->launch(target);
}