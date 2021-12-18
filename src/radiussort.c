/* Caleb Sjostedt
COP3502C 
Covid Testing Sorting */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//node 
typedef struct node{
    int x;
    int y;
    double distance;
}node;

//prototypes
void insertionSort(node A[], int n);
void merge(node A[], int l, int m, int r);
void mergeSort(node A[], int l, int r, int threshold);
node *readData(FILE *ifp, int numInfected);
int compareTo(node *ptr1, node *ptr2);
int binarySearch(node A[], int l, int r, node x);

int globalX, globalY;

void main(){
    int numInfected, numQueries, threshold;
    
    FILE *ifp = fopen("input.txt", "r"); //change this filename to the dataset needed. No exception handling in C is a pain
    FILE *ofp = fopen("out.txt", "w");

    fscanf(ifp, "%d %d", &globalX, &globalY); //sets global X and Y position
    fscanf(ifp, "%d", &numInfected); //int n
    fscanf(ifp, "%d %d", &numQueries, &threshold); //queries and threshold 

    node *infected = readData(ifp, numInfected); //reads infected coords data

    mergeSort(infected, 0 , numInfected-1, threshold); //inits merge/insertion sorts

    node *queries = readData(ifp, numQueries); //reads queries coords data

    //file output lines
    for(int i=0; i<numInfected; i++){
        fprintf(ofp,"%-2d %-2d\n", infected[i].x, infected[i].y);
    }

    for(int j=0; j<numQueries; j++){
       int found = binarySearch(infected, 0, numInfected-1, queries[j]);
       if(found == -1){
           fprintf(ofp, "%d %d not found\n", queries[j].x, queries[j].y);
       } else {
           fprintf(ofp, "%d %d found at rank %d\n", queries[j].x, queries[j].y, found);
       }
    }
    
    free(infected);
    free(queries);
    fclose(ifp);
    fclose(ofp);
}

//reads data from file and returns Array
node *readData(FILE *ifp, int n){
    
    //mem alloc for struct Array
    node *temp = malloc(sizeof(node) * n);
    
    //scanning in info from text file
    for(int i=0; i<n; i++){
        
        fscanf(ifp, "%d %d", &temp[i].x, &temp[i].y); //scanning in struct x/y coords
        temp[i].distance = sqrt(pow(globalX - temp[i].x, 2) + pow(globalY - temp[i].y, 2)); //calculates the distance of the point from "your" location to the patient
    }

    
    

    //returns Array
    return temp;
}

int compareTo(node *ptrPt1, node *ptrPt2){ 
    
    if(ptrPt1->distance < ptrPt2->distance){
        return -1; //return case when pointer 2 is further than pointer 1
    } else if(ptrPt1->distance > ptrPt2->distance){
        return 1; //return case when pointer 1 is further than pointer 2
    } else {

        if(ptrPt1->x < ptrPt2->x){
            return -1; //return case when pointer 2's x val is higher than pointer 1
        } else if(ptrPt1->x > ptrPt2->x){
            return 1; //return case when pointer 1's x val is higher than pointer 2
        } else if(ptrPt1->x == ptrPt2->x){//when pointer 1 and 2 have same x val

            if(ptrPt1->y < ptrPt2->y){
                return -1; //return case when pointer 2's y val is higher than pointer 1
            } else if(ptrPt1->y > ptrPt2->y){
                return 1; //return case when pointer 1's y val is higher than pointer 2
            } else {
                return 0; //return case if both pointers are identical
            }
        }
    }
}

void insertionSort(node A[], int n){ //insertion sort algo
    for(int i=1; i<n;i++){
        node item = A[i];

        int j;
        for(j=i-1; j>=0; j--){
            //compares to find a value smaller than the next in line
            if(compareTo(&A[j], &item) > 0){
                A[j+1] = A[j];
            } else {
                break;
            }
        }
        A[j+1] = item;
    }

}

void mergeSort(node A[], int l, int r, int threshold){

    if(l < r){

        int m = (l+r)/2;
        
        if(r <= threshold){ //if under threshold insertion
            insertionSort(A, r);
        } else {
            //until under threshold, mergeSort
            mergeSort(A, l, m, threshold);
            mergeSort(A, m+1, r, threshold);
        }
        merge(A, l, m, r); //merge the insertion sort arrays
    }

}

void merge(node A[], int l, int m, int r){ //merge sort algo
    int i,j,k;
    int n1 = m-l+1;
    int n2 = r-m;

    //mem alloc
    node *L = (node *)malloc(sizeof(node) * n1);
    node *R = (node *)malloc(sizeof(node) * n2);

    //increments the left pointer towards the middle of the array
    for(i=0; i < n1; i++){
        L[i] = A[l+i];
    }
    //increments right pointer towards the middle of the array
    for(j=0; j<n2; j++){
        R[j] = A[m+1+j];
    }

    i=0; j=0; k=l;

    while(i<n1 && j <n2){
        //compares to see if Left and Right pointers have crossed each other
        if(compareTo(&L[i], &R[j]) < 0){
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    //copies extra values from Left pointer to array
    while(i<n1){
        A[k] = L[i];
        i++;
        k++;
    }

    //copies extra values from Right pointer to array
    while(j < n2){
        A[k] = R[j];
        j++;
        k++;
    }
    
    //free mem
    free(L);
    free(R);
}

//binary search algo
int binarySearch(node A[], int l, int r, node x){
    int m;
    if(l <= r){
        m = (l+r)/2;
        if(compareTo(&x, &A[m]) < 0){
            return binarySearch(A, l, m-1, x); //looks at bottom half of array
        } else if(compareTo(&x, &A[m]) > 0){
            return binarySearch(A, m+1, r, x); //looks at top half of array
        } else {
            return m+1; //value found and returns place in line
        }
    }
    return -1; //value not found
}
