#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
using std::string;

class Warlock
{
	public :
		Warlock(const string& N, const string& T);
		~Warlock();

		const string& getName(void) const;
		const string& getTitle(void) const;
		void setTitle(const string& new_title);
		void introduce(void) const;

	private:
		Warlock();
		Warlock(const Warlock& copy);
		Warlock& operator=(const Warlock& copy);
		
		string	name;
		string title;
};

#endif