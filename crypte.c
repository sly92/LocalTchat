#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char cle[8];
	char g[4];
	char d[4];
} sous_cle;

// ces tables sont deja predefinie de facon a crypter correctement et pouvoir decrypter par la suite
int table_permutation_init_cle_C[] = {57,49,41,33,25,17,9,
				       1,58,50,42,34,26,18,
				      10,2,59,51,43,35,27,
				      19,11,3,60,52,44,36,
				      63,55,47,39,31,23,15,
				       7,62,54,46,38,30,22,
				      14,6,61,53,45,37,29,
				      21,13,5,28,20,12,4};

static int table_permutation_init_block_C[] = {58,50,42,34,26,18,10,2,
					       60,52,44,36,28,20,12,4,
					       62,54,46,38,30,22,14,6,
					       64,56,48,40,32,24,16,8,
					       57,49,41,33,25,17,9,1,
					       59,51,43,35,27,19,11,3,
					       61,53, 45,37,29,21,13,5,
					       63,55,47,39,31,23,15,7};

static int table_permutation_sous_cle_C[] = {14,17,11,24,1,5,
					      3,28,15,6,21,10,
					     23,19,12,4,26,8,
					     16,7,27,20,13,2,
					     41,52,31,37,47,55,
					     30,40,51,45,33,48,
					     44,49,39,56,34,53,
					     46,42,50,36,29,32};

static int bytes_de_decalage_par_cle_C[] = {-1,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

static int table_expansion_block_C[] =  {32,1,2,3,4,5,
					  4,5,6,7,8,9,
		       		          8,9,10,11,12,13,
		     		         12,13,14,15,16,17,
				         16,17,18,19,20,21,
					 20,21,22,23,24,25,
				         24,25,26,27,28,29,
				         28,29,30,31,32,1};

static int table_permutation_block_partie_droite_C[] = {16,7,20,21,
							29,12,28,17,
							1,15,23,26,
							5,18,31,10,
							2,8,24,14,
							32,27,3,9,
							19,13,30,6,
							22,11,4,25};

static int table_permutation_final_C[] =  {40,8,48,16,56,24,64,32,
					   39,7,47,15,55,23,63,31,
					   38,6,46,14,54,22,62,30,
					   37,5,45,13,53,21,61,29,
					   36,4,44,12,52,20,60,28,
					   35,3,43,11,51,19,59,27,
					   34,2,42,10,50,18,58,26,
					   33,1,41,9,49,17,57,25};

static int S1_C[] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		      0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		      4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		     15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};

static int S2_C[] = {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		      3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		      0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		     13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

static int S3_C[] = {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		     13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		     13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		      1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};

static int S4_C[] = {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		     3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};

static int S5_C[] = {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		     4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};

static int S6_C[] = {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		     10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		      9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		      4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

static int S7_C[] = {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		     1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		     6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};

static int S8_C[] = {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		      1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		      7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		      2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

void generer_sous_cle_C(char* cle, sous_cle* sous_cles) {
	int i, j;
	int decalage;
	char octet_decalage, octet_decale1, octet_decale2, octet_decale3, octet_decale4;

	for (i=0; i<8; i++) {
		sous_cles[0].cle[i] = 0;
	}

	// on cree une cle de 56 bit à partir de la cle principale de 64 bits (8 octets) et de la table table_permutation_init_cle
	for (i=0; i<56; i++) {
		decalage = table_permutation_init_cle_C[i];
		octet_decalage = 0x80 >> ((decalage - 1)%8); // exemple : 1000 0000 >> ((2-1)%8) = 0100 0000
		octet_decalage &= cle[(decalage - 1)/8]; // fonction and (l'operateur bit a bit "&")
		octet_decalage <<= ((decalage - 1)%8); // on decale le bit par rapport à la table de permutation des clé

		sous_cles[0].cle[i/8] |= (octet_decalage >> i%8); // fonction or "|" exemple : 1111 0000 | 0000 1111 = 1111 1111
	}
	// on separe en 2 partie gauche et droite cette derniere cle obtenu
	for (i=0; i<3; i++) {
		sous_cles[0].g[i] = sous_cles[0].cle[i];
	}

	sous_cles[0].g[3] = sous_cles[0].cle[3] & 0xF0;

	for (i=0; i<3; i++) {
		sous_cles[0].d[i] = (sous_cles[0].cle[i+3] & 0x0F) << 4;
		sous_cles[0].d[i] |= (sous_cles[0].cle[i+4] & 0xF0) >> 4;
	}

	sous_cles[0].d[3] = (sous_cles[0].cle[6] & 0x0F) << 4;

	for (i=1; i<17; i++) {
		for (j=0; j<4; j++) {
			// chaque parties est donnée par les parties du cycle précedent qui à l'origine sont les 2 parties gauche et droite de la clé de 56 bits obtenu à partir de la clé de 64 bits principale
			sous_cles[i].g[j] = sous_cles[i-1].g[j];
			sous_cles[i].d[j] = sous_cles[i-1].d[j];
		}

		decalage = bytes_de_decalage_par_cle_C[i];
		if (decalage == 1){
			octet_decalage = 0x80;
		} else {
			octet_decalage = 0xC0;
		}

		// on décale les bits de chaque partie gauche et droite vers la gauche, le nombre de bits de décalage dépend du numéro du cycle
		// Partie gauche
		octet_decale1 = octet_decalage & sous_cles[i].g[0];
		octet_decale2 = octet_decalage & sous_cles[i].g[1];
		octet_decale3 = octet_decalage & sous_cles[i].g[2];
		octet_decale4 = octet_decalage & sous_cles[i].g[3];

		sous_cles[i].g[0] <<= decalage;
		sous_cles[i].g[0] |= (octet_decale2 >> (8 - decalage));

		sous_cles[i].g[1] <<= decalage;
		sous_cles[i].g[1] |= (octet_decale3 >> (8 - decalage));

		sous_cles[i].g[2] <<= decalage;
		sous_cles[i].g[2] |= (octet_decale4 >> (8 - decalage));

		sous_cles[i].g[3] <<= decalage;
		sous_cles[i].g[3] |= (octet_decale1 >> (4 - decalage));

		// Partie droite
		octet_decale1 = octet_decalage & sous_cles[i].d[0];
		octet_decale2 = octet_decalage & sous_cles[i].d[1];
		octet_decale3 = octet_decalage & sous_cles[i].d[2];
		octet_decale4 = octet_decalage & sous_cles[i].d[3];

		sous_cles[i].d[0] <<= decalage;
		sous_cles[i].d[0] |= (octet_decale2 >> (8 - decalage));

		sous_cles[i].d[1] <<= decalage;
		sous_cles[i].d[1] |= (octet_decale3 >> (8 - decalage));

		sous_cles[i].d[2] <<= decalage;
		sous_cles[i].d[2] |= (octet_decale4 >> (8 - decalage));

		sous_cles[i].d[3] <<= decalage;
		sous_cles[i].d[3] |= (octet_decale1 >> (4 - decalage));

		// on joint les 2 parties gauche et droite et on la transforme en une cle de 48 bit à partir de la table table_permutation_sous_cle
		for (j=0; j<48; j++) {
			decalage = table_permutation_sous_cle_C[j];
			if (decalage <= 28) {
				octet_decalage = 0x80 >> ((decalage - 1)%8);
				octet_decalage &= sous_cles[i].g[(decalage - 1)/8];
				octet_decalage <<= ((decalage - 1)%8);
			} else {
				octet_decalage = 0x80 >> ((decalage - 29)%8);
				octet_decalage &= sous_cles[i].d[(decalage - 29)/8];
				octet_decalage <<= ((decalage - 29)%8);
			}

			sous_cles[i].cle[j/8] |= (octet_decalage >> j%8);
		}
	}
}


char* crypter(char* message) {
	long taille_message;
	int padding;
	char* message_crypted = (char*)malloc((sizeof(message)/sizeof(char))*sizeof(char));

	FILE *cle_file;
	cle_file = fopen("cle.txt", "r"); // option "r" pour lire dans un fichier texte

	int total_octet;
	char* cle = (char*) malloc(8*sizeof(char));
	total_octet = fread(cle, 1, 8, cle_file);
	if (total_octet != 8) {
		printf("La clé n'a pas une taille valide");
		fclose(cle_file);
		exit(0);
	}
	fclose(cle_file);


	long i = 0, total_block;
	char* block = (char*) malloc(8*sizeof(char));
	char* block_crypted = (char*) malloc(8*sizeof(char));
	sous_cle* sous_cles = (sous_cle*)malloc(17*sizeof(sous_cle));
	// Generation des 16 sous clés a partir de la clé principale
	generer_sous_cle_C(cle, sous_cles);

	taille_message = sizeof(message)/sizeof(char);

	total_block = taille_message/8 + ((taille_message%8)?1:0);

	// debut du cryptage
	while(i<total_block) {
			i++;

			padding = 8 - taille_message%8; // on compte le nbre de caracteres vide dans le dernier octet du message

			if (i == total_block && padding < 8) {
				memset((block + 8 - padding), padding, padding); // on rempli chacune des cases prévu vides pour le dernier block de message par le nbre de cases vides
			}

			if (i == total_block && padding == 8) { // Si on a pas de caracteres vide dans le dernier octet hormis le caractere de fin de chaine on rempli le dernier block par 8
				memset(block, padding, 8);
			}

			int j, k;
			int decalage;
			char octet_decalage;

			char permutation_initial[8];
			memset(permutation_initial, 0, 8);
			memset(block_crypted, 0, 8);

			for (j=0; j<64; j++) {
				decalage = table_permutation_init_block_C[j]; // decalage = 58 ; octet_decalage = 01000000
				octet_decalage = 0x80 >> ((decalage - 1)%8);
				octet_decalage &= block[(decalage - 1)/8]; // octet_decalage = 01000000 & 01000001 = 01000000
				octet_decalage <<= ((decalage - 1)%8);	// = 01000000 << 1 = 10000000

				permutation_initial[j/8] |= (octet_decalage >> j%8); // 0 | 10000000 = 10000000
			}

			// ex: block = {"m","i","a","g","e","","",""} ( chaque caractere correspond a une valeur , ex: 'c'=97)
			// pour permutation_initial[0] c a d de i=0 à 7
			// i=0  permutation_initial[0] = 10000000
			// i=1  permutation_initial[0] = 10000000
			// i=2  permutation_initial[0] = 10000000
			// i=3  permutation_initial[0] = 10000000
			// i=4  permutation_initial[0] = 10000000
			// i=5  permutation_initial[0] = 10000000
			// i=6  permutation_initial[0] = 10000000
			// i=7  permutation_initial[0] = 10000000

			char partie_gauche[4], partie_droite[4];

			// on separe la partie gauche et droite
			for (j=0; j<4; j++) {
				partie_gauche[j] = permutation_initial[j];
				partie_droite[j] = permutation_initial[j+4];
			}

			char g[4], d[4], droite_etendue[6], droite_etendue_substituee[4];

			int cycle;

			// on effectue les 16 cycles
			for (k=1; k<=16; k++) {
				memcpy(g, partie_droite, 4);

				memset(droite_etendue, 0, 6);
				// On etend la partie droite à 48 bits ou 6 octets en utilisant une table d'expansion qui va dupliquer 16 des 32 bits
				for (j=0; j<48; j++) {
					decalage = table_expansion_block_C[j];
					octet_decalage = 0x80 >> ((decalage - 1)%8);
					octet_decalage &= partie_droite[(decalage - 1)/8];
					octet_decalage <<= ((decalage - 1)%8);

					droite_etendue[j/8] |= (octet_decalage >> j%8);
				}
				// on suit l'ordre normal pr le cryptage et l'inverse pr le decryptage
				cycle = k;

				for (j=0; j<6; j++) {
					droite_etendue[j] ^= sous_cles[cycle].cle[j]; // fonction xor entre la partie droite et la premiere cle pr k=1
				}

				char ligne, colonne;

				for (j=0; j<4; j++) {
					droite_etendue_substituee[j] = 0;
				}
				// On transforme la partie droite de 48 bits à 32 bits (4 octet) avec une table de substitution
				// la ligne est definie par le premier et dernier bit ex : 1 et 0 = 2
				// la colonne est definie par les 4 autres bits dans le mm ordre
				// Octet 1
				ligne = 0;
				ligne |= ((droite_etendue[0] & 0x80) >> 6);
				ligne |= ((droite_etendue[0] & 0x04) >> 2);

				colonne = 0;
				colonne |= ((droite_etendue[0] & 0x78) >> 3);

				droite_etendue_substituee[0] |= ((char)S1_C[ligne*16+colonne] << 4);

				ligne = 0;
				ligne |= (droite_etendue[0] & 0x02);
				ligne |= ((droite_etendue[1] & 0x10) >> 4);

				colonne = 0;
				colonne |= ((droite_etendue[0] & 0x01) << 3);
				colonne |= ((droite_etendue[1] & 0xE0) >> 5);

				droite_etendue_substituee[0] |= (char)S2_C[ligne*16+colonne];

				// Octet 2
				ligne = 0;
				ligne |= ((droite_etendue[1] & 0x08) >> 2);
				ligne |= ((droite_etendue[2] & 0x40) >> 6);

				colonne = 0;
				colonne |= ((droite_etendue[1] & 0x07) << 1);
				colonne |= ((droite_etendue[2] & 0x80) >> 7);

				droite_etendue_substituee[1] |= ((char)S3_C[ligne*16+colonne] << 4);

				ligne = 0;
				ligne |= ((droite_etendue[2] & 0x20) >> 4);
				ligne |= (droite_etendue[2] & 0x01);

				colonne = 0;
				colonne |= ((droite_etendue[2] & 0x1E) >> 1);

				droite_etendue_substituee[1] |= (char)S4_C[ligne*16+colonne];

				// Octet 3
				ligne = 0;
				ligne |= ((droite_etendue[3] & 0x80) >> 6);
				ligne |= ((droite_etendue[3] & 0x04) >> 2);

				colonne = 0;
				colonne |= ((droite_etendue[3] & 0x78) >> 3);

				droite_etendue_substituee[2] |= ((char)S5_C[ligne*16+colonne] << 4);

				ligne = 0;
				ligne |= (droite_etendue[3] & 0x02);
				ligne |= ((droite_etendue[4] & 0x10) >> 4);

				colonne = 0;
				colonne |= ((droite_etendue[3] & 0x01) << 3);
				colonne |= ((droite_etendue[4] & 0xE0) >> 5);

				droite_etendue_substituee[2] |= (char)S6_C[ligne*16+colonne];

				// Octet 4
				ligne = 0;
				ligne |= ((droite_etendue[4] & 0x08) >> 2);
				ligne |= ((droite_etendue[5] & 0x40) >> 6);

				colonne = 0;
				colonne |= ((droite_etendue[4] & 0x07) << 1);
				colonne |= ((droite_etendue[5] & 0x80) >> 7);

				droite_etendue_substituee[3] |= ((char)S7_C[ligne*16+colonne] << 4);

				ligne = 0;
				ligne |= ((droite_etendue[5] & 0x20) >> 4);
				ligne |= (droite_etendue[5] & 0x01);

				colonne = 0;
				colonne |= ((droite_etendue[5] & 0x1E) >> 1);

				droite_etendue_substituee[3] |= (char)S8_C[ligne*16+colonne];

				for (j=0; j<4; j++) {
					d[j] = 0;
				}
				// la nouvelle partie droite de 32 bits subit une autre permutation avec la table table_permutation_block_partie_droite
				for (j=0; j<32; j++) {
					decalage = table_permutation_block_partie_droite_C[j];
					octet_decalage = 0x80 >> ((decalage - 1)%8);
					octet_decalage &= droite_etendue_substituee[(decalage - 1)/8];
					octet_decalage <<= ((decalage - 1)%8);

					d[j/8] |= (octet_decalage >> j%8);
				}

				for (j=0; j<4; j++) {
					d[j] ^= partie_gauche[j]; // fonction xor entre la partie gauche initiale et la nouvelle partie droite
				}
				// on inverse les 2 parties
				for (j=0; j<4; j++) {
					partie_gauche[j] = g[j];
					partie_droite[j] = d[j];
				}
			}

			char tableau_final[8];
			// on joint les 2 parties dans un mm tableau
			for (i=0; i<4; i++) {
				tableau_final[i] = partie_droite[i];
				tableau_final[4+i] = partie_gauche[i];
			}
			// on permute le dernier tableau obtenu en joignant les 2 parties avec la table table_permutation_final et on obtient notre block crypté
			for (i=0; i<64; i++) {
				decalage = table_permutation_final_C[i];
				octet_decalage = 0x80 >> ((decalage - 1)%8);
				octet_decalage &= tableau_final[(decalage - 1)/8];
				octet_decalage <<= ((decalage - 1)%8);

				block_crypted[i/8] |= (octet_decalage >> i%8);
			}

			memset(block, 0, 8);

			memcpy(message_crypted +i*8,block_crypted,8);
	}
	// enfin on libere l'espace memoire des 3 tableaux
	free(cle);
	free(block);
	free(block_crypted);

	return message_crypted;
}
