#include "Attack.h"

Attack::Attack(int id, string name, int pp, int accuracy, int damage, int firstUsage) {
	Id = id;
	Name = name;
	PP = pp;
	Accuracy = accuracy;
	Damage = damage;
	FirstUsage = firstUsage;
}

Attack::Attack() {
}
Attack::~Attack() {
}



