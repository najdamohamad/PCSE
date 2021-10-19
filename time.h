#include <cpu.h>
#include <inttypes.h>
#include <string.h>
#include "start.h"
#include <stdbool.h>

void affichetempsadroite(char* blabla) ;
void init_traitant_IT(int32_t num_IT, void (*traitant)(void));
void tic_PIT(void);
void reglagefrequence();
void receivefreq();
void masque_IRQ(uint32_t num_IRQ, bool masque);
