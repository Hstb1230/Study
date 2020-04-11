#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef struct stu_info
{
	char name[10];
	int age;
} elem_type;

typedef struct node
{
	elem_type data;
	node * next;
} list_node, *list_ptr;

list_ptr create_node();
void insert_node(list_ptr & list);
void print_list(list_ptr list);

int main(int argc, const char * args[])
{
	list_ptr list = NULL;
	while(true)
	{
		printf("Opt\n");
		printf("1. Create List\n");
		printf("2. Insert Node\n");
		printf("3. Print  List\n");
		printf("4. Quit\n");
		char opt;
		// Filter line break in the buffer
		while((opt = getchar()) == '\n');
		switch(opt)
		{
			case '1':
			{
				list = create_node();
				break;
			}
			case '2':
			{
				insert_node(list);
				break;
			}
			case '3':
			{
				print_list(list);
				break;
			}
			case '4':
			{
				return 0;
			}
		}
	}
	return 0;
}

list_ptr create_node()
{
	list_ptr node = new list_node();
	node->next = NULL;
	return node;
}

void insert_node(list_ptr & node)
{
	// find the linked-list's end
	if(node != NULL && node->next != NULL)
		return insert_node(node->next);
	string name;
	int age;
	cin >> name >> age;
	list_ptr next = create_node();
	strcpy(next->data.name, name.c_str());
	next->data.age = age;
	// The next is the node if the node is null
	if(node == NULL)
		node = next;
	else
		node->next = next;
	return;
}

void print_list(list_ptr node)
{
	if(node == NULL)
		return;
	printf("name: %10s , age: %2d\n", node->data.name, node->data.age);
	print_list(node->next);
}

