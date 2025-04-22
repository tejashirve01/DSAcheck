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

vector<int> merge(vector<int>& m, vector<int>& n) {
    vector<int> final;
    int i = 0, j = 0;

    while (i < m.size() && j < n.size()) {
        if (m[i] < n[j]) {
            final.push_back(m[i]);
            i++;
        } else {
            final.push_back(n[j]);
            j++;
        }
    }
    while (i < m.size()) {
        final.push_back(m[i]);
        i++;
    }
    while (j < n.size()) {
        final.push_back(n[j]);
        j++;
    }

    return final;
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


void printinorder(Node* root){  
    if(root==NULL){
        return;
    }
    printinorder(root->left);
    cout<<root->data<< " ";
    printinorder(root->right);
} 

int main(){
    Node* root1 = NULL;
    cout<< "Enter values to insert in BST1"<< endl;
    takeInput(root1);

    Node* root2 = NULL;
    cout<< "Enter values to insert in BST2"<< endl;
    takeInput(root2);

    vector<int> first;
    vector<int> second;

    inorder(root1, first);
    inorder(root2, second);

    vector<int> final = merge(first, second);

    Node* ans = inordertoBST(0, final.size() - 1, final);

    printinorder(ans);

}