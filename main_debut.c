#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "von_neumann.h"
#include "mersenne_twister.h"

#include "e0.h"

#define ARRAY_MAX_SIZE 1000


static int next;

int rdtsc()
{
	// cette fonction suivante cree un warning : c'est normal.
	__asm__ __volatile__("rdtsc");
}

int main()
{
	word16 x=1111; // nombre entre 1000 et 9999 pour Von Neumann
	struct mt19937p mt; // Pour Mersenne-Twister
	int tmp = rand(), seed; // Pour Mersenne-Twister


	word16 output_VN; // sortie pour pour Von Neumann
	word32 output_MT; // sortie pour Mersenne-Twister


	// initialisation des graines des generateurs

	srand(rdtsc());  // rand du C
	seed = rand();
	sgenrand(time(NULL)+(tmp), &mt); // Mersenne-Twister

	// sorties des generateurs
	output_VN = Von_Neumann(&x); // Von Neumann
	output_MT = genrand(&mt); // Mersenne-Twister


	// affichage
	printf("- Generation de nombres aleatoires -\n");
	printf("Von Neumann : %u\n",output_VN);
	printf("Mersenne Twister : %u\n",output_MT);


	byte_t tab[2];
	tab[0] = 0;
	tab[1] = 0;

	//test get
	bool res = get(tab, 12, 8);
	printf("get(8) : %d\n", (int) res);


	//test set
	set(tab, 12, 8, 1);
	//res = get(tab, 12, 8);
	//printf("res : %d\n", (int) res);
	printf("tab[1] : %d\n", (int) tab[1]);

    //LFSR(26, 25, 20, 12, 8);

	return 0;
}
