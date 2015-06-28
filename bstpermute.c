//Generate all possible binary search trees given 'N' key values
#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *llink,*rlink,*pptr;
};

int val;
static int gName=0;
typedef struct node *node;
node root=NULL;

//creates new node
node getnode() {
	node x;
	x=(node)malloc(sizeof(struct node));
	if(x==NULL) {
		printf("Out of memory\n");
		exit(0);
	}
	return x;
}

//insert new node into binary search tree
node insert(int item,node root) {
	node temp,cur,prev;
	temp=getnode();
	temp->data=item;
	temp->llink=temp->rlink=NULL;
	temp->pptr=NULL;
	//if tree is initially empty
	if(root == NULL )
		return temp;
	prev=NULL;
	cur=root;
	//else insert based on the key value
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

//generate dotty output for the BST
void preorderDotDump (node root, FILE* outputFile) {
	if (root != NULL) {
		fprintf (outputFile, "%d [label=%d,color=black];\n",root->data, root->data);
		if (root->llink != NULL) 
		    fprintf (outputFile, "%d -> %d ;\n", root->data, (root->llink)->data);
        if (root->rlink != NULL)
           	fprintf (outputFile, "%d -> %d;\n", root->data, root->rlink->data);
        preorderDotDump (root->rlink, outputFile);
        preorderDotDump (root->llink, outputFile);
    }
}

void dotDump(node root, FILE *outFile) {
	gName++;
	fprintf (outFile, "digraph BST {\n",gName);
	preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}

//Construct tree for every permutation of key values
FILE *output;
void printArray(int *a,int n) {
	int i;
	for(i=0;i<=n;i++)	
		root=insert(a[i],root);
	output=fopen("bstpermute.dot","a");
	if(output != NULL) {
		dotDump(root,output);
	}
	fclose(output);	
	free(root);
}

//Generate permutations of key values
void swap (int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(int *a, int i, int n) {
	int j;
	if(i==n)
		printArray(a,n);
	else {
        for (j = i; j <= n; j++) {
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); //backtrack
       }
   }
}

void main() {
	FILE *pipe;
	int a[]={1,2,3,4,5};	
	int n=5;
	//clear file
	output=fopen("bstpermute.dot","w");
	fclose(output);
	permute(a,0,n-1);
	pipe=popen("dot -Tps bstpermute.dot -o bstpermute.ps","w");
	pclose(pipe);	
	pipe=popen("evince bstpermute.ps","r"); 
	pclose(pipe);
}
