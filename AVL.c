
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int MAX(int x,int y)
{if(x>y)
 return x;
 else
 return y;
}

struct node
 {long int key;
  int height;
  struct node *l,*r;
 };

typedef struct node *node_ptr;

struct AVL
    {
      node_ptr root;
    };

node_ptr create_avl(long int k)
{node_ptr temp;
temp=(node_ptr)malloc(sizeof(struct node));
temp->key=k;
temp->l=temp->r=NULL;
temp->height=0;
return temp;
}

int height(node_ptr T)
{
    if (T == NULL)
        return -1;
    return T->height;
}

int getbalance(node_ptr A,long int k)     //k is bs.
{
if(A==NULL)
 return 0;     
                                 
return (height(A->l)-height(A->r));
}

long int MAX_TREE(node_ptr T,long int max)
{if(T!=NULL)
 {max=MAX_TREE(T->l,max);
  if(T->key>max)
   max=T->key;
  max=MAX_TREE(T->r,max);}

  return max;
}

long int MIN_TREE(node_ptr T,long int min)
{if(T!=NULL)
 {min=MIN_TREE(T->l,min);
  if(T->key<min)
   min=T->key;
  min=MIN_TREE(T->r,min);}

  return min;
}

int isAVL(node_ptr A)
{ int blnc=getbalance(A,0);
  
  if(A==NULL)
   return 1;
  
  if(blnc>1||blnc<-1)
   return 0;
 
  if((A->l!=NULL )&&( MAX_TREE(A->l,A->l->key) > A->key)) 
   return 0;
  if((A->r!=NULL )&&( MIN_TREE(A->r,A->r->key) < A->key)) 
   return 0;

  if(!isAVL(A->l)||!isAVL(A->r))
   return 0;

  return 1;  

}

node_ptr leftrotate(struct AVL *A,node_ptr n)     //A is bs.
{node_ptr p=n->r;
 n->r=p->l;
 p->l=n;



n->height=MAX(height(n->l),height(n->r))+1;
p->height=MAX(height(p->l),height(p->r))+1;

return p;
}

node_ptr rightrotate(struct AVL *A,node_ptr n)    //A is bs.
{node_ptr p=n->l;
 n->l=p->r;
 p->r=n;


n->height=MAX(height(n->l),height(n->r))+1;
p->height=MAX(height(p->l),height(p->r))+1;

return p;
}

node_ptr search(struct AVL A,long int k)
{node_ptr y;
 y=A.root;
while(y!=NULL&&y->key!=k)
 {if(y->key>k)
   y=y->l;
   else
   y=y->r;   
 }
 return y;
}

node_ptr insert(node_ptr A,long int k)
{
  if(A==NULL)
  return create_avl(k);

  if(k<A->key)
   A->l=insert(A->l,k);
  else if(k>A->key)
   A->r=insert(A->r,k);
  else
   return A;

 A->height=1+MAX(height(A->l),height(A->r));
 int blc=getbalance(A,k);

 if((blc>1) && (k<A->l->key))     //LLC
  return rightrotate(NULL,A);
 if((blc<-1) && (k>A->r->key))    //RRC
  return leftrotate(NULL,A);

 if((blc>1) && (k>A->l->key))     //LRC
  { A->l=leftrotate(NULL,A->l);
    return rightrotate(NULL,A);
  }  
 if((blc<-1) && (k<A->r->key))    //RLC
  { A->r= rightrotate(NULL,A->r);
    return leftrotate(NULL,A);
  }   

  return A;
}

node_ptr MIN_AVL(node_ptr x)
{while(x->l!=NULL)
{x=x->l;}
return x;
}

node_ptr delete(node_ptr A,long int k)
{
  if(A==NULL)
   return A;

  if(k<A->key)
   A->l=delete(A->l,k);
  else if(k>A->key)
   A->r=delete(A->r,k);
  else
  {
    if((A->l==NULL)||(A->r==NULL))
    {
       node_ptr temp=(A->l)?A->l:A->r;
       if(temp==NULL)                      //leaf node
        {temp=A;
         A=NULL;}
       else 
        *A=*temp;

       free(temp);
    }
    else
    {
      node_ptr temp=MIN_AVL(A->r);             //replaced with its successor
      A->key=temp->key;
      A->r=delete(A->r,temp->key);
    }
  } 

  if(A==NULL)          //if tree had only one node
   return A;

  A->height=1+MAX(height(A->l),
                  height(A->r));

  int blc=getbalance(A,0);   

  if ((blc>1) && (getbalance(A->l,0)>=0))    //LLC
   return rightrotate(NULL,A);

  if ((blc>1) && (getbalance(A->l,0)<0))     //LRC
  {
    A->l=leftrotate(NULL,A->l);
    return rightrotate(NULL,A);
  }   

  if ((blc<-1) && (getbalance(A->r,0)<=0))   //RRC
   return leftrotate(NULL,A); 

  if ((blc<-1) && (getbalance(A->r,0)>0))    //RLC
  {
    A->r=rightrotate(NULL,A->r);
    return leftrotate(NULL,A);
  }    

  return A;
}

void preorder(node_ptr T)
{if(T!=NULL)
 {printf("( ");
   printf("%ld ",T->key);
  preorder(T->l);
  preorder(T->r);
  printf(") ");}
else
   printf("( ) ");
}

void Print(struct AVL tree)
{
  preorder(tree.root);
  printf("\n");
}

void main()
{char a;
 long int val;
 node_ptr temp;
 struct AVL A;
 A.root=NULL;

 do
 {scanf("%c",&a);
  switch(a)
  {case 'i':scanf("%ld",&val);
            A.root=insert(A.root,val);
   break;
   case 'd':scanf("%ld",&val);
            temp=search(A,val);
            if(temp!=NULL)
             {A.root=delete(A.root,val);
              printf("%ld\n",val);}
            else
             printf("FALSE\n");  
   break;
   case 's':scanf("%ld",&val);
            temp=search(A,val);
            if(temp!=NULL)
             printf("TRUE\n");  
            else
             printf("FALSE\n");  
   break;
   case 'b':scanf("%ld",&val);
            temp=search(A,val);
            if(temp!=NULL)
             printf("%d\n",getbalance(temp,0));
            else
             printf("FALSE\n");
   break;
   case 'p':Print(A);
   break;
   case 'c':printf("%d\n",isAVL(A.root));
   break;}
 
 }while(a!='e');
 
}