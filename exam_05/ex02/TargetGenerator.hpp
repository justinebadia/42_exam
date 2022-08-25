#ifndef TargetGenerator_HPP
#define TargetGenerator_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

class ASpell;
class ATarget;

class TargetGenerator
{
	public :
		TargetGenerator();
		~TargetGenerator();

	void learnTargetType(ATarget*);
	void forgetTargetType(string const &target_name);
	ATarget* createTarget(string const &target_name);

	vector<ATarget*> targen;

	private:
		TargetGenerator(const TargetGenerator& copy);
		TargetGenerator& operator=(const TargetGenerator& copy);
		
};

#endif