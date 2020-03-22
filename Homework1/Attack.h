#pragma once
#include <string>

using namespace std;

class Attack
{
public:
	int Id;
	string Name;
	int PP;
	int Accuracy;
	int Damage;
	int FirstUsage;
	
	Attack(int id, string name, int pp, int accuracy, int damage, int firstUsage);
	Attack();
	~Attack();
	
};

