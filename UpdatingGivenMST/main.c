#include <stdio.h>
#define MAX 20

typedef struct edges{
    int u,v,w;
}EDGES;

typedef struct edgeList{
    EDGES data[MAX];
    int maxEdgeIndex;
    int n;
}EDGE_LIST;

void createTree(EDGE_LIST *tree, int u, int v, int w){

    tree->data[tree->n].u=u;
    tree->data[tree->n].v=v;
    tree->data[tree->n].w=w;

}

// Printing the minimum spanning tree
void printMST(EDGE_LIST *tree){
    int i;
    for (i=0 ; i < tree->n; i++) {
        printf("\nFrom: %d"
               " To: %d"
               " Weight: %d",
               tree->data[i].u,tree->data[i].v,tree->data[i].w);
    }
}

// It finds the path and returns the maximum edge value from that path
int findPath(EDGE_LIST *tree,int init, int u, int dest, int w){
    int i;
    int max = 0;

    static int isPathFound= 0;

    for ( i = 0; i < tree->n; i++) {

        if (tree->data[i].u == u){
            if (tree->data[i].v == dest){
                isPathFound=1;
                max= tree->data[i].w;
                tree->maxEdgeIndex=i;
                return max;
            }
            else if (tree->data[i].v != init){

                init = tree->data[i].u;
                max = findPath( tree, init, tree->data[i].v, dest, w);
                if (isPathFound==1){
                    if (max < tree->data[i].w)
                    {
                        max = tree->data[i].w;
                        tree->maxEdgeIndex=i;
                    }
                    return max;
                }
            }
        }
        else if (tree->data[i].v == u){
            if (tree->data[i].u == dest){
                max= tree->data[i].w;
                isPathFound=1;
                tree->maxEdgeIndex=i;
                return max;
            }
            else if (tree->data[i].u != init)
            {

                init = tree->data[i].v;
                max = findPath( tree, init, tree->data[i].u, dest, w);
                if (isPathFound==1){
                    if (max < tree->data[i].w)
                    {
                        max = tree->data[i].w;
                        tree->maxEdgeIndex=i;
                    }
                    return max;
                }
            }
        }
    }
    if (isPathFound!=1)
        return 0;
}

// Sort
void bubbleSort(EDGE_LIST *tree, int size) {

    EDGES temp;
	int step, i;

    for ( step = 0; step < size - 1; ++step) {

        for ( i = 0; i < size - step - 1; ++i) {

            if (tree->data[i].w > tree->data[i + 1].w) {

                temp = tree->data[i];
                tree->data[i] = tree->data[i+1];
                tree->data[i+1] = temp;
            }
        }
    }
}

// It updates the minimum spanning tree via changing the values of max edge index with new edge
void updateMST(EDGE_LIST *tree, int u, int v, int w){

    tree->data[tree->maxEdgeIndex].u=u;
    tree->data[tree->maxEdgeIndex].v=v;
    tree->data[tree->maxEdgeIndex].w=w;

    // sorting the tree
    bubbleSort(tree,tree->n);
}

// Main
int main() {

    int i, size = 0;
    int u, v, w;
    int maxEdgeValue;
    EDGE_LIST tree;
    tree.n = 0;

    printf("Please enter the node number given Minimum Spanning Tree: \n");
    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        printf("Edge: ");
        scanf("%d", &w);

        printf("From where: ");
        scanf("%d", &u);

        printf("To where: ");
        scanf("%d", &v);
        createTree(&tree, u, v, w);
        tree.n++;
    }
    printMST(&tree);


    // We suppose, that we are entering a new edge which nodes are already in MST
    printf("\nPlease enter tne new Edge: ");
    scanf("%d", &w);

    printf("From where: ");
    scanf("%d", &u);

    printf("To where: ");
    scanf("%d", &v);

    // Now we are going to find the path between u-v and max edge between that path
    maxEdgeValue = findPath(&tree, u, u, v, w);

    // now we have to delete the max edge and implement our new edge
    // that way we update the minimum spanning tree

    if (maxEdgeValue >= w)
        updateMST(&tree, u, v, w);
    else
        printf("\nThe new edge values are not minimizing the spanning tree."
               " Thats why MST did not updated.");


    printMST(&tree);

    return 0;
}
