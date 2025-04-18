#include<iostream>
using namespace std;
#include<string>
#include<vector>

class TrieNode{
    public:
    char data;
    TrieNode* children[26];
    bool isTerminal;

    TrieNode(char ch){
        data = ch;
        for(int i = 0; i < 26; i++ ){
            children[i] = NULL;
        } 
        isTerminal = NULL;
    }
};

class Trie{
    public:
    TrieNode* root;
    Trie(){
        root = new TrieNode('\0');
    }
    void insertUtil(TrieNode* root, string word){
        if(word.length() == 0){
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'A';
        TrieNode* child;
        if(root->children[index]!= NULL){
            child = root->children[index];

        }
        else{
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }
        insertUtil(child, word.substr(1));
    }

    void insert(string word){
        insertUtil(root, word);
    }

    vector<vector<string>> getSuggestion(string str){
        TrieNode* prev = root;
        vector<vector<string>> output;
        string prefix = "";
        for( int i = 0; i < str.length(); i++ ){
            char lastch = str[i];
            prefix.push_back(lastch);
            TrieNode* curr = prev->children[lastch - 'A'];
            if(curr == NULL){
                break;
            }
            vector<string> temp;
            printSuggestion(curr, temp, prefix);
            output.push_back(temp);
            temp.clear();
            prev = curr;
        }
        return output;
    }

    void printSuggestion(TrieNode* curr, vector<string> &temp, string prefix){
        if(curr->isTerminal){
            temp.push_back(prefix);
        }
        for(char ch ='A'; ch <= 'Z'; ch++){
            TrieNode* next = curr->children[ch - 'A'];
            if(next != NULL){
                prefix.push_back(ch);
                printSuggestion(next,temp,prefix);
                prefix.pop_back();
            }
        }
    }
};


int main(){
    Trie* t = new Trie();
    t->insert("CODING");
    t->insert("CODDING");
    t->insert("COLY");
    t->insert("CODE");
    t->insert("CODES");

    vector<vector<string>> suggestions = t->getSuggestion("CODING");
    for(auto group : suggestions) {
        for(auto word : group) {
            cout << word << " ";
        }
        cout << endl;
    }

    return 0;
}
