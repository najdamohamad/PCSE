#include <cpu.h>
#include <inttypes.h>
#include <string.h>
#include "start.h"
#include <stdbool.h>



#define nb_processus_max 4 

typedef struct processus{
    int pid ;
    char name[50];
    enum {elu, activable, endormi }etat;
    int sauvegard[5];
    int pile[512];
}processus ;





processus table_of_processus[4];

//struct processus* actif ;
// void idle_function(void);
// void proc1_function(void);

void idle_func(void); 
void proc1_func(void);
int32_t mon_pid(void);
char *mon_nom(void);
void ordonnance(void);
void idle_ord(void); 
void proc2_ord(void);
void proc3_ord(void);
void proc4_ord(void);
int32_t cree_processus(void (*code)(void), char *nom);
