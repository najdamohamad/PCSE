  #include <cpu.h>
#include <inttypes.h>

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue
uint32_t fact(uint32_t n)
{
    uint32_t res;
    if (n <= 1) {
        res = 1;
    } else {
        res = fact(n - 1) * n;
    }
    return res;
}

uint16_t *ptr_mem(uint32_t lig, uint32_t col)
{
  uint16_t* p = (uint16_t*) (0xB8000 + 2*(80*lig + col)) ;
  return p ;
}

void ecrit_car(uint32_t lig, uint32_t col, char c , uint32_t text , uint32_t fond)
{
  uint16_t* p = ptr_mem(lig , col);
  *p = c + (text << 8) + (fond << 12);

}

void efface_ecran()
{
  for (int i = 0 ; i< 25 ; i++)
  {
    for ( int j = 0; j<80 ; j++)
    {
      ecrit_car(i,j,' ',0,15);

    }
  }



}


void kernel_start(void)
{

    // quand on saura gerer l'ecran, on pourra afficher x
   efface_ecran () ;
    //ecrit_car(5,10,'K',15,0);
    //ecrit_car(15,40,'K',15,0);
  //  ecrit_car(10,12,'K');

    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
