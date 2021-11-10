#include "processus.h"
#include <stdio.h>


    extern void ctx_sw(int *save , int *restsore);


    void idle_function(void)
    {
    printf("[idle] je tente de passer la main a proc1...\n");
    ctx_sw(table_of_processus[0].sauvegard,table_of_processus[1].sauvegard);
    }
    void proc1_function(void)
    {
    printf("[proc1] idle m’a donne la main\n");
    printf("[proc1] j’arrete le systeme\n");
    hlt();
    }