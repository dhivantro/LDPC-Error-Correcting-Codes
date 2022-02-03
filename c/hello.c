#include <stdio.h>
#include <math.h>



int i, j, k;

void get_parity(int input[], int z, int sizeMsg, int B_msg_col);

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
  int codeword[sizeC]; //initialise size of codeword array

  for(i=0; i<sizeC; i++)
    {
      codeword[i] = 0;
    }

  int H[3][7] = {
     {1,1,1,0,1,0,0},
     {1,0,1,1,0,1,0},
     {1,1,0,1,0,0,1}
};

  //test
  int B_msg_col = 3;
  int sizeMsg = z*B_msg_col;  //input size is z*num of message row in B
 
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
 
  int p1[z], p2[z];
   get_parity(input, z, sizeMsg, B_msg_col);
  //append p1 to codeword
    for(i=0; i<z; i++)
      {
	codeword[i+sizeMsg-1] = p1[i];
      }

  
  
 
}//end codeword fx

void get_parity(int input[], int z, int sizeMsg, int B_msg_col){ //find p1, p2-p4
  //need H array, msg array, z(expansion factor)
  int m, k, i ,j, r;
  int  parity[]={}, product[]={}, prodIM[]={};

  // int input [] = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1};  //z*3=9

  /*
  //Debug: testing is input array is passing to function
    printf("\ninput:\n");
for(i=0; i<sizeMsg; i++)
  {
      printf("%d ", input[i]); 
    
  }
  */
 
    printf("\n\nget parity\n\n");

    for(i=0; i<z; i++)
      {
	parity[i]=0;
      }
    
    for(m=0; m<B_msg_col; m++) //1st 4 col of H
    {
      for(k=0; k<4; k++) //1st 4 rows of H
	{
	  printf("\nH Col %d ",m);
	  printf("\nH Row %d ",k);
	  for(i=0; i<z; i++) //First I col... got z bits
	    {
	      printf("\nI col %d:  ",i);
	      
	      for(j=0; j<z; j++) //First I row... got z bits
		{
		  
		  // H[k][m][i][j];
		  // input[m]; //index 0-4 (m+0z)=(m+input*z) , index 5-9 (m+5)=(m+z), index 10-14 (m+10)=(m+2z)=(m+
		  
		   product[j] = input[j + m*z] * H[k][m][j][i];
		  //insert parity in empty array, at the end, sum all elements together(binary sum)
		  //p1[j + m*z] = parity[j + m*z];
	      		   		   
		   // int index = j + m*z;
		   //printf("%d ",index);
		  
		}//j

	      int sum=0;
	      for(r=0; r<z; r++)
		{
		  sum = sum + product[r]; //value of product of every I*m		 
		}
	      
	      prodIM[i] = sum; //will have z size array containing IM elements
	     		   
	      // printf("\n");
	      
	    }//i
	  
	   //Sum parities at every new row in 1st column (for IM)
	    for(r=0; r<z; r++)
	     {
	       parity[r] = parity[r] + prodIM[r];
	     }
	}//k
    }//m


    //Now, need to shift the parity[] to get p1[]

       
 
    
}//fx





