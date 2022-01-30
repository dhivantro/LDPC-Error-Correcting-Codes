#include <stdio.h>
#include <math.h>



int i, j, k;

/*
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
        // printf("%d ", G[i][j]);
         if(j==N-1){
	   //   printf("\n");
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
    


    // printf("\nCode word:\n");
for(i=0; i<1; i++) {
      for(j=0;j<N;j++) {
        // printf("%d ", C[i][j]);
         
         }
       }
 printf("\n\n");


 int arr[3]={0};
 for(i=0; i<3; i++){
   //  printf(" %d ",arr[i]);}
 } 
}//main
*/
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


int main(){
  
  int i, j ,k, z=5;
  //B: base matrix
  //z: expansion factor
  //codeword: codeword //output signal
  //H: parity check matrix
  //m: message (input) signal

  //N: length of output signal (codeword)
  //K: length of input signal
  //M: length of parity bits
 
  //Size of base matrix B
  int rows, cols=10;

  int sizeC=cols*z;
  printf("\ncodeword size: %d\n",sizeC);
  int codeword[]={0}; //initialise size of codeword array

  int H[3][7] = {
     {1,1,1,0,1,0,0},
     {1,0,1,1,0,1,0},
     {1,1,0,1,0,0,1}
};

  //test
  int sizeMsg=z*3;  //input size is z*num of message row in B
 
  int input [] = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1};  //z*3=9
  
    printf("\ninput:\n");
for(i=0; i<sizeMsg; i++)
  {
      printf("%d ", input[i]); 
    
  }
 
  //Append message or input bits to codeword array
  for (k=0; k<sizeMsg; k++) //row index of input
    {
      if (k>sizeMsg && k<=sizeC)
	{codeword[k] = 0;}
      
      else
	{ codeword[k] = input[k];}
      
    }

  
   printf("\n\nCodeword with message appended:\n");
   for(i=0; i<sizeC; i++) {
        printf("%d ", codeword[i]);   
       }
 
 
   // get_parity();
 
}//end codeword fx

void get_parity(){ //find p1, p2-p4
  //need H array, msg array, z(expansion factor)
  int m, k, i ,j, z=5;

  //for(input=0; input<len(input)/z; input++) //1st round m1, 2nd round m2
  for(m=0; m<4; m++) //1st 4 col of H
    {
      for(k=0; k<4; k++) //1st 4 rows of H
	{
	  for(i=0; i<z; i++) //First I row... got z bits
	    {
	      for(j=0; j<z; j++) //First I column... got z bits
		{
		  // H[k][m][i][j];
		  // input[m]; //index 0-4 (m+0z)=(m+input*z) , index 5-9 (m+5)=(m+z), index 10-14 (m+10)=(m+2z)=(m+
		}
	    }	  
	}
    }
}





