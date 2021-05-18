
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



struct node
 {long int key;
  int colour;
  struct node *l,*r;
 };

typedef struct node *node_ptr;

struct RBT
    {
      node_ptr root;
    };

node_ptr create_RBT(long int k)       // nil nodes are black
{node_ptr temp;
temp=(node_ptr)malloc(sizeof(struct node));
temp->key=k;
temp->l=temp->r=NULL;
temp->colour=1;                       // 1->RED  0->BLACK

return temp;
} 

node_ptr leftrotate(node_ptr n)     
{node_ptr p=n->r;
 n->r=p->l;
 p->l=n;

return p;
}

node_ptr rightrotate(node_ptr n)    
{node_ptr p=n->l;
 n->l=p->r;
 p->r=n;

return p;
}

node_ptr insert_RBT(node_ptr root,node_ptr ptr)
{
 if(root==NULL)
  return ptr;
 else if(ptr->key>root->key)
  {root->r=insert_RBT(root->r,ptr);
   
   if(root->r->colour==0)
    return root;
   else                                                                                       // parent is red
    {if( ((root->r->l!=NULL)&&(root->r->l->colour==1)) || ((root->r->r!=NULL)&&(root->r->r->colour==1)) )   
      {if((root->l!=NULL)&&(root->l->colour==1))               //when uncle is red
        {
            root->l->colour=0;
            root->r->colour=0;
            root->colour=1;
            return root;

        }
       else
        {
            if((root->r->l!=NULL)&&(root->r->l->colour==1))      //RL case
              root->r=rightrotate(root->r);

            root=leftrotate(root);                               //RR case
            root->l->colour=1;
            root->colour=0;
            return root;
                          
        } 
      }
      else
       return root;
    }
  }
 else if(ptr->key<root->key)
  {root->l=insert_RBT(root->l,ptr);
   
    if(root->l->colour==0)
     return root;
    else                                                                                       // parent is red
     {if( ((root->l->l!=NULL)&&(root->l->l->colour==1)) || ((root->l->r!=NULL)&&(root->l->r->colour==1)) )   
       {if((root->r!=NULL)&&(root->r->colour==1))               //when uncle is red
         {
             root->l->colour=0;
             root->r->colour=0;
             root->colour=1;
             return root;
   
         }
        else
         {
             if((root->l->r!=NULL)&&(root->l->r->colour==1))      //LR case
               root->l=leftrotate(root->l);
   
             root=rightrotate(root);                               //LL case
             root->r->colour=1;
             root->colour=0;
             return root;
                           
         } 
       }
       else
        return root;
     }
   
  }
  else                           //ignoring duplicate cases
   return root;

}

void preorder(node_ptr T)
{if(T!=NULL)
 {printf("( ");
   printf("%ld %c ",T->key,(T->colour==1)?'R':'B');
  preorder(T->l);
  preorder(T->r);
  printf(") ");}
else
   printf("( ) ");
}

void Print(struct RBT tree)
{
  preorder(tree.root);
  printf("\n");
}

void main()
{struct RBT T;
 char st[100];
 long int val;
 node_ptr p;
 T.root=NULL;
 scanf("%s",st);
 while(st[0]!='t')
 {
  val=atoi(st);
  p=create_RBT(val);
  T.root=insert_RBT(T.root,p);
  if(T.root!=NULL)
   T.root->colour=0;
  Print(T); 
  scanf("%s",st);
  
 }
 


}
