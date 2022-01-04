#include <stdio.h>
#include <math.h>



int i, j, k;
 
int main(){
  int N=7, K=4;

  int M[1][4]={1,0,0,1};
  // int G[K][N];
  int C[1][7];
  
 int H[3][7] = {
     {1,1,1,0,1,0,0},
     {1,0,1,1,0,1,0},
     {1,1,0,1,0,0,1}
};

 //for testing first, use manual G
 int G[4][7] = {
     {1,0,0,0,1,1,1},
     {0,1,0,0,1,0,1},
     {0,0,1,0,1,1,0},
     {0,0,0,1,0,1,1}
};

 // int size =  (sizeof(G));
 // printf("\nsize: %d\n",size);
 
int disp[2][4] = {
    {10, 11, 12, 13},
    {14, 15, 16, 17}
};
 
for(i=0; i<K; i++) {
      for(j=0;j<N;j++) {
         printf("%d ", G[i][j]);
         if(j==N-1){
            printf("\n");
         }
       }
   }


//
 //for(i=0; i<4; i++) //message bits
 //{
    for(j=0; j<N; j++) //column of G
      {
	for (k=0; k<K; k++) //row of G
	  {
	    int c=M[0][k]*G[k][j];
	    // pl=pl+c;
	    C[0][j] += c;
	    if(C[0][j]>1)
	      {C[0][j]=1;}  //making it binary
	    // printf("\n%d",c);
	  }
	//printf("\n%d",C[0][j]);
	// printf("\n\n\n");
      }
    


 printf("\nCode word:\n");
for(i=0; i<1; i++) {
      for(j=0;j<N;j++) {
         printf("%d ", C[i][j]);
         
         }
       }
 printf("\n\n");
 
}//main

/*
void codeword(){
  //B: base matrix
  //z: expansion factor
  //c: codeword
  //H: parity check matrix
  //m: message (input) signal
  
  //find p1, p2, p3, p4
  //Double diagonal encoding

  temp[z]; //temp with zeros of size 1:z
  (m,n)=size(B); //size of base matrix //adjust format

  //parity p1
  for(i=1; i<5; i++) //row 1 to 4 of H
    {
      for (j=1; j<n-m+1; j++) //message columns
	{
	  temp = mod(temp + H[i][j]); //need to check the H range index
	  //mod returns the remainder... need to change in c
	  temp = temp/H[i][j] ;
	}
    }

  if (B[2][n-m+1]==-1) //example index, need to check and adjust
    {
      p1 = B[3][n-m+1];   //need to check values
    }

  codeword[n-m-1]=temp; //need to check
  
  //parity p2 to p4
  for (i=1; i<4; i++) //only 3 steps
    {
      temp[1][z]; //making it equal to zeros later
      for (j=1; j<n-m+i+1; j++)
	{
	  temp = mod(temp + H[i][j]);
	}
      codeword[n-m+i-1]=temp;  //assign temp value to codeword with that index
    }

  //parity p5 to pn
  
}
*/

void codeword(){

  int i, j ,k;
  //B: base matrix
  //fac: expansion factor
  //codeword: codeword //output signal
  //H: parity check matrix
  //m: message (input) signal

  //N: length of output signal (codeword)
  //K: length of input signal
  //M: length of parity bits
 
  //Size of base matrix B
  int rows, cols;

  int codeword[1][cols*fac]; //initialise size of codeword array

  //Append message or input bits to codeword array
  for (k=0; k<K; k++) //row index of input
    {
      for(i=0; i<1; i++)  //row of codeword
	{
	  for (j=0; j<(K*fac); j++) //column of codeword
	    {
	      codeword[i][j] = input[k]; 
	    }
	}
    }
  
}//end fx

