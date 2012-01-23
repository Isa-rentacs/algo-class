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
#define LOOP_MAX 10000;

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
    vector<P> p;
    int index, x, y, num_node;
    double ret = 0;
    vector<int> his;
    vector<int> cand;
    for(int i=0;i<6;i++){
        //dispose headers
        getline(cin,str);
    }

    while(getline(cin,str)){
        if(str == "EOF") break;
        cin >> index >> x >> y;
        p.PB(MP(x,y));
    }
    num_node = p.size();

    //calculate distance matrix
    double dist[num_node][num_node];
    for(int i=0;i<num_node;i++){
        for(int j=i+1;j<num_node;j++){
            if(i == j){
                dist[i][j] = 0;
            }else{
                dist[i][j] = euc_dist(p[i],p[j]);
                dist[j][i] = dist[i][j];
            }
        }
    }

    //generate initial solution randomly
    srand(time(NULL));
    bool used[num_node];
    int pos;
    memset(used, false, num_node);
    while(1){
        bool isended = true;
        for(int i=0;i<num_node;i++){
            if(!used[i]) isended = false;
        }
        if(isended) break;
        do{
            pos = rand() % num_node;
        }while(used[pos] == true);
        used[pos] = true;
        his.PB(pos);
    }

    //print initial solution
    for(int i=0;i<num_node;i++){
        cout << his[i] << " ";
    }
    cout << endl;

    //calculate length of initial solution
    for(int i=0;i<num_node;i++){
        ret += (i != num_node-1?dist[his[i]][his[i+1]]:dist[his[i]][his[0]]);
    }
    cout << "initial length = " << ret << endl;

    //近傍探索を行う
    double candlen = ret;
    for(int loop=0;loop < 100000; loop++){
        double tmpdist;
        int cand_index = -1;
        for(int i=0;i<num_node-1;i++){
            swap(his[i], his[i+1]);
            tmpdist = 0;
            for(int j=0;j<num_node;j++){
                tmpdist += (j != num_node - 1? dist[his[j]][his[j+1]]:dist[his[j]][his[0]]);
            }
            if(candlen > tmpdist){
                candlen = tmpdist;
                cand_index = i;
            }
            swap(his[i], his[i+1]);
        }
        if(cand_index != -1){
            swap(his[cand_index],his[cand_index + 1]);
        }else{
            break;
        }
        cout << loop << endl;
    }
    cout << "length of euler cycle = " << candlen << endl;
}
