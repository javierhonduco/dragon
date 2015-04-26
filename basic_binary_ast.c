#include <stdio.h>

typedef struct Node Node;
struct Node{
	char* type;
	char* value;
	int is_leaf;
	Node* children[2];
};



void
printAST(Node* node, int level)
{
	printf("%s\n", node->type);
	
	while(level>=0){
		printf("\t");
		level--;
	}
	int i;
	
	int new_level = level+1;
	for(i=0; i<2; i++){
		if(node->is_leaf!=1){
			printAST(node->children[i], new_level);
		}
	}
}

Node
create_node(char* type, char* value, int is_leaf)
{
	Node node = {
		.type		= type, 
		.value		= value,
		.is_leaf	= is_leaf,
		.children = {0, 0}
	};
	return node;
}

void
add_child(Node* parent, Node* child)
{
	if((parent->children)[0]==0){
		(parent->children)[0] = child;
	}else if((parent->children)[1]==0){
		(parent->children)[1] = child;
	}else{
		printf("[error] Not enough space for a new child\n");
	}
}

int
main(int argc, char* argv[])
{
	Node node1 = create_node("hello", "lol", 0);
	Node node2 = create_node("bai", "hehe", 1);
	Node node3 = create_node("wat", "such", 1);
	
	add_child(&node1, &node2);
	add_child(&node1, &node3);

	printAST(&node1, 0);
}
