#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node
{char *word;
 struct node *next;
};

typedef struct node *node_p;

struct linkedlist
{node_p head;
};

typedef struct linkedlist *ll;

node_p create(char k[])
{  node_p temp;
   temp=(node_p)malloc(sizeof(struct node));
   if(temp==NULL)
    {exit(0);} 
   temp->word=malloc(strlen(k)*sizeof(char));
   strcpy(temp->word,k);
   temp->next=NULL;
   return temp;
}    

 void insert_t_l(struct linkedlist *l,struct node x)
{node_p temp,p;
 temp=create(x.word);
 p=l->head;
 if(l->head==NULL)
   l->head=temp;
 else
 {while(p->next!=NULL)
  {p=p->next;}
  p->next=temp;}
}

void insert_b_l(struct linkedlist *l,struct node x,struct node y)
{node_p p,temp;
 p=l->head;
 if(strcmp(p->word,y.word)==0)
  {temp=create(x.word);
   temp->next=p;
   l->head=temp;}
 else
 {while(strcmp(p->next->word,y.word)!=0)
 {p=p->next;}
  temp=create(x.word);
  temp->next=p->next;
  p->next=temp;}
}

node_p search(struct linkedlist l,char wrd[])
{node_p p;
 p=l.head;
 while(p!=NULL)
 {if(strcmp(p->word,wrd)==0)
   {return p;}
  p=p->next;
 }
 return NULL;
 }

struct HashT
{struct linkedlist *items;
  int m;
};

typedef struct HashT HashTable;

HashTable hashtable(int size)
{
    HashTable table;
    table.m = size;
    table.items = (ll)calloc(table.m, sizeof(struct linkedlist));
    for(int i=0;i<table.m;++i)
     table.items[i].head=NULL;
    return table;
}

int hash(char p[],int size)
{int j=0;
 int a[8]={0};
 int sum=0;

 while(j<strlen(p))
 {if(a[p[j]-'a']==0)
   {sum=sum+pow(2.0,(p[j]-'a'));
    a[p[j]-'a']=1;
   }
  j++;
 }
return (sum);
}

void insert(struct HashT *T,char p[])
{int j;
 struct node temp,targ;
 node_p ptr;

 temp.word=malloc(strlen(p)*sizeof(char));
 strcpy(temp.word,p);
 j=hash(p,T->m);
 
   if(T->items[j].head==NULL)
    {insert_t_l(&T->items[j],temp); 
     return;}
   else
    {if(search(T->items[j],p)==NULL)
     {ptr=T->items[j].head;
      
      while(ptr!=NULL)
      {if(strcmp(p,ptr->word)<0)
        {targ.word=ptr->word;
         insert_b_l(&T->items[j],temp,targ);
         return;}
       ptr=ptr->next;
      }   
     insert_t_l(&T->items[j],temp);
     return;
     }
    }
 return;
}

void print(HashTable T)
{int i=0;
 node_p p;
 do
 {
  
  if(T.items[i].head!=NULL)
  {p=T.items[i].head;
   do
    {printf("%s ",p->word);
     p=p->next;
     if(p==NULL)
      printf("\n"); 
    }while(p!=NULL);
  }

 i++;  
 }while(i<T.m);
}

 void main()
 {int m,count=1;
  HashTable T;
  char str[50];
  scanf("%d ",&m);
  T=hashtable(256);

  
  while (count<=m)
  {scanf("%s",str);
   insert(&T,str);
   count++;
  }

  print(T);
 }