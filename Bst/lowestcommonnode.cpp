#include<iostream>
#include<queue>
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



void inorder(Node* root){
    
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<< " ";
    inorder(root->right);
} 

Node* LCA(Node* root, Node* P, Node* Q){

    if(root == NULL){
        return NULL;
    }

    if(root->data < P->data && root->data < Q->data){
        return LCA(root->right , P, Q);
    }

    if(root->data > P->data && root->data > Q->data){
        return LCA(root->left , P, Q);
    }

    return root;

}
int main(){
    Node* root = NULL;
    
    cout<< "Enter data to create BST" << endl ;
    takeInput(root);
    inorder(root);
    cout<< endl;

    int Pa,Qa;
    cout<< "Enter P";
    cin>> Pa;
    cout<< "Enter Q";
    cin >> Qa;
    Node* P = new Node(Pa);
    Node* Q = new Node(Qa);

    Node* lca = LCA(root, P, Q);
    if (lca != NULL) {
        cout << "Lowest Common Ancestor of " << Pa << " and " << Qa << " is: " << lca->data << endl;
    } else {
        cout << "Lowest Common Ancestor does not exist." << endl;
    }

    return 0;
}
    
    
