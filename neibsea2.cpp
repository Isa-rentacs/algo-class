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
    //fstream cin("./eil51.tsp");
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
                cand_dist = dist[pos][i];
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
    ret += dist[pos][0];
    cout << "euler cycle length = " << ret << endl;
    for(int i=0;i<his.size();i++){
        cout << his[i] << " ";
    }
    cout << endl;

    //近傍探索を行う
    srand(time(NULL));
    double candlen = ret;
    for(int loop=0;loop < 10000000; loop++){
        double tmpdist;
        int cand_index = -1;
        //ランダムな2点の訪問順を入れ替える
        int s,e;
        do{
            s = rand()%num_node;
            e = rand()%num_node;
        }while(s == e);
        swap(his[s],his[e]);
        tmpdist = 0;
        for(int j=0;j<num_node;j++){
            tmpdist += (j != num_node - 1? dist[his[j]][his[j+1]]:dist[his[j]][his[0]]);
        }
        if(tmpdist < candlen){
            candlen = tmpdist;
        }else{
            swap(his[e],his[s]);
        }
    }

    for(int i=0;i<num_node;i++){
        cout << his[i] << " ";
    }
    cout << endl;
    cout << "length of euler cycle = " << candlen << endl;
}
