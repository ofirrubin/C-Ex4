//
//  Graph.h
//  Ex4
//
//  Created by Ofir Rubin on 27/12/2021.
//

#ifndef Graph_h
#define Graph_h
struct Element{
    int id_;
    double weight;
    struct Element* next;
};

struct Graph{
    struct Element* v; // Value (first element is node, others are it's edges)
    struct Graph* next; // next Element (node which contains its edges)
};
typedef struct Graph Graph;
typedef struct Element Node;
typedef struct Element Element;
typedef struct Element Edge;
typedef enum { False, True } boolean;

Graph* createGraph(void);
void freeGraph(Graph* g);

Node* createNode(int id, double weight);
void addNode(Graph* g, int id_, int weight);
void addNodeFrom(Graph* g, Node* n);
void removeNode(Graph* g, int n);
Node* getNode(Graph*, int id_);

boolean addEdge(Graph* g, int src, int dest, double weight);
boolean removeEdge(Node* src, int dest);
void addEdgeFrom(Node* src, int dest, double weight);
Edge* getEdges(Graph*, int src_);
Edge* getEdge(Graph* g, int src, int dest);
void removeNodeEdges(Node* src);


void printGraph(Graph* g);
#endif /* Graph_h */
