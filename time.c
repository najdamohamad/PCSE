
#include "time.h"




void affichetempsadroite(char* time1)
{
  efface_ecran();
  place_curseur(0,72);
  console_putbytes(time1,strlen(time1));
}
