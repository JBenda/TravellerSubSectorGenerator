#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

class Confederation
{
public:
	Confederation(std::string name, std::shared_ptr<Confederation> leader) 
	{
		this->name = name;
		this->leading = leader;
	}
	~Confederation() {}
	std::string getName() { return name; }
	std::shared_ptr<Confederation> getLeader() { return leading; }
private:
	std::string name;
	std::shared_ptr<Confederation> leading;
};