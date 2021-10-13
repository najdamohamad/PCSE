#ifndef __START_H__
#define __START_H__

#define FIRST_STACK_SIZE 16384

#ifndef ASSEMBLER

extern char first_stack[FIRST_STACK_SIZE];

/* The kernel entry point */
void kernel_start(void);


uint16_t trouve_curseur(void);
void efface_ecran();
void ecrit_car(uint32_t lig, uint32_t col, char c , uint32_t text , uint32_t fond);
void place_curseur(uint32_t lig, uint32_t col);
uint16_t *ptr_mem(uint32_t lig, uint32_t col);
void traite_car(char c);
void console_putbytes(char *chaine, int32_t taille);

#endif

#endif
