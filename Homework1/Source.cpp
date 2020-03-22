#include<stdio.h>  //(Standard input-output header)
#include<string.h> //(String header)
#include "Pokemon.h"
#include "Attack.h"

using namespace std;

Pokemon CreatePikachu();
Pokemon CreateBlastoise();

int main() {
	Pokemon pikachu = CreatePikachu();
	Pokemon blastoise = CreateBlastoise();

	string a = pikachu.Attacks[1].Name;
	return 0;
}

Pokemon CreatePikachu() {
	Pokemon result = Pokemon("Pikachu", 273, 100);
	result.AddAttack(Attack(1, "Thundershock", -10, 100, 40, 0));
	result.AddAttack(Attack(2, "Skull Bash", -15, 70, 50, 0));
	result.AddAttack(Attack(3, "Slam", -20, 80, 60, 0));
	result.AddAttack(Attack(4, "Skip", 100, 100, 0, 3));

	return result;
}

Pokemon CreateBlastoise() {
	Pokemon result = Pokemon("Blastoise", 361, 100);
	result.AddAttack(Attack(1, "Tackle", -10, 100, 30, 0));
	result.AddAttack(Attack(2, "Water Gun", -20, 100, 40, 0));
	result.AddAttack(Attack(3, "Bite", -25, 100, 60, 0));
	result.AddAttack(Attack(4, "Skip", 100, 100, 0, 3));

	return result;
}