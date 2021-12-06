#include "processus.h"
#include <stdio.h>

//esp pointeur de la pile 


    extern void ctx_sw(int *save , int *restsore);

/////////////////////// aller /////////////////////////////////
    // void idle_function(void)
    // {
    // printf("[idle] je tente de passer la main a proc1...\n");
    // ctx_sw(table_of_processus[0].sauvegard,table_of_processus[1].sauvegard);
    // }
    // void proc1_function(void)
    // {
    // printf("[proc1] idle m’a donne la main\n");
    // printf("[proc1] j’arrete le systeme\n");
    // hlt();
    // }

////////////////////////////////////aller-retour 3fois/////////////////////////

// void idle_func(void)
//     {
//         for (int i = 0; i < 3; i++) {
//             printf("[idle] je tente de passer la main a proc1...\n");
//             ctx_sw(table_of_processus[0].sauvegard,table_of_processus[1].sauvegard);
//             printf("[idle] proc1 m’a redonne la main\n");
//         }
//         printf("[idle] je bloque le systeme\n");
//         hlt();
//     }
// void proc1_func(void)
// {
//     // for (int i = 0; i < 3; i++)
//     for (;;) {
//         printf("[proc1] idle m’a donne la main\n");
//         printf("[proc1] je tente de lui la redonner...\n");
//         ctx_sw(table_of_processus[1].sauvegard,table_of_processus[0].sauvegard);
//     }
// }



/////////////////////////////////ORDONNANCE//////////////////////////////

int current_pid = 0 ;
int next_pid = 0 ;
int nb_processus = 2 ;

int mon_pid(void)
{
    return table_of_processus[current_pid].pid ;    
}


char* mon_nom(void)
{
    return table_of_processus[current_pid].name ;
}


void ordonnance(void)
{   
    current_pid = next_pid ;

    next_pid = table_of_processus[ (previous_pid + 1)%nb_processus ].pid ;

    table_of_processus[current_pid].etat = activable ; 
    table_of_processus[next_pid].etat = elu ;  
    
    ctx_sw(table_of_processus[previous_pid].sauvegard , table_of_processus[current_pid].sauvegard );
   
}


void idle_ord(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1_ord(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}