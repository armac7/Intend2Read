#ifndef NODE_H
#define NODE_H

template <typename Type>
struct Node 
{
    Type data;
    Node *link;
};

#endif