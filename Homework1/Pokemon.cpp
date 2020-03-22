#include "Pokemon.h"

Pokemon::Pokemon(string name, int hp, int pp) {
	Name = name;
	HP = hp;
	PP = pp;
	AttacksCount = 0;
	Attacks = new Attack[4];
}
void Pokemon::AddAttack(Attack attack) {
	Attacks[AttacksCount++] = attack;
}
Pokemon::~Pokemon() {

}

