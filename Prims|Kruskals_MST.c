
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

struct ARR_Edges{
    int src,dest,weight;            //for kruskal part
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

//for subsets in union-find
struct subset {
 int parent;
 int rank;
};

//------------------------------KRUSKALS-ALGORITHM------------------------------------------------------------------------------
int find(struct subset subsets[], int i)            //utility function using path compression tech.
{
    if(subsets[i].parent!=i)
      subsets[i].parent=find(subsets,subsets[i].parent);
 return subsets[i].parent;
}

void Union(struct subset subsets[],int x,int y)     //utility function using rank heuristics  
{
    int xroot = find(subsets,x);
    int yroot = find(subsets,y);

    if(subsets[xroot].rank < subsets[yroot].rank)
      subsets[xroot].parent = yroot;
    else if(subsets[xroot].rank > subsets[yroot].rank)
      subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent =  xroot;
        subsets[xroot].rank++;
    }

}

int myComp(const void* a,const void* b)  //in qsort() for comparing weights
{
   struct ARR_Edges* a1 = (struct ARR_Edges*)a;
   struct ARR_Edges* b1 = (struct ARR_Edges*)b;
   return a1->weight > b1->weight;
}

void Kruskal_MST(struct Graph* G,struct ARR_Edges E[])
{
 int min_cost=0;   
 int V = G->N_Vertices;
 struct ARR_Edges result[V];
 int e = 0,i = 0;
 
 qsort(E,2*G->N_Edges,sizeof(E[0]),myComp);             //sorts in ascending order of weights

 struct subset* subsets = (struct subset*)calloc(V,sizeof(struct subset));

 for(int v =0;v<V;++v)
  {subsets[v].parent = v;
   subsets[v].rank = 0;
  }
 
  while ((e < (V - 1)) && (i < 2*G->N_Edges))
   {
     struct ARR_Edges next_edge = E[i++];

     int x = find(subsets, next_edge.src);
     int y = find(subsets, next_edge.dest);

     if (x != y) 
     {   min_cost += next_edge.weight;                         //if not a cycle add else discard
         result[e++] = next_edge;
         Union(subsets, x, y);
     }
     
   }
  /* 
   printf(
		"Following are the edges in the constructed MST\n");
	int minimumCost = 0;
	for (i = 0; i < e; ++i)
	{
		printf("%d -- %d == %d\n", result[i].src,
			result[i].dest, result[i].weight);
		minimumCost += result[i].weight;
	}
	printf("Minimum Cost Spanning tree : %d",minimumCost);
	return; */
 printf("%d\n",min_cost);  
}

//-------------------------------PRIMS-ALGORITHM-------------------------------------------------------------------------------

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

void Prim_MST(struct Graph* G)
{
    int V = G->N_Vertices; 
    int parent[V]; 
    int key[V]; // Key values used to pick minimum weight edge in cut
  
    
    struct MinHeap* minHeap = create_MH(V);
  
   
    for (int v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->a[v] = new_MHNode(v, key[v]);
        minHeap->pos[v] = v;
    }
  
    key[0] = 0;
    minHeap->a[0] = new_MHNode(0, key[0]);
    minHeap->pos[0] = 0;
  
 
    minHeap->n = V;
  
   
    while (minHeap->n) {

        struct MinHeap_Node minHeapNode = h_extract_min(minHeap);
        int u = minHeapNode.v; 
       
        struct EDGES *pCrawl = G->adjLists[u];
        while (pCrawl != NULL) {
            int v = pCrawl->vertex;
  
            if (IsInMinHeap(minHeap, v) && pCrawl->weight < key[v]) 
            {
                key[v] = pCrawl->weight;
                parent[v] = u;
                hdecrease_k(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
            
        }
    }
  
    // print edges of MST
 int sum=0;
    /*for (int i = 1; i < V; ++i)
        {sum+=key[i];
          printf("%d - %d--->%d\n", parent[i], i,key[i]);
        }*/
     for (int i = 1; i < V; ++i)
        {sum+=key[i];}

  printf("%d\n",sum);     
}





void main()
{char ch,junk;
 int v,i=0,src,dest,flag_src=0,W;
 char str[1000],*token;
 struct Graph *G;


 scanf("%c",&ch);
 scanf("%d\n",&v);
 //scanf("%c",&junk);                  //SOME BS COMPILER ERROR COZ ONE GUY SCREWED UP BIG TIME

 int A[v][v];
 for(int x=0;x<v;++x)
  for(int y=0;y<v;++y)
   A[x][y]=0;

 G = create_graph(v,0);

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
/*
for(int p=0;p<v;++p)
 for(int q=0;q<v;++q)
  {
    if(p>q)
     A[p][q] = 0;
  }
*/
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
i=0;

G->N_Edges=G->N_Edges/2;

struct ARR_Edges edges[2*G->N_Edges];
struct EDGES *temp;

if(ch=='a')
{ 
  
  int e=0;
  
  while(i<v)                                       //to add the edges in a ARR_Edges for kruskals part
  {temp = G->adjLists[i];
   while(temp!=NULL)
    { 
        edges[e].src = i;
        edges[e].dest = temp->vertex;
        edges[e].weight = temp->weight;
        e++;
        temp=temp->next;
    }
  i++;
  }
}  
/*
	for (i = 0; i < max_e; ++i)
	{
		printf("%d -- %d == %d\n", edges[i].src,
			edges[i].dest, edges[i].weight);
	}*/
if(ch=='a')
 Kruskal_MST(G,edges);
else
 Prim_MST(G);
}