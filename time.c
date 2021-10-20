
#include "time.h"
#include "segment.h"
#include <stdio.h>
#include <stdbool.h>


void affichetempsadroite(char* time1)
{
  efface_ecran();
  place_curseur(0,70);
  console_putbytes(time1,strlen(time1));
}



void init_traitant_IT(int32_t num_IT, void (*traitant)(void))
{

  uint32_t* ptr_table = (uint32_t*)0x1000 ;
  uint32_t* ptr_kernel = ptr_table + num_IT*2 ;
  *ptr_kernel = (KERNEL_CS << 16) | ((uint32_t)traitant & 0xFFFF);
  uint32_t* ptr_cte = ptr_kernel + 1  ;
  *ptr_cte = (((uint32_t)traitant) & 0xFFFF0000) |  (0x00008E00) ;


}

uint32_t seconds = 0 ;
uint32_t minutes = 0 ;
uint32_t hours = 0 ;

void tic_PIT(void)
{
  outb(0x20,0x20);
  seconds ++ ;
  if (seconds == 60 )
  {
    seconds = 0 ;
    minutes ++ ;
    if(minutes == 60)
    {
      minutes = 0;
      seconds = 0;
      hours ++ ;
      if(hours == 24)
      {
        hours = 0 ;
        minutes = 0 ;
        seconds = 0 ;
      }
    }
  }
  char output[50] ;
  sprintf(output," %d :%d :%d ",hours,minutes,seconds);
  affichetempsadroite(output);
}

#define QUARTZ 0x1234DD
#define CLOCKFREQ 50


void reglagefrequence()
{
  outb(0x34,0x43) ;
  outb((QUARTZ/CLOCKFREQ) %256 , 0x40);
  outb((QUARTZ/CLOCKFREQ) >>8 , 0x40);

}

// void receivefreq()
// {
//   inb(0x43);
//   uint8_t pfa = inb(0x40);
//   uint16_t pfo = inb(0x40);
//   pfo = pfo << 8 ;
//   pfo = pfo + pfa ;
// }

void masque_IRQ(uint32_t num_IRQ, bool masque)
{
  uint8_t oct = inb(0x21) ;
  if(masque == 1)
  {
    uint8_t mask2 = 1 << num_IRQ ;
    oct = oct | mask2 ;
  }
  else
  {
    uint8_t mask2 = 0 << num_IRQ ;
    oct = ~oct ;
    oct = oct | mask2 ;
    oct = ~oct ;
  }

  outb(oct,0x21) ;

}

void mask0()
{
    uint8_t oct = inb(0x21) ;
    oct = ~oct ;
    oct = oct | 0b0000001 ;
    oct = ~oct ;
      outb(oct,0x21) ;
}
// void masque_IRQ(uint32_t num_IRQ, bool masque)
// {
//   uint8_t oct = inb(0x21) ;
//   switch (num_IRQ) {
//   case 7:
//       if(masque)
//       {
//         oct = oct | 0b10000000 ;
//       }
//       else
//       {
//         oct = ~oct ;
//         oct = oct | 0b10000000 ;
//         oct = ~oct ;
//       }
//   case 6 :
//     if(masque)
//     {
//       oct = oct | 0b01000000 ;
//     }
//     else
//     {
//       oct = ~oct ;
//       oct = oct | 0b01000000 ;
//       oct = ~oct ;
//     }
//   case 5:
//     if(masque)
//     {
//       oct = oct | 0b00100000 ;
//     }
//     else
//     {
//       oct = ~oct ;
//       oct = oct | 0b00100000 ;
//       oct = ~oct ;
//     }
//   case 4:
//     if(masque)
//     {
//       oct = oct | 0b00010000 ;
//     }
//     else
//     {
//       oct = ~oct ;
//       oct = oct | 0b00010000 ;
//       oct = ~oct ;
//     }
//   case 3:
//     if(masque)
//     {
//       oct = oct | 0b00001000 ;
//     }
//     else
//     {
//       oct = ~oct ;
//       oct = oct | 0b00001000 ;
//       oct = ~oct ;
//     }
//   case 2:
//     if(masque)
//     {
//       oct = oct | 0b00000100 ;
//     }
//     else
//     {
//       oct = ~oct ;
//       oct = oct | 0b00000100 ;
//       oct = ~oct ;
//     }
//   case 1:
//       if(masque)
//       {
//         oct = oct | 0b00000010 ;
//       }
//       else
//       {
//         oct = ~oct ;
//         oct = oct | 0b00000010 ;
//         oct = ~oct ;
//       }
//   case 0:
//         if(masque)
//         {
//           oct = oct | 0b00000001 ;
//         }
//         else
//         {
//           oct = ~oct ;
//           oct = oct | 0b00000001 ;
//           oct = ~oct ;
//         }
//
//       }
//       outb(oct,0x21) ;
//
// }
