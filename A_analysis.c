//Given 'N' transactions, find the item set(s) which most frequently occurs in the transactions
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node {
	int item;
	int index;
	struct node *link;
};

typedef struct node *node;
node head=NULL;

//Function to create a new node
node getnode() {
	node root=(node)malloc(sizeof(struct node));
	root->item=0;
	root->link=NULL;
	root->index=0;
	return root;
}

//Function to insert into a node
node Insert(int itemop,int h,node root) {
	node p,q,temp;
	//If root is NULL
	if(root==NULL) {
		root=getnode();
		root->index=h;
		root->item = (1<<(itemop-1));
		return root;
	}
	p=root;
	q=root;
	//In same transaction
	while(p != NULL) {
		if(p->index==h) {
			p->item |= (1<<(itemop-1));
			return root;
		}
		p=p->link;
	}
	//Create new node for new transaction
	while(q->link != NULL)
		q=q->link;
	temp=getnode();
	temp->item = (1<<(itemop-1));
	temp->index=h;
	q->link=temp;
	return root;
}

//To compute the support of all item sets and compare with Minimum support
int size=0,minsup=3,array[100];
void support(node root) {
	int i,j,sup,a,b;
	node p;
	for(i=(pow(2,6)-1);i>0;i--) {
		p=root;
		sup=0;
		while(p != NULL) {
			a = p->item & i;
			if(a==i) {
				sup++;
				//greater than minimum support count
				if(sup >= minsup) {
					//empty array
					if(size==0) {
						array[size]=i;
						size++;
						break;
					}
					//if super set of transaction already exists in array
					for(j=0;j<size;j++) {
						b=array[j] | i;
						if(b==array[j])
							break;
					}
					//If it doesn't exist, insert into array
					if(j==size) {
						array[size]=i;
						size++;
					}
				}
			}
			p=p->link;
		}
	}
}

void main() {
	int t,i,j,ch,op,a;
	char items[6][8]={"Bread\0","Milk\0","Diaper\0","Beer\0","Eggs\0","Cola\0"};
	printf("Enter the number of transactions\n");
	scanf("%d",&t);
	for(i=1;i<=t;i++) {
		printf("Enter the items for transaction %d\n",i);
		do {
			printf("Enter the item(s) you want to purchase\n 1.Bread\n 2.Milk\n 3.Diaper\n 4.Beer\n 5.Eggs\n 6.Cola\n");
			scanf("%d",&op);
			head=Insert(op,i,head);
			printf("Do you want to purchase more items? (1 for continue)\n");
			scanf("%d",&ch);
		}while(ch==1);
	}
	printf("The items frequently used are\n");
	support(head);
	//display the frequent item set(s)
	for(i=0;i<size;i++) {
		for(j=0;j<6;j++) {
			a=array[i];
			if( (a >> j) & 0x1)
				printf("%s\t",items[j]);
		}
		printf("\n");
	}
}	
