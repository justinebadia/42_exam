#include "TargetGenerator.hpp"
#include <iostream>
#include "ASpell.hpp"
#include "ATarget.hpp"

using std::cout;
using std::endl;
using std::string;

TargetGenerator::TargetGenerator()
{

}

TargetGenerator::~TargetGenerator()
{

}

void TargetGenerator::learnTargetType(ATarget* target)
{
	if (target)
		targen.push_back(target);
}

void TargetGenerator::forgetTargetType(string const& target_name)
{
	vector<ATarget*>::iterator it = targen.begin();
	vector<ATarget*>::iterator ite = targen.end();
	
	if (target_name.empty())
		return ;
	for (; it != ite; it++)
	{
		if ((*it)->getType() == target_name)
			targen.erase(it);
	}
}

ATarget* TargetGenerator::createTarget(string const& target_name)
{
	vector<ATarget*>::iterator it = targen.begin();
	vector<ATarget*>::iterator ite = targen.end();
	
	if (target_name.empty())
		return NULL;
	for (; it != ite; it++)
	{
		if ((*it)->getType() == target_name)
			return ((*it)->clone());
	}
	return NULL;
}