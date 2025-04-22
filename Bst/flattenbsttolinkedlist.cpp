#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int d){
        this -> data = d;
        this -> left = NULL;
        this -> right = NULL;
    }
};

Node* insertintoBST(Node* root, int d){

    if(root == NULL){
        root = new Node(d);
        return root;
    }
    if(d>root->data){
        root -> right = insertintoBST(root -> right , d);
    }

    else{
        root -> left = insertintoBST( root -> left , d);
    }
    return root;
}


void takeInput(Node* &root){
    int data;
    cin >> data;

    while(data != -1){
        root = insertintoBST(root,data);
        cin >> data;
    }
}

void inorder(Node* root, vector<int> &in){
    if( root == NULL ){
        return;
    }

    inorder( root -> left, in );
    in.push_back( root -> data );
    inorder( root -> right, in );

}

Node* flatten( Node* root){
    vector<int> inorderVal;
    inorder(root, inorderVal);
    int n = inorderVal.size();

    Node* newroot = new Node (inorderVal[0]);
    Node* curr = newroot;

    for ( int i = 1; i <= n; i++ ){
        Node* temp = new Node (inorderVal[i]);
        curr -> left = NULL;
        curr -> right = temp;
        curr = curr -> right;
    }
    curr -> left = NULL;
    curr -> right = NULL;
    return newroot;
}

void printList( Node* root){
    if( root == NULL ){
        return;

    }
    while(root->right!= NULL){
        cout<< root->data << " ";
        root = root -> right;
    }
}

int main(){
    Node* root = NULL;
    cout << "Enter data to insert in node";
    takeInput(root);

    cout<< " Flatten BST converted";
    Node* flatroot = flatten(root);

    printList(flatroot);
}