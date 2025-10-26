#include "reseau.h"

Network init_layer_list() {
	Network n = (Network)malloc(sizeof(Layer_list));
	n->size = 0;
	n->head = NULL;
	n->tail = NULL;
	return n;
}

void delete_tail_net(Network n) {
	if (n->size == 0) {
		printf("List already empty !\n");
	} else if (n->size == 1) {
		n->size = 0;
		release_layer(n->tail->value);
		free(n->tail);
		n->head = NULL;
		n->tail = NULL;
	} else if (n->size >= 2) {
		n->size --;
		Layer* new_last = n->tail->previous;
		n->tail->previous->next = NULL;
		release_layer(n->tail->value);
		free(n->tail);
		n->tail = new_last;
	}
}

void insert_tail_net(Network n, List_neur value) {
	// value est une liste de neurones (une couche) deja initialisé, alloué et valide
	Layer* new_last = (Layer*)malloc(sizeof(Layer));
	new_last->next = NULL;
	new_last->previous = n->tail;
	new_last->value = value;
	if(n->size == 0) {
		n->head = new_last;
	} else {
		n->tail->next = new_last;
	}
	n->tail = new_last;
	n->size++;
}

void print_network(Network n) {
	Layer* current_layer = n->head;
	int i = 1;
	while (current_layer != NULL) {
		printf("Couche %d :\n", i);
		display_layer(current_layer->value);
		printf("\n");
		current_layer = current_layer->next;
		i++;
	}
}

void insert_head_net(Network n, List_neur value) {
	Layer* new_first = (Layer*)malloc(sizeof(Layer));
	new_first->next = n->head;
	new_first->previous = NULL;
	new_first->value = value;
	if (n->size == 0) {
		n->tail = new_first;
	} else {
		n->head->previous = new_first;
	}
	n->head = new_first;
	n->size++;
}

void delete_head_net(Network n) {
	if (n->size == 0) {
		printf("List already empty !\n");
	} else if (n->size == 1) {
		n->size = 0;
		release_layer(n->head->value);
		free(n->head);
		n->head = NULL;
		n->tail = NULL;
	} else if (n->size >= 2) {
		n->size--;
		Layer* new_first = n->head->next;
		n->head->next->previous = NULL;
		release_layer(n->head->value);
		free(n->head);
		n->head = new_first;
	}
}

bool is_empty_list_net(Network n) {
	return n->size == 0;
}

void delete_network(Network n) {
	// On fait ici le choix de ne pas libérer la structure 
	// d'entête qui contient les pointeurs, au cas où elle serait
	// reutilisée ensuite
	while (!is_empty_list_net(n)) {
		delete_head_net(n);
	}
}

int len_network(Network n) {
	return n->size;
}

List_neur get_element_at_given_pos_network(Network n, int pos) {
	if (pos < 0 || pos >= len_network(n)) {
		printf("index out of range !!!!!!!!\n");
		return NULL;
	}
	Layer* current_pos = n->head;
	while (pos != 0) {
		current_pos = current_pos->next;
		pos--;
	}
	return current_pos->value;
}

int out_network(Network n, int* input_list, int nb_inputs) {
	// Le choix a été fait d'afficher les étapes lors de l'execution de cette fonction afin de vérifier l'execution correcte de la fonction
	int tours_necessaires = len_network(n);

	// Ces deux listes acuilleront les entrées et sorties des differentes couches
	int* input_layer = NULL;
	int* output_layer = NULL;
	int size_output_layer = nb_inputs; // Seulement pour la première couche, apres on le met à jour

	for (int i = 0; i < tours_necessaires; i++) {
		List_neur couche_consideree = get_element_at_given_pos_network(n, i);

		if (i == 0) {
			input_layer = input_list;
			output_layer = out_layer(couche_consideree, size_output_layer, input_layer);

			// Affichage de la couche entrée
			printf("Couche entree : ");
			for (int j = 0; j < size_output_layer; j++) {
				printf(" %d ", input_layer[j]);
			}
			printf("\n");
		} else {
			if (i > 1) {
				free(input_layer);
			}
			input_layer = output_layer;
			output_layer = out_layer(couche_consideree, size_output_layer, input_layer);

			printf("Sortie de la %d eme couche : ", i);
			for(int j = 0; j < size_output_layer; j++) {
				printf(" %d ", input_layer[j]);
			}
			printf("\n");
		}

		// Mise à jour de la taille de la liste sortie
		size_output_layer = len_list_neur(couche_consideree);
	}
	
	int result = output_layer[0];
	free(output_layer);

	printf("Sortie du réseau : %d\n\n", result);
	return result;
}
