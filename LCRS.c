//Generate Left Child Right Sibling tree

#include<stdio.h>
#include<stdlib.h>

struct node {
	int info;
	struct node *llink;
	struct node *rsib;
};

typedef struct node *node;
node q=NULL;
static int gName=0;

//Create new node in tree
node getnode() {
	node N;
	N=(node)malloc(sizeof(struct node));
	if(N==NULL) {
		printf("\n No memory ");
		exit(0);
	}
	N->llink=NULL;
	N->rsib=NULL;
	return N;
}

//Search for first info element in the current tree
void Search(int info,node root) {
	if(root==NULL) return;
	if(root->info==info) {
		q=root;
		return;
	}
	Search(info,root->llink);	
	if(root->rsib!=NULL) {	
		Search(info,root->rsib);
		root=root->rsib;
	}
}

//Insert new info to the tree
node Insert(int info1,int info2,node root) {
	node temp1,temp2;
	temp1=getnode();
	if(root==NULL) {
		if(info1==info2) {
			temp1->info=info1;
			root=temp1;
			return root;
		}
		temp2=getnode();
		temp1->info=info1;
		temp2->info=info2;
		root=temp1;
		temp1->llink=temp2;
		return root;
	}
	q=NULL;
	Search(info1,root);
	//If first info does not exist in the tree, exit
	if(q==NULL) {
		printf("\n Insertion not possible ");
		return root;
	}
	//else insert
	if(q->llink==NULL) {
		temp1->info=info2;
		q->llink=temp1;
		return root;
	}
	q=q->llink;
	while(q->rsib!=NULL) {
		q=q->rsib;
	}
	temp1->info=info2;
	q->rsib=temp1;
	return root;
}

//Display the traversal of tree
void Display(node root) {
	if(root==NULL)
		return;
	printf(" %d\t",root->info);
	Display(root->llink);
	if(root->rsib!=NULL) {	
		Display(root->rsib);
		root=root->rsib;
	}
}

//Display dotty output for tree
void preorderDotDump (node root, FILE* outputFile)
{
	if (root != NULL) 
	{
		fprintf (outputFile, "%d [label=%d,color=black];\n",root->info, root->info);
		if (root->llink != NULL) 
			fprintf (outputFile, "%d -> %d ;\n", root->info, (root->llink)->info);
        if (root->rsib != NULL) {
        	fprintf (outputFile, "%d -> %d [style=dashed,color=blue];\n", root->info, (root->rsib)->info);
          	fprintf(outputFile, "%d [shape=rect];\n",(root->rsib)->info);
        }
        preorderDotDump (root->llink, outputFile);
        if(root->rsib!=NULL) {
        	preorderDotDump (root->rsib, outputFile);
        	root=root->rsib;
        }
    }
}

void dotDump(node root, FILE *outFile)
{
	gName++;
	fprintf (outFile, "digraph BST { \n",gName);
	preorderDotDump (root, outFile);
    fprintf (outFile, "}\n");
}

FILE *OutputFile;
main() {
	FILE *pipe;
	int k1,k2,ch,n,i,choice;
	node R=NULL;
	OutputFile = fopen ("lcrs.dot", "w");
    fclose (OutputFile);
	do {
		printf("Choose the operation you want to perform\n 1.Insert\n 2.Display\n");
		scanf("%d",&ch);
		switch(ch) {
			case 1: //Insert
				printf("Enter number of nodes (If 1, enter 2 and path of form n1->n1)\n");
				scanf("%d",&n);
				printf("\n Enter nodes in the form n1->n2 ");
				for(i=1;i<n;i++) {
					scanf("%d%d",&k1,&k2);
                    R=Insert(k1,k2,R);
                }
                break;
            case 2: //Display pre-order and dotty for tree
				printf("The pre-order traversal of the tree is \n");
				Display(R);
				printf("\n");
                OutputFile=fopen("lcrs.dot","a");
				if(OutputFile != NULL) {	
					dotDump(R,OutputFile);
					fclose(OutputFile);	
				}
				pipe=popen("dot -Tps lcrs.dot -o lcrs.ps","w");
				pclose(pipe);
				pipe=popen("evince lcrs.ps","r"); 
				pclose(pipe);
                break;
            default:
				printf("Invalid choice!\n");
				break;
        }
		printf("Do you want to continue? (1 for continue)\n");
		scanf("%d",&choice);
	}while(choice==1);
}
