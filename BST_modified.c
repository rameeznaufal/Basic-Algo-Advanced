
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
 {long int key;
  struct node *l,*r;
 };

typedef struct node *node_ptr;

struct BST
    {
      node_ptr root;
    };

node_ptr create(long int k)
{node_ptr temp;
temp=(node_ptr)malloc(sizeof(struct node));
temp->key=k;
temp->l=temp->r=NULL;
return temp;
}

node_ptr inp_parenth(node_ptr tree,char *token,long int *count)
{

long int val;

if(strncmp(token,"(",1)==0)
{token=strtok(NULL," ");}
if(strncmp(token,")",1)==0)
 {token=strtok(NULL," ");
  return (NULL);}
else
 {val=atoi(token);
  (*count)++;
  token=strtok(NULL," ");}

 tree=create(val);
 tree->l=inp_parenth(tree->l,token,count);
 tree->r=inp_parenth(tree->r,token,count);
 token=strtok(NULL," ");
 return(tree);
}

void inorder(node_ptr T)
{if(T!=NULL)
 {inorder(T->l);
  printf("%ld ",T->key);
  inorder(T->r);}
}

node_ptr search(struct BST T,long int k)
{node_ptr y;
 y=T.root;
while(y!=NULL&&y->key!=k)
 {if(y->key>k)
   y=y->l;
   else
   y=y->r;   
 }
 return y;
}

node_ptr tree_min(node_ptr x)
{while(x->l!=NULL)
{x=x->l;}
return x;
}

node_ptr tree_max(node_ptr x)
{while(x->r!=NULL)
{x=x->r;}
return x;
}

long int successor(struct BST T,long int y)
{node_ptr temp,p;
p=T.root;
temp=search(T,y);
if(temp==NULL)
 return -1;

if(temp->r!=NULL)
 {temp=tree_min(temp->r);
  return(temp->key);}
else
 {temp=NULL;
  while(p!=NULL)
    {if(p->key>y)
      {temp=p;
       p=p->l;}
     else
      {p=p->r;}
      if(p==NULL)
        return -1;
     if(p->key==y) 
      {if(temp!=NULL)
        return temp->key;
       else
        return -1; }    
    }
 }
}

long int predecessor(struct BST T,long int y)
{node_ptr temp,p;
p=T.root;
temp=search(T,y);
if(temp==NULL)
 return -1;

if(temp->l!=NULL)
 {temp=tree_max(temp->l);
  return(temp->key);}
else
 {temp=NULL;
  while(p!=NULL)
    {if(p->key>y)
      p=p->l;
     else
      {temp=p;
       p=p->r;}
       if(p==NULL)
        return -1;
     if(p->key==y) 
      {if(temp!=NULL)
        return temp->key;
       else
        return -1; }    
    }
 }
}

long int KSL(node_ptr T,long int k,long int *flg)
{long int temp=-1;
  if(T!=NULL)
 {temp=KSL(T->l,k,flg);
  if((*flg)==k)
   {(*flg)++;
    return T->key;}
  else if((*flg)>k)
   return temp;
  else
   (*flg)++;
  temp=KSL(T->r,k,flg);}
 
 return temp;
}

long int Ksmallest(struct BST T,long int val)
{long int junk=1;
  return KSL(T.root,val,&junk);
}

long int Klargest(struct BST T,long int val)
{long int junk=1;
  return KSL(T.root,val,&junk);
}





void main()
{
 char str[1000000];
 long int val,count=0;
 char *token,c;
 

 struct BST T;
 T.root=NULL;

 scanf("%[^\n]%*c",str);
 token=strtok(str," ");
 T.root=inp_parenth(T.root,token,&count);

 do{
     scanf("%c",&c);
     switch(c)
     {case 'r':scanf("%ld",&val);
               printf("%ld\n",predecessor(T,val));
      break;
      case 'u':scanf("%ld",&val);
               printf("%ld\n",successor(T,val));
      break;
      case 'i':inorder(T.root);
               printf("\b\n");
      break;
      case 'l':scanf("%ld",&val);
               printf("%ld\n",Klargest(T,count-val+1));
      break;
      case 's':scanf("%ld",&val);
               printf("%ld\n",Ksmallest(T,val));
      break;
      }
 }while(c!='e');
}
