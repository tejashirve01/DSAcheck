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



void levelOrderTraversal(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp == NULL){
            cout << endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout<< temp->data << " ";
        if(temp->left){
            q.push(temp->left);
        }
        if(temp->right){
        q.push(temp->right);
        }
    } 
}
}

bool Search(Node* root, int x){
    Node* temp = root;
    while( temp != NULL ){
        if(temp->data == x){
            return true;
        }
        if(temp->data > x){
            temp = temp->left;
        }
        else{
            temp = temp -> right;
        }
    }
    return false;
}

Node* minVal(Node* root){
    Node* temp = root;
    while(temp->left != NULL){
        temp=temp->left;
    }
    return temp;
}

Node* maxVal(Node* root){
    Node* temp = root;
    while(temp->right != NULL){
        temp=temp->right;
    }
    return temp;
}

Node* deleteNode(Node* root, int key) {
        if (root == NULL) {
            return root;
        }

        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else { 
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp; 
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp; 
            }
            Node* temp = minVal(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    return root; 
}


int main(){
    Node* root = NULL;
    cout<< "Enter data to create BST" << endl ;
    takeInput(root);
    levelOrderTraversal(root);

    int number;
    cout<< " Enter the number to search in BST";
    cin >> number;
    if(Search(root, number)){
        cout<< "Present";
    }
    else{
        cout<< "Not present";
    }
    cout<< "The minimum value is " << minVal(root)->data;
    cout<< "The maximum value is " << maxVal(root)->data;

    int a;
    cout<< " Enter a node to delete";
    cin>> a;

    deleteNode(root, a);
    levelOrderTraversal(root);
    return 0;
}