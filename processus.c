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
void mon_pid(void)
{

}

void mon_nom(void)
{

}


void ordonnance(void)
{
    if()
}


void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}