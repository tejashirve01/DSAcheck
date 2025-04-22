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

int solve (Node* root , int& i, int k){
    if(root == NULL){
        return -1;
    }

    int left = solve(root->left, i, k);

    if(left != -1) {
        return left;
    }
    i++;

    if(i==k)
    return root->data;

    return solve(root->right,i,k);

}

int kthsmallest(Node* root, int k){
    int i = 0;
    int ans = solve(root, i, k);
    return ans;
}
int main(){
    Node* root = NULL;
    int e;
    cout<<"Enter k"<< endl;
    cin>> e;
    cout<< "Enter data to create BST" << endl ;
    takeInput(root);
    inorder(root);
    int a = kthsmallest(root,e);
    cout << endl << a << endl;
    return 0;
}