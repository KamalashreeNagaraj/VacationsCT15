//Program to compute K-nearest neighbours in recommender system
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node {
	int head;
	int kna[10];
	int count;
	struct node *link;
};
typedef struct node *node;

float cosine[10],cosd,min,sq1,sq2,sum;
int i,j,k,p,a[943][1682],v;

node getnode(int usr) {
	node N;
	N=(node)malloc(sizeof(struct node));
	N->link=NULL;
	N->count=0;
	N->head=usr;
	return N;
}

node insert(node N,node R) {
	node p;
	if(R==NULL)
		return N;
	p=R;
	while(p->link != NULL)
		p=p->link;
	p->link=N;
	return R;
}

node computeKNN(node R) {
	node temp;
	for(i=0;i<943;i++) {
		temp=getnode(i);
		for(j=0;j<943;j++) {
			if(i==j)
				continue;
			sq1=0;
			sq2=0;
			sum=0;
			for(k=0;k<1682;k++) {
				if(a[i][k] != 0)
					sq1 += pow(a[i][k],2);
				if(a[j][k] != 0)
					sq2 += pow(a[j][k],2);
				if(a[i][k] != 0 && a[j][k] != 0)
					sum += a[i][k] * a[j][k];
			}
			cosd=sum/(sqrt(sq1) * sqrt(sq2));
			if(temp->count < 10) {
				temp->kna[temp->count]=j;
				cosine[temp->count]=cosd;
				temp->count++;
				continue;
			}
			min=1;
			for(p=0;p<10;p++) {
				if(cosine[p]<min) {
					min=cosine[p];
					v=p;
				}
			}
			if(cosine[v]<cosd) {
				temp->kna[v]=j;
				cosine[v]=cosd;
			}
		}
		R=insert(temp,R);
	}
	return R;
}
				
void main() {
	node R=NULL,p;
	int ur,item,user,c,rating,extra,index;
	for(i=0;i<100000;i++) {
			scanf("%d%d%d%d",&ur,&item,&rating,&extra);
			a[ur-1][item-1]=rating;
	}
	R=computeKNN(R);
	p=R;
	/*while( p != NULL) {
		printf("K-nearest neighbours of head %d\n",p->head);
		for(i=0;i<10;i++) 
			printf("%d\t",p->kna[i]);
		printf("\n");
		p=p->link;
	}*/
	printf("Enter the user you want to recommend for : \n");
	scanf("%d",&user);
	printf("Recommended items are\n");
	while(1) {
		if(p->head==user)
			break;
		p=p->link;
	}
	for(j=0;j<1682;j++) {
		c=0;
		for(k=0;k<10;k++) {
			index=p->kna[k];
			if(a[index][j] != 0 && a[user][j] == 0)
				c++;
		}
		if(c>6)
			printf("%d\t",j);
	}
}
