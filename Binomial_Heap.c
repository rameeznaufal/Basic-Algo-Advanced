#include<stdio.h>
#include<stdlib.h>



//***************************************BINOMIAL HEAP

struct node 
  {int n;
   int degree;
   struct node *p,*c,*sib;
  };

typedef struct node *node_ptr;

//************************************QUEUE
struct node_q{
                  node_ptr data;
                  struct node_q *next;
                  };

typedef struct node_q *nde;

struct queue {
                    nde head,tail;
                    };     


int qe(struct queue l)
{if(l.head==NULL)
 return 0;
 else 
 return 1;
}

nde create(node_ptr k)
{  nde temp;
   temp=(nde)malloc(sizeof(struct node_q));
   if(temp==NULL)
    {exit(0);} 
   temp->data=k;
   temp->next=NULL;
   return temp;
}                              

void enqueue(struct queue *l,struct node_q x)
{nde temp;
 temp=create(x.data);
 if(l->head==NULL)
   {l->head=temp;
    l->tail=temp;}
 else
 {l->tail->next=temp;
  l->tail=temp;}
}

node_ptr dequeue(struct queue *l)
{node_ptr y;
 nde p;
 if(l->head!=NULL)
 {y=l->head->data;
  p=l->head;
  l->head=l->head->next;
  free(p);
  return(y);}
  else
   return NULL;}


//***************************************BINOMIAL HEAP
//node_ptr H = NULL;
//node_ptr Hr = NULL;

void LINK(node_ptr y, node_ptr z) 
{y->p = z;
 y->sib = z->c;
 z->c = y;
 z->degree = z->degree + 1;
}

node_ptr CREATE_NODE(int k) 
{ 
 node_ptr p;//new node;
 p = (node_ptr) malloc(sizeof(struct node));
 p->n = k;
 p->p = NULL;
 p->c = NULL;
 p->sib = NULL;
 p->degree = 0;
 return p;
} 

node_ptr MERGE(node_ptr H1, node_ptr H2) 
{ node_ptr H = NULL;
 node_ptr y;
 node_ptr z;
 node_ptr a;
 node_ptr b;
 y = H1;
 z = H2;
 if (y != NULL) 
 {
     if (z != NULL && y->degree <= z->degree)
         H = y;
     else if (z != NULL && y->degree > z->degree)
         H = z;
     else
         H = y;
 } 
 else
     H = z;
 while (y != NULL && z != NULL) 
 {
     if (y->degree < z->degree) {
         y = y->sib;
     } 
     else if (y->degree == z->degree) {
         a = y->sib;
         y->sib = z;
         y = a;
     } 
     else {
         b = z->sib;
         z->sib = y;
         z = b;
     }
 }
 return H;
}

node_ptr UNION(node_ptr H1, node_ptr H2) 
{ node_ptr prev_x;
 node_ptr next_x;
 node_ptr x;
 node_ptr H = NULL;
 H = MERGE(H1, H2);
 if (H == NULL)
     return H;
 prev_x = NULL;
 x = H;
 next_x = x->sib;
 while (next_x != NULL) 
 {
     if ((x->degree != next_x->degree) || ((next_x->sib != NULL)&& (next_x->sib)->degree == x->degree)) 
     {
         prev_x = x;
         x = next_x;
     } 
     else 
     {
           if (x->n <= next_x->n) 
           {
             x->sib = next_x->sib;
             LINK(next_x, x);
           }
           else 
           {
             if (prev_x == NULL)
                 H = next_x;
             else
                 prev_x->sib = next_x;
             LINK(x, next_x);
             x = next_x;
           }
     }
     next_x = x->sib;
 }
 return H;
}

node_ptr INSERT(node_ptr H, node_ptr x) 
{ node_ptr H1 = NULL;
 H1 = x;
 H = UNION(H, H1);
 return H;
}

void levelorder(node_ptr p)
{struct queue Q;
Q.head=Q.tail=NULL;
struct node_q q_temp;
node_ptr temp;
temp=p;
while(temp!=NULL)
{printf("%d ",temp->n);
 if(temp->c!=NULL)
  {q_temp.data=temp->c;
   enqueue(&Q,q_temp);}  
 if(temp->sib==NULL)
  temp=dequeue(&Q);
 else
  temp=temp->sib;
}

}

void PRINT(node_ptr H) 
{ node_ptr p;
 

 p = H;
 while(p!=NULL)
  {printf("%d ",p->n);  
   levelorder(p->c);
       p = p->sib;}
    
 printf("\n");
}

node_ptr REVERT_LIST(node_ptr y) 
 {node_ptr Hr=NULL;
  if (y->sib != NULL) {
        Hr=REVERT_LIST(y->sib);
        (y->sib)->sib = y;}
  else 
        Hr = y;

    return Hr;    
}

int MIN(node_ptr H1) 
{
  int min;
  node_ptr x = H1;
  node_ptr p; 
  if (x == NULL) 
  {
      return -1;
  }
  min=x->n;
  p = x;
  while (p->sib != NULL) {
      if ((p->sib)->n < min) {
          min = (p->sib)->n;
          x = p->sib;
      }
      p = p->sib;
  }
  return min;
}

node_ptr EXTRACT_MIN(node_ptr *H1) 
{
  int min;
  node_ptr t = NULL;
  node_ptr x = *H1;
  node_ptr p;
  node_ptr Hr = NULL;
  if (x == NULL) 
  {
      return x;
  }
  min=x->n;
  p = x;
  while (p->sib != NULL) {
      if ((p->sib)->n < min) {
          min = (p->sib)->n;
          t = p;
          x = p->sib;
      }
      p = p->sib;
  }
  if (t == NULL && x->sib == NULL)
      *H1 = NULL;
  else if (t == NULL)
      *H1 = x->sib;
  else if (t->sib == NULL)
      t = NULL;
  else
      t->sib = x->sib;
  if (x->c != NULL) {
      Hr=REVERT_LIST(x->c);
      (x->c)->sib = NULL;
  }
  *H1 = UNION(*H1, Hr);
  return x;
}

node_ptr FIND_NODE(node_ptr H, int k) 
{node_ptr x = H;
 node_ptr p = NULL;
 if (x==NULL)
  return p;

 if (x->n == k) {
     p = x;
     return p;
 }
 if (x->c != NULL && p == NULL) {
     p = FIND_NODE(x->c, k);
 }
 if (x->sib != NULL && p == NULL) {
     p = FIND_NODE(x->sib, k);
 }
 return p;

}

int DECREASE_KEY(node_ptr *H, int i, int k) 
{
 int temp;
 node_ptr p,y,z;

 p = FIND_NODE(*H, i);
 if (p == NULL) 
     return -1;

 if (k > p->n) 
 {
     return -1;
 }
if(k!=-1000)
  p->n = i-k;
else
  p->n=k;
 y = p;
 z = p->p;
 while ((z != NULL )&&( y->n < z->n)) 
 {
     temp = y->n;
     y->n = z->n;
     z->n = temp;
     y = z;
     z = z->p;
 }
 return i-k;
}
 
int DELETE(node_ptr *H, int k) 
{node_ptr np;
 if (H == NULL) 
    return -1;
 
int val=DECREASE_KEY(H, k, -1000);
if (val==-1)
 return -1;
 np = EXTRACT_MIN(H);
 if (np != NULL)
     return k;
return -1;
}

 

void main() 
{char o;
 node_ptr temp;
 int x,y;
 node_ptr H=NULL;

do{scanf("%c",&o);
    switch(o)
    {
    case 'i':scanf("%d",&x);
            temp=CREATE_NODE(x);
            H=INSERT(H,temp);
    break;
    case 'm':printf("%d\n",MIN(H));
    break;
    case 'x':temp=EXTRACT_MIN(&H);
             printf("%d\n",(temp!=NULL)?temp->n:-1);
    break;
    case 'r':scanf("%d %d",&x,&y);
             printf("%d\n",DECREASE_KEY(&H,x,y));
    break;
    case 'd':scanf("%d",&x);
             printf("%d\n",DELETE(&H,x));
    break;
    case 'p':PRINT(H);
    break;}
   }while(o!='e');

}