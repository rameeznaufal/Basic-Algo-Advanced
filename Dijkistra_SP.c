
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct EDGES {
  int vertex,weight;
  struct EDGES *next;
};

struct Graph {
  int N_Vertices,N_Edges;
  struct EDGES **adjLists;         //an array of pointers of EDGES
};


struct EDGES* create_node(int v,int w) 
{
  struct EDGES* n = (struct EDGES*)malloc(sizeof(struct EDGES));
  n->vertex = v;
  n->weight = w;
  n->next = NULL;
  return n;
}

struct Graph* create_graph(int v,int e) {
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->N_Vertices = v;
  graph->N_Edges = e;
  graph->adjLists = (struct EDGES**)calloc(v,sizeof(struct EDGES*));

  for (int j = 0; j < v; j++)
    graph->adjLists[j] = NULL;

  return graph;
}

void add_E(struct Graph* graph, int s, int d,int w) {       //insertion in tail
  // Add edge from s to d
  struct EDGES *temp,*n;
  n = create_node(d,w);
  temp=graph->adjLists[s];
  if(temp==NULL)
    graph->adjLists[s]=n;
  else
  {
    while(temp->next!=NULL)
     {temp=temp->next;}
    temp->next=n;
  }  
  (graph->N_Edges)++;
}

struct MinHeap_Node {
  int v;
  int key;
};

struct MinHeap{
  int n;
  int capacity;
  int *pos;
  struct MinHeap_Node *a;
};

struct MinHeap_Node new_MHNode(int v, int key)
{
    struct MinHeap_Node x;
    x.v = v;
    x.key = key;
    return x;
}

struct MinHeap* create_MH(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->n = 0;
    minHeap->capacity = capacity;
    minHeap->pos = (int*)calloc(capacity,sizeof(int));
    minHeap->a = (struct MinHeap_Node*)calloc(capacity,sizeof(struct MinHeap_Node));
    return minHeap;
}

void swap(struct MinHeap_Node a[],int c,int b)
{struct MinHeap_Node temp;
 temp=a[c];
 a[c]=a[b];
 a[b]=temp;}
 
void min_heapify(struct MinHeap *b,int i)
{int l,r,min;
 min=i;
 l=2*i+1;
 r=2*i+2;
 if((l<b->n)&&(b->a[l].key<b->a[min].key))
  min=l;
 if((r<b->n)&&(b->a[r].key<b->a[min].key))
  min=r;
  
   
 if(min!=i)
   {b->pos[b->a[min].v] = i;
    b->pos[b->a[i].v] = min;   

    swap(b->a,i,min);
    min_heapify(b,min);}
}

int parent(int i)
{
  return((i-1)/2);
}

void hdecrease_k(struct MinHeap *a,int j,int k)
{int i= a->pos[j];
  a->a[i].key=k;
 while(i&&a->a[i].key<a->a[parent(i)].key)
 {
  a->pos[a->a[i].v] = parent(i);
  a->pos[a->a[parent(i)].v] = i;
  swap(a->a,i,parent(i));
  i=parent(i);
 }
}  
  
int IsInMinHeap(struct MinHeap *a,int v)
{
  if (a->pos[v] < a->n)
    return 1;
   return 0;
}

struct MinHeap_Node h_extract_min(struct MinHeap *a)
{struct MinHeap_Node min = new_MHNode(0,0);
 if(a->n)
  {min=a->a[0];
   a->pos[min.v] = ((a->n)-1);
   a->pos[a->a[(a->n)-1].v] = 0;
   swap(a->a,0,--a->n);
   min_heapify(a,0);}
  
  return min;
}

void Dijkstra(struct Graph* G, int src, int dest)
{
    int V = G->N_Vertices;
   
    int dist[V];    
 
    struct MinHeap* minHeap = create_MH(V);
    
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->a[v] = new_MHNode(v,dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->a[src] = new_MHNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    hdecrease_k(minHeap, src, dist[src]);
 
    minHeap->n = V;
 
   
    while (minHeap->n)
    {
        struct MinHeap_Node minHeapNode = h_extract_min(minHeap);

        int u = minHeapNode.v;
 
        struct EDGES* pCrawl = G->adjLists[u];
        while (pCrawl != NULL)
        {
            int v = pCrawl->vertex;
 
            if ((IsInMinHeap(minHeap, v)) && (dist[u] != INT_MAX) && (pCrawl->weight + dist[u] < dist[v]))
            {
                dist[v] = dist[u] + pCrawl->weight;
                hdecrease_k(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    if(dest==-1)
    {
      for(int i=0;i<V;++i)
      {
        if(dist[i]==INT_MAX)
         printf("INF ");
        else
         printf("%d ",dist[i]);
      }
    }
    else
    {if(dist[dest]!=INT_MAX)
      printf("%d ",dist[dest]);
     else
      printf("UNREACHABLE ");
    }
    printf("\n");  
}

void main()
{int src,dest,flag_src=0,i=0,v,W;
 char str[1000],*token,junk;
 struct Graph *G;

 scanf("%d",&v);

 G = create_graph(v,0);
 int A[v][v];

 for(int p=0;p<v;++p)
  for(int q=0;q<v;++q)
    A[p][q]=0;

scanf("%c",&junk);

 while (i<v)                                 //to input edges
 { 
     scanf("%[^\n]%*c",str);
   token=strtok(str," ");
   do{
   
   if(flag_src==0)
     {
      src=atoi(token);
      token=strtok(NULL," ");
      flag_src=1;}

   if(token==NULL)
    break;
   dest=atoi(token);
   A[src][dest]=1;
   token=strtok(NULL," ");
   
      }while(token!=NULL);
   i++;
   flag_src=0;
}
i=0;
dest=0;
flag_src=0;

 while(i<v)                                    //to input edges weigths
 { scanf("%[^\n]%*c",str);
   token=strtok(str," ");
   do{
   
   if(flag_src==0)
     {
      src=atoi(token);
      token=strtok(NULL," ");
      flag_src=1;}

   if(token==NULL)
    break;
   W=atoi(token);
   while(dest!=v && A[src][dest]!=1)
    {dest++;}
    
     add_E(G,src,dest,W);

   token=strtok(NULL," ");
   dest++;
      }while(token!=NULL);
   i++;
   flag_src=0;
   dest=0;
}

do
{ dest=-1; 
  scanf("%s",str);
  if(strcmp(str,"apsp")==0)
   {
     scanf("%d",&src);
   }
  else if(strcmp(str,"sssp")==0)
   {
     scanf("%d %d",&src,&dest);
   }
  else
    break;
   Dijkstra(G,src,dest);
}while(1);

}