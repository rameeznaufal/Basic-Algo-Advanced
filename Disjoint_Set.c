#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    int rank;
    struct node *p;
};

struct DisjSet{
    int n;
    struct node **A;
    int access;
};


struct DisjSet create_DisjSet(int s)           //capacity is 10,000
{
   struct DisjSet F;
   F.n = s;
   F.access=0;
   F.A = (struct node**)calloc(10000,sizeof(struct node*)); 
   for(int i=0;i<10000;++i)
   {F.A[i]=NULL;}

   return F;
}

struct node* findset_PathC(struct DisjSet *F,int x)
{struct node *temp;
 temp=F->A[x];
 F->access++;
   if(temp==NULL)
    return temp;
   else if(temp->p==temp) 
    return temp;
   else
    temp->p = findset_PathC(F,temp->p->key); 
 
 return temp->p;
}

struct node* findset(struct DisjSet *F,int x)
{struct node *temp;
 temp=F->A[x];
 F->access++;
    while(temp && temp->p!=temp)
     {temp=temp->p;
       F->access++;}

 return temp;   
}

int makeset(struct DisjSet *F,int x)
{
 if(F->A[x]==NULL)
  {F->A[x]=(struct node*)malloc(sizeof(struct node));
   F->A[x]->p = F->A[x];
   F->A[x]->key = x;
   F->A[x]->rank = 0;}
 else
  return -1;
 F->n++;
 return x; 
}

void link(struct node* a,struct node* b)
{
 b->p=a; 
}

int link_Rnk_H(struct node* a,struct node* b)
{if(a->rank > b->rank)
   {b->p=a;
    return a->key;}
 else if (a->rank < b->rank)
   {a->p=b;
    return b->key;}
 else
  {
     b->p=a;
     a->rank++; 
     return a->key;
  }  
    
}

int Union_A(struct DisjSet *F,int x,int y)
{
 struct node *a,*b;
 a = findset(F,x);
 b = findset(F,y);
 if(a==NULL || b==NULL)
  return -1;
 
 link(a,b);

 return(a->key);
}

int Union_B(struct DisjSet *F,int x,int y)
{
 struct node *a,*b;
 a = findset(F,x);
 b = findset(F,y);
 if(a==NULL || b==NULL)
  return -1;
 int rep;
 rep=link_Rnk_H(a,b);

 return(rep);
}

int Union_C(struct DisjSet *F,int x,int y)
{
 struct node *a,*b;
 a = findset_PathC(F,x);
 b = findset_PathC(F,y);
 if(a==NULL || b==NULL)
  return -1;
 
 link(a,b);

 return(a->key);
}

int Union_D(struct DisjSet *F,int x,int y)
{
 struct node *a,*b;
 a = findset_PathC(F,x);
 b = findset_PathC(F,y);
 if(a==NULL || b==NULL)
  return -1;

 int rep;
 rep=link_Rnk_H(a,b);
 return(rep);
}

void main()
{struct DisjSet A = create_DisjSet(0);
 struct DisjSet B = create_DisjSet(0);
 struct DisjSet C = create_DisjSet(0);
 struct DisjSet D = create_DisjSet(0);
 
 
 char c;
 struct node *temp;
 int x,y;

 do{scanf("%c",&c);
switch (c)
{
 case 'm':scanf("%d",&x);
          printf("%d \n",makeset(&A,x));
          makeset(&B,x);
          makeset(&C,x);
          makeset(&D,x);

 break;
 case 'f':scanf("%d",&x);
          printf("%d ",((temp=findset(&A,x))!=NULL)?temp->key:-1 );
          printf("%d ",((temp=findset(&B,x))!=NULL)?temp->key:-1 );
          printf("%d ",((temp=findset_PathC(&C,x))!=NULL)?temp->key:-1 );
          printf("%d\n",((temp=findset_PathC(&D,x))!=NULL)?temp->key:-1 );
 break;
 case 'u':scanf("%d %d",&x,&y);
          printf("%d ",Union_A(&A,x,y));
          printf("%d ",Union_B(&B,x,y));
          printf("%d ",Union_C(&C,x,y));
          printf("%d\n",Union_D(&D,x,y));
 break;
 case 's':printf("%d %d %d %d\n",A.access,B.access,C.access,D.access);
 break;
}
   }while(c!='s');

}

