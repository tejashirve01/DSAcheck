#include<iostream>
#include<queue>
#include<vector>
#include <climits>
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

void preorder( Node* root, vector<int> &pre){
    if( root == NULL ){
        return;
    }

    pre.push_back(root -> data);
    preorder(root -> left,pre);
    preorder(root -> right,pre);
}
Node* solve(vector<int> &preorder, int mini, int maxi, int &i){
    if(i >= preorder.size()){
        return NULL;
    }
    if(preorder[i] < mini || preorder[i] > maxi ){
        return NULL;
    }

    Node* root = new Node (preorder[i++]);
    root -> left = solve(preorder, mini, root -> data, i);
    root -> right = solve(preorder, root -> data, maxi, i);
    return root;

}



Node* preordertoBST( vector<int> &preorder){
    int mini = INT_MIN;
    int maxi = INT_MAX;
    int i = 0;
    return solve(preorder, mini, maxi, i);
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

    vector<int> final;
    preorder(root, final);

    cout<<"Preorder";
    Node* ans = preordertoBST(final);

    cout << "Inorder traversal of the balanced BST: ";
    printInOrder(ans);
    cout << endl;

    return 0;
    
}