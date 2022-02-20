#include <stdio.h>
#include <math.h>



int i, j, k;

void get_parity(int input[], int z, int sizeMsg, int B_msg_col, int Brows, int codeword[]);

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
  int Brows=20, Bcols=20;

  int sizeC=Bcols*z;
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
  int B_msg_col = 10;
  int sizeMsg = z*B_msg_col;  //input size is z*num of message row in B
  printf("\nmessage size: %d\n",sizeMsg);
 
  int input [] = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1};  //z*3=9
  
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
  get_parity(input, z, sizeMsg, B_msg_col, Brows, codeword);
 

}//end codeword fx

void get_parity(int input[], int z, int sizeMsg, int B_msg_col, int Brows, int codeword[]){ //find p1, p2-p4
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
    
    for(m=0; m<B_msg_col; m++) //1st x col of H (msg part)
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
	  //At the end, will have parity array with z bits
	    for(r=0; r<z; r++)
	     {
	       parity[r] = parity[r] + prodIM[r];
	     }
	}//k
    }//m


    //Now, need to shift the parity[] to get p1[]

     //append p1 to codeword
    for(i=0; i<z; i++)
      {
	codeword[i+sizeMsg-1] = parity[i];
      }
    
    //-------P2 TO P4-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
      }

    //traverse by row and Hcolumn in codeword (all msg and one p)
    
    for (k=0; k<3; k++) //row H 1 to 3
      {
	for (m=0; m<B_msg_col+(k+1); m++) //H column from msg 0 to parity 1,2,3
	  {
	    for (i=0; i<z; i++) //I col
	      {
		for (j=0; j<z; j++) //I row
		  {
		    product[j] = codeword[j + m*z] * H[k][m][j][i];
		  }//j
		
		int sum=0;
		for(r=0; r<z; r++)
		  {
		    sum = sum + product[r]; //value of product of every I*m		 
		  }
	      
		prodIM[i] = sum;
		
	      }//i
	    
	     //Sum parities at every new row in 1st column (for IM)
	    for(r=0; r<z; r++)
	     {
	       parity[r] = parity[r] + prodIM[r];
	     }
	    
	  }//m

	//append parity array to codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    codeword[(sizeMsg-1) + (k+1)*w] = parity[w];
	  }

	//reset parity array before going to new row
	int y;
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	    }	
      }//k
      	  
    //-------P5 TO PN-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
      }

      for (k=4; k<Brows; k++)
	{
	  for (m=0; m<(B_msg_col+k); m++)
	    {
	      for (i=0; i<z; i++) //I col
		{
		  for (j=0; j<z; j++) //I row
		    {

		      product[j] = codeword[j + m*z] * H[k][m][j][i];
		      
		    }//j

		int sum=0;
		for(r=0; r<z; r++)
		  {
		    sum = sum + product[r]; //value of product of every I*m		 
		  }
	      
		prodIM[i] = sum;
		
		}//i

	       //Sum parities at every new row in 1st column (for IM)
	    for(r=0; r<z; r++)
	     {
	       parity[r] = parity[r] + prodIM[r];
	     }
	    
	    }//m

	  //append parity array to codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    codeword[(sizeMsg-1) + k*w] = parity[w];
	  }

	//reset parity array before going to new row
	int y;
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	    }
	  
	}//k
    
}//fx





