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

void syndrome(int codeword[]){

  //This section calculates syndrome
  //If 0, valid

  int column_H = column_B * expFactor;
  int row_H = row_B * expFactor;

  int multiply[column_H], sum_temp[]={};
  int synd[row_H];
  int sum ;

  for (i=0; i<row_H; i++)
    {
      for (j=0; j<column_H; j++)
	{
	  multiply[j] = H_2D[i][j] * codeword[j];
	 	  
	  //printf("\ni: %d ",i);
	}
      //printf("\n\n");
      sum = 0;

      for (k=0; k<column_H; k++)
	{
	  sum = sum + multiply[k]; //Updating
	}

      synd[i] = sum%2;   //perform modulo 2
      //printf("\n%d",synd[i]%2); 
      if (synd[i] != 0)
	{
	  printf("\n\n Invalid Codeword \n\n");
	}
      else
	{
	  printf("\n\n Valid Codeword \n\n");
	}
    
    }

}

void print_codeword(int codeword[]){

  int i;
  
  printf("\n\n--------------------codeword:-------------\n\n");
  for(i=0; i<sizeC; i++)
    {
      printf("%d ", codeword[i]);   
    }

  printf("\n\n-------------Codeword is printed---------------\n\n");
}

void append_p1(int codeword[]){
  //append p1 to codeword
  for(i=0; i<expFactor; i++)
    {
      codeword[i+sizeMsg] = parity[i];
      //codeword_temp[i+sizeMsg] = parity[i];
      //printf("\n%d    %d",parity[i], codeword[i+sizeMsg]);
      //printf("\n%d",parity[i]);
 
    }
  //print_codeword();
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

void shifting_p1(int n, int z, int codeword[]){

  rotating_p1(0, z-1);
  rotating_p1(0, n-1);
  rotating_p1(n, z-1);

  append_p1(codeword);
}


void get_parity(int msgs[], int codeword[]){

  int m, k, i, j, r, b, q, z=expFactor, sum, bb;
  int product[]={}, prodIM[row_B*z], multiply[z], temp[z], sum_temp[z], input[sizeMsg];

  

  for (i=0; i<sizeMsg; i++)
    {
      input[i] = msgs[i];
      //printf(" %d",i);
    }
  
  //-------------------P1------------------//
  
  //reset parity array
  for(i=0; i<z; i++)
   {
     parity[i]=0;  //temp
     sum_temp[i] = 0;
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
		  //printf("%d ",m);
		  //for (int t=0; t<z; t++)
		  // {
		      temp[j] = input[j + m*z];
		      
		      //printf("\n %d",  j + m*z);
		      //}
		  //product[j] = input[j + m*z] * H[k][m][i][j];
		  // product[j] = input[j] * H[k][m][i][j];
		   //printf(" %d ", input[j]);
		    multiply[j] = (temp[j] * H[k][m][i][j] );
	     
		    //printf(" %d", H[k][m][i][j]);
		   //printf("\n");		  		  
		}//j

	      //printf("\n\n");
	       int sum=0;
	       for(r=0; r<z; r++)
	      	{
	        sum = sum + multiply[r]; //value of product of every I*m
	        		
		//prodIM[r] = temp2;
		//printf("%d ",sum);
	      	}
	       
	       //printf("\n %d ",sum);
	       //prodIM[i + k*z] = sum;
	       prodIM[i] = sum;
	       sum_temp[i] = sum_temp[i] + prodIM[i];
		for (b=0; b<z; b++)
		  {
		    //sum_temp[b] = sum_temp[b] + prodIM[b];
		    //printf("\n %d",sum_temp[b]);
		  }
		
	        //will have z size array containing IM elements
	     	//printf("\n %d ",prodIM[i]);
		//printf("\n %d ",sum_temp[i]);
	      
	    }//i
	  
	   //Sum parities at every new row in 1st column (for IM)
	  //At the end, will have parity array with z bits
	  //  for(r=0; r<z; r++)
	  // {
	  //  parity[r] = parity[r] + prodIM[r];
	       //printf("\npar: %d ",parity[r]);
	  //printf("\n");
	  // }
	    
	}//k
    }//m

   for(int r=0; r<z; r++)
	{
	       //parity[r] = parity[r] + prodIM[r];
	  //parity[r] = parity[r]%2;
	   parity[r] = sum_temp[r]%2;
	   //printf("\n %d  ", parity[r]);
	   //codeword[r+sizeMsg] = parity[i];
	     }
  
   //print_codeword();

   //printf("\n");

  //---------------Reshifting for P1--------------//
  //Now, need to shift the parity[] to get p1[]
  //Getting value of p1 position in B
    int n;
    
    if (B[1][column_msg_B] == -1)
      { n = B[2][column_msg_B]; }
    else
      { n = B[1][column_msg_B]; }
    //printf("\n%d",z-n-1);
    shifting_p1( n, z, codeword); //shift by n to the right to get original parity bit

    //print_codeword();

    
    
    //-------P2 TO P4-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
	sum_temp[i] = 0;
      }

      int  cword_temp[(column_B - column_msg_B - 1)*z];
      
      //m<column_msg_B+(q+1)
    //traverse by row and Hcolumn in codeword (all msg and one p)
      for(q=0; q<3; q++)
	{
      for (m=0; m<column_msg_B+(q+1); m++ ) //row H 1 to 3
      {
	//printf("\nm: %d \n",m);
	for (k=0; k<(1+q); k++) //H column from msg 0 to parity 1,2,3
	  {
	    //printf("\nk: %d ",k);
	    
	    for (i=0; i<z; i++) //I col
	      {
		for (j=0; j<z; j++) //I row
		  {

		    temp[j] = codeword[j + m*z];
		    //printf("\nm:%d k:%d i:%d   %d ",m,k,i,j+m*z);
		    //product[j] = codeword[j + m*z] * H[k][m][j][i];
		     multiply[j] = (temp[j] * H[k][m][i][j] );
		     //printf("%d ",  H[k][m][i][j]);
		     //printf("\nm: %d  k: %d i: %d  j: %d",m,k,i,j);
		  }//j

		//printf("\n");
		int sum=0;
		for(r=0; r<z; r++)
		  {
		    sum = sum + multiply[r]; //value of product of every I*m		 
		  }
		//printf(" \n %d ",sum);
	      
		prodIM[i] = sum;
	        sum_temp[i] = sum_temp[i] + prodIM[i];
		//printf(" \n %d  %d",m,sum_temp[i]);	           
		
	      }//i
	    
	     //Sum parities at every new row in 1st column (for IM)
	   
	    //printf("\n m %d \n",m+1);
	    	 for(r=0; r<z; r++)
	     {
	       //parity[r] = parity[r] + prodIM[r];
	       //printf("\nm: %d k: %d  %d ",m,k,sum_temp[r]);
	     }
		 //printf("\n");
	  }//k

	//append parity array to temp codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    parity[w] = sum_temp[w];
	    //cword_temp[(sizeMsg+z) + w + q*z] = parity[w];
	    cword_temp[w+q*z] = parity[w];
	    //codeword[sizeMsg + q + q*z] = parity[w];
	    //printf("\nm: %d   %d ",m,w+q*z);
	    //printf("\nk:%d %d",k, cword_temp[(sizeMsg+z) + w + q*z] );	    	    
	  }

	//reset parity array before going to new row
	int y;
	  for(y=0; y<z; y++)
	    {
	      //parity[y]=0;
	      //prodIM[y]=0;
	      //sum_temp[y]=0;
	    }
	  //q++;
	  //printf("\n");
	  //int w;

      }//m

      // int w; //append
      //	for(w=0; w<z; w++)
      // {
	    
	    //codeword_temp[(sizeMsg-1) + (k+1)*w] = (sum_temp[w]);
	    //printf("\nm: %d   %d ",m,sum_temp[w]);	    
      //  }
	
      	int y; //reset
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	      sum_temp[y]=0;
	    }

	}//q

      for(bb=0; bb<(3*z); bb++)
	  {	    
	    codeword[(sizeMsg+z) + bb] = cword_temp[bb]%2; //perform modulo 2
	    //codeword_temp[(sizeMsg+z) + bb] = cword_temp[bb]%2;
	    //printf("\n %d ",codeword[(sizeMsg+z) + bb]);
	    
	  }
      //print_codeword();
      
    
    //-------P5 TO PN-------//

    //reset parity array
      for(i=0; i<z; i++)
      {
	parity[i]=0;
      }

      int cword_temp2[(column_B - column_msg_B - 4)*z]; //fix stash smashing
           
      //m<column_msg_B+(q+1)
    //traverse by row and Hcolumn in codeword (all msg and one p)
      for(q=0; q<(column_B - column_msg_B - 4); q++)  //< must be from p5 till pn length, this is K-4
	{
	  for (m=0; m<column_msg_B+(q+4); m++ ) //row H 1 to 3  //column_msg_B+(q+1)
      {
	//printf("\nm: %d\n ",m);
	for (k=4+q; k<(5+q); k++) //H column from msg 0 to parity 1,2,3, 4+q so that it starts from the next k row directly
	  {
	    //printf("\nk: %d ",k);
	    
	    for (i=0; i<z; i++) //I col
	      {
		for (j=0; j<z; j++) //I row
		  {

		    temp[j] = codeword[j + m*z];
		    
		    //product[j] = codeword[j + m*z] * H[k][m][j][i];
		     multiply[j] = (temp[j] * H[k][m][i][j] );
		     //printf("%d ", j + m*z);
		     //printf("\nk: %d  m: %d",k,m);
		  }//j

		//printf("\n");
		int sum=0;
		for(r=0; r<z; r++)
		  {
		    sum = sum + multiply[r]; //value of product of every I*m		 
		  }
		//printf(" \n %d ",sum);
	      
		prodIM[i] = sum;
	        sum_temp[i] = sum_temp[i] + prodIM[i];
		//printf(" \nm:%d  %d",m,sum_temp[i]);	           
		
	      }//i
	    
	     //Sum parities at every new row in 1st column (for IM)
	   
	    //printf("\n m %d \n",m+1);
	    	 for(r=0; r<z; r++)
	     {
	       //parity[r] = parity[r] + prodIM[r];
	       //printf("\nm: %d k: %d  %d ",m,k,sum_temp[r]);
	     }
		 //printf("\n");
	  }//k

	//append parity array to temp codeword
	int w;
	for(w=0; w<z; w++)
	  {
	    parity[w] = sum_temp[w];
	    //cword_temp[(sizeMsg+z) + w + q*z] = parity[w];
	    cword_temp2[w+q*z] = parity[w];
	    //printf("\nm: %d   %d ",m,w+q*z);
	    //printf("\nk:%d %d",k, cword_temp2[w + q*z] );	    	    
	  }

	//reset parity array before going to new row
	int y;
	  for(y=0; y<z; y++)
	    {
	      //parity[y]=0;
	      //prodIM[y]=0;
	      //sum_temp[y]=0;
	    }
	  //q++;
	  //printf("\n");
	  //int w;

      }//m

	  //int w; //append
	  //for(w=0; w<z; w++)
	  //{
	    
	    //codeword[(sizeMsg-1) + (k+1)*w] = (sum_temp[w]);
	    //printf("\nm: %d   %d ",m,sum_temp[w]);	    
	  // }
	
      	int y; //reset
	  for(y=0; y<z; y++)
	    {
	      parity[y]=0;
	      prodIM[y]=0;
	      sum_temp[y]=0;
	    }

	}//q

      //append
      for(bb=0; bb< (column_B - column_msg_B - 4) * z; bb++)
	  {	    
	    codeword[(sizeMsg+4*z) + bb] = cword_temp2[bb]%2; //perform modulo 2
	    //codeword_temp[(sizeMsg+4*z) + bb] = cword_temp2[bb]%2; //perform modulo 2
	    //printf("\n %d ",(sizeMsg+4*z) + bb);	    
	  }


      for (i=0; i<sizeC; i++) 
	{
	  //codeword[i] = codeword_temp[i];
	}
      
    
}//get_parity fx


void initialise_codeword(int input[], int codeword[]){

  int i, j, k;
  

  for(i=0; i<sizeC; i++)
    {
      codeword[i] = 0;
    }

   int sizeMsg = expFactor*column_msg_B;


    //Append message or input bits to codeword array
  for (k=0; k<sizeMsg; k++) //row index of input
    {
      if (k>sizeMsg && k<=sizeC)
	{
	  codeword[k] = 0;
	  //codeword_temp[k] = 0;
	}
      
      else
	{
	  codeword[k] = input[k];
	  //codeword_temp[k] = input[k];
	}  
    }

  // get_parity(input);
  
}

void convert(){

  int k, m, i ,j;

   //printf("\n\n-----------------------------------------\n\n");
   //printf("            Converting 4D H to 2D H            ");
   //printf("\n\n-----------------------------------------\n\n");
   
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
   //printf("\n\n");

  for (i=0; i<(row_B*expFactor); i++)
    {
      for (j=0; j<(column_B*expFactor); j++)
	{
	  //printf("%d",H_2D[i][j]);
	}
      //printf("\n");
    }

  //printf("\n\n\n Finish converting to 2D H  \n\n\n");

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
   int input [] = {1,	1,	0,	1,	1,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1};

   /*
  int input [] = {1,	1,	0,	1,	1,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	1,	1,	1,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1};
   */
  
  /*
    int input[] = {0,	0,	0,	1,	0,	1,	1,	1,	0,	0,	0,	1,	0,	1,	1,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	0,	1,	1,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	0,	1,	1,	0,	1,	1,	1,	1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0};
    */

  int codeword[sizeC];
   
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
   initialise_codeword(input, codeword);
   //print_codeword(codeword);
   //get_parity();
   get_parity(input, codeword);
    convert(); //Convert 4D H to 2D h
    //print_codeword();
    syndrome(codeword); //To check for valid codeword

   
 }
