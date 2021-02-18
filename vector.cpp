#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<string> names;
    names.push_back("amao");
    names.push_back("adong");
    names.push_back("messi");
    names.push_back("kevin");
    names.push_back("ronaldo");
    for(int i=0;i<names.size();i++)
    {
        cout<<names[i]<<endl;
    }
    vector<string>::iterator iter=names.begin();
    while(iter != names.end())
    {
        cout << *iter << endl;
        iter++;
    }
    sort(names.begin(),names.end());
    for(int i=0;i<names.size();i++)
    {
        cout<<names[i]<<endl;
    }
    return 0;
}

