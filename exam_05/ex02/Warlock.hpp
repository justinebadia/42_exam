#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
#include <vector>
#include "SpellBook.hpp"

using std::string;
using std::vector;

class ASpell;
class ATarget;

class Warlock
{
	public :
		Warlock(const string& N, const string& T);
		~Warlock();

		const string& getName(void) const;
		const string& getTitle(void) const;
		void setTitle(const string& new_title);
		void introduce(void) const;

		void learnSpell(ASpell* spell);
		void forgetSpell(const string& spell_name);
		void launchSpell(const string& spell_name, const ATarget& target);

		SpellBook book;


	private:
		Warlock();
		Warlock(const Warlock& copy);
		Warlock& operator=(const Warlock& copy);
		
		string	name;
		string title;
};

#endif