#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define FPP(i,start,end) for(int i = start; i < end; i++)
#define FMM(i,start,end) for(int i = end-1; i >= start; i--)
#define MAXN 200005

typedef struct _node
{
    double p;
    bool flag;
    struct _node * left;
    struct _node * right;
    char ch;
} node;

bool cmp(node * n1, node * n2)
{
    if(n1->p != n2->p) return n1->p < n2->p;
    return n1->ch < n2->ch;
}

node * createNode(double p, node * left, node * right, char ch)
{
    node * n = (node *) malloc(sizeof(node));
    if(!n) return 0;
    n->ch = ch;
    n->left = left;
    n->right = right;
    n->p = p;
    return n;
}

void travarse(string s, node * n, map<char,string> &huffman)
{
    if(n->left == NULL && n->right == NULL)
    {
        huffman[n->ch] = s;
        return;
    }
    travarse(s+"0",n->left, huffman);
    travarse(s+"1",n->right, huffman);
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(NULL);
    string s;
    map<char,double> prob;
    map<char, int> k;
    map<char, string> huffman;
    int cnt = 0;
    getline(cin,s);
    FPP(i,0,s.size())
    {
        k[s[i]]++;
        cnt++;
    }

    for(auto it: k)
    {
        prob[it.first] = 1.0*it.second/cnt;
    }

    deque <node *> dq;

    for(auto it: prob)
    {
        dq.push_back(createNode(it.second, NULL, NULL, it.first));
    }

    sort(dq.begin(), dq.end(), cmp);
    // for(auto it: dq) cout << "'" << (it->ch) << "'" << " \t";/////
    // cout << "\n";///
    while(dq.size() > 1)
    {
        node * n1, * n2;
        n1 = dq[0];
        n2 = dq[1];
        dq.pop_front();
        dq.pop_front();
        if(n1->p != n2->p) dq.push_back(createNode(n1->p + n2->p, n2, n1, n2->ch));
        else if(n1->ch > n2->ch) dq.push_back(createNode(n1->p + n2->p,n2, n1, n2->ch));
        else dq.push_back(createNode(n1->p + n2->p,n1, n2, n1->ch));
        sort(dq.begin(), dq.end(), cmp);
        // for(auto it: dq) cout << (it->p) << " ";/////
        // cout << "\n";////
        for(auto it: dq) cout << "'" << (it->ch) << "'" << " \t";/////
        cout << "\n";///
    }

    travarse("", dq[0], huffman);
    for(auto it: huffman) cout << "'" << it.first << "' -> " << it.second << "\n";

    cout << s << " = ";
    for(int i = 0; i < s.size(); i++) cout << huffman[s[i]];
    cout << endl;
    system("pause");
    return 0;
}