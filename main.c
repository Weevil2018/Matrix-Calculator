#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef struct
{
    int el[10][10][2];
    int r;
    int c;
}ARRAY;
void input(ARRAY*);//To take input in the current matrix

void intro();//For Introduction

void print(ARRAY*);//For printing the matrix passed

void fraction(int*,int*);//for Reducing the fraction passed in its simplest form.

int lcf(int,int);//To calculate Highest(Largest) Common Factor of the two passed Integers .

int digitC(int);//To calculate the no. of digits of the passed Integer.

int max_length(ARRAY*);//To calculate the length of the element that occupies maximum space while printing.

int length(int[]);//to calculate the no. of characters in the given fraction including Numerator, Denominator and '/' symbol.

void fr_add(int*,int*,int*);//to add two fractions and store it in third argument.

int lcm(int,int);//To calculate Least Common Multiple of the two passed Integers .

void reduce(ARRAY*);//To reduce each element of the array passed to its simplest form using fraction function and handle the special cases of Numerator and Denominator.

void confirm(ARRAY*);//To get input in an Array using input() and re-confirm it if it is entered correctly (again and again).

void fr_mul(int*,int*,int*);//To multiply two fractions and store it in the third parameter.

void scalar_mul(int*,ARRAY*);//To multiply a Matrix by a scalar number.

int* det(int*,int);//A recursive function to return determinant of the passed matrix

void copy(int*,ARRAY*);//To copy a matrix from ARRAY structure to a simple integer pointer

int* adj(int *,int);//To calculate and return adjoint of a matrix.

void trans(ARRAY*);//To calculate transpose of the matrix passed in form of ARRAY

void multiply(ARRAY*,ARRAY*,ARRAY*);//To multiply two matrices in ARRAY

void add(ARRAY*,ARRAY*,ARRAY*,char);//To add or subtract two matrices in ARRAY

void ad_in(ARRAY*,ARRAY*,char);//This is the actual function that calculates adjoint or inverse using adj function.

//The functions below are the "functions" that the software provide.

void add_sub(char);

void sp();

void matrix_mul();

void transpose();

void determinant();

void adjoint_inverse(char);

void equation();

int main()
{
    int s;
    intro();
    do
    {
        printf("Select one of the following options:\n\n");
        printf("1.) Addition of two matrices.\n");
        printf("2.) Subtraction of two matrices.\n");
        printf("3.) Scalar product of a matrix with a number.\n");
        printf("4.) Multiplication of two matrices.\n");
        printf("5.) Transpose of a matrix.\n");
        printf("6.) Determinant of a square matrix.\n");
        printf("7.) Adjoint of a square matrix.\n");
        printf("8.) Inverse of a square matrix.\n");
        printf("9.) Matrix Equation.\n");
        printf("0.) Exit\n\n");
        scanf("%d",&s);
        if (s==0)
            break;
        else
            switch(s)
            {
                case 1:
                    add_sub('A');
                    break;
                case 2:
                    add_sub('S');
                    break;
                case 3:
                    sp();
                    break;
                case 4:
                    matrix_mul();
                    break;
                case 5:
                    transpose();
                    break;
                case 6:
                    determinant();
                    break;
                case 7:
                    adjoint_inverse('A');
                    break;
                case 8:
                    adjoint_inverse('I');
                    break;
                case 9:
                    equation();
                    break;
                default:
                    printf("\nWrong Input.\tEnter a number between (1 - 9)\n\n");
            }
        printf("\nPress any key to continue...\n\n");
        getch();
        getch();
    }while(s>0||s<10);
    printf("\nTHANKS FOR USING REAL MATRIX MANIPULATOR.\n\n");
    getch();
    getch();
    return 0;
}

void equation()
{
    int i,j,t,k;
    int coefficient[2],radix;
    ARRAY a,r,unitary,temp,mul;
    confirm(&a);
    r.r=a.r;
    r.c=a.c;
    unitary.r=a.r;
    unitary.c=a.c;
    for (i=0;i<unitary.r;i++)
        for (j=0;j<unitary.c;j++)
        {
            if (i==j)
                unitary.el[i][j][0]=1;
            else
                unitary.el[i][j][0]=0;
                unitary.el[i][j][1]=1;
                r.el[i][j][0]=0;
                r.el[i][j][1]=1;
        }
    printf("\nEnter the number of terms :\n");
    scanf("%d",&t);
    printf("\nEnter the power and coefficient of each term of equation one by one.\t\tFor unitary matrix , enter power = \"zero\"\n");
    for (k=1;k<=t;k++)
    {
        mul=a;
        printf("\nEnter power of the matrix :\n");
        scanf("%d",&radix);
        if (radix<0)
        {
            ad_in(&a,&temp,'I');
            mul=temp;
        }
        else
            temp=a;
        do{
            printf("\nEnter the coefficient :\nNumerator = ");
            scanf("%d",&coefficient[0]);
            printf("Denominator = ");
            scanf("%d",&coefficient[1]);
            if(coefficient[1]==0)
                printf("The denominator can't be zero.Try again");
        }while(coefficient[1]==0);
        if (radix==0)
            temp=unitary;
        else
        for (i=1;i<((radix<0)?(radix*=-1):radix);i++)
            multiply(&temp,&mul,&temp);
        scalar_mul(coefficient,&temp);
        add(&r,&temp,&r,'A');
    }
    printf("Solution is:\n");
    print(&r);
}

void adjoint_inverse(char ch)
{
    ARRAY a,b;
    do
    {
        printf("\nNote - Number of Rows and Columns of the matrix should be same. \n");
        confirm(&a);
        if (a.r!=a.c)
            printf("\nPlease enter a \"Square\" Matrix. Try again !!!\n\n");
    }while(a.r!=a.c);
    ad_in(&a,&b,ch);
    if (ch=='A')
        printf("\nAdjoint of the given matrix is :\n");
    else
        printf("\nInverse of the given matrix is:\n");
    print(&b);
}

void determinant()
{
    ARRAY a;
    int *ptr,*p;
    do
    {
        printf("\nNote - Number of Rows and Columns of the matrix should be same. \n");
        confirm(&a);
        if (a.r!=a.c)
            printf("\nPlease enter a \"SQUARE\" Matrix. Try again !!!\n\n");
    }while(a.r!=a.c);
    ptr=(int*)malloc(a.c*a.r*2*sizeof(int));
    copy(ptr,&a);
    p=det(ptr,a.r);
    if (p[1]<=1)
        printf("\nDeterminant = %d \n",p[0]);
    else
        printf("\nDeterminant = %d/%d \n",p[0],p[1]);
    free(ptr);
    if (a.r!=1)
    free(p);
}

void transpose()
{
    ARRAY a1;
    confirm(&a1);
    trans(&a1);
    print(&a1);
}

void matrix_mul()
{
    ARRAY a1,a2,r;
    do
        {
            printf("\nNote-Column of the first matrix should be equal to the row of the second matrix.\n");
            printf("\nEnter the details of FIRST Matrix:\n");
            confirm(&a1);
            printf("\n\nEnter the details of SECOND Matrix:\n");
            confirm(&a2);
            if (a1.c!=a2.r)
                printf("\nIncompatible Dimensions of the matrices.\t Please read the note below carefully.\n\n");
        }while(a1.c!=a2.r);
    r.r=a1.r;
    r.c=a2.c;
    multiply(&a1,&a2,&r);
    reduce(&r);
    printf("\nThe Product is:\n");
    print(&r);
}

void sp()
{
    int s[2];
    ARRAY a;
    confirm(&a);
    printf("\nEnter the SCALAR in fractional form :\n");
    printf("Numerator = ");
    scanf("%d",s);
    printf("Denominator = ");
    scanf("%d",s+1);
    scalar_mul(s,&a);
    printf("\nThe resultant matrix is :\n");
    print(&a);
}

void add_sub(char ch)
{
    ARRAY a1,a2,r;
        do
        {
            printf("\nNote-DIMENSIONS OF BOTH THE MATRICES SHOULD BE SAME.\n\n");
            printf("\nEnter the details of FIRST Matrix:\n");
            confirm(&a1);
            printf("\n\nEnter the details of SECOND Matrix:\n");
            confirm(&a2);
            if (a1.r!=a2.r||a1.c!=a2.c)
                printf("\nDimensions of both the matrix should be same.");
        }while(a1.r!=a2.r||a1.c!=a2.c);
    r.r=a1.r;
    r.c=a2.c;
    add(&a1,&a2,&r,ch);
    reduce(&r);
    if (ch=='A')
        printf("\nSUM is :\n");
    else
        printf("\nDIFFERENCE is :\n");
    print(&r);

}

void add(ARRAY* a1,ARRAY* a2,ARRAY* r,char ch)
{
    int i,j;
    for (i=0;i<a1->r;i++)
        for(j=0;j<a2->c;j++){
            if (ch=='S')
                a2->el[i][j][0]*=-1;
            fr_add(a1->el[i][j],a2->el[i][j],r->el[i][j]);
        }
}

void multiply(ARRAY* a1,ARRAY* a2,ARRAY* resultant)
{
    ARRAY r;
    r=*resultant;
    int i,j,k,s[2];
    for (i=0;i<r.r;i++)
        for (j=0;j<r.c;j++)
        {
            r.el[i][j][0]=0;
            r.el[i][j][1]=1;
            for (k=0;k<a1->c;k++)
            {
                fr_mul(a1->el[i][k],a2->el[k][j],s);
                fr_add(r.el[i][j],s,r.el[i][j]);
            }

        }
    *resultant=r;
}

void ad_in(ARRAY* a,ARRAY* b,char ch)
{
    int *ptr1,*ptr2,i,j;
    ptr1=(int*)malloc(a->r*a->c*2*sizeof(int));
    copy(ptr1,a);
    ptr2=ptr1;
    ptr2=adj(ptr2,a->r);
    b->r=a->r;
    b->c=a->c;
    for (i=0;i<a->r;i++)
        for (j=0;j<a->c;j++)
            {
                b->el[i][j][0]=*(ptr2+i*b->r*2+j*2);
                b->el[i][j][1]=*(ptr2+i*b->r*2+j*2+1);
            }
    trans(b);
    if (ch!='A')
    {
        int *s;
        s=det(ptr1,a->r);
        if (s[0]==0)
            printf("The matrix is NOT Invertible. It is a singular matrix.\n");
        else
        {
            s[0]+=s[1];
            s[1]=s[0]-s[1];
            s[0]-=s[1];
            scalar_mul(s,b);
        }
        free(s);
    }
    free(ptr1);
    free(ptr2);
}
int* adj(int* p,int size)
{
    int *r,h,i,j,k,*ptr,x,y,*temp;
    r=(int*)malloc(size*size*2*sizeof(int));
    for (h=0;h<size;h++)
    for (i=0;i<size;i++)
    {
        ptr=(int*)malloc((size-1)*(size-1)*2*sizeof(int));
        x=0,y=0;
        for (j=0;j<size;j++)
        {
            for (k=0;k<size;k++)
                if (j!=h&&k!=i)
                {
                    *(ptr+x*(size-1)*2+y*2)=*(p+j*size*2+k*2);
                    *(ptr+x*(size-1)*2+y*2+1)=*(p+j*size*2+k*2+1);

                    if(y<size-2)
                        y++;
                    else
                    {
                        y=0;
                        x++;
                    }
                }
        }
        temp=det(ptr,size-1);
        *(r+h*size*2+i*2)=temp[0]*(((h+i)%2==0)?1:-1);
        *(r+h*size*2+i*2+1)=temp[1];
        free(ptr);
    }
    return r;
}

int* det(int* m,int size)
{
    int h,i,j,k,l,*ptr,temp[2],*s;
    if (size==1)
        return m;
    else
    {
        s=(int*)malloc(2*sizeof(int));
        s[0]=0;
        s[1]=1;
        ptr=(int*)malloc((size-1)*(size-1)*2*sizeof(int));
        for (h=0;h<size;h++)
        {
            k=0,l=0;
            for (i=1;i<size;i++)
                for (j=0;j<size;j++)
                {
                    if (j!=h)
                    {
                        *(ptr+k*(size-1)*2+l*2)=*(m+i*size*2+j*2);
                        *(ptr+k*(size-1)*2+l*2+1)=*(m+i*size*2+j*2+1);
                        if (l==size-2)
                        {
                            k++;
                            l=0;
                        }
                        else
                            l++;
                    }
                }
             fr_mul((m+h*2),det(ptr,(size-1)),temp);
             temp[0]*=(h%2==0)?1:-1;
             fr_add(temp,s,s);
        }
    free(ptr);
    if(s[0]==0)
        s[1]=1;
    return s;
    }
}

void trans(ARRAY* a1)
{
    int i,j,k;
    for (i=0;i<a1->r;i++)
        for (j=i;j<((a1->c>a1->r)?a1->c:a1->r);j++)
            if (i!=j)
            {
                for (k=0;k<2;k++)
                {
                    a1->el[i][j][k]=a1->el[i][j][k]+a1->el[j][i][k];
                    a1->el[j][i][k]=a1->el[i][j][k]-a1->el[j][i][k];
                    a1->el[i][j][k]=a1->el[i][j][k]-a1->el[j][i][k];
                }

            }
    a1->r+=a1->c;
    a1->c=a1->r-a1->c;
    a1->r-=a1->c;
}

void scalar_mul(int* s,ARRAY* a)
{
    int i,j;
    for (i=0;i<a->r;i++)
        for (j=0;j<a->c;j++)
            fr_mul(a->el[i][j],s,a->el[i][j]);
    reduce(a);
}

void copy(int* ptr,ARRAY* a)
{
    int i,j,x=0;
    for(i=0;i<a->r;i++)
        for(j=0;j<a->c;j++)
        {
            *(ptr+x++)=a->el[i][j][0];
            *(ptr+x++)=a->el[i][j][1];
        }
}

void confirm(ARRAY* c)
{
    int i;
    do
    {
        input(c);
        printf("\nThe Matrix you entered is :\n\n");
        print(c);
        printf("Enter 1 to continue or any other INTEGER to re-enter the matrix.\t");
        scanf("%d",&i);
    }while(i!=1);
}

int digitC(int x)
{
    int i=0;
    if (x<0)
        x*=-1;
    if(x==0)
        return 1;
    else
    {
        for (;x>0;x/=10,i++);
        return i;
    }
}

void fraction(int* num,int* den)
{
    if (*num!=0){
    int hcf=lcf(*num,*den);
    *num=*num/hcf;
    *den=*den/hcf;
    }
}

int lcf(int a,int b)
{
    if (a<0)
        a*=-1;
    int i=(a<b)?a:b;
    for (;i>0;i--)
        if (a%i==0&&b%i==0)
            break;
    return i;
}
int max_length(ARRAY* ml)
{
    int i,j,t,max=0;
    for (i=0;i<ml->r;i++)
         for(j=0;j<ml->c;j++)
        {
            t=length(ml->el[i][j]);
            if (max<t)
                max=t;
        }
    return max;
}

int length(int a[])
{
    int l;
    l=digitC(a[0])+digitC(a[1]);
    return ++l;
}

void fr_add(int* a1,int* a2,int* r)
{
    int lc=lcm(a1[1],a2[1]),t;
    t=a1[0]*(lc/a1[1])+a2[0]*(lc/a2[1]);
    r[0]=t;
    r[1]=lc;
    fraction(r,r+1);
}

void fr_mul(int* p1,int* p2,int* p3)
{
    p3[0]=p1[0]*p2[0];
    p3[1]=p1[1]*p2[1];
}

int lcm(int x,int y)
{
    int i=(x>y)?x:y,a=1,j=(x<y)?x:y;
    for (;;a++)
        if ((i*a)%j==0)
            return i*a;
}

void reduce(ARRAY* a)
{
    int k,j;
    for (k=0;k<a->r;k++)
        for (j=0;j<a->c;j++)
        {
            if (a->el[k][j][1]<0)
            {
                a->el[k][j][0]*=-1;
                a->el[k][j][1]*=-1;
            }

            if (a->el[k][j][0]==0)
                a->el[k][j][1]=1;
            fraction(&a->el[k][j][0],&a->el[k][j][1]);
        }
}

void print(ARRAY* out)
{
    int i,j,k,space;
    reduce(out);
    space=max_length(out)+3;
    printf("\n\n");
    for (i=0;i<out->r;i++)
    {
        for (j=0;j<out->c;j++)
        {
            if (out->el[i][j][0]<0)
                printf("%d",out->el[i][j][0]);
            else
                printf(" %d",out->el[i][j][0]);
            k=length(out->el[i][j]);
            if(out->el[i][j][1]<=1)
                k-=2;
            else
                printf("/%d",out->el[i][j][1]);
            for (;k<=space;k++)
                printf(" ");
        }
        for (j=1;j<=2;j++)
            printf("\n");
    }
}

void input(ARRAY *p){
    int i,j,k;
    do
    {
        printf("\nEnter the number of rows and columns of the matrix : (Maximum -> 10)\nRows = ");
        scanf("%d",&p->r);
        printf("Columns = ");
        scanf("%d",&p->c);
        if (p->r<=0||p->r>10||p->c<=0||p->c>10)
            printf("\nInvalid input !!!  Try again\n\n");
    }while(p->r<=0||p->r>10||p->c<=0||p->c>10);
    do
    {
        printf("\nSelect 1 if the Matrix contains fractional values else select 0.\n");
        scanf("%d",&i);
        if (i!=1&&i!=0)
            printf("\nWrong Input.\tSelect 1 or 0.\tTry Again.\n\n");
    }while(i!=1&&i!=0);
    printf("\nEnter the elements of the matrix:\n\n");
        for (k=0;k<p->r;k++)
            for (j=0;j<p->c;j++)
            {
                p->el[k][j][1]=1;
                printf("Enter the element of row %d column %d :\n",k+1,j+1);
                if (i==0)
                    scanf("%d",&p->el[k][j][0]);
                else
                {
                    do
                    {
                        printf("Numerator = ");
                        scanf("%d",&p->el[k][j][0]);
                        printf("Denominator = ");
                        scanf("%d",&p->el[k][j][1]);
                        if (p->el[k][j][1]==0)
                            printf("Denominator can't be 0.\tEnter again\n\n");
                    }while(p->el[k][j][1]==0);
                }
            }
    reduce(p);

}

void intro()
{
     printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
     printf("||                                                                                                            ||\n");
     printf("||                                _                    _               _                    _                 ||\n");
     printf("||       ||''''.                 | |\\\\              //| |             | |\\\\              //| |                ||\n");
     printf("||       ||     '                | | \\\\            // | |             | | \\\\            // | |                ||\n");
     printf("||       ||      '               | |  \\\\          //  | |             | |  \\\\          //  | |                ||\n");
     printf("||       ||      |               | |   \\\\        //   | |             | |   \\\\        //   | |                ||\n");
     printf("||       ||     /                | |    \\\\      //    | |             | |    \\\\      //    | |                ||\n");
     printf("||       ||    /                 | |     \\\\    //     | |             | |     \\\\    //     | |                ||\n");
     printf("||       ||---'                  | |      \\\\__//      | |             | |      \\\\__//      | |                ||\n");
     printf("||       ||\\\\                    | |       '--'       | |             | |       '--'       | |                ||\n");
     printf("||       || \\\\                   | |                  | |             | |                  | |                ||\n");
     printf("||       ||  \\\\                  | |                  | |             | |                  | |                ||\n");
     printf("||       ||   \\\\       __        | |                  | |     __      | |                  | |                ||\n");
     printf("||       ||    \\\\     |__|       | |                  | |    |__|     | |                  | |                ||\n");
     printf("||                                                                                                            ||\n");
     printf("||                                                                                                            ||\n");
     printf("||       Real                    Matrix                               Manipulator                             ||\n");
     printf("||                                                                                                            ||\n");
     printf("||                                                                                                            ||\n");
     printf("||                                                                          -Developed by                     ||\n");
     printf("||                                                                           ABHINAV PARAG MISHRA (WEEVIL)    ||\n");
     printf("  ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''  \n\n");
     printf("Press any key to continue...");
     getch();
     printf("\n\n\n\n\n\n\n");
}
