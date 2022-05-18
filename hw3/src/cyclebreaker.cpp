/////////////////////////////////////////////////////////////////////////////////////////
//                                    include                                          //                        
/////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <stdio.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
//                                     struct                                          //                        
/////////////////////////////////////////////////////////////////////////////////////////
// Struct edges
struct Edge
{
    int u, v, w;
    friend bool operator<(const Edge& E1, const Edge& E2)
    {
        return E1.w > E2.w;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////
//                                     class                                           //                        
/////////////////////////////////////////////////////////////////////////////////////////
class Vertex_d
{
public:
	Vertex_d(int s=0) :pi(s), rank(0) {}
	~Vertex_d() {}

	void setRank() { rank += 1; }
    int getRank() { return rank; }
	void setPi(int p) { pi = p; }
    int getPi() { return pi; }

private:
    int rank;
	int pi;
};

class Edge_d
{
public:
	Edge_d(int s=0, int e=0, int w=0) :start_v(s), end_v(e), weight(w) {}
	~Edge_d() {}
	 
    int getWeight() { return weight; }
	int getStart() { return start_v; }
	int getEnd() { return end_v; }

private:
	int start_v, end_v, weight;
};

/////////////////////////////////////////////////////////////////////////////////////////
//                                   parameter                                         //                        
/////////////////////////////////////////////////////////////////////////////////////////
int V_NUM, E_NUM, total_weight_u, total_weight_d;
char type = 0;
// Undirected
vector<Edge> remove_edge_u, SpanTree;
vector<int> uset;
// Directed
vector<Edge> remove_edge_d, MST_d;
vector<Vertex_d> V;
vector<Edge_d> E;
vector<vector<int> > adj;
int weight_d[10000][10000];
int remove_cost_d=0;

/////////////////////////////////////////////////////////////////////////////////////////
//                                    function                                         //                        
/////////////////////////////////////////////////////////////////////////////////////////
// Directed findset
int FindSet_d(int u)
{
    int u_pi = V[u].getPi();
    if (u != u_pi){
        V[u].setPi(FindSet_d(u_pi));
    }
    return V[u].getPi();
}

// Directed union set
void Union_d(int u, int v)
{
    if ((V[u].getRank()) > (V[v].getRank())){
        V[v].setPi(u);
    }
    else if ((V[u].getRank()) < (V[v].getRank())){
        V[u].setPi(v);
    }
    else if ((V[u].getRank()) == (V[v].getRank())){
        V[v].setRank();
    }
}

// Makeset 
void MakeSet(vector<int>& uset, int n)
{
    // Reset n*[0]
    uset.assign(n, 0); 
    for (int i = 0; i < n; i++) { uset[i] = i; }
}

// 查找當前元素所在集合的代表元
int FindSet(vector<int>& uset, int u)
{
    int i = u;
    while (uset[i] != i) { i = uset[i]; }
    return i;
}

// 輸出美觀, 排序輸出最左邊那行
bool compare(Edge a, Edge b)
{
	return a.u < b.u;
}

// bool compare_w(Edge a, Edge b)
// {
// 	return a.w > b.w;
// }

// Modified Kruskal (greedy Max spanning tree)
void Modified_Kruskal(const vector<Edge>& edges, int n)
{
    // Reset
    uset.clear();
    SpanTree.clear();
    remove_edge_u.clear();
    MST_d.clear();
    remove_edge_d.clear();
    // sort(edges.begin(), edges.end());
    // Undirected
    int total_cost=0, check_remove_cost=0;
    int Cost = 0, e1, e2;
    MakeSet(uset, n);
    for (int i = 0; i < edges.size(); i++) //按權值從大到小的順序取邊
    {
        total_cost += edges[i].w;
        e1 = FindSet(uset, edges[i].u);
        e2 = FindSet(uset, edges[i].v);
        if (e1 != e2) //若當前邊連接的兩個結點在不同集合中，選取該邊併合並這兩個集合
        {
            // Undirected
            if (type == 'u'){
                SpanTree.push_back(edges[i]);
                Cost += edges[i].w;
            }
            else if (type == 'd'){
                MST_d.push_back(edges[i]);
            }
            uset[e1] = e2; //合併當前邊連接的兩個頂點所在集合
        }
        else
        {
            if (type == 'u'){
                remove_edge_u.push_back(edges[i]);
                check_remove_cost += edges[i].w;
            }
            else if (type == 'd'){
                remove_edge_d.push_back(edges[i]);
                remove_cost_d += edges[i].w;
            }
        }        
    }
    if (type == 'u'){
        // Removed edges
        int remove_cost = total_cost-Cost;
        total_weight_u = check_remove_cost;
        sort(remove_edge_u.begin(), remove_edge_u.end(), compare);
        // cout << check_remove_cost << endl;
        // for (int j = 0; j < remove_edge_u.size(); j++)
        // cout << remove_edge_u[j].u << " " << remove_edge_u[j].v << " " << remove_edge_u[j].w << endl;
        // cout << endl;
    }
    else if (type == 'd'){
        // 第一次做完MST的邊
        sort(MST_d.begin(), MST_d.end(), compare);
        // 第一次被移除的邊
        sort(remove_edge_u.begin(), remove_edge_u.end(), compare);
    }
}

bool Modified_DFS(int u, int v, vector<char>& color)
{
    color[v] = 'g';
    for (int i = 0 ; i < adj[v].size() ; i++){
        int v_next = adj[v][i];
        // 若繞回來, 有cycle, return true
        if (v_next == u){
            return true;
        }
        // 繼續recursive往下挖
        if (color[v_next] == 'w'){
            if (Modified_DFS(u, v_next, color)){
                return true;
            }
        }
    }
    color[v] = 'b';
    return false;
}

bool DFS_detect_cycle(Edge& e)
{
    vector<char> color(V_NUM, 'w');
    return Modified_DFS(e.u, e.v, color);
}

void Add_Edge_Back(vector<Edge>& rm_edge_d)
{
    // rm_edge_d has been sorted
    sort(rm_edge_d.begin(), rm_edge_d.end(), compare);
    remove_edge_d = rm_edge_d;
    // for (int i = 0 ; i < rm_edge_d.size() ; i++){
    //     cout << "remove edge: " << rm_edge_d[i].u << ' ' << rm_edge_d[i].v << ' ' << rm_edge_d[i].w << endl;
    // }
    // cout << "removed size: " << rm_edge_d.size() << endl;
    // cout << "removed cost: " << remove_cost_d << endl;
    // run DFS, if there's still no cycle, add it back
    for (int i = 0 ; i < rm_edge_d.size() ; i++){
        // only add back positive weight edge
        if (rm_edge_d[i].w > 0){
            if ((DFS_detect_cycle(rm_edge_d[i])) == false){
                adj[rm_edge_d[i].u].push_back(rm_edge_d[i].v);
                MST_d.push_back(rm_edge_d[i]);
                remove_edge_d.erase(remove_edge_d.begin()+i);
                remove_cost_d = remove_cost_d - rm_edge_d[i].w;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                      main                                           //                        
/////////////////////////////////////////////////////////////////////////////////////////
// graph implementation
int main(int argc, char* argv[])
{
    //////////// read the input file /////////////
    if(argc != 3) {
       cout << "Fail to read files..." << endl;
       return 0;
    }

    fstream fin(argv[1]);

    fin >> type;
    fin >> V_NUM;
    fin >> E_NUM;

    if (type == 'u')
    {
        vector<Edge> edges;
        edges.assign(E_NUM, Edge());
        for (int i = 0; i < E_NUM; i++)
        {
            fin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        // 排序之後，可以以邊權值從大到小的順序選取邊 (在struct Edge的operator已經操作過降序排列)
        sort(edges.begin(), edges.end()); 
        // Maximum spanning tree
        Modified_Kruskal(edges, V_NUM);
        
        fin.close();

        // Write the output file
        FILE* fout;
        fout = fopen(argv[2], "w+t");
            
        fprintf(fout, "%d\n", total_weight_u);
        for (int i=0; i < (int)(remove_edge_u.size()); i++) {
            fprintf(fout, "%d %d %d\n", remove_edge_u[i].u, remove_edge_u[i].v, remove_edge_u[i].w);
        }
        type = 0;
        fclose(fout);
    }

    else if (type == 'd')
    {
        vector<Edge> edges;
        vector<int> init_adj;
        edges.assign(E_NUM, Edge());

        // Initialize
        E.clear();
        V.clear();
        remove_edge_d.clear();
        total_weight_d = 0;
        // Construct vertices
        for (int i = 0 ; i < V_NUM ; i++){
            V.push_back(Vertex_d(i));
            adj.push_back(init_adj);
        }
        // Construct weighted edges
        for (int i = 0 ; i < V_NUM ; i++){
            for (int j = 0 ; j < V_NUM ; j++){
                weight_d[i][j] = -200;
            }
        }
        // Given weighted edges
        for (int i = 0 ; i < E_NUM ; i++){
            int u, v, w;
            fin >> edges[i].u >> edges[i].v >> edges[i].w;
            weight_d[edges[i].u][edges[i].v] = edges[i].w;
            adj[edges[i].u].push_back(edges[i].v);
        }
        // 排序之後，可以以邊權值從大到小的順序選取邊 (在struct Edge的operator已經操作過降序排列)
        sort(edges.begin(), edges.end()); 
        // Maximum spanning tree
        Modified_Kruskal(edges, V_NUM);
        
        fin.close();
        // (1) Do Modified-Kruskal with no direction, return (MST_d, remove_edge_d, remove_cost_d)
        Modified_Kruskal(edges, V_NUM);
        // (2) Add edge back to see if there's a cycle
        vector<Edge> temp = remove_edge_d;
        Add_Edge_Back(temp);
        // (3) Write the output file
        FILE* fout;
        fout = fopen(argv[2], "w+t");
            
        fprintf(fout, "%d\n", remove_cost_d);
        for (int i=0; i < (int)(remove_edge_d.size()); i++) {
            fprintf(fout, "%d %d %d\n", remove_edge_d[i].u, remove_edge_d[i].v, remove_edge_d[i].w);
        }
        type = 0;
        fclose(fout);
    }

    return 0;
}