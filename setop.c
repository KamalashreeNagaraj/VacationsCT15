//Program to perform operations on SETs
#include<stdio.h>
#include<stdlib.h>

struct node {
	int index;
	int a;
	struct node *link;
};

typedef struct node *node;
node head1=NULL;
node head2=NULL;
node head3=NULL;

//Insert new node into the linked list
node insert(int key,node head) {
	node temp=(node)malloc(sizeof(node));
	node p;
	int k_index;
	//If linked list is empty
	if(head==NULL) {
		temp->index=(key/32)*32;
		temp->a = 1 << (key % 32);
		temp->link=NULL;
		head=temp;
		return head;
	}
	//else compare index and set bit in corresponding node
	k_index=(key/32)*32;
	p=head;
	while(p != NULL) {
		if(k_index > p->index) {
			p=p->link;
			continue;
		}
		if( k_index == p->index) {
			p->a |= 1 << (key%32);
			return head;
		}
		else {
			node q;
			q=head;
			if(p==head) {
				temp->index=(key/32)*32;
				temp->a = 1 << (key%32);
				temp->link=p;
				head=temp;
				return head;
			}
			while(q->link != p) {
				q=q->link;
			}
			temp->index=(key/32)*32;
			temp->a |= 1 << (key%32);
			temp->link=p;
			q->link=temp;
			return head;
		}
	}
	//if node for corresponding index does not exist, create node
	p=head;
	while(p->link != NULL)
		p=p->link;
	temp->index=(key/32)*32;
	temp->a |= 1 << (key%32);
	temp->link=NULL;
	p->link=temp;
	return head;
}

//Display the set elements
void display(node head) {
	node p;
	int i,y,x,b;
	p=head;
	while (p != NULL) {
		x=p->index;
		y=0;
		for(i=x;i<x+32;i++) {
			b=p->a;
			if( (b >> y) & 0x1) 
				printf("%d\t",i);
			y++;
		}
		p=p->link;
	}
	printf("\n");
}

//Compute union of two sets and store the result in new linked list
node gen_union(node p,node q,node head3) {
	int i,y,x,b;
	while (p != NULL) {
		x=p->index;
		y=0;
		for(i=x;i<x+32;i++) {
			b=p->a;
			if( (b >> y) & 0x1) 
				head3=insert(i,head3);
			y++;
		}
		p=p->link;
	}
	while (q != NULL) {
		x=q->index;
		y=0;
		for(i=x;i<x+32;i++) {
			b=q->a;
			if( (b >> y) & 0x1) 
				head3=insert(i,head3);
			y++;
		}
		q=q->link;
	}
	return head3;
}

//Compute intersection of two sets and store result in new linked list
node intersect(node h1,node h2,node head3) {
	node p,q;
	p=h1;
	q=h2;
	int b,x,y,z,d,c,i;
	while(p != NULL && q != NULL) {
		if(p->index == q->index) {		
			x=p->index;
			z=0;
			for(i=x;i<x+32;i++) {
				b=p->a;
				c=q->a;
				d=b & c;			
				if( (d >> z) & 0x1) 
					head3=insert(i,head3);
				z++;
			}
			q=q->link;
			p=p->link;
		}
		else if(p->index < q->index)
			p=p->link;
		else
			q=q->link;
	} 
	return head3;
}

//Compute set A-B and store result in new linked list
node adiffb(node h1,node h2,node head3) {
	node p,q;
	p=h1;
	q=h2;
	int x,d,z,i;
	while( p != NULL && q != NULL) {
		if(p->index == q->index) {
			x=p->index;
			z=0;
			// (A xor B) and A
			for(i=x;i<x+32;i++) {
				d=(p->a ^ q->a) & p->a;
				if( (d>>z) & 0x1)
					head3=insert(i,head3);
				z++;
			}
			q=q->link;
			p=p->link;
		}
		else if(p->index < q->index) {
			x=p->index;
			z=0;
			for(i=x;i<x+32;i++) {
				d=p->a ;
				if( (d>>z) & 0x1)
					head3=insert(i,head3);
				z++;
			}
			p=p->link;
		}
		else
			q=q->link;
	}
	return head3;
}

void main() {
	int n1,n2,j,v,ch;
	int choice;
	//Insert elements into the sets
	printf("Enter the number of elements in set 1\n");
	scanf("%d",&n1);
	for(j=0;j<n1;j++) {
		v=rand()%50;
		printf("%d\t",v);
		head1=insert(v,head1);
	}
	printf("\nEnter the number of elements in set 2\n");
	scanf("%d",&n2);
	for(j=0;j<n2;j++) {
		v=rand()%50;
		printf("%d\t",v);
		head2=insert(v,head2);
	}
	do {
		printf("\nEnter the operation you want to perform :\n 1.Display set1\n 2.Display set2\n 3.Perform Union of two sets\n 4.Perform Intersection of two sets\n 5.Perform Set1-Set2\n 6.Perform Set2-Set1\n");
		scanf("%d",&ch);
		switch(ch) {
			case 1: display(head1);
					break;
			case 2: display(head2);
					break;
			case 3: head3=gen_union(head1,head2,head3);				
					display(head3);
					head3=NULL;
					break;
			case 4: head3=intersect(head1,head2,head3);
					display(head3);
					head3=NULL;
					break;
			case 5: head3=adiffb(head1,head2,head3);
					display(head3);
					head3=NULL;
					break;
			case 6: head3=adiffb(head2,head1,head3);
					display(head3);
					break;
			default: printf("Invalid choice\n");
					break;
		}
		printf("Do you want to continue?(1 for continue)\n");
		scanf("%d",&choice);
	}while(choice==1);
}
