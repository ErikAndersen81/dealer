typedef struct Drugs {
  char name[5];
  int price;
  int low;
  int high;
  int stash;
  int quantity;
}Drug;

typedef struct Cities {
  char name[20];
}City;


void set_price();
void set_quantity();

void show_table();
void print_drug();

int sell();
int buy();
int select_drug();
int action();

void select_city();
void update();

void init_drugs();
void init_cities();

int cash=200;

Drug drugs[4];
Drug *drug;

City cities[4];
City *city;

char chosen_action;
char chosen_drug[5];
