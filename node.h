//Kyle Werstlein
//3/9/20
//Node class for binary search tree.

class Node {
public:
    Node();
    ~Node();
    int getData();
    void setData(char newdata);
    Node* getLeft();
    void setLeft(Node* newleft);
    Node* getRight();
    void setRight(Node* newright);
private:
    int data;
    Node* leftP;
    Node* rightP;
};