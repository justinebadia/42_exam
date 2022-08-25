#ifndef ASpell_HPP
#define ASpell_HPP

#include <string>
using std::string;

class ATarget;

class ASpell
{
	public :
		ASpell();
		ASpell(const string& N, const string& E);
		ASpell(const ASpell& copy);
		ASpell& operator=(const ASpell& copy);
		virtual ~ASpell();

		const string& getName(void) const;
		const string& getEffects(void) const;
		virtual ASpell* clone( void ) const = 0;
		void launch( const ATarget& target ) const;
		

	protected:
		
		string	name;
		string effects;
};

#endif