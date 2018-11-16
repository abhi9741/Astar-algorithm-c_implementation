#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>

char citylist[13]={'S','A','B','C','D','E','F','G','H','I','J','K','L'};
int xarray[13] = {3,1,5,7,1,7,1,6,5,6,11,9,9};
int yarray[13] ={10,7,8,7,5,1,3,2,4,5,5,3,6};
float distance(int x1, int y1, int x2, int y2)
{

	return sqrt(pow(x2 - x1, 2) +
				pow(y2 - y1, 2) * 1.0);
}

struct adjacentlistnode{
    float dist;
    int dest;
    struct adjacentlistnode* next;
};

struct adjacentlist{
    int neighbours;
    int visited;
    struct adjacentlistnode *head;
};

struct Graph{
    int n;
    struct adjacentlist* array;
};

struct adjacentlistnode* createadjacentlistnode(int dest,float dist){
    struct adjacentlistnode* newNode =
     (struct adjacentlistnode*) malloc(sizeof(struct adjacentlistnode));
    newNode->dest = dest;
    newNode->dist = dist;
    newNode->next = NULL;
    return newNode;
}

struct Graph* creategraph(int n){
    struct Graph* graph =
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->n = n;

    graph->array =
      (struct adjacentlist*) malloc(n * sizeof(struct adjacentlist));

    int i;
    for (i = 0; i < n; ++i)
        graph->array[i].head = NULL;
        graph->array[i].neighbours =0;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest,float dist){
    struct adjacentlistnode* newNode = createadjacentlistnode(dest,dist);
    graph->array[src].neighbours++;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createadjacentlistnode(src,dist);
    graph->array[dest].neighbours++;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph){
    int n;
    for (n = 0; n < graph->n; ++n)
    {
        struct adjacentlistnode* p = graph->array[n].head;
        printf("\n Adjacency list of nertex %d\n neighbours :%d ", n,graph->array[n].neighbours);
        while (p)
        {
            printf("-> %d ", p->dest);
            printf("dist %f", p->dist);
            p = p->next;
        }
        printf("\n");
    }
}

struct Graph* buildgraph (){
  int n = 13;
  struct Graph* graph = creategraph(n);
  addEdge(graph, 1, 2 ,distance(xarray[1],yarray[1],xarray[2],yarray[2]));
  addEdge(graph, 1, 0 ,distance(xarray[1],yarray[1],xarray[0],yarray[0]));
  addEdge(graph, 1, 4 ,distance(xarray[1],yarray[1],xarray[4],yarray[4]));
  addEdge(graph, 0, 2 ,distance(xarray[0],yarray[0],xarray[2],yarray[2]));
  addEdge(graph, 2, 8 ,distance(xarray[2],yarray[2],xarray[8],yarray[8]));
  addEdge(graph, 4, 6 ,distance(xarray[4],yarray[4],xarray[6],yarray[6]));
  addEdge(graph, 8, 6 ,distance(xarray[8],yarray[8],xarray[6],yarray[6]));
  addEdge(graph, 8, 7 ,distance(xarray[8],yarray[8],xarray[7],yarray[7]));
  addEdge(graph, 7, 5 ,distance(xarray[7],yarray[7],xarray[5],yarray[5]));
  addEdge(graph, 5, 11 ,distance(xarray[5],yarray[5],xarray[11],yarray[11]));
  addEdge(graph, 0, 3 ,distance(xarray[0],yarray[0],xarray[3],yarray[3]));
  addEdge(graph, 3, 12 ,distance(xarray[3],yarray[3],xarray[12],yarray[12]));
  addEdge(graph, 9, 12 ,distance(xarray[9],yarray[9],xarray[12],yarray[12]));
  addEdge(graph, 10, 12 ,distance(xarray[10],yarray[10],xarray[12],yarray[12]));
  addEdge(graph, 9, 11 ,distance(xarray[9],yarray[9],xarray[11],yarray[11]));
  addEdge(graph, 9, 10 ,distance(xarray[9],yarray[9],xarray[10],yarray[10]));
  addEdge(graph, 10, 11 ,distance(xarray[10],yarray[10],xarray[11],yarray[11]));
  addEdge(graph, 4, 2 ,distance(xarray[4],yarray[4],xarray[2],yarray[2]));
//  addEdge(graph, 0, 5 ,distance(xarray[0],yarray[0],xarray[5],yarray[5]));

  return graph;
}

struct QNode{
    int name;
    float distance;
    float heuristic;
    int via;
    struct QNode* next;
    struct QNode* prev;
};

struct Queue{
    int members ;
    struct QNode *current,*start,*rear;
};

struct QNode* newNode(int name,float distance,float heuristic,int via){
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->name = name;
    temp->distance = distance;
    temp->via =  via;
    temp->next = NULL;
    temp->heuristic = heuristic;
    return temp;
}

struct Queue *createQueue(){
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->current = NULL;
    q->start = NULL;
    q->members = 0;
    return q;
}

void swap(struct QNode *a, struct QNode *b){
    int temp = a->name;
    float temp1 = a->distance;
    int temp2 = a->via;
    float temp3 = a->heuristic;
    a->name = b->name;
    b->name = temp;
    a->distance = b->distance;
    b->distance = temp1;
    a->via = b->via;
    b->via = temp2;
    a->heuristic=b->heuristic;
    b->heuristic=temp3;
}

void bubbleSort(struct QNode *start){
    int swapped, i;
    struct QNode *ptr1;
    struct QNode *lptr = NULL;


    if (ptr1 == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->distance + ptr1->heuristic > ptr1->next->distance + ptr1->heuristic)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

bool ifpresent(struct Queue* q,int name,float distance,float heuristic,int via){
  struct QNode* p = q->start;
  while(p->next != NULL){
    if(p->name == name){
     float f = p->distance;
     if (distance<=f){
       p->distance = distance;
       p->via = via;
       p->heuristic = heuristic;
     }

      q->members++;
      return true;
    }
    p = p->next;
  }
}

void enQueue(struct Queue *q, int name,float distance,float heuristic,int via){

    struct QNode *temp = newNode(name,distance,heuristic,via);


    if (q->current == NULL)
    {
       q->rear = q->start = q->current = temp;
       q->members++;
       return;
    }
    if (ifpresent(q,name,distance,heuristic,via)){

    }
    else {
    q->rear->next = temp;
    q->rear = temp;
    q->members++;
     }
    bubbleSort(q->current);
}

void print(struct Queue* q){
  struct QNode* p = q->start;
  while(p->next != NULL){
    printf("name -%d,distance -%f,via -%d \n",p->name,p->distance,p->via);
    p = p->next;
  }
}

void traceback(struct Queue* q,int destination,int departure){
  if (destination==departure){
    printf(" %c ,",citylist[departure]);
    return;
  }
  struct QNode* tempq = q->start;
  while(tempq->name != destination){
    tempq = tempq->next;
  }
  printf(" %c <-",citylist[tempq->name] );
  traceback(q,tempq->via,departure);
}

int main()
{

    struct Graph* graph =buildgraph();
    printGraph(graph);
    printf("--------------------------------------------------------------------------------------------------------- \n");
    printf("above is the adjacency list representation \n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    printf("cities avilable :\n");
    int i=0;
    while(i<13){
      printf("%d ) %c \n",i,citylist[i]);
      i++;
    }
    printf("---------------------------------------------------------------------------------------------------------\n");
    struct Queue* q = createQueue();
    int initialcity,endingcity;
    printf("enter the departure city : \n");
    scanf("%d",&initialcity);
    printf("enter the destination city : \n");
    scanf("%d",&endingcity);

   int n ;
   float d;
  struct adjacentlist currentcity = graph->array[initialcity];
  struct adjacentlistnode* currentnode = currentcity.head;
  enQueue(q,initialcity,0,0,initialcity);
  while (q->current->name != endingcity){
    n = currentcity.neighbours;
    d = q->current->distance;
    //printf("d value %d \n",d);
     currentnode = currentcity.head;
    for(int j=0;j<n;j++){
      if (graph->array[currentnode->dest].visited != 1){
      enQueue(q,currentnode->dest,d+currentnode->dist,distance(xarray[currentnode->dest],yarray[currentnode->dest],xarray[endingcity],yarray[endingcity]),q->current->name);
    }
      currentnode=currentnode->next;
    }
  graph->array[q->current->name].visited = 1;
  q->current=q->current->next;
  currentcity = graph->array[q->current->name];

  }
  printf("---------------------------------------------------------------------------------------------------------\n");
    printf("current queue \n");
    print(q); //printing whole Queue
    printf("---------------------------------------------------------------------------------------------------------\n");
    //printf("name : %d ,distance :  %d ,via : %d \n",q->current->name,q->current->distance,q->current->via);
    float dist = q->current->distance;
    traceback(q,q->current->name,initialcity);
    printf("Total distance : %f \n",dist);
    printf("thankyou for using our services ! \n");

    return 0;
}
