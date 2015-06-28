//Program to generate pre-order,in-order and post-order traversals for any randomly generated tree
#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *llink,*rlink,*pptr;
};

int val;
typedef struct node * node;

//Creates new tree node
node getnode() {
	node x;
	x=(node)malloc(sizeof(struct node));
	if(x==NULL) {
		printf("Out of memory\n");
		exit(0);
	}
	return x;
}

//Inserts new node to the tree
node insert(int item,node root) {
	node temp,cur,prev;
	temp=getnode();
	temp->data=item;
	temp->llink=temp->rlink=NULL;
	temp->pptr=NULL;
	//If tree is initially empty
	if(root == NULL )
		return temp;
	prev=NULL;
	cur=root;
	//Else attach node to the tree based on the data value
	while(cur != NULL) {
		prev=cur;
		if(item==cur->data) {
			val++;
			return root;
		}
		if(item<cur->data)
			cur=cur->llink;
		else
			cur=cur->rlink;
	}
	if(item < prev->data)
		prev->llink=temp;
	else
		prev->rlink=temp;
	temp->pptr=prev;
	return root;
}

//Gives pre-order traversal of constructed tree
void Preorder(node root) {
	if(root == NULL)
		return;
	printf("%d\t",root->data);
	Preorder(root->llink);
	Preorder(root->rlink);
}

//Gives in-order traversal of constructed tree
void Inorder(node root) {
	if(root == NULL)
		return;
	Inorder(root->llink);
	printf("%d\t",root->data);
	Inorder(root->rlink);
}

//Gives post-order traversal of constructed tree
void Postorder(node root) {
	if(root == NULL)
		return;
	Postorder(root->llink);
	Postorder(root->rlink);
	printf("%d\t",root->data);
}

void main() {
	node root,temp;
	int i,n,x;
	root='\0';
	printf("Enter the number of nodes you need\n");
	scanf("%d",&val);
	//Generates random data values for the tree nodes
	for(i=0;i<val;i++) {
		x=rand()%30;
		root=insert(x,root);
	}
	Inorder(root);
	printf("\n");
	Preorder(root);
	printf("\n");
	Postorder(root);
}
