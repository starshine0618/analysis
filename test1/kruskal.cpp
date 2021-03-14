#include<iostream>
#include<string.h>
using namespace std;

#define len 100

// 边的结构体
class EData{
    public:
        char start;  // 边的起点
        char end;    // 边的终点
        int weight;  // 边的权重

        EData(){

        }
        EData(char s, char e, int w){
            start  = s;
            end    = e;
            weight = w;
        }
};

class Graph{
    // 内部类
    private:
        // 邻接表中表对应的链表的顶点
        class ENode{
            public:
                int vex;         // 顶点
                int weight;      // 权重 
                ENode *nextEdge; // 指向下一条弧
        };

        // 邻接表中表的顶点
        class VNode{
            public:
                char data; // 顶点信息
                ENode *firstEdge; // 指向第一条依付该顶点的弧
        };

    // 私有成员
    private:
        int n;              // 节点个数 
        int e;              // 边的个数
        VNode mVexs[len];
    
    public:
        Graph(){
            ENode *node1, *node2;
            n = 7; 
            e = 12;

            // 设置节点为默认数值
            string nodes = "ABCDEFG";
            // 输入节点
            for(int i=0; i < n; i++){
                mVexs[i].data = nodes[i];
                mVexs[i].firstEdge = NULL;
            }

            // 设置边为默认值
            char edges[][2] = {
                {'A', 'B'}, 
                {'A', 'F'}, 
                {'A', 'G'}, 
                {'B', 'C'}, 
                {'B', 'F'}, 
                {'C', 'D'}, 
                {'C', 'E'},
                {'C', 'F'}, 
                {'D', 'E'},
                {'E', 'F'}, 
                {'E', 'G'},
                {'F', 'G'}
            };
            
            // 边的权重
            int weights[len] = {12, 16, 14, 10, 7, 3, 5, 6, 4, 2, 8, 9};
            
            //　初始化邻接表的边
            for(int i=0; i < e; i++){
                int start = get_Node_Index(edges[i][0]);
                int end = get_Node_Index(edges[i][1]);

                // 初始化 node1
                node1 = new ENode();
                node1->vex = end;
                node1->weight = weights[i];
                node1->nextEdge = NULL;
                // 将 node 添加到 srart 所在链表的末尾
                if(mVexs[start].firstEdge == NULL){
                    mVexs[start].firstEdge = node1;
                }
                else{
                    linkLast(mVexs[start].firstEdge, node1);
                }

                // 初始化 node2
                node2 = new ENode();
                node2->vex = start;
                node2->weight = weights[i];
                node2->nextEdge = NULL;
                // 将 node 添加到 end 所在链表的末尾
                if(mVexs[end].firstEdge == NULL){
                    mVexs[end].firstEdge = node2;
                }
                else{
                    linkLast(mVexs[end].firstEdge, node2);
                }
            }
        }

        void linkLast(ENode*p1, ENode*p2){
            ENode*p = p1;
            while(p->nextEdge){
                p = p->nextEdge;
            }
            p->nextEdge = p2;
        }
        
        // 返回顶点下标
        int get_Node_Index(char number){
            for(int i=0; i < n; i++){
                if(number == mVexs[i].data){
                    return i;
                }
            }
            return -1; 
        }

        // 输出邻接表
        void print(){
            for(int i=0; i < n; i ++){
                cout<<mVexs[i].data;
                ENode *temp = mVexs[i].firstEdge;
                while(temp){
                    cout<<" -> "<<temp->vex;
                    temp = temp->nextEdge;
                }
                cout<<endl;
            }
            cout<<endl;
        }
        
        // 获取图中的边
        EData* get_Edge(){
            EData *edges;
            ENode *node;
            int index = 0;

            edges = new EData[e];
            for(int i=0; i < n; i++){
                node = mVexs[i].firstEdge;
                while(node){
                    if(node->vex > i){
                        edges[index].start  = mVexs[i].data;
                        edges[index].end    = mVexs[node->vex].data;
                        edges[index].weight = node->weight;
                        index ++;
                    }
                    node = node->nextEdge;
                }
            }
            return edges;
        }

        // 对边依据权重大小进行排序 
        // 此处采用　冒泡排序
        void sort_Edge(EData *edges){
            EData temp;
            for(int i = e-1; i > 0; i--){
                for(int j=0; j < i; j++){
                    if(edges[j].weight > edges[j+1].weight){
                        temp = edges[j];
                        edges[j] = edges[j+1];
                        edges[j+1] = temp;
                    }
                }
            }
        }
        
        // 获取节点的'终点'
        int get_End(int vends[], int i){
            while(vends[i] != 0){
                i = vends[i];
            }
            return i;
        }

        // 克鲁斯卡尔算法用于生成最小生成树
        void kruskal(){
            int index = 0;
            EData *all_Edge; // 存放全部的边
            
            int vends[len];    // 保存最小生成树中每个节点的 '终点'
            memset(vends, 0, len);
            
            EData *ret;      // 存放克鲁斯卡尔生成最小生成树的边
            ret = new EData[e-1];

            // 获取图中的边
            all_Edge = get_Edge();

            // 对边依据权重大小进行排序
            sort_Edge(all_Edge);

            for(int i=0; i < e; i++){
                int p1 = get_Node_Index(all_Edge[i].start);
                int p2 = get_Node_Index(all_Edge[i].end);

                int m = get_End(vends, p1);
                int n = get_End(vends, p2);

                if(m != n){
                    vends[m] = n;
                    ret[index++] = all_Edge[i];
                }
            }

            delete[] all_Edge;

            // 统计并打印 kruskal 最小生成树的信息
            int length = 0;
            for(int i = 0; i < index; i++){
                length += ret[i].weight;
            }
            
            for(int i=0; i < index; i++){
                cout<<ret[i].start <<"-" << ret[i].end<<endl;
            }
            cout<<"最小生成树的长度为: "<<length<<endl;
        }
};

int main(){
    Graph g;
    // 输出邻接表
    // g.print();

    g.kruskal();
    return 0;
}
