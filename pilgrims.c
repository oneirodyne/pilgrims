#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*

   In this game, you must manage a English Colony in 1600s North America, it is text based
   and lightweight, so it can be played anywhere, on anything.

*/



const char startmsg[] = "\nMinister James : Captain! We have finally arrived in the New World, praise be God! This land is our salvation, but we must first figure out how to survive. So, I must teach you about resources and the commands we use to manipulate them!\n\nFood is the most important resource, the more population we have, the more we can harvest with the 'farm' command. If we have no food, our colony will starve\n\nPopulation is important, if we have less than 10, our colony will vanish. People can die in attacks, or in the mines. When people die, we lose piety.\n\nPiety can be gained with the 'pray' command. If we lose all faith, we cannot go on.\n\nResource can be gained with the 'prod' command. We need it to farm.\n\nIf you want to end the game, use the 'exit' command, if you want to end action mode, use the 'end' command.\n\nIf you want to deal with the native tribes, use the 'trib' command.\n\n";

// Declaring important functions

void dayloop();
void actionloop();
void endloop();
void tribeloop();

	// Declaring global variables

// Resources

int day = 1;
int food = 100;
int pop = 80;
int piety = 100;
int resource = 100;

// Tribal Stats

int relations = 50;

// Other

int ingame = 1;
int gameover = 0;

// Settings

int devmode = 0;

// Self explanatory, it's the main function that runs on start.

int main(void){

	printf("%s", startmsg);
	
	while(ingame == 1){	
	dayloop();
	actionloop();
	endloop();
	}

	// Testing Zone
	

	return 0;

}

// This function is used to update various variables, simulating a day passing

void dayloop(){

	printf("Day : %d\nFood : %d\nPopulation : %d\nPiety : %d\nResources : %d\n\n",day,food,pop,piety,resource);
	
	// Gets a number between 1 and 10, we can use it later to set an event. The seed can also help us with other events later.

	srand(time(0));

	int randomevent = (rand()/(RAND_MAX/10))+1;

	// The random events, they only fire after day one. We also initialize the loss variables.
	int kills = 0;
	int eaten = 0;
	int joined = 0;
	if(day != 1 || devmode){
		
		// Wolf attack event, kills between 1 and 20 people, 20% chance.
		if(randomevent <= 2){
			kills = rand()/(RAND_MAX/20)+1;
			pop -= kills;
			
			printf("A wolf came in and killed %d people. leaving us with %d souls. May they rest in heaven...\n\n",kills,pop);
		}
		
		// Rat storm event, divides food supply by 3 to 7, 20% chance.

		if(randomevent > 2 && randomevent <= 4){
			eaten = food/((rand()/(RAND_MAX/5)+3));
			food -= eaten;	

			printf("A storm of rats ravished our food supply, eating %d of our grains. We are left now with %d food\n\n",eaten,food);
		}
		
		// The native roll, can either trigger
		//
		// The scouting party event
		//
		// The gifts event.
		//
		// Or the native American Warband Event, probably the most damaging one, this only triggers if your pop is below 300, there is a 10% chance of it happening and it kills between 1 and 50 people, while removing 30 food.

		if(randomevent == 10 && pop < 300){
			
			if(relations < 35){
			kills = rand()/(RAND_MAX/50)+1;
			pop -= kills;
			food -= 30;
		
			printf("A native american warband sieged our town, They ravished 30 of our food, leaving %d, and killed %d of our people\n\n",food,kills);
			}else if(relations > 75){
			food += 30;

			printf("A native american gift party graced our town, they gave us 30 food. Thank the Lord.\n\n");
			}else{
			printf("We saw a native american scouting party\n\n");
			}
		}

		// Random ship join event, this gives you between 1 and 100 people, it has a 10% chance of firing

		if(randomevent == 9){
		joined = rand()/(RAND_MAX/100)+1;
		pop += joined;
		printf("A ship full of settlers joined us, we gained %d people, and now have %d souls.\n\n",joined,pop);
		}
	}

	// We check for gameovers.
	
	if(pop < 10){gameover = 1;}
	if(food < 0){gameover = 2;}
	if(piety < 10){gameover = 4;}

	// Now, we calculate how our resources are effected.

	if(kills >= 1){piety -= kills/2;}

	if(piety>100){piety = 100;}

	// If devmode is enabled, we print some stats that might help with debugging.

	if(devmode == 1){
	
		printf("Rolled %d\n\n", randomevent);

	}
}

// This function is used to allow the player to make their actions

void actionloop(){
	
	// Random seed.
	
	srand(time(0));


	// The player can enter various commands which take actions, he can use up to three actions, thus three commands per day.

	int actions = 3;

	while(actions >= 1){
		int loss;
		char buff[6];

		printf("%d actions left.\n\n",actions);
		fgets(buff,6,stdin);
		buff[strlen(buff)-1] = '\0';
		

		if(strcmp(buff, "end\0") == 0){
		actions = 0;
		printf("\nEnding turn...\n\n");
		}else if(strcmp(buff,"exit\0") == 0){
		printf("\nEnding game...\n\n");
		actions = 0;
		gameover = 3;	
		}else if(strcmp(buff,"pray\0") == 0){
		piety += 5;
		actions--;
		printf("\nYou pray to the lord, for in trying times, that is all you can do... Gained 5 piety, your piety is now %d\n\n",piety);
		}else if(strcmp(buff,"farm\0") == 0){
		if(resource > 5){
		resource -= 5;
		food = food + pop/5;
		actions--;
		printf("\nYou order your colonists to farm, you lose 5 resources, but your foodstocks are now at %d\n\n", food);
		}else{
		printf("\nYou do not have the resources to farm...\n\n");
		}
		}else if(strcmp(buff,"prod\0") == 0){
		loss = rand()/(RAND_MAX/10)+1;
		resource += 10;
		pop -= loss;
		piety -= loss/2;
		actions--;
		printf("\nYou mine and smith tools, %d died in the mines... But you gained 10 resource.\n\n",loss,resource);
		}else if(strcmp(buff,"trib\0") == 0){
		tribeloop();
		actions--;
		}
		
		else{
		printf("Invalid Command\n");
		}

	}

}

// This function parses different game over screens, and also does a couple checks and changes some values every passed day.

void endloop(){

	// Checks

	day++;
	if(relations < 0){relations = 0;} 
	if(relations > 100){relations = 100;}
	relations -= 3;

	if(resource < 0){resource = 0;}

	pop += food/10;

        food -= pop/3;


	// Game Over screens

	if(gameover == 1){
		printf("Too many had died from the perilous struggle, now too little were left to continue the settlement. The few left integrated into native tribes, became hermits, or died to the wilderness.\n\n");

		ingame = 0;
	}

	if(gameover == 2){
		printf("Your colony is left to starve, nothing of your work is remembered but dust and bone.\n\n");

		ingame = 0;
	}

	if(gameover == 3){
		
		printf("You gave up your administration to the next leader, and lived your life quietly\n\n");
		
		ingame = 0;
	}

	if(gameover == 4){

		printf("Your colony lost all faith, those remaining still alive went insane, or simply gave up\n\n");

		ingame = 0;
	}
}

// This function manages tribal relations, extortion, slavery, and raiding.

void tribeloop(){
	
	printf("\nYou send scouts to deal in diplomacy with the nearby native tribe.\n\nThey advise you of the commands that you can use.\n\nFirst, is the pros command, which allows you to prostelytize to the natives, gaining piety for reducing relations.\n\nSecond, is the exto command, which allows you to extort the natives, gaining 25 resources for reduced relations\n\nThird, is the trad command, which allows you to trade with the natives, trading 25 resources for 50 food, and increased relations.\n\n");

	printf("Current Relations = %d\n\n",relations);

	char buff[6];
	
	fgets(buff,6,stdin);
	buff[strlen(buff)-1] = '\0';

	if(strcmp(buff, "pros\0") == 0){
		
		piety += 10;

		relations -= 5;

		printf("\nYou prostelytize to the natives, losing 5 relations but gaining 10 piety.\n\n");

	} else if(strcmp(buff, "exto\0") == 0){
	
		resource += 25;
		relations -= 20;
		piety -= 10;	

		printf("\nYou extort the natives, losing 25 relations and 10 piety, and gaining 25 resource\n\n");

	} else if(strcmp(buff, "trad\0") == 0){

		resource -= 25;
		food += 50;
		relations += 12;

		printf("\nYou trade with the natives, losing 25 resource, but gaining 50 food and 12 relations\n\n");
	}


}
