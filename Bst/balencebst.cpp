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

void inorder(Node* root, vector<int> &in){
    if( root == NULL ){
        return;
    }

    inorder(root -> left, in);
    in.push_back(root -> data);
    inorder(root -> right, in);
}

Node* inordertoBST(int s, int e, vector<int> &in){
    if (s > e) {
        return NULL;
    }

    int mid = (s + e) / 2;
    Node* root = new Node (in[mid]);
    root -> left = inordertoBST(s, mid - 1, in);
    root -> right = inordertoBST(mid + 1, e, in);
    return root;
}

Node* balenced(Node* root){
    vector<int> inorderVal;
    inorder(root, inorderVal);
    
    return inordertoBST(0, inorderVal.size() - 1, inorderVal);
}

void printInOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

int main(){
    Node* root = NULL;
    cout<<"Enter the data to insert in BST";
    takeInput(root);

    cout<<"converting to balenced BST";
    Node* final = balenced(root);

    cout << "Inorder traversal of the balanced BST: ";
    printInOrder(final);
    cout << endl;
    

}