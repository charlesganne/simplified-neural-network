#include "listes_doublement_chainees_entiers.h"

void delete_tail_int(List_int l) {
	if (l->size == 0) {
		printf("List already empty !\n");
	} else if (l->size == 1) {
		l->size = 0;
		free(l->tail);
		l->head = NULL;
		l->tail = NULL;
	} else if (l->size >= 2) {
		l->size --;
		Element_int* new_last = l->tail->previous;
		l->tail->previous->next=NULL;
		free(l->tail);
		l->tail=new_last;
	}
}

List_int init_list_int() {
	List_int l = (List_int)malloc(sizeof(List_struct_int));
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	return l;
}

void insert_tail_int(List_int l, int value) {
	Element_int* new_last = (Element_int*)malloc(sizeof(Element_int));
	new_last->next = NULL;
	new_last->previous=l->tail;
	new_last->value=value;
	if (l->size == 0) {
		l->head=new_last;
	} else {
		l->tail->next=new_last;
	}
	l->tail=new_last;
	l->size++;
}

void print_list_int(List_int l) {
	Element_int* sequence=l->head;
	printf("[");
	while (sequence != NULL) {
		printf(" %d ", sequence->value);
		sequence=sequence->next;
	}
	printf("]\n");
}

void insert_head_int(List_int l, int value) {
	Element_int* new_first = (Element_int*)malloc(sizeof(Element_int));
	new_first->next = l->head;
	new_first->previous=NULL;
	new_first->value=value;
	if (l->size == 0) {
		l->tail=new_first;
	} else {
		l->head->previous=new_first;
	}
	l->head=new_first;
	l->size++;
}

void delete_head_int(List_int l) {
	if (l->size == 0) {
		printf("List already empty !\n");
	} else if (l->size > 0) {
		l->size --;
		Element_int* new_first = l->head->next;
		free(l->head);
		l->head=new_first;
	}
}

bool is_empty_list_int(List_int l) {
	return l->size == 0;
}

void delete_list_int(List_int l) {
	// On fait ici le choix de ne pas liberer la structure 
	// d'entête qui contient les pointeurs, au cas où elle serait
	// reutilisée ensuite
	while (!is_empty_list_int(l)) {
		delete_head_int(l);
	}
}

int len_list_int(List_int l) {
	return l->size;
}

int get_element_at_given_pos_list_int(List_int l, int pos) {
	if (pos < 0 || pos >= len_list_int(l)) {
		printf("index out of range !!!\n");
		return -1;
	}
	Element_int* current_pos=l->head;
	while (pos != 0) {
		current_pos=current_pos->next;
		pos--;
	}
	return current_pos->value;
}