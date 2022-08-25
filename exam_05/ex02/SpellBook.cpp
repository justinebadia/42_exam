#include "SpellBook.hpp"
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

SpellBook::SpellBook()
{

}

SpellBook::~SpellBook()
{

}

void SpellBook::learnSpell(ASpell* spell)
{
	if (spell)
		book.push_back(spell);
	return;
}

void SpellBook::forgetSpell(const string& spell_name)
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

ASpell* SpellBook::createSpell(const string& spell_name)
{
	vector<ASpell*>::iterator it = book.begin();
	vector<ASpell*>::iterator ite = book.end();
	
	if (spell_name.empty())
		return NULL;
	for (; it != ite; it++)
	{
		if ((*it)->getName() == spell_name)
			return ((*it)->clone());
	}
	return NULL;
}