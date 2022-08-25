#ifndef SpellBook_HPP
#define SpellBook_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

class ASpell;
class ATarget;

class SpellBook
{
	public :
		SpellBook();
		~SpellBook();

		void learnSpell(ASpell* spell);
		void forgetSpell(const string& spell_name);
		ASpell* createSpell(const string& spell_name);

		vector<ASpell *> book;


	private:
		SpellBook(const SpellBook& copy);
		SpellBook& operator=(const SpellBook& copy);
		
};

#endif