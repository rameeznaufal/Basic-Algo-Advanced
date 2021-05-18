
#include <stdio.h>
#include <stdlib.h>

struct node {
  int vertex;
  struct node *next;
};

struct Graph {
  int N_Vertices;
  struct node **adjLists;         //an array of pointers of node
};

struct node* create_node(int v) 
{
  struct node* n = malloc(sizeof(struct node));
  n->vertex = v;
  n->next = NULL;
  return n;
}

struct Graph* create_graph(int v) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->N_Vertices = v;

  graph->adjLists = calloc(v,sizeof(struct node*));

  for (int i = 0; i < v; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

void add_E(struct Graph* graph, int s, int d) {       //insertion in front
  // Add edge from s to d
  struct node* n = create_node(d);
  n->next = graph->adjLists[s];
  graph->adjLists[s] = n;

  /*  // Add edge from d to s
  newNode = createNode(s);                   //for undirected graphs
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;  */
}

void print(struct Graph* graph) 
{
  int v;
  struct node* temp; 
  for (v = 0; v < graph->N_Vertices; v++) 
  {
    temp = graph->adjLists[v];
    printf("%d ", v);
    while (temp) {
      printf("%d ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

void main()
{int n,val;
 struct Graph *G;
 scanf("%d",&n);
 G = create_graph(n);
 int a[n][n];
 
 for(int i=0;i<n;++i)
 {for(int j=0;j<n;++j)
   {
    scanf("%d",&a[i][j]);
   }
 }

 for(int i=0;i<n;++i)
 {for(int j= n-1;j>=0;--j)
  {
   if(a[i][j]==1)
   {
    add_E(G,i,j);
   }
  }
 }
 print(G);
 }