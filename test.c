#include "reseau.h" // Cette inclusion suffit pour inclure tous les autres moduls par "transitivité"

Network user_created_network() {
	int nb_couches;
	printf("Entrez le nombre de couches : ");
	scanf("%d", &nb_couches);

	Network n = init_layer_list();

	for (int i = 0; i < nb_couches; i++) {
		int nb_neurones;
		printf("Entrez le nombre de neurones pour la couche %d : ", i + 1);
		scanf("%d", &nb_neurones);

		int** poids = (int**)malloc(nb_neurones * sizeof(int*));
		int* biais = (int*)malloc(nb_neurones * sizeof(int));
		int nb_poids;

		for (int j = 0; j < nb_neurones; j++) {
			printf("Entrez le nombre de poids pour le neurone %d de la couche %d : ", j + 1, i + 1);
			scanf("%d", &nb_poids);

			poids[j] = (int*)malloc(nb_poids * sizeof(int));
			for (int k = 0; k < nb_poids; k++) {
				printf("Entrez le poids %d pour le neurone %d de la couche %d : ", k + 1, j + 1, i + 1);
				scanf("%d", &poids[j][k]);
			}

			printf("Entrez le biais pour le neurone %d de la couche %d : ", j + 1, i + 1);
			scanf("%d", &biais[j]);
		}

		List_neur couche = init_layer(nb_neurones, nb_poids, poids, biais);
		insert_tail_net(n, couche);

		for (int j = 0; j < nb_neurones; j++) {
			free(poids[j]);
		}
		free(poids);
		free(biais);
	}

	return n;
}

void provide_inputs(Network n) {
	int nb_inputs;
	printf("Entrez le nombre d'entrées : ");
	scanf("%d", &nb_inputs);

	int* inputs = (int*)malloc(nb_inputs * sizeof(int));
	for (int i = 0; i < nb_inputs; i++) {
		printf("Entrez l'entrée %d : ", i + 1);
		scanf("%d", &inputs[i]);
	}

	out_network(n, inputs, nb_inputs);

	free(inputs);
}

int main() {
/*
	// Création d'un réseau un peu plus complexe représentant une expression logique fixée :
	// Il évaluera l'expression (A ET (non B) ET C) OU (A ET (non C)) à la fin du sujet en choisissant bien les poids et biais
	
	// Couche 1 :
	int n11[3] = {1, 0, 0}; // biais : 1
	int n12[3] = {0, -1, 0}; // biais : 0
	int n13[3] = {0, 0, 1}; // biais : 1
	int n14[3] = {0, 0, -1}; // biais : 0

	int* tab_l1[4] = {n11, n12, n13, n14};
	int les_biais1[4] = {1, 0, 1, 0};
	// Initialisation de la couche
	List_neur l1 = init_layer(4, 3, tab_l1, les_biais1);

	// Couche 2 :
	int n21[4] = {1, 0, 0, 1}; // biais : 2
	int n22[4] = {1, 1, 1, 0}; // biais : 3

	int* tab_l2[2] = {n21, n22};
	int les_biais2[2] = {2, 3};
	// Initialisation de la couche
	List_neur l2 = init_layer(2, 4, tab_l2, les_biais2);

	// Couche 3 :
	int n31[2] = {1, 1}; // biais : 1

	int* tab_l3[1] = {n31};
	int les_biais3[1] = {1};
	// Initialisation de la couche
	List_neur l3 = init_layer(1, 2, tab_l3, les_biais3);

	// Réseau qui est enfaite une liste de couches
	Network n = init_layer_list();
	insert_tail_net(n, l1);
	insert_tail_net(n, l2);
	insert_tail_net(n, l3);

	// Affichage du réseau (pas visuel, seulement)
	print_network(n);

	// test des 8 combinaisons possibles pour etre exhaustif
	int t1[3] = {1, 1, 1}; // -> 0
	int t2[3] = {1, 1, 0}; // -> 1
	int t3[3] = {1, 0, 1}; // -> 1
	int t4[3] = {1, 0, 0}; // -> 1
	int t5[3] = {0, 1, 1}; // -> 0
	int t6[3] = {0, 1, 0}; // -> 0
	int t7[3] = {0, 0, 1}; // -> 0
	int t8[3] = {0, 0, 0}; // -> 0
	out_network(n, t1, 3);
	out_network(n, t2, 3);
	out_network(n, t3, 3);
	out_network(n, t4, 3);
	out_network(n, t5, 3);
	out_network(n, t6, 3);
	out_network(n, t7, 3);
	out_network(n, t8, 3);

	delete_network(n);
	free(n);
*/

	Network n;
	int choix;
	do {
		printf("Choisissez une option:\n");
		printf("1. Créer un réseau\n");
		printf("2. Donner des entrées au réseau\n");
		printf("3. Supprimer le réseau\n");
		printf("4. Sortir\n");
		scanf("%d", &choix);

		switch (choix) {
			case 1:
				n = user_created_network();
				printf("Réseau créé.\n");
				break;
			case 2:
				if (n != NULL) {
					provide_inputs(n);
				} else {
					printf("Veuillez d'abord créer un réseau.\n");
				}
				break;
			case 3:
				if (n != NULL) {
					delete_network(n);
					free(n);
					n = NULL;
					printf("Réseau supprimé.\n");
				} else {
					printf("Aucun réseau à supprimer.\n");
				}
				break;
			case 4:
				if (n != NULL) {
					delete_network(n);
					free(n);
				}
				printf("Sortie.\n");
				break;
			default:
				printf("Option invalide. Veuillez réessayer.\n");
				break;
		}
	} while (choix != 4);
	return 0;
}