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
		book.push_back(spell);
	return;
}

void Warlock::forgetSpell(const string& spell_name)
{
	vector<ASpell*>::iterator it = book.begin();
	vector<ASpell*>::iterator ite = book.end();
	
	if (spell_name.empty())
		return ;
	for (; it != ite; it++)
	{
		if ((*it)->getName() == spell_name)
			book.erase(it);
	}
	return ;
}

void Warlock::launchSpell(const string& spell_name, const ATarget& target)
{
	vector<ASpell*>::iterator it = book.begin();
	vector<ASpell*>::iterator ite = book.end();
	
	if (spell_name.empty())
		return ;
	for (; it != ite; it++)
	{
		if ((*it)->getName() == spell_name)
			(*it)->launch(target);
	}
	return ;
}