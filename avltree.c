//Tree-balancing using AVL tree
#include<stdio.h>
#include<stdlib.h>

struct node {
	int key;
	char BI;
	struct node *llink,*rlink;
};

int level,mark,i;
static int gName=0;
char dir[20];
typedef struct node *node;
node T,X,Y,Z,F,P;
node path[20];
char D;

//Function to create a node
node Create_Leaf(int key,node N) {
	N=(node)malloc(sizeof(struct node));
	if(N==NULL) {
		printf("\n No memory ");
		exit(0);
	}
	N->llink=N->rlink=NULL;
	N->BI='B';
	N->key=key;
	return N;
}

//Function to create header node
node Create_Head(int key,node H) {
	H=Create_Leaf(0,H);
	H->llink=H->rlink=H;
	return H;
}

//Function to Insert a key to the AVL tree
node Insert(int key,node H) {
	node NN;
	if(H->llink==H) {
		NN=Create_Leaf(key,NN);
		H->llink=NN;
		return H;
	}
	level=0;
	dir[level]='L';
	path[level]=H;
	T=H->llink;
	while(1) {
		if(key<T->key) {
			if(T->llink!=NULL) {
				level=level+1;
				path[level]=T;
				dir[level]='L';
				T=T->llink;
			}
			else {
				NN=Create_Leaf(key,NN);
				T->llink=NN;
				level=level+1;
				path[level]=T;
				dir[level]='L';
				break;
			}
		}
		else if(key>T->key) {
			if(T->rlink!=NULL) {
				level=level+1;
				path[level]=T;
				dir[level]='R';
				T=T->rlink;
			}
			else {
				NN=Create_Leaf(key,NN);
				T->rlink=NN;
				level=level+1;
				path[level]=T;
				dir[level]='R';
				break;
			}
		}
		else {
			printf("\n Key already exists ");
			return H;
		}
	}	
	mark=0;
	for(i=level;i>=1;i--) {
		P=path[i];
		if(P->BI!='B') {
			mark=i;
			break;
		}
	}
	for(i=mark+1;i<=level;i++) {
		if(key<path[i]->key)
			path[i]->BI='L';
		else 
			path[i]->BI='R';
	}
	if(mark==0)
		return H;
	D=dir[mark];
	X=path[mark];
	Y=path[mark+1];
	if(X->BI!=D) {
		X->BI='B';
		return H;
	}
	//rebalancing case 1
	if(Y->BI==D) {
		if(D=='L') {
			X->llink=Y->rlink;
			Y->rlink=X;
		}
		else {
			X->rlink=Y->llink;
			Y->llink=X;
		}
		X->BI=Y->BI='B';
		F=path[mark-1];
		if(X==F->llink)
			F->llink=Y;
		else 
			F->rlink=Y;
		return H;
	}
	//rebalancing case 2
	//changing structure link
	if(D=='L') {
		Z=Y->rlink;
		Y->rlink=Z->llink;
		Z->llink=Y;
		X->llink=Z->rlink;
		Z->rlink=X;
	}
	else {
		Z=Y->llink;
		Y->llink=Z->rlink;
		Z->rlink=Y;
		X->rlink=Z->llink;
		Z->llink=X;
	}
	F=path[mark-1];
	if(X==F->llink)
		F->llink=Z;
	else F->rlink=Z;
	//changing balance indicators
	if(Z->BI==D) {
		Y->BI=Z->BI='B';
		if(D=='L')
			X->BI='R';
		else 
			X->BI='L';
	}
	else if(Z->BI=='B')
		X->BI=Y->BI=Z->BI='B';
	else {
		X->BI=Z->BI='B';
		Y->BI=D;
	}
	return H;
}

//Function to generate pre-order traversal of AVL tree
void Preorder(node R) {
	if(R==NULL)
		return;
	printf(" %d, %c\t",R->key,R->BI);
	Preorder(R->llink);
	Preorder(R->rlink);
}

//Function to plot dotty for AVL tree
void preorderDotDump (node R, FILE* outputFile) {
	if (R != NULL) {
		fprintf (outputFile, "%d [label=%d,color=black];\n",R->key, R->key);
		if (R->llink != NULL) 
	        fprintf (outputFile, "%d -> %d ;\n", R->key, (R->llink)->key);
       	if (R->rlink != NULL)
      		fprintf (outputFile, "%d -> %d;\n", R->key, (R->rlink)->key);
        preorderDotDump (R->rlink, outputFile);
        preorderDotDump (R->llink, outputFile);
    }
}

void dotDump(node R, FILE *outFile) {
	gName++;
	fprintf (outFile, "digraph BST {\n",gName);
	preorderDotDump (R, outFile);
    	fprintf (outFile, "}\n");
}

FILE *OutputFile;
void main()
{
	FILE *pipe;
	node H=NULL;
	int n,k,j;
    int m=0;
	H=Create_Head(0,H);
	printf("\n Enter number of nodes ");
	scanf("%d",&n);
	//clear the file
    OutputFile = fopen ("avltree.dot", "w");
    fclose (OutputFile);
	//Insert elements(nodes) into tree
	for(j=0;j<n;j++) {
		k=++m;
		H=Insert(k,H);
	}
    if(H->llink!=NULL) {
		Preorder(H->llink);
		printf("\n");
	}
	else {
		Preorder(H->rlink);
		printf("\n");
	}
	OutputFile=fopen("avltree.dot","a");
	if(OutputFile != NULL) {
        if(H->llink!=NULL)
			dotDump(H->llink,OutputFile);
        else 
        	dotDump(H->rlink,OutputFile);
	}
	fclose(OutputFile);
    pipe=popen("dot -Tps avltree.dot -o avltree.ps","w");
	pclose(pipe);	
	pipe=popen("evince avltree.ps","r"); 
	pclose(pipe);
}
