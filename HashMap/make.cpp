#include<iostream>
using namespace std;
#include<map>
#include<unordered_map>


int main(){

    unordered_map<string,int> m;

    pair<string,int> pair1 = make_pair("Tejas",1);
    m.insert(pair1);
    pair<string,int> pair2("Hirve",2);
    m.insert(pair2);
    m["Vaibhavi"] = 3;

    cout << m["Tejas"] << endl;
    cout << m.size() << endl;
    cout << m["Hirve"] << endl;

    for( auto i : m){
        cout<< i.first << " " << i.second << endl;
    }

    cout<< m.erase("Hirve") << endl;
    cout << m.size() << endl; 

    unordered_map<string,int> :: iterator it = m.begin();
    while(it != m.end()){
        cout<< it->first << " " << it->second << endl;
        it++;
    }
    return 0;
}