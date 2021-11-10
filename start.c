  #include <cpu.h>
#include <inttypes.h>
#include <string.h>
#include "time.h"
#include "processus.h"
#include <stdio.h>
#include <stdlib.h>


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
}// char* time1 ;
// time1 = "00:00:00" ;

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
      ecrit_car(i,j,' ',0,0);

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



// void traite_car(char c,uint32_t lig, uint32_t col)
// {
//   uint8_t acii = (uint8_t)c ;
//   if(acii > 31 && acii < 127)
//   {
//     ecrit_car(lig,col,c,15,0);
//   }
//   else
//   {
//     switch(acii)
//     {
//       case 8:
//         if(col != 0)
//         {
//           place_curseur(lig , col -1);
//         }
//         break;
//
//       case 9:
//           if(col < 72)
//           {
//             place_curseur(lig , col+8);
//           }
//affichetempsadroite(output);
//         break;
//
//
//     case 10:
//         if(lig != 24)
//         {
//           place_curseur(lig +1 , 0);
//         }
//         break;
//
//     case 12:
//           efface_ecran();
//           place_curseur(0,0);
//
//         break;
//     case 13:
//
//         place_curseur(lig,0);
//         break;
//     }
//   }
// }
//

//vini part

#define NLIG 25
#define NCOL 80


uint16_t trouve_curseur(void)
{
    uint16_t pos;

    outb(0x0E, 0x3D4);
    pos = inb(0X3D5) << 8;
    outb(0x0F, 0x3D4);
    pos += inb(0X3D5);

    return pos;
}

void traite_car(char c)
{
    uint8_t ascii = (uint8_t)c;
    uint16_t lig, col, pos;

    pos = trouve_curseur();
    lig = pos / NCOL;
    col = pos % NCOL;

    if( 31 < ascii && ascii < 127 ) {
        ecrit_car(lig, col, c ,7 , 0);
        if (col < NCOL) {
            place_curseur(lig, col+1);
        } else {
            place_curseur(lig+1, 0);
        }
    } else {
        switch(ascii) {
            case 8:
                if (col != 0) {
                    place_curseur(lig, col-1);
                }
                break;

            case 9:
                if ((col % 8) != 0 && col != (NCOL - 1)) {
                    col = col - (col%8) + 8;
                    if(col < NCOL)
                        place_curseur(lig, col);
                    else
                        place_curseur(lig, NCOL-1);
                }
                break;

            case 10:
                if (lig != NLIG - 1)
                    place_curseur(lig + 1, 0);
                break;

            case 12:
                efface_ecran();
                place_curseur(0,0);
                break;

            case 13:
                place_curseur(lig, 0);
                break;

            default:
                break;
        }
    }
}


//mydefi
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

void console_putbytes(char *chaine, int32_t taille)
{
    // traite_car('\f'); //effacer ecran
    for (int32_t i = 0; i < taille; i++){
        traite_car(chaine[i]);
    }
}

//  void console_putbytes(const char *s, int len)
// {
//     // On cherche la position du place_curseur
//
//
// }
//
//







extern void traitant_IT_32();
extern void ctx_sw(int *save , int *restsore);



void kernel_start(void)
{
  //place_curseur(12 , 1);
  //traite_car('\n',0,15);
    // quand on saura gerer l'ecran, on pourra afficher x
   //efface_ecran () ;
   // for (int i = 0 ; i< 25 ; i++)
   // {
   //   for ( int j = 0; j<80 ; j++)
   //   {
   //     ecrit_car(i,j,'m',7,0);
   //   }
   // }
   // char* name ;
   // name = "mohamad" ;
   // console_putbytes(name,7/*strlen(name)*/);

   //defilement();
    //ecrit_car(5,10,'K',15,0);
    //ecrit_car(15,40,'K',15,0);

    //
    // on ne doit jamais sortir de kernel_start


    //time functions :
    // char* time1 ;
    // time1 = "00:00:00" ;
    // affichetempsadroite(time1);

    //efface_ecran() ;
      //masque_IRQ(0,0);
    //  masque_IRQ(0,0) ;

    //time :
    // reglagefrequence() ;
    // init_traitant_IT(32,traitant_IT_32) ;
    // mask0();
    // sti() ;



    // char c[50] = "moe" ;
    // affichetempsadroite(c) ;

    struct processus idle  ;
    idle.pid = 0 ; 
    strcpy(idle.name , "idle" );
    idle.etat = elu ;

    
    struct processus proc1 ;
    proc1.pid = 1 ;
    strcpy(proc1.name , "proc1" );    
    proc1.etat = activable ;
    proc1.sauvegard[1] = (int) proc1.pile + 511 ;
    *(proc1.pile + 511) = (int)  proc1_function ; 


    table_of_processus[0] = idle ;
    table_of_processus[1] = proc1 ;



    idle_function();

    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
