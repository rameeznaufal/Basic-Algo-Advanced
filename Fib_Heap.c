#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ERR -10101101

struct node
{
  long int key;
  int degree;
  struct node *l_sib,*r_sib,*p,*child;
  int mark;              //bool values
  int visited;           //bool values
};

typedef struct node *NODE;

NODE create_node(long int val)
{
  NODE n;
  n = (NODE)malloc(sizeof(struct node));
  n->key = val;
  n->degree = 0;
  n->mark = 0;
  n->p = NULL;
  n->child = NULL;
  n->visited = 0;
  n->l_sib = n;
  n->r_sib = n;
  return n;
}

struct fibonacci_heap
{
  int n;
  NODE min;
};

typedef struct fibonacci_heap *FIB_HEAP;

FIB_HEAP MakeHeap()
{
  FIB_HEAP H;
  H = (FIB_HEAP)malloc(sizeof(struct fibonacci_heap));
  H->n = 0;
  H->min = NULL;
  return H;
}

void Heap_Link(FIB_HEAP H, NODE y, NODE x)
{
  y->r_sib->l_sib = y->l_sib;
  y->l_sib->r_sib = y->r_sib;

  if (x->r_sib == x)
    H->min = x;

  y->l_sib = y;
  y->r_sib = y;
  y->p = x;

  if (x->child == NULL)
  {
    x->child = y;
  }
  y->r_sib = x->child;
  y->l_sib = x->child->l_sib;
  x->child->l_sib->r_sib = y;
  x->child->l_sib = y;
  if ((y->key) < (x->child->key))
    x->child = y;

  (x->degree)++;
}

void Insert(FIB_HEAP H,long int val)
{ NODE new;
  new = create_node(val);
  if (H->min == NULL)
  {
    H->min = new;
  }
  else
  {
    H->min->l_sib->r_sib = new;
    new->r_sib = H->min;
    new->l_sib = H->min->l_sib;
    H->min->l_sib = new;
    if (new->key < H->min->key)
    {
      H->min = new;
    }
  }
  (H->n)++;
}

NODE Minimum(FIB_HEAP H)
{
  if (H == NULL)
  {
    return NULL;
  }
  else
    return H->min;
}

int cal_degree(int n)
{
  int count = 0;
  while (n > 0)
  {
    n = n / 2;
    count++;
  }
  return count;
}

void consolidate(FIB_HEAP H)
{
  int degree, i, d;
  degree = cal_degree(H->n);
  NODE A[degree], x, y;
  for (i = 0; i <= degree; i++)
  {
    A[i] = NULL;
  }
  x = H->min;
  do
  {
    d = x->degree;
    while (A[d] != NULL)
    {
      y = A[d];
      if (x->key > y->key)
      {
        NODE exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min)
        H->min = x;
      Heap_Link(H, y, x);
      if (y->r_sib == x)
        H->min = x;
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->r_sib;
  } while (x != H->min);

  H->min = NULL;
  for (i = 0; i < degree; i++)
  {
    if (A[i] != NULL)
    {
      A[i]->l_sib = A[i];
      A[i]->r_sib = A[i];
      if (H->min == NULL)
      {
        H->min = A[i];
      }
      else
      {
        H->min->l_sib->r_sib = A[i];
        A[i]->r_sib = H->min;
        A[i]->l_sib = H->min->l_sib;
        H->min->l_sib = A[i];
        if (A[i]->key < H->min->key)
        {
          H->min = A[i];
        }
      }
      if (H->min == NULL)
      {
        H->min = A[i];
      }
      else if (A[i]->key < H->min->key)
      {
        H->min = A[i];
      }
    }
  }
}

NODE extract_min(FIB_HEAP H)
{

  if (H->min == NULL)
    return NULL;
  else
  {
    NODE temp = H->min;
    NODE pntr;
    pntr = temp;
    NODE x = NULL;
    if (temp->child != NULL)
    {

      x = temp->child;
      do
      {
        pntr = x->r_sib;
        (H->min->l_sib)->r_sib = x;
        x->r_sib = H->min;
        x->l_sib = H->min->l_sib;
        H->min->l_sib = x;
        if (x->key < H->min->key)
          H->min = x;
        x->p = NULL;
        x = pntr;
      } while (pntr != temp->child);
    }

    (temp->l_sib)->r_sib = temp->r_sib;
    (temp->r_sib)->l_sib = temp->l_sib;
    H->min = temp->r_sib;

    if (temp == temp->r_sib && temp->child == NULL)
      H->min = NULL;
    else
    {
      H->min = temp->r_sib;
      consolidate(H);
    }
    H->n = H->n - 1;
    return temp;
  }
}

void cut(FIB_HEAP H, NODE n, NODE parent_node)
{
  if (n == n->r_sib)
    parent_node->child = NULL;

  n->l_sib->r_sib = n->r_sib;
  n->r_sib->l_sib = n->l_sib;
  if (n == parent_node->child)
    parent_node->child = n->r_sib;
  (parent_node->degree)--;

  n->l_sib = n;
  n->r_sib = n;
  H->min->l_sib->r_sib = n;
  n->r_sib = H->min;
  n->l_sib = H->min->l_sib;
  H->min->l_sib = n;

  n->p = NULL;
  n->mark = 0;
}

void cascading_cut(FIB_HEAP H, NODE parent_node)
{
  NODE aux;
  aux = parent_node->p;
  if (aux != NULL)
  {
    if (parent_node->mark == 0)
    {
      parent_node->mark = 1;
    }
    else
    {
      cut(H, parent_node, aux);
      cascading_cut(H, aux);
    }
  }
}

long int decrease_key(FIB_HEAP H, NODE n, long int new_key)
{
  NODE parent_node;
  if (H == NULL)
  {
    return ERR;
  }
  if (n == NULL)
  {
    return ERR;
  }
  else
  {
    if (n->key < new_key)
    {
      return ERR;
    }
    else
    {
       n->key = new_key;
      
      parent_node = n->p;
      if ((parent_node != NULL) && (n->key < parent_node->key))
      {
        cut(H, n, parent_node);
        cascading_cut(H, parent_node);
      }
      if (n->key < H->min->key)
      {
        H->min = n;
      }
    }
  }
  return n->key;
}

int find_node(FIB_HEAP H, NODE n, long int key, long int new_key)
{  
  if(n == NULL)
   return 0;
  int Found=0;
  NODE find_use = n;
  NODE f = NULL;
  find_use->visited = 1;

  if (find_use->key == key)
  {
    find_use->visited = 0;
    f = find_use;
    if(decrease_key(H, f, new_key)!=ERR)
     Found=1;
    return Found; 
  }
  if (find_use->child != NULL)
  {
    Found+=find_node(H, find_use->child, key, new_key);
  }
  if ((find_use->r_sib->visited != 1))
  {
    Found+=find_node(H, find_use->r_sib, key, new_key);
  }

  find_use->visited = 0;
  return Found;
}

long int Delete(FIB_HEAP H, long int dec_key)
{
  NODE p = NULL;
  if(find_node(H, H->min, dec_key, INT_MIN)==0)
   return ERR;
  p = extract_min(H);
  if (p != NULL)
    return dec_key;
  else
    return ERR;
}


struct node_Q{
                  NODE data;
                  struct node_Q *next;
                  };

typedef struct node_Q *ptr_node_Q;

struct queue {
                    ptr_node_Q head,tail;
                    };     


int qe(struct queue l)
{if(l.head==NULL)
 return 1;
 else 
 return 0;
}

ptr_node_Q create(NODE k)
{  ptr_node_Q temp;
   temp=(ptr_node_Q)malloc(sizeof(struct node_Q));
   if(temp==NULL)
    {exit(0);} 
   temp->data=k;
   temp->next=NULL;
   return temp;
}                              

void enqueue(struct queue *l,NODE x)
{ptr_node_Q temp;
 temp=create(x);
 if(l->head==NULL)
   {l->head=temp;
    l->tail=temp;}
 else
 {l->tail->next=temp;
  l->tail=temp;}
}

NODE dequeue(struct queue *l)
{NODE y;
 ptr_node_Q p;
 if(l->head!=NULL)
 {y=l->head->data;
  p=l->head;
  l->head=l->head->next;
  free(p);
  return(y);}
  else
   return NULL;}

void levelorder(NODE p)
{struct queue Q;
Q.head=Q.tail=NULL;
NODE temp;
temp=p;

do
{printf("%ld ",temp->key);
 if(temp->child!=NULL)
  {enqueue(&Q,temp->child);}  
 if(temp->r_sib==p)
  {temp=dequeue(&Q);
   p=temp;}
 else
  temp=temp->r_sib;
}while(temp);

}

void PRINT_L_E(NODE H) 
{ NODE p;

 p = H;
 while(p)
  {printf("%ld ",p->key);  
   if(p->child!=NULL)
    levelorder(p->child);
   p = p->r_sib;
   if(p==H)
    break;    }
    
 printf("\n");
}

void PRINT(NODE H)
{ NODE p;

 p = H;
 while(p)
  {printf("%ld ",p->key);  
   p = p->r_sib;
   if(p==H)
    break;    }
    
 printf("\n");

}

void main()
{
  FIB_HEAP H = MakeHeap();
  NODE temp;
  long int x,y;
  char c;
  do{scanf("%c",&c);
      switch(c)
      {
          case 'i':scanf("%ld",&x);
                   Insert(H,x);
          break;
          case 'm':printf("%ld\n",(Minimum(H)!=NULL)? Minimum(H)->key : -1);
          break;
          case 'x':printf("%ld\n",((temp=extract_min(H))!=NULL)? temp->key : -1);
          break;
          case 'r':scanf("%ld %ld",&x,&y);
                   printf("%ld\n",(find_node(H,H->min,x,y)!=0)? y : -1);
          break;
          case 'd':scanf("%ld",&x);
                   printf("%ld\n",(Delete(H,x)!=ERR)? x : -1);
          break;
          case 'p':PRINT(H->min);
          break;
      }
     }while(c!='e');
 
}