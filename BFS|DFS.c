#include<stdio.h>
#include<stdlib.h>

struct node_Q{
                  int data;
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

ptr_node_Q create(int k)
{  ptr_node_Q temp;
   temp=(ptr_node_Q)malloc(sizeof(struct node_Q));
   if(temp==NULL)
    {exit(0);} 
   temp->data=k;
   temp->next=NULL;
   return temp;
}                              

void enqueue(struct queue *l,int x)
{ptr_node_Q temp;
 temp=create(x);
 if(l->head==NULL)
   {l->head=temp;
    l->tail=temp;}
 else
 {l->tail->next=temp;
  l->tail=temp;}
}

int dequeue(struct queue *l)
{int y;
 ptr_node_Q p;
 if(l->head!=NULL)
 {y=l->head->data;
  p=l->head;
  l->head=l->head->next;
  free(p);
  return(y);}
  else
   return -1;}

struct EDGES {
  int vertex;
  struct EDGES *next;
};

struct Graph {
  int N_Vertices,N_Edges;
  int *visited;
  struct EDGES **adjLists; 
};

struct EDGES* create_EDGES(int v) 
{
  struct EDGES* n = (struct EDGES*)malloc(sizeof(struct EDGES));
  n->vertex = v;
  n->next = NULL;
  return n;
}

struct Graph* create_graph(int v,int e) {
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->N_Vertices = v;
  graph->N_Edges = e;
  graph->adjLists = (struct EDGES**)calloc(v,sizeof(struct EDGES*));
  graph->visited =(int*) calloc(v,sizeof(int));
  for (int j = 0; j < v; j++)
   {graph->adjLists[j] = NULL;
    graph->visited[j] = 0;}
  return graph;
}

void add_E(struct Graph* graph, int s, int d) {       //insertion in tail
  // Add edge from s to d
  struct EDGES *temp,*n;
  n = create_EDGES(d);
  temp=graph->adjLists[s];
  if(temp==NULL)
    graph->adjLists[s]=n;
  else
  {
    while(temp->next!=NULL)
     {temp=temp->next;}
    temp->next=n;
  }  
}

void BFS(struct Graph *G,int SV)
{
    struct queue Q;
    Q.head=Q.tail=NULL;

    G->visited[SV] = 1;
    enqueue(&Q,SV);

    while(!qe(Q))
    {
        int CV = dequeue(&Q);
        printf("%d ",CV);
        struct EDGES *temp = G->adjLists[CV];

        while(temp)
        {
            int ADJV = temp->vertex;
            if(G->visited[ADJV]==0)
            {
                G->visited[ADJV] = 1;
                enqueue(&Q,ADJV);

            }
            temp=temp->next;
        }
    }
    printf("\n");
}

void DFS(struct Graph *G,int SV)
{
    struct EDGES *temp = G->adjLists[SV];
    G->visited[SV] = 1;
    printf("%d ",SV);

    while(temp)
    {
        int CV = temp->vertex;

        if(G->visited[CV]==0)
        {
            DFS(G,CV);
        }
        temp=temp->next;
    }
}

void DFS_Disconnected(struct Graph *G,int SV)
{int i=0;
    for(i=0;i<G->N_Vertices;++i)
     G->visited[i] = 0;
 i=SV;
   do{
       if(G->visited[i]==0)
        DFS(G,i);
       
       i = ((i+1)%G->N_Vertices);
     }while(i!=SV);
 printf("\n"); 
}

void main()
{int v,e,x,y;
char a,b;
 scanf("%d %d",&v,&e);
 struct Graph *G=create_graph(v,e);
 int i=0;

while(i<e)
{
 scanf("%d %d",&x,&y);
 add_E(G,x,y);
 i++;
}
 
 scanf("%d",&x);
 BFS(G,x);
 DFS_Disconnected(G,x);
}