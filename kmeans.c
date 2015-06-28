//K-Means cluster program
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x4,y4,v,i,j,a[100][2],x3,y3,c[5][2];
float xm,ym,d,min=999;

//Calculate Euclidian distance
void distance(float xm,float ym,int arr[100][2],int n) {
	int temp;
    for(temp=0;temp<n;temp++) {
        d=sqrt(pow((xm-arr[temp][0]),2)+pow((ym-arr[temp][1]),2));
        if(d<min && d != 0) {
            min=d;
            x3=arr[temp][0];
            y3=arr[temp][1];
        }
    }
    min=99;
}
//compute assumed centroids
int compute(int x2,int y2,int x1,int y1,int arr[100][2],int n) {
    xm=(x1+x2)/2.0;
    ym=(y1+y2)/2.0;
    distance(xm,ym,arr,n);
}

//Update new centroid point for given cluster
int updcent(int arr[100][2],int n,int val) {
	float sum1=0,sum2=0;
	int k;
	for(k=0;k<n;k++) {
		sum1=sum1+arr[k][0];
		sum2=sum2+arr[k][1];
	}
	distance(sum1/n,sum2/n,arr,n);
	c[val][0]=x3;
	c[val][1]=y3;
}

//Display the cluster points
FILE *outputFile;
void display(int clus[100][2],int value,FILE *pipe,int k) {
	pipe=popen("gnuplot -persist","w");
	outputFile=fopen("K-means.txt","w");
    for(i=0;i<value;i++) {
    	fprintf(outputFile,"%d\t%d\n",clus[i][0],clus[i][1]);
		printf("(%d,%d)\t",clus[i][0],clus[i][1]);
	}
	fclose(outputFile);
	fprintf(pipe,"set style function linespoints\n");
	fprintf(pipe,"plot 'K-means.txt' using 1:2 lc '%d'\n",k);
	pclose(pipe);

}
void main() {
	FILE *pipe;
	outputFile=fopen("K-means.txt","w");
	fclose(outputFile);
    int x1=0,y1=0,flag,x2=99,y2=99,p=0,q=0,r=0,s=0,t=0,c1[100][2],c2[100][2],c3[100][2],c4[100][2],c5[100][2];
    printf("Initial set of 100 points\n");
    for(i=0;i<100;i++) {
            a[i][0]=rand()%40;
            a[i][1]=rand()%40;
            printf("(%d,%d)\t",a[i][0],a[i][1]);
    }
    //Computation of assumed 5 centroids
    for(i=0;i<100;i++) {
        if(a[i][0]<x2)
            x2=a[i][0];
        if(a[i][1]<y2)
            y2=a[i][1];
        if(a[i][0]>x1)
            x1=a[i][0];
        if(a[i][1]>y1)
            y1=a[i][1];
    }
    distance(x2,y2,a,100);
    c[0][0]=x2=x3;
    c[0][1]=y2=y3;
    distance(x1,y1,a,100);
    c[4][0]=x1=x3;
    c[4][1]=y1=y3;
    compute(x2,y2,x1,y1,a,100);
    c[2][0]=x3;
    c[2][1]=y3;
    x4=x3;
    y4=y3;
    compute(x2,y2,x3,y3,a,100);
    c[1][0]=x3;
    c[1][1]=y3;
    compute(x4,y4,x1,y1,a,100);
    c[3][0]=x3;
    c[3][1]=y3;
    printf("\nAssumed cluster centroids\n");
    for(i=0;i<5;i++)
            printf("(%d,%d)\t",c[i][0],c[i][1]);
    //Calculate distance between remaining 95 points with the 5 cluster points
    for(i=0;i<100;i++) {
        for(j=0;j<5;j++) {
            d=sqrt(pow((a[i][0]-c[j][0]),2)+pow((a[i][1]-c[j][1]),2));
            if( d==0 ) {
                flag=1;
                break;
            }
            if(d<min) {
                v=j;
                min=d;
            }
        }
        if(flag==1) {
            min=99;
            flag=0;
            continue;
        }
        switch(v) {
            case 0:
                c1[p][0]=a[i][0];
                c1[p][1]=a[i][1];
                p++;
				updcent(c1,p,0);
                break;
            case 1:
                c2[q][0]=a[i][0];
                c2[q][1]=a[i][1];
                q++;
				updcent(c2,q,1);
                break;
            case 2:
                c3[r][0]=a[i][0];
                c3[r][1]=a[i][1];
                r++;
				updcent(c3,r,2);
                break;
            case 3:
                c4[s][0]=a[i][0];
                c4[s][1]=a[i][1];
                s++;
				updcent(c4,s,3);
                break;
            case 4:
                c5[t][0]=a[i][0];
                c5[t][1]=a[i][1];
                t++;
				updcent(c5,t,4);
                break;
            default:printf("Error occurred!");
                break;
        }
        min=999;
    }
    //Display points in each cluster
	printf("\n\nCluster 1\n");
    printf("Number of points in cluster 1 is %d\n",p);
    display(c1,p,pipe,1);	
    printf("\nCluster 2\n");
    printf("Number of points in cluster 2 is %d\n",q);
   	display(c2,q,pipe,2);
    printf("\nCluster 3\n");
   	printf("Number of points in cluster 3 is %d\n",r);
    display(c3,r,pipe,3);
    printf("\nCluster 4\n");
    printf("Number of points in cluster 4 is %d\n",s);
    display(c4,s,pipe,4);
    printf("\nCluster 5\n");
    printf("Number of points in cluster 5 is %d\n",t);
    display(c5,t,pipe,5);
	//Final 5 cluster centroids
	printf("\nUpdated cluster centroids are\n");
	for(i=0;i<5;i++)
		printf("(%d,%d)\t",c[i][0],c[i][1]);
}
