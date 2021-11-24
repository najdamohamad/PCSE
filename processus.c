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
int mon_pid(void)
{
    return actif->pid ;
}

int ton_pid(void)
{
    int t = mon_pid();
    t = 1 - t ; //inverser 0 et 1 --> obtenir l'autre pid //
    return t ;
}

char* mon_nom(void)
{
    return actif->name ;
}


void ordonnance(void)
{   
    table_of_processus[mon_pid()].etat = activable ; 
    table_of_processus[ton_pid()].etat = elu ;  
    
    ctx_sw(table_of_processus[mon_pid()].sauvegard ,
    table_of_processus[ton_pid()].sauvegard );
   
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