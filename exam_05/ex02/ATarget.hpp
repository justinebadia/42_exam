#ifndef ATarget_HPP
#define ATarget_HPP

#include <string>
using std::string;

class ASpell;

class ATarget
{
	public :
	 	ATarget();
		ATarget(const string& T);
		ATarget(const ATarget& copy);
		ATarget& operator=(const ATarget& copy);
		virtual  ~ATarget();

		const string& getType(void) const;
		virtual ATarget* clone( void ) const = 0;
		void getHitBySpell( const ASpell& spell) const;
		

	protected:
		
		string	type;
};

#endif