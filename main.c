#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dealer.h"

int main(){
  int i;
  init_drugs();
  init_cities();
  city = &cities[0];  
  for (i=0;i<4;i++)
    {
      drug = &drugs[i];
      set_price();
      set_quantity();
      drugs[i].stash=0;
    };
  for (i=0;i<100;i++)
    {
      printf("\n\nYou are in %s. \t\t\tCash: %d\n" ,city->name,cash);
      show_table();
      action();
    };  
  return 0;
}

/* Functions for initializing cities and drugs */
void init_cities(){
  strcpy(cities[0].name , "NY");
  strcpy(cities[1].name , "LA");
  strcpy(cities[2].name , "Boston");
  strcpy(cities[3].name , "Washington");
}
  
void init_drugs(){
  strcpy(drugs[0].name, "weed");
  drugs[0].low=5;
  drugs[0].high=15;
  strcpy(drugs[1].name, "dope");
  drugs[1].low=20;
  drugs[1].high=60;  
  strcpy(drugs[2].name, "coke");
  drugs[2].low=17;
  drugs[2].high=70;  
  strcpy(drugs[3].name, "meth");
  drugs[3].low=13;
  drugs[3].high=50;
}

/* The update() function calls set_price() and set_quantity() when arriving at a new city */
void update()
{
  int i;
  for (i=0;i<4;i++)
    {
      drug=&drugs[i];
      set_price();
      set_quantity();
    }
  ;
}

void set_price()
{
  int diff, rnd;
  srand(time(NULL));
  diff = drug->high - drug->low;
  rnd = rand() % diff;
  drug->price = drug->low + rnd;
}

void set_quantity()
{
  int rnd;
  srand(time(NULL));
  rnd = rand() % (100 - drug->high);
  drug->quantity = rnd;
}  

/* This function prints information about the drugs to the screen with the use of print_drug() */
void show_table()
{
  int i;
  printf("\nDrug\tPrice\tQty\tStash\n\n");
  for (i=0;i<4;i++)
    {
      drug = &drugs[i];
      print_drug();
    }
  ;
  printf("\n");  
}

void print_drug()
{
  printf("%s\t", drug->name);
  printf("%d\t", drug->price);
  printf("%d\t",drug->quantity);
  printf("%d\n",drug->stash);  
}

/* 
 * The remaining functions handles player input,
 * with action() being the main entry point.
 * The chain is as follows:
 *
 *           action()
 *              |
 *        ----------------
 *        |              |
 *   select_drug()  select_city()
 *        |
 *  -------------
 *  |           |
 * buy()      sell()
 *    
 */
int action() {
  int ret;
  printf("1. Buy\t2. Sell\t3. Travel\n\nEnter choice: ");
  scanf("%c", &chosen_action);
  getchar();
  if ((chosen_action==49))
    {
      ret = select_drug();
	if (ret==0){buy();return 0;}
	else
	  return 1;
    }
  else if ((chosen_action == 50) && (select_drug() == 0)) {sell(); return 0;}
  else if (chosen_action == 51) {select_city(); return 0;}
  else
    {
      printf("\nThat's not an option.\n");
      return 1;
    }
}

int select_drug()
{
  printf("\nEnter drug: ");
  scanf("%4s", &chosen_drug);
  if (strcmp("weed",chosen_drug) == 0) drug=&drugs[0];
  else if (strcmp("dope",chosen_drug) == 0) drug=&drugs[1];
  else if (strcmp("coke",chosen_drug) == 0) drug=&drugs[2];
  else if (strcmp("meth",chosen_drug) == 0) drug=&drugs[3];
  else
    {
      printf("\nWhat?! Are you high?\n");
      return 1;
    }  
  return 0;
}

int sell()
{  
  int amount;
  printf("How many of your %d units of %s do you want to sell? ", drug->stash, drug->name);
  scanf("%i",&amount);
  getchar();
  if(amount > drug->stash)
    {
      printf("You don't have that much. \n");
      return 1;
    }
  else if(amount==0)
    {
      printf("You didn't sell any %s.\n",drug->name);
      return 1;
    }
  else
    {	  
      cash+=(amount * drug->price);
      drug->stash -= amount;
      drug->quantity += amount;
      printf("You now have %d dollars.\n",cash);
      return 0;
    }
}

int buy()
{  
  int amount, afford;
  afford = (cash / drug->price);
  if (afford >= drug->quantity)
    {
      printf("How many of the %d units of %s do you want to buy? ", drug->quantity, drug->name);
    }
  else
    {
      printf("You can afford %d units, how many do you want to buy? ", afford);
    }  
  scanf("%i",&amount);
  getchar();
  if((amount > drug->quantity) || (amount > afford))
    {
      printf("You can't do that.\n");
      return 1;
    }
  else if(amount==0)
    {
      printf("You didn't buy any %s.\n",drug->name);
      return 1;
    }
  else
    {	  
      cash-=(amount * drug->price);
      drug->stash += amount;
      drug->quantity -= amount;
      printf("You now have %d dollars.\n",cash);
      return 0;
    }
}

void select_city()
{
  int i;
  char choice[20];
  unsigned int flag;
  for (i=0;i<4;i++)
    {
      if (strcmp(cities[i].name, city->name) != 0) printf("%s\n",cities[i].name);
    }  
  printf("\nEnter city: ");
  scanf("%s", &choice);
  getchar();  
  if (strcmp(choice,city->name) == 0) printf("You are already in %s!",choice);
  else
    {
      flag=0;
      for (i=0;i<4;i++)
	{
	  if (strcmp(cities[i].name, choice) == 0)
	    {
	      printf("\nWelcome to %s!\n",choice);
	      city = &cities[i];
	      update();
	      flag=1;
	    }
	}
      if (flag==0) printf("That's not an option..\n");
    }
}
