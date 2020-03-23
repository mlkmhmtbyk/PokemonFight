#include<stdio.h>  //(Standard input-output header)
#include<string.h> //(String header)
#include <vector>
#include <string>

using namespace std;
// ---------------------------------- CLASS SECTION ------------------------
//Generating CLASS for Attack
class Attack
{
public:
	string Name;
	int PP;
	int Accuracy;
	int Damage;
	int FirstUsage;
};

//Generating Class for Pokemon
class Pokemon
{
public:
	string Name;
	int HP;
	int PP;
	Attack Attacks[4];
};

//Generating Class for Graph's Node
class Node
{
public:
	int ID;
	Pokemon Pikachu;
	Pokemon Blastoise;
	char Turn;
	double Porbablity;
	int Level;
	bool IsLeaf;
};
// --------------------------------------- METHODS --------------------------------
vector<Node> NextLevel(Node parentNode, vector<Node> nodeList);

vector<Node> NextLevel(Node parentNode, vector<Node> nodeList) {
	

	if (parentNode.Turn == 'P' && !parentNode.IsLeaf) { // Pikachu's Turn
		for (int i = 0; i < 4; i++) {//4 loop for every attack possibilty
			Node node; //child node
			int idCounter = parentNode.ID + 1;
			node.ID = idCounter;			
			node.Pikachu = parentNode.Pikachu;
			node.Blastoise = parentNode.Blastoise;
			node.Turn = parentNode.Turn;
			node.Level = parentNode.Level;
			node.IsLeaf = parentNode.IsLeaf;
			node.Porbablity = parentNode.Porbablity;

			//calculate the current statistics
			if (i == 0) {  //the Thunder Shock attack step
				node.Pikachu.PP = node.Pikachu.PP + node.Pikachu.Attacks[0].PP;
				if (node.Pikachu.PP >= 0) {  // if current PP is not less than 0(that means attack can be used)
					node.Blastoise.HP = node.Blastoise.HP - node.Pikachu.Attacks[0].Damage;
					node.Turn = 'B';
					node.Level = node.Level + 1;
					if (node.Level < 3) { node.Porbablity = node.Porbablity / double(3); }
					else { node.Porbablity = node.Porbablity / double(4); }//added the possibilty of skip attack
					if (node.Blastoise.HP <= 0) { node.IsLeaf = 1; } //Control of the K.O
					else { node.IsLeaf = 0; }

					nodeList.push_back(node); //pushing the new generated node to the nodeList
					NextLevel(node, nodeList); //recursively generate new nodes untill K.O
				}
				else { idCounter--; }
			}
			else if (i == 1) {//the Skull Bash attack step

				Node nodeMissSkull; //miss attack case node generated
				idCounter++;
				nodeMissSkull.ID = idCounter;
				nodeMissSkull.Pikachu = parentNode.Pikachu;
				nodeMissSkull.Blastoise = parentNode.Blastoise;
				nodeMissSkull.Turn = parentNode.Turn;
				nodeMissSkull.Level = parentNode.Level;
				nodeMissSkull.IsLeaf = parentNode.IsLeaf;

				node.Pikachu.PP = node.Pikachu.PP + node.Pikachu.Attacks[1].PP;//pp calculated
				nodeMissSkull.Pikachu.PP = nodeMissSkull.Pikachu.PP + nodeMissSkull.Pikachu.Attacks[1].PP;
				if (node.Pikachu.PP >= 0 && nodeMissSkull.Pikachu.PP >= 0) {  // if current PPs is not less than 0(that means attack can be used)
					node.Blastoise.HP = node.Blastoise.HP - node.Pikachu.Attacks[1].Damage; //no damage calc. for miss 
					node.Turn = 'B';
					nodeMissSkull.Turn = 'B';
					node.Level = node.Level + 1;
					nodeMissSkull.Level = nodeMissSkull.Level + 1;
					if (node.Level < 3) { //no permission to skip (Same level for nodeMissSkull)
						node.Porbablity = (node.Porbablity * (node.Pikachu.Attacks[1].Accuracy / 100)) / double(3);
						nodeMissSkull.Porbablity = (nodeMissSkull.Porbablity * (double(1) - (nodeMissSkull.Pikachu.Attacks[1].Accuracy / 100))) / double(3); ///// Work On numbers
					}
					else {//added the possibilty of skip attack
						node.Porbablity = (node.Porbablity * (node.Pikachu.Attacks[1].Accuracy / 100)) / double(4);
						nodeMissSkull.Porbablity = (nodeMissSkull.Porbablity * (double(1) - (nodeMissSkull.Pikachu.Attacks[1].Accuracy / 100))) / double(4);
					}

					if (node.Blastoise.HP <= 0) { node.IsLeaf = 1; }
					else { node.IsLeaf = 0; }
					nodeMissSkull.IsLeaf = 0; // not possible to kill the Blastoise with missed attack
					nodeList.push_back(node);//Pushing the nodes to the nodeList
					nodeList.push_back(nodeMissSkull);//multiple nodes added for miss
					NextLevel(node, nodeList);//Recursively keep generating untill K.O
					NextLevel(nodeMissSkull, nodeList);//Recursively keep generating untill K.O
				}
				else { idCounter--; }
			}
			else if (i == 2) {//The Slam Attack step
				Node nodeMissSlam; //miss attack case node generated
				idCounter++;
				nodeMissSlam.ID = idCounter;
				nodeMissSlam.Pikachu = parentNode.Pikachu;
				nodeMissSlam.Blastoise = parentNode.Blastoise;
				nodeMissSlam.Turn = parentNode.Turn;
				nodeMissSlam.Level = parentNode.Level;
				nodeMissSlam.IsLeaf = parentNode.IsLeaf;

				node.Pikachu.PP = node.Pikachu.PP + node.Pikachu.Attacks[2].PP;// PP calculated
				nodeMissSlam.Pikachu.PP = nodeMissSlam.Pikachu.PP + nodeMissSlam.Pikachu.Attacks[2].PP;
				if (node.Pikachu.PP >= 0 && nodeMissSlam.Pikachu.PP >= 0) {
					node.Blastoise.HP = node.Blastoise.HP - node.Pikachu.Attacks[2].Damage;//damage calculation
					node.Turn = 'B';
					nodeMissSlam.Turn = 'B';
					node.Level = node.Level + 1;
					nodeMissSlam.Level = nodeMissSlam.Level + 1;
					if (node.Level < 3) {//no permission to skip
						node.Porbablity = (node.Porbablity * (node.Pikachu.Attacks[2].Accuracy / 100)) / double(3);
						nodeMissSlam.Porbablity = (nodeMissSlam.Porbablity * (double(1) - nodeMissSlam.Pikachu.Attacks[2].Accuracy / 100)) / double(3) ;
					}
					else {
						node.Porbablity = (node.Porbablity * (node.Pikachu.Attacks[2].Accuracy / 100)) / double(4);
						nodeMissSlam.Porbablity = (nodeMissSlam.Porbablity * (double(1) - nodeMissSlam.Pikachu.Attacks[2].Accuracy / 100)) / double(4);
					}

					if (node.Blastoise.HP <= 0) { node.IsLeaf = 1; }//blastoise is K.O
					else { node.IsLeaf = 0; }
					nodeMissSlam.IsLeaf = 0; // not possible to kill the Blastoise with missed attack
					nodeList.push_back(node);//Pushing the nodes to the nodeList
					nodeList.push_back(nodeMissSlam);//multiple nodes added for miss
					NextLevel(node, nodeList);//Recursively keep generating
					NextLevel(nodeMissSlam, nodeList);//Recursively keep generating untill K.O
				}
				else { idCounter--; }
			}
			else { // i == 3 so skip attack step
				if (node.Level >= 2 && node.Pikachu.PP < 100) {//check if the first usage passed
					node.Pikachu.PP = node.Pikachu.PP + node.Pikachu.Attacks[3].PP;// PP calculated
					node.Turn = 'B';//No need to control PP and calc blastoise.HP and no miss possibilty
					node.Level = node.Level + 1;
					node.Porbablity = (node.Porbablity * (node.Pikachu.Attacks[3].Accuracy / 100)) / double(4);//probablity of skip
					nodeList.push_back(node);//Pushing the node to the nodeList
					NextLevel(node, nodeList);//No way to K.O and IsLeaf
				}
			}
		}
	}
	else if (parentNode.Turn == 'B' && !parentNode.IsLeaf) { //Blastoise's Turn
		for (int i = 0; i < 4; i++) { //4 case for each attack		
			Node node;//child node
			int idCounter = parentNode.ID + 1;
			node.ID = idCounter;
			idCounter++;
			node.Pikachu = parentNode.Pikachu;
			node.Blastoise = parentNode.Blastoise;
			node.Turn = parentNode.Turn;
			node.Level = parentNode.Level;
			node.IsLeaf = parentNode.IsLeaf;
			node.Porbablity = parentNode.Porbablity;

			//calculate the current statistics
			if (i == 0) {  //the Tackle attack step
				node.Blastoise.PP = node.Blastoise.PP + node.Blastoise.Attacks[0].PP;
				if (node.Blastoise.PP >= 0) {  // if current PP is not less than 0(that means attack can be used)
					node.Pikachu.HP = node.Pikachu.HP - node.Blastoise.Attacks[0].Damage;
					node.Turn = 'P';
					node.Level = node.Level + 1;
					if (node.Level < 3) { node.Porbablity = (node.Porbablity) / double(3); }//calc possibilty at first 3 step
					else { node.Porbablity = parentNode.Porbablity / double(4); }//added the possibilty of skip attack
					if (node.Pikachu.HP <= 0) { node.IsLeaf = 1; } //Control of the K.O
					else { node.IsLeaf = 0; }

					nodeList.push_back(node); //pushing the new generated node to the nodeList
					NextLevel(node, nodeList); //recursively generate new nodes untill K.O
				}
				else { idCounter--; }
			}
			else if (i == 1) {  //the Watergun attack step
				node.Blastoise.PP = node.Blastoise.PP + node.Blastoise.Attacks[1].PP;
				if (node.Blastoise.PP >= 0) {  // if current PP is not less than 0(that means attack can be used)
					node.Pikachu.HP = node.Pikachu.HP - node.Blastoise.Attacks[1].Damage;
					node.Turn = 'P';
					node.Level = node.Level + 1;
					if (node.Level < 3) { node.Porbablity = node.Porbablity / double(3); }//calc possibilty at first 3 step
					else { node.Porbablity = node.Porbablity / double(4); }//added the possibilty of skip attack
					if (node.Pikachu.HP <= 0) { node.IsLeaf = 1; } //Control of the K.O
					else { node.IsLeaf = 0; }

					nodeList.push_back(node); //pushing the new generated node to the nodeList
					NextLevel(node, nodeList); //recursively generate new nodes untill K.O
				}
				else { idCounter--; }
			}

			else if (i == 2) {  //the Bite attack step
				node.Blastoise.PP = node.Blastoise.PP + node.Blastoise.Attacks[2].PP;
				if (node.Blastoise.PP >= 0) {  // if current PP is not less than 0(that means attack can be used)
					node.Pikachu.HP = node.Pikachu.HP - node.Blastoise.Attacks[2].Damage;
					node.Turn = 'P';
					node.Level = node.Level + 1;
					if (node.Level < 3) { node.Porbablity = node.Porbablity / double(3); }//calc possibilty at first 3 step
					else { node.Porbablity = node.Porbablity / double(4); }//added the possibilty of skip attack
					if (node.Pikachu.HP <= 0) { node.IsLeaf = 1; } //Control of the K.O
					else { node.IsLeaf = 0; }

					nodeList.push_back(node); //pushing the new generated node to the nodeList
					NextLevel(node, nodeList); //recursively generate new nodes untill K.O
				}
				else { idCounter--; }
			}
			else if(node.Level >= 2 && node.Blastoise.PP < 100) {  //the skip attack step i == 3
				node.Blastoise.PP = node.Blastoise.PP + node.Blastoise.Attacks[3].PP;//PP + 100							
				node.Turn = 'P'; // no need to check K.O (isLeaf)
				node.Level = node.Level + 1;
				if (node.Level < 3) { node.Porbablity = node.Porbablity / double(3); }//calc possibilty at first 3 step
				else { node.Porbablity = node.Porbablity / double(4); }//added the possibilty of skip attack

				nodeList.push_back(node); //pushing the new generated node to the nodeList
				NextLevel(node, nodeList); //recursively generate new nodes untill K.O				
			}
		}
	}
	else {
		// K.O
	}
	return nodeList;
}
//---------------------------------------------- MAIN -----------------------
int main() {

	//Generating the Pokemon - PIKACHU
	Pokemon pikachu;

	pikachu.Name = "Pikachu"; pikachu.HP = 150; pikachu.PP = 100;
	//Adding attacks to Pikachu
	pikachu.Attacks[0].Name = "Thundershock"; pikachu.Attacks[0].PP = -10; pikachu.Attacks[0].Accuracy = 100; pikachu.Attacks[0].Damage = 40; pikachu.Attacks[0].FirstUsage = 0;
	pikachu.Attacks[1].Name = "Skull Bash"; pikachu.Attacks[1].PP = -15; pikachu.Attacks[1].Accuracy = 70; pikachu.Attacks[1].Damage = 50; pikachu.Attacks[1].FirstUsage = 0;
	pikachu.Attacks[2].Name = "Slam"; pikachu.Attacks[2].PP = -20; pikachu.Attacks[2].Accuracy = 80; pikachu.Attacks[2].Damage = 60; pikachu.Attacks[2].FirstUsage = 0;
	pikachu.Attacks[3].Name = "Skip"; pikachu.Attacks[3].PP = 100; pikachu.Attacks[3].Accuracy = 100; pikachu.Attacks[3].Damage = 0; pikachu.Attacks[3].FirstUsage = 3;

	//Generating the Pokemon - BLASTOISE
	Pokemon blastoise;

	blastoise.Name = "Blastoise"; blastoise.HP = 150; blastoise.PP = 100;
	//Adding attacks to Blastoise
	blastoise.Attacks[0].Name = "Tackle"; blastoise.Attacks[0].PP = -10; blastoise.Attacks[0].Accuracy = 100; blastoise.Attacks[0].Damage = 30; blastoise.Attacks[0].FirstUsage = 0;
	blastoise.Attacks[1].Name = "Water Gun"; blastoise.Attacks[1].PP = -20; blastoise.Attacks[1].Accuracy = 100; blastoise.Attacks[1].Damage = 40; blastoise.Attacks[1].FirstUsage = 0;
	blastoise.Attacks[2].Name = "Bite"; blastoise.Attacks[2].PP = -25; blastoise.Attacks[2].Accuracy = 100; blastoise.Attacks[2].Damage = 60; blastoise.Attacks[2].FirstUsage = 0;
	blastoise.Attacks[3].Name = "Skip"; blastoise.Attacks[3].PP = 100; blastoise.Attacks[3].Accuracy = 100; blastoise.Attacks[3].Damage = 0; blastoise.Attacks[3].FirstUsage = 3;

	//Generating the first node of the graph
	Node firstNode;
	//filling the attributes of firstNode object
	firstNode.ID = 0;
	firstNode.Pikachu = pikachu;
	firstNode.Blastoise = blastoise;
	firstNode.Turn = 'P';
	firstNode.Level = 0;
	firstNode.IsLeaf = 0;
	firstNode.Porbablity = 1;
	
	vector<Node> nodeList;
	nodeList.push_back(firstNode);
	
	NextLevel(firstNode, nodeList);

	return 0;
}


