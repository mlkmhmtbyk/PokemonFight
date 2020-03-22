#include <string>
#include "Attack.h"

using namespace std;

class Pokemon
{
public :
	string Name;
	int HP;
	int PP;
	Attack* Attacks; 
	Pokemon(string name, int hp, int pp);
	void AddAttack(Attack attack);
	~Pokemon();

private:
	int AttacksCount;
};

