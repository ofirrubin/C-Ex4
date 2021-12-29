//
//  Graph.c
//  Ex4
//
//  Created by Ofir Rubin on 27/12/2021.
//

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Graph* createGraph(){
    Graph *g = malloc(sizeof(Graph));
    if (! g){
        printf("Error malloc Graph\n");
        exit(-1);
    }
    g-> v = NULL;
    g -> next = NULL;
    return g;
}
Node* createNode(int id, double weight){
    Node *n = malloc(sizeof(Node)); // NodeData = Element + Edges
    if (! n){
        printf("Error malloc NodeData\n");
        exit(-1);
    }
    n -> id_ = id;
    n -> weight = weight;
    n -> next = NULL;
    return n;
}

Node* getNode(Graph* g, int src){
    // Returns null if not exists
    Graph* n = g;
    while (n != NULL){
        if (n -> v != NULL && n -> v -> id_ == src){
            return n -> v;
        }
        n = n -> next;
    }
    return NULL;
}

Edge* getEdges(Graph* g, int src){
    Node* n = getNode(g, src);
    if (n == NULL) return NULL; // No node;
    return n->next;
}

Edge* getEdge(Graph* g, int src, int dest){
    Node* n = getNode(g, src);
    if (n == NULL) return NULL;
    Edge* e = getEdges(g, src);
    while (e != NULL){
        if (e -> id_ == dest)
            return e;
        e = e -> next;
    }
    return NULL;
}

boolean addEdge(Graph* g, int src, int dest, double weight){
    Graph* p = g;
    if (getNode(g, dest) == NULL) return False; // Dest node not found.
    while(p != NULL){
        if (p -> v != NULL && p -> v -> id_ == src){
            addEdgeFrom(p ->v, dest, weight);
            return True;
        }
        p = p -> next;
    }
    return False;
}

void addEdgeFrom(Node* src, int dest, double weight){
    Edge *e = malloc(sizeof(Edge));
    if (! e){
        printf("Error malloc Edge\n");
        exit(-1);
    }
    e -> id_ = dest;
    e -> weight = weight;
    if (src -> next != NULL){
        e -> next = src -> next; // Making this node the first
    }
    else{
        e -> next = NULL; // the graph doesn't have any node except this one.
    }
    src -> next = e;
}

void addNodeFrom(Graph* g, Node* n){ // Adds node from existing node object
    if (g-> v == NULL){
        g -> v = n; // Adding this node container
    }
    else{
        Graph* h = createGraph(); // Graph points to thisNode, nextNodeGraph
        h -> v = n;
        h -> next = g -> next; // Making this node the first
        g -> next = h;
    }
}


void addNode(Graph* g, int nodeID, int weight){
    if (getNode(g, nodeID) == NULL)
        addNodeFrom(g, createNode(nodeID, weight));
}

boolean removeEdge(Node* src, int dest){
    if (src->next == NULL) return False; // Node has no edges.
    Edge* e = src -> next;
    if (e -> id_ == dest){
        src->next =e->next; // Skip this edge
        free(e); // Free edge space.
        return True;
    }
    while(e){ //
        if (e -> next -> id_ == dest){ // The next edge is the edge we are looking for
            Edge* rmv = e -> next; // Save this edge pointer to free it later
            e -> next = rmv -> next; // Skip the edge we remove
            free(rmv);
            return True;
        }
    }
    return False;
}

void removeNodeEdges(Node* src){
    if (! src) return; // No node to remove from
    if (! src -> next) return;
    Edge* current = src -> next;
    while(current != NULL){
        Edge* next = current -> next; // Save pointer to other edge of src if any.
        free(current); // Clear this edge
        current = next; // Set this pointer to the next edge pointer if any.
    }
}

void removeNode(Graph* g, int n){ // removes node with id=n
    if (g->next != NULL) return; // No node to remove
    Node* node = g-> v;
    if (node->id_ == n){
        removeNodeEdges(node); // Remove all nodes edges.
        if (g -> next){
            g  = g -> next; // The list skips this node.
        }
        free(node); // Free up node.
    }
    else{
        removeEdge(node, n); // Remove possible edge from node.
    }
    Graph* this = g;
    Graph* next = g -> next;
    while(next != NULL && next -> v != NULL){ // For every other node in the list
        if ((next -> v)-> id_ != n){
            // If it's other node, it might have edge with this node:
            removeEdge(next -> v, n); // Remove possible edge with the node.
            this = next; // Go to next node and save this node for skipping if required.
            next = this -> next;
        }
        else{
            // Next node is the node to be removed.
            removeNodeEdges(next -> v); // We remove all edges from the node.
            this = next;
            this -> next = next -> next; // We skip this node in the node list
            free(this); // We free this node of the memory.
        }
    }
}

void freeGraph(Graph* g){
    Graph* this = g; // this - points to subgraph, it's value is a node container (which include the node + edges) and it's next value is the next node container in the graph.
    while(this != NULL){
        Graph* nxt = this->next;
        removeNodeEdges(this->v); // Remove any edge going out of this node
        free(this->v); // Remove this node (edges have been removed, node left)
        free(this); // Remove this node container (now, an empty sub-Graph)
        this = nxt;
    }
}

void printGraph(Graph* g){
    Graph* this = g;
    Node* n;
    Edge* e;
    while(this != NULL){
        n = this -> v;
        if (n != NULL){
            printf("ID: %d (w: %.2f), Edges: ", n -> id_, n->weight);
            e = n -> next;
            while (e !=NULL){
                printf("%d (w: %.2f), ", e -> id_, e -> weight);
                e = e -> next;
            }
            printf("\n");
        }
        this = this -> next;
    }
}
