 #include <stdio.h>
 #define row_B 46
#define column_B 68
#define expFactor 5

 int B[row_B][column_B];
 int H[row_B][column_B][expFactor][expFactor];

 //variables in for loop
 int i=0;
 int j=0;
 int k=0;
 int m=0;
 int pK=0;
 int pM=0;

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
   //write H into text file
   FILE * file;
   file = fopen ("H_pchk.txt", "w+");
   int row_H=row_B*expFactor;
   int column_H=column_B*expFactor;
   for (k=0;k<row_B;k++)
     {
     for (j=0;j<expFactor;j++)
       {
           for (m=0;m<column_B;m++)
            {
                for (i=0;i<expFactor;i++)
                {
                    fprintf(file, "%d ", H[k][m][j][i]);
                }
            }
            fprintf(file, "\n");
       }
   }
   fclose(file);
   printf("done");
 }
