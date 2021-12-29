//
//  GraphAlgo.c
//  Ex4
//
//  Created by Ofir Rubin on 29/12/2021.
//

#include "GraphAlgo.h"


#include <math.h>
#include <stdlib.h>


double _getWeight(Node* weightList, int id){
    Node* n = weightList;
    while(n != NULL){
        if (n->id_ == id)
            return n -> weight;
        n = n -> next;
    }
    return INFINITY;
}

Node* _getNodeFromList(Node* nodes, int id_){
    if (nodes == NULL) return NULL;
    Node* ptr = nodes;
    while(ptr != NULL){
        if (ptr -> id_ == id_){
            return ptr;
        }
        ptr = ptr -> next;
    }
    return NULL;
}

void _freeShortestPathBuilder(Node* visitedList, Node* q, Node* parents){
    if (visitedList != NULL){
        removeNodeEdges(visitedList);
        free(visitedList);
    }
    if (q != NULL){
        removeNodeEdges(q);
        free(q);
    }
    if (parents != NULL){
        removeNodeEdges(parents);
        free(parents);
    }
}

void _addOrUpdateParent(Node* parents, int c, int parent){
    Node* p = parents;
    while (p != NULL){
        if (p -> id_ == c)
        {
            p -> weight = parent;
            return;
        }
        p = p -> next;
    }
    addEdgeFrom(parents, c, parent);
}


int getParent(Node* parents, int c){
    Node* ptr = parents;
    while(ptr != NULL){
        if (ptr -> id_ == c)
            return ptr -> weight;
        ptr = ptr -> next;
    }
    return -1;
}

void swap_start_at(Node* nodes, int start_at){
    Node* ptr = nodes;
    while(ptr != NULL){
        if (ptr -> id_ == start_at){
            ptr -> id_ = nodes -> id_;
            nodes -> id_ = start_at;
            return;
        }
        ptr = ptr -> next;
    }
}

Node* getMinimum(Node* q, Node* visited){
    // Assuming every element in q exists in visited
    if (q == NULL) return NULL;
    Node* minimum = q;
    double minWeight = minimum -> weight;
    Node* nextNode = q;
    double nextWeight;
    while(nextNode != NULL){
        nextWeight = _getWeight(visited, nextNode->id_);
        if (nextWeight < minWeight){
            minimum = nextNode;
            minWeight = nextWeight;
        }
        nextNode = nextNode -> next;
    }
    return minimum;
}

Node* shortestPathBuilder(Graph* g, int src, int dest){
    Node* visitedList = createNode(src, 0); // List of nodes visited, contains list of updated weight
    Node* q = createNode(src, 0);
    Node* parents = NULL; // parents: like dict where id=nodeID, weight=cameFromID, next is the next node in list.
    Edge* edges;
    int min_id;
    while(q != NULL)
    {
        if (q -> next == NULL){
            min_id = q -> id_;
            free(q);
            q = NULL;
        }
        else{
            min_id = getMinimum(q, visitedList) -> id_; // Because q is not empty it must give us a value.
            if (min_id == q -> id_){ // If the first element is the minimum
                Node* rm = q;
                q = q -> next;
                free(rm); // Clearing the first element.
            }
            else{
                Node* ptr = q;
                while(ptr -> next != NULL && (ptr -> next -> id_) != min_id)
                    ptr = ptr -> next;
                if (ptr -> next != NULL) // Thus next id is min_id
                {
                    Node* rm = ptr -> next;
                    ptr -> next = rm -> next;
                    free(rm);
                }
            }
        }
        if (min_id == dest){
            _freeShortestPathBuilder(visitedList, q, NULL); // DO NOT free parents yet.
            return parents;
        }
        edges = getEdges(g, min_id);
        while(edges != NULL){
            Node* n = _getNodeFromList(visitedList, edges ->id_); // Holds if visited and if so what's the updated weight.
            if (n == NULL){
                addEdgeFrom(visitedList, edges -> id_, INFINITY);
                if (q == NULL){
                    q = createNode(edges ->id_, 0.0);
                }
                else{
                    addEdgeFrom(q, edges ->id_, 0.0); // We ignore the weight anyway
                }
                n = _getNodeFromList(visitedList, edges -> id_);
            }
            if (_getNodeFromList(q, edges -> id_))
            { // If we've been in this node before we check for weight update
                Node* mWeight = _getNodeFromList(visitedList, min_id);
                // u is now called m, node/v is now called n which holds it's weight, parents is parents.
                if (n->weight > mWeight->weight + edges->weight){
                    // We found a better path
                    n -> weight = mWeight -> weight + edges -> weight;
                    _getNodeFromList(q, n ->id_) -> weight = n -> weight; // Update the weight in the queue.
                    if (parents == NULL){
                        parents = createNode(n->id_, min_id);
                    }
                    else{
                        _addOrUpdateParent(parents, n->id_, min_id);
                    }
                }
            }
            edges = edges -> next;
        }
    }
    _freeShortestPathBuilder(visitedList, q, parents);
    return NULL; // No way
}

Node* shortestPath(Graph* g, int src, int dest){
    Node* head = shortestPathBuilder(g, src, dest);
    if (head == NULL){
        return NULL;
    }
    int parent = getParent(head, dest);
    Node* n = createNode(dest, 0);
    Node* last = n;
    while(parent != -1){
        addEdgeFrom(last, parent, 0);
        last = last -> next;
        parent = getParent(head, last ->id_);
    }
    
    removeNodeEdges(head);
    free(head);
    return n;
}

int getShortestPathDist(Graph* g, int src, int dest){
    Node* head = shortestPath(g, src, dest);
    if (head == NULL) return -1;
    double weight = 0;
    Node* ptr = head;
    Edge* e;
    while(ptr -> next != NULL){
        e = getEdge(g, ptr -> next -> id_, ptr -> id_);
        if (e == NULL)
            break;
        weight += e -> weight;
        ptr = ptr -> next;
    }
    removeNodeEdges(head);
    free(head);
    return weight;
}


double pathWeight(Graph* g, Node* head){ // Returns the path of a path except the last two elements
    if (head == NULL) return -1;
    if (head -> next == NULL) return -1; // No node to go for.
    //if (nodes -> next -> next -> next == NULL) return 0; // It has to calculate the last two elements only but it will be done in _tsp
    double weight = 0;
    double tmp;
    Node* ptr = head;
    while (ptr -> next -> next != NULL){ // untile: node -> node -> NULL
        tmp = getShortestPathDist(g, ptr -> id_, ptr -> next -> id_);
        if (tmp == -1) return -1;
        weight += tmp;
        ptr = ptr -> next;
    }
    return weight;
}

double shortestDistOf2(Graph* g, Node* n1, Node* n2, Node* lastNode){
    double pathA2last = -1, pathB2last = -1, a = -1, b = -1;
    if (lastNode != NULL){
        pathA2last = getShortestPathDist(g, lastNode -> id_, n1 -> id_);
        pathB2last = getShortestPathDist(g, lastNode -> id_, n2 -> id_);
    }
    if (pathA2last != -1)
        a = getShortestPathDist(g, n1 -> id_, n2 -> id_);
    if (pathB2last != -1)
        b = getShortestPathDist(g, n2 -> id_, n1 -> id_);
    if (a == -1 || pathA2last == -1){
        if (pathB2last == -1 || b == -1) return -1;
        return pathB2last + b;
    }
    if (b == -1 || pathB2last == -1){ // If either a or pathA2last is -1 (no path) it would've got into the last if, thus there is a path through a
        return pathA2last + a;
    }
    // There is a path through a and b
    if (a + pathA2last < b + pathB2last)
        return a + pathA2last;
    return b + pathB2last;
}

double _tsp(Graph* g, Node* nodes, Node* lastNode, Node* head){ // IMPLEMENT PURE PATH SHORTEST PATH DISTANCE
    if (head -> id_ == 0 && head -> next -> id_ == 3){
    }
    if (nodes == NULL) return -1;
    else if (nodes -> next == NULL) return 0;
    if (nodes -> next -> next == NULL) // 2 nodes only left to be compared
       return shortestDistOf2(g, nodes, nodes -> next, lastNode);
    double w = -1;
    int start_id = nodes -> id_;
    Node* ptr = nodes;
    while(ptr != NULL){
        nodes -> id_ = ptr -> id_;
        ptr -> id_ = start_id;
        double o = _tsp(g, nodes -> next, nodes, head);
        if (w == -1 || (o != -1 && o < w))
            w = o;
        
        ptr -> id_ = nodes -> id_;
        ptr = ptr -> next;
    }
    nodes -> id_ = start_id;
    return w;

}


double tsp_from(Graph* g, Node* nodes, int start_at){
    // Now we can make sure that the node actually starts at certain point
    // For no start limit it would've been: since nodes is the list of nodes that can be changed,
    //return _tsp(g, nodes, NULL, nodes);
    swap_start_at(nodes, start_at); // Make start_at the first element in the list
    return _tsp(g, nodes -> next, nodes, nodes);
}

double tsp(Graph* g, Node* nodes){
    return _tsp(g, nodes, NULL, nodes);
}


void printShortestPath(Graph* g, int src, int dest){
    Node* head = shortestPath(g, src, dest);
    if (head == NULL){
        printf("-1\n");
        return;
    }
    Node* ptr = head;
    while(ptr != NULL){
        printf("%d, ", ptr ->id_);
        ptr = ptr -> next;
    }
    printf("\n");
    removeNodeEdges(head);
    free(head);
}
