#include<stdio.h>
#include<stdlib.h>

char CR;
int c1,c2;

struct HashT
 {long int *items;
  int m;
 };

typedef struct HashT HashTable;

int hash_a(long int k,int i,int m)
{
    return(((k%m)+c1*i+c2*i*i)%m);
}

int hash_b(long int k,int i,int m)
{int R=m-1,j;
 while(1)
 {
     for(j=2;j<R;++j)
      {if(R%j==0)
       break;}
if(R==j)
 break;
 R--;
 }

    return(((k%m)+i*(R-(k%R)))%m);
}

HashTable hashtable(int size)
{
    HashTable table;
    table.m = size;
    table.items = (long*)calloc(table.m, sizeof(long int));
    return table;
}

void insert(struct HashT *T,long int k)
{int i=0,j;
 if(CR=='a')
 {do
  {j=hash_a(k,i,T->m);
   if(T->items[j]==0)
    {T->items[j]=k;
    return;}
   else
    i++;
  }while(i<T->m); 
 }
 if(CR=='b')
 {do
  {j=hash_b(k,i,T->m);
   if(T->items[j]==0)
    {T->items[j]=k;
    return;}
   else
    i++;
  }while(i<T->m);
 } 
 return;
}

int search(HashTable T,long int k)
{int i=0,j;
 if(CR=='a')
 {do
   {j=hash_a(k,i,T.m);
    if(T.items[j]==k)
     return 1;
    i++;
    }while(i<T.m);
 } 
 if(CR=='b')
 {do
   {j=hash_b(k,i,T.m);
    if(T.items[j]==k)
     return 1;
    i++;
    }while(i<T.m);
 } 
 return -1;  
}

void print(HashTable T)
{int i=0;
    while(i<T.m)
    {
        if(T.items[i]==0)
         printf("%d ()\n",i);
        else
         printf("%d (%ld)\n",i,T.items[i]);

         i++;
    }
}

void delete(HashTable *T,long int k)
{int i=0,j;
 if(CR=='a')
 {do
   {j=hash_a(k,i,T->m);
    if(T->items[j]==k)
     {T->items[j]=0;
     return;}
    i++;
    }while(i<T->m);
 } 
 if(CR=='b')
 {do
   {j=hash_b(k,i,T->m);
    if(T->items[j]==k)
     {T->items[j]=0;
     return;}
    i++;
    }while(i<T->m);
 } 
 return;
}

void main()
{char c;
 HashTable T;
 int m;
 long int k;
  
  scanf("%c",&CR);
  scanf("%d",&m);
  T=hashtable(m);
  if(CR=='a')
   scanf("%d %d",&c1,&c2);
  do
  {scanf("%c",&c);
   switch(c)
   {case 'i':scanf("%ld",&k);
             insert(&T,k);
    break;
    case 's':scanf("%ld",&k);
             printf("%d\n",search(T,k));
    break;
    case 'd':scanf("%ld",&k);
             delete(&T,k);
    break;
    case 'p':print(T);
    break;}
  }while(c!='t');    
}
