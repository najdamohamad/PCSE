#include <cpu.h>
#include <inttypes.h>
#include <string.h>
#include "start.h"
#include <stdbool.h>


struct processus{
    int pid ;
    char name[50];
    enum {elu, activable , endormi }etat;
    int sauvegard[5];
    int pile[512];
};

struct processus table_of_processus[2];

// void idle_function(void);
// void proc1_function(void);

void idle_func(void); 
void proc1_func(void);
int32_t mon_pid(void);
char *mon_nom(void);
void ordonnance(void);

