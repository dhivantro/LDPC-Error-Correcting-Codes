#include <stdio.h>
#include <stdint.h> //for uint8_t

#define row_B 46
#define column_B 68
#define expFactor 5
#define column_msg_B 22
#define sizeC (column_B*expFactor)

 int B[row_B][column_B];
 int H[row_B][column_B][expFactor][expFactor];
 int H_2D [row_B*expFactor] [column_B*expFactor];
 int codeword[sizeC];
//int codeword[sizeC];
 int parity[expFactor];

int sizeMsg = expFactor*column_msg_B; //Get from make file ->N
//int sizeMsg = column_B - row_B;


 //variables in for loop
 int i=0;
 int j=0;
 int k=0;
 int m=0;
 int pK=0;
 int pM=0;

void print_codeword(){

  int i;
  
  printf("\n\n--------------------codeword:-------------\n\n");
  for(i=0; i<sizeC; i++)
    {
      printf("%d ", codeword[i]%2);   
    }

  printf("\n\n-------------Codeword is printed---------------\n\n");
}

void append_p1(){
  //append p1 to codeword
  for(i=0; i<expFactor; i++)
    {
      codeword[i+sizeMsg-1] = (parity[i]%2);
      //printf("\n%d    %d",parity[i]%2, codeword[i+sizeMsg-1]);
      printf("\n%d",parity[i]%2);
 
    }
}

void rotating_p1(int start, int end){

  while (start < end)
    {
      int temp = parity[start];
      parity[start] = parity[end];
      parity[end] = temp;
      start++;
      end--;
    }
}

void shifting_p1(int n, int z){

  rotating_p1(0, z-1);
  rotating_p1(0, n-1);
  rotating_p1(n, z-1);

  append_p1();
}


void get_parity(){

  int m, k, i, j, r, z=expFactor;
  int product[]={}, prodIM[]={};

  
  int input [] = {1,	1,	0,	1,	1,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1};
  
  
  //-------------------P1------------------//
  
  //reset parity array
  for(i=0; i<z; i++)
   {
     parity[i]=0;  //temp
   }

  //Finding p1
  for(m=0; m<column_msg_B; m++) //1st x col of H (msg part)
    {
      for(k=0; k<4; k++) //1st 4 rows of B
	{
	  //printf("\nH Col %d ",m);
	  // printf("\nH Row %d ",k);
	  for(i=0; i<z; i++) //First I col... got z bits
	    {
	      //printf("\nI col %d:  ",i);
	      
	      for(j=0; j<z; j++) //First I row... got z bits
		{
	 	        
		  //product[j] = input[j + m*z] * H[k][m][i][j];
		  product[j] = input[j] * H[k][m][i][j];
		   //printf(" %d ", input[j]);
		  printf("%d ", input[j]);
		  //printf("\n");
		  		  
		}//j

	      printf("\n\n");
	      int sum=0;
	      for(r=0; r<z; r++)
		{
		  sum = sum + product[r]; //value of product of every I*m
		  //printf("%d ",sum);
		}

	      prodIM[i] = sum; //will have z size array containing IM elements
	     		   
	      
	    }//i
	  
	   //Sum parities at every new row in 1st column (for IM)
	  //At the end, will have parity array with z bits
	    for(r=0; r<z; r++)
	     {
	       parity[r] = parity[r] + prodIM[r];
	       //printf("\npar: %d ",parity[r]);
	       
	     }
	    
	}//k
    }//m

   for(int r=0; r<z; r++)
	{
	       //parity[r] = parity[r] + prodIM[r];
	  //parity[r] = parity[r]%2;
	       printf("\npar: %d ",parity[r]);
	       
	     }

  //---------------Reshifting for P1--------------//
  //Now, need to shift the parity[] to get p1[]
  //Getting value of p1 position in B
    int n;
    
    if (B[1][column_msg_B] == -1)
      { n = B[2][column_msg_B]; }
    else
      { n = B[1][column_msg_B]; }
    //printf("\n%d",z-n-1);
    shifting_p1( (z-n-1), z ); //(z-1) so that it shifts to the left


    //-------P2 TO P4-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
      }

    //traverse by row and Hcolumn in codeword (all msg and one p)
    
    for (k=0; k<3; k++) //row H 1 to 3
      {
	for (m=0; m<column_msg_B+(k+1); m++) //H column from msg 0 to parity 1,2,3
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
	    codeword[(sizeMsg-1) + (k+1)*w] = (parity[w]%2);
	    //printf("%d ",parity[w]%2);
	    
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

      for (k=4; k<row_B; k++)
	{
	  for (m=0; m<(column_msg_B+k); m++)
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
	       //printf("\n %d",parity[r]%2);
	       //parity[r] = parity[r];
	     }
	    
	    }//m

	  //append parity array to codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    codeword[(sizeMsg-1) + k*w] = (parity[w]%2);
	    // printf("%d ",parity[w]%2);
	  }

	//reset parity array before going to new row
	int y;
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	    }
	  
	}//k
      
}//get_parity fx


void initialise_codeword(){

  int i, j, k;

  for(i=0; i<sizeC; i++)
    {
      codeword[i] = 0;
    }

   int sizeMsg = expFactor*column_msg_B;

   int input [] = {1,	1,	0,	1,	1,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1};


    //Append message or input bits to codeword array
  for (k=0; k<sizeMsg; k++) //row index of input
    {
      if (k>sizeMsg && k<=sizeC)
	{codeword[k] = 0;}
      
      else
	{ codeword[k] = input[k];}  
    }

  // get_parity(input);
  
}

void convert(){

  int k, m, i ,j;

   printf("\n\n-----------------------------------------\n\n");
   printf("Converting 4D H to 2D H");
   printf("\n\n-----------------------------------------\n\n");
   
   for (k=0; k<row_B; k++)  //row B
    {
      for (i=0; i<expFactor; i++)
	{
	  for (m=0; m<column_B; m++) //column B
	    {
	      for (j=0; j<expFactor; j++)
		{
		  H_2D[((expFactor-1)*k)+k+i][((expFactor-1)*m)+m+j] = H[k][m][i][j];
		  //printf("\n k:%d m:%d i:%d j:%d index:[%d][%d]   H_old: %d Hnew: %d",k,m,i,j, ((5-1)*k)+k+i, ((5-1)*m)+m+j,  H[k][m][i][j], Hnew[(3*k)+i][(3*m)+j]);
		}
	    }
	}
    }
  printf("\n\n");

  for (i=0; i<(row_B*expFactor); i++)
    {
      for (j=0; j<(column_B*expFactor); j++)
	{
	  printf("%d",H_2D[i][j]);
	}
      printf("\n");
    }

  printf("\n\n\n Finish converting to 2D H  \n\n\n");

}


 void zeros_matrix()
 {
   for (i=0;i<expFactor;i++)
     {
       for (j=0;j<expFactor;j++)
 	{
 	  if (i==j)
 	    {
 	      H[k][m][i][j]=1;
 	    }
 	  else
 	    {
 	      H[k][m][i][j]=0;
 	    }
 	  //printf("H[%d][%d][%d][%d]: %d\n",k, m, i, j, H[k][m][i][j]);
 	}
     }
 }

void positive_matrix()
 {
   for (i=0;i<expFactor;i++)
     {
       for (j=0;j<expFactor;j++)
 	{
 	  if (i==j)
 	    {
 	      H[k][m][i][j]=1;
 	    }
 	  else
 	    {
 	      H[k][m][i][j]=0;
 	    }
 	  //printf("H[%d][%d][%d][%d]: %d\n",k,m,i,j, H[k][m][i][j]);
 	}

     }
   int n,N, temp;
   N=B[k][m];
   for (n=0;n<N;n++)
    {
        for (i=0;i<expFactor;i++)
        {
            temp=H[pK][pM][i][expFactor-1];
            for (j=expFactor-1;j>0;j--)
            {
                H[k][m][i][j]= H[k][m][i][j-1];
            }
            H[k][m][i][0]= temp;
        }
    }
}


 void negative_matrix()
 {
   for (i=0;i<expFactor;i++)
     {
       for (j=0;j<expFactor;j++)
 	{
 	  H[k][m][i][j]=0;
 	  //To check result of negative numbers
 	  //printf("H[%d][%d][%d][%d]: %d\n",k,m,i,j, H[k][m][i][j]);
 	}
     }
 }
//Print out the final H
 void print_All()
 {
   for (k=0;k<row_B;k++)
     {
     for (j=0;j<expFactor;j++)
       {
 	for (m=0;m<column_B;m++)
 	  {
 	    for (i=0;i<expFactor;i++)
 	      {
 		printf("%d", H[k][m][j][i]);
 	      }
 	  }
 	printf("\n");
       }
   }
 }



 int main()
 {
   
    //Import base matrix from txt file
    FILE* f;
    f=fopen("NR_1_2_5.txt", "r");
    if (!feof(f))
    {
        for (k=0;k<row_B;k++)
        {
            for (j=0;j<column_B;j++)
            {
                fscanf(f, "%d",&B[k][j]);
                //printf("B[%d][%d]: %d\n", k, j, B[k][j]);
            }
        }
    }
    fclose(f);
    //Check whether the elements is positive, negative or zero
   for (k=0;k<row_B;k++)
     {
       for (m=0;m<column_B;m++)
        {
 	  if (B[k][m]==0)
 	    {
            zeros_matrix();
 	    }
 	  else if (B[k][m]<0)
 	    {
            negative_matrix();
 	    }
 	  else if (B[k][m]>0)
        {
            //printf("B[%d][%d]=%d is positive\n", k, m, B[k][m]);
            pK=k;
            pM=m;
            positive_matrix();
            //printf("K: %d, M=%d\n", pK, pM);
 	    }
 	}
     }
   //print_All();   
   initialise_codeword();
   get_parity();
   // convert(); //Convert 4D H to 2D h
   //print_codeword();

   
 }
