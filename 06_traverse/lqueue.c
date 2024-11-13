    // SS 2019, KPI FEI TUKE

    #include "lqueue.h"
    #include "err.h"
    #include <stdlib.h>

    struct Node
    {
        PNode	Next;
        TElem	Elem;
    };

    struct LnkQueue
    {
        PNode	Front;
        PNode	Rear;
    };

    int IsEmptyQueue( LQueue Q )
    {
        if(Q == NULL) Error("IsEmptyQueue: incorrect queue!");
        return Q->Front == NULL;
    }

    LQueue CreateQueue( void )
    {
        LQueue Q;
        Q = malloc(sizeof(struct LnkQueue));
        if(Q == NULL)Error("CreateQueue: out of memory!");
        Q->Front = NULL;
        Q->Rear = NULL;
        return Q;
    }

    // Removes a queue
    // Receives a pointer to LQueue, not LQueue itself
    void RemoveQueue( LQueue *PQ )
    {
        if(PQ == NULL) Error("RemoveQueue: incorrect pointer!");
        if(*PQ == NULL) return;
        LQueue Q = *PQ;
        MakeEmptyQueue(Q);
        free(Q);
        *PQ = NULL;
    }

    // Removes elements from a queue
    void MakeEmptyQueue( LQueue Q )
    {
        if(Q == NULL) Error("MakeEmptyQueue: incorrect queue!");
        PNode PFirst;
        while(!IsEmptyQueue(Q)){
            PFirst = Q->Front;
            if(Q->Front == Q->Rear) Q->Rear = NULL;         // the only element in queue
            Q->Front = Q->Front->Next;
            free(PFirst);
        }
    }

    // Inserts element to the end of a list
    void Enqueue( TElem X, LQueue Q )
    {
        PNode PNew;
        if(Q == NULL) Error("Enqueue: incorrect queue!");
        PNew = malloc(sizeof(struct Node));
        if(PNew == NULL) Error("Enqueue: out of memory!");
        PNew->Elem = X;
        PNew->Next = NULL;
        if(IsEmptyQueue(Q)) Q->Front = PNew;
        else Q->Rear->Next = PNew;
        Q->Rear = PNew;
    }

    void PrintQueue( LQueue Q )
    {
        if(Q == NULL) Error("PrintQueue: incorrect queue!");
        if(IsEmptyQueue(Q)) printf("Empty queue");
        else{
            PNode PTmp = Q->Front;
            while(PTmp != NULL){
                printf("%d ", PTmp->Elem);
                PTmp = PTmp->Next;
            }
        }
    }
// show front element
TElem Front (LQueue Q){
    if(Q == NULL){
        Error("Front: incorrect queue!");
        return 0;
    }
    if(IsEmptyQueue(Q)){
        Error("Front: empty queue!");
        return 0;
    }

    return Q->Front->Elem;

}
// remove front element
void Dequeue(LQueue Q){
    if(Q == NULL){
        Error("Dequeue: incorrect queue!");
        return;
    }
    if(IsEmptyQueue(Q)){
        Error("Dequeue: empty queue!");
        return;
    }
    if(Q->Front == Q->Rear) Q->Rear = NULL;
    Q->Front = Q->Front->Next;
}

// show and remove front element

TElem FrontAndDequeue(LQueue Q){
    if(Q == NULL){
        Error("FrontAndDequeue: incorrect queue!");
        return 0;
    }
    if(IsEmptyQueue(Q)){
        Error("FrontAndDequeue: empty queue!");
        return 0;
    }
    TElem elem = Q->Front->Elem;
    Dequeue(Q);
    return elem;
}