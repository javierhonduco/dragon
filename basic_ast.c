#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

typedef struct{
	int length;
	int cursor;
	Node* array;
}DynamicArray;

struct Node{
	char* type;
	char* value;
	int is_leaf;
	DynamicArray* children;
};


DynamicArray*
init_array(int length)
{
	DynamicArray* array = malloc(sizeof(DynamicArray));
	
	array->length	= length;
	array->cursor	= 0;
	array->array	= malloc(length*sizeof(Node));
	
	return array;
}


void
printNode(Node* node)
{
	printf("%s\n", node->type);
}

void
printArray(DynamicArray* array)
{
	int i;
	if(array->cursor==0){
		printf("Empty array\n");
	}
	for(i=0; i<array->cursor; i++){
		printNode(&(array->array)[i]);
	}
}

void
printAST(Node* node, int level)
{
	printNode(node);
	
	while(level>=0){
		printf("\t");
		level--;
	}
	int i;
	
	int new_level = level+1;
	for(i=0; i<2; i++){
		if(node->is_leaf!=1){
			printAST(&node->children->array[i], new_level);
		}
	}
}

Node*
create_node(char* type, char* value, int is_leaf)
{
	DynamicArray* array = init_array(10);
	Node* node = malloc(sizeof(Node));
	node->type = type;
	node->value = value;

	node->is_leaf = is_leaf;
	node->children = array;

	return node;
}

void
free_node(Node* node)
{
	free(node);
}

void
array_append(DynamicArray* array, Node* node){
	
	if((array->cursor)+1 <= array->length){
		array->array[array->cursor] = *node;
		array->cursor++;
	}else{
		int new_length = (array->length) * 2;
		array->length = new_length;
		array->array = realloc(array->array, new_length*sizeof(Node));
		array_append(array, node);
	}
}

void
add_child(Node* parent, Node* child)
{
	array_append(parent->children, child);
}

int
main(int argc, char* argv[])
{
	Node* node1 = create_node("hello", "lol", 0);

	Node* node2 = create_node("bai", "hehe", 1);
	Node* node3 = create_node("wat", "such", 1);
	
	add_child(node1, node2);
	add_child(node1, node3);
	printArray(node1->children);

	printAST(node1, 0);
	
	DynamicArray* array = init_array(2);
	array_append(array, node1);
	array_append(array, node2);
	array_append(array, node3);
	array_append(array, node2);
	array_append(array, node1);
	array_append(array, node2);

	printArray(array);

}
