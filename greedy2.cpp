#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>

#define PB push_back
#define MP make_pair
#define X first
#define Y second

using namespace std;

typedef pair<int,int> P;

class vertex{
public:
    vertex(int xx, int yy, int ii){
        x = xx;
        y = yy;
        index = ii;
    }
    
    int x;
    int y;
    int index;

    bool operator <(const vertex &arg) const{
        if(x == arg.x){
            return y < arg.y;
        }else{
            return x < arg.x;
        }
    }
};

inline double euc_dist(P p1, P p2){
    return sqrt(pow((double)p1.X - p2.X, 2) + pow((double)p1.Y - p2.Y, 2));
}

double euc_dist(vertex p1, vertex p2){
    return sqrt(pow((double)p1.x - p2.x, 2) + pow((double)p1.y - p2.y, 2));
}

int main(){
    fstream cin("./eil51.tsp");
    string str;
    vector<vertex> p;
    int index, x, y, num_node;
    double ret = 0;
    vector<int> his;

    for(int i=0;i<6;i++){
        //dispose headers
        getline(cin,str);
    }

    int cnt = 0;
    while(getline(cin,str)){
        if(str == "EOF") break;
        cin >> index >> x >> y;
        p.PB(vertex(x,y,cnt));
        cnt++;
    }
    num_node = p.size();
    sort(p.begin(),p.end());

    for(int i=0;i<num_node;i++){
        his.PB(p[i].index);
        if(i != num_node - 1){
            ret += euc_dist(p[i],p[i+1]);
        }else{
            ret += euc_dist(p[i],p[0]);
        }
    }
    cout << "euler cycle length = " << ret << endl;
    for(int i=0;i<his.size();i++){
        cout << his[i] << " ";
    }
    cout << endl;

}
