  #include <cpu.h>
#include <inttypes.h>
#include <string.h>

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

void place_curseur(uint32_t lig, uint32_t col)
{
    uint16_t p = (col + lig*80);
    outb( 0x0F , 0x3D4);
    outb((uint8_t) p, 0x3D5);
    outb( 0x0E , 0x3D4);
    outb( (uint8_t)(p >> 8) , 0x3D5);
}

void traite_car(char c,uint32_t lig, uint32_t col)
{
  uint8_t acii = (uint8_t)c ;
  if(acii > 31 && acii < 127)
  {
    ecrit_car(lig,col,c,15,0);
  }
  else
  {
    switch(acii)
    {
      case 8:
        if(col != 0)
        {
          place_curseur(lig , col -1);
        }
        break;

      case 9:
          if(col < 72)
          {
            place_curseur(lig , col+8);
          }

        break;


    case 10:
        if(lig != 24)
        {
          place_curseur(lig +1 , 0);
        }
        break;

    case 12:
          efface_ecran();
          place_curseur(0,0);

        break;
    case 13:

        place_curseur(lig,0);
        break;
    }
  }
}

void defilement(void)
{
  void* Destination ;
  void* source ;
  size_t size ;

  size = 2*(80*24);
  Destination = (void*)ptr_mem(0,0) ;
  source = (void*)ptr_mem(1,0) ;

  memmove( Destination , source , size);


  for ( int j = 0; j<80 ; j++)
  {
    ecrit_car(24,j,' ',0,0);
  }
}

 void console_putbytes(const char *s, int len)
{


}











void kernel_start(void)
{
  //place_curseur(12 , 1);
  //traite_car('\n',0,15);
    // quand on saura gerer l'ecran, on pourra afficher x
   //efface_ecran () ;
   for (int i = 0 ; i< 25 ; i++)
   {
     for ( int j = 0; j<80 ; j++)
     {
       ecrit_car(i,j,'m',7,0);
     }
   }


   defilement();
    //ecrit_car(5,10,'K',15,0);
    //ecrit_car(15,40,'K',15,0);


    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
