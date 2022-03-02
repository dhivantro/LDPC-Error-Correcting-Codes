#include <stdio.h>

int main() {
  
   int H[3][7] = {
     {1,1,1,0,1,0,0},
     {1,0,1,1,0,1,0},
     {1,1,0,1,0,0,1}
};

int cword[] ={1, 1, 1, 1, 1, 1, 1};
int mult[7], synd[3];

int r=3, c=7, i, j, k, sum;

for (i=0; i<r; i++)
{
    for(j=0; j<c; j++)
    {
        mult[j] = H[i][j] * cword[j];
        //printf("\n%d", mult[j]);
    }
    printf("\n\n");
    sum=0;
    for(k=0; k<c; k++)
    {
        sum = sum + mult[k];
        //printf("\n%d",sum);
    }
    
    //printf("\n%d  %d",i, sum);
    synd[i] = sum;
    printf("\n%d",synd[i]);
}

}
