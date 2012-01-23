#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#define PB push_back
#define MP make_pair
#define X first
#define Y second

using namespace std;

typedef pair<int,int> P;

inline double euc_dist(P p1, P p2){
    return sqrt(pow((double)p1.X - p2.X, 2) + pow((double)p1.Y - p2.Y, 2));
}

int main(){
    //fstream cin("./eil51.tsp");
    string str;
    vector<P> p;
    int index, x, y, num_node;
    double ret = 0;
    vector<int> his;

    for(int i=0;i<6;i++){
        //dispose headers
        getline(cin,str);
    }

    while(getline(cin,str)){
        if(str == "EOF") break;
        istringstream iss(str);
        iss >> index >> x >> y;
        p.PB(MP(x,y));
    }
    num_node = p.size();


    bool visited[num_node];
    memset(visited, false, sizeof(visited));
    srand(time(NULL));
    //the first vertex should be determined randomly
    int pos = rand() % num_node;
    double cand_dist,min_dist;
    int cand_vertex;
    visited[pos] = true;
    his.PB(pos);
    while(1){
        bool isended = true;
        for(int i=0;i<num_node;i++){
            if(visited[i] == false){
                isended = false;
            }
        }

        if(isended) break;

        min_dist = 1e+10;
        for(int i=0;i<num_node;i++){
            if(visited[i] == false){
                cand_dist = euc_dist(p[pos],p[i]);
                if(cand_dist < min_dist){
                    min_dist = cand_dist;
                    cand_vertex = i;
                }
            }
        }

        pos = cand_vertex;
        ret += min_dist;
        visited[pos] = true;
        his.PB(pos);
    }
    ret += euc_dist(p[pos], p[0]);
    cout << "euler cycle length = " << ret << endl;
    for(int i=0;i<his.size();i++){
        cout << his[i] << " ";
    }
    cout << endl;
}
