#include<iostream>
#include<string.h>
using namespace std;

#define len 100

// �ߵĽṹ��
class EData{
    public:
        char start;  // �ߵ����
        char end;    // �ߵ��յ�
        int weight;  // �ߵ�Ȩ��

        EData(){

        }
        EData(char s, char e, int w){
            start  = s;
            end    = e;
            weight = w;
        }
};

class Graph{
    // �ڲ���
    private:
        // �ڽӱ��б��Ӧ������Ķ���
        class ENode{
            public:
                int vex;         // ����
                int weight;      // Ȩ�� 
                ENode *nextEdge; // ָ����һ����
        };

        // �ڽӱ��б�Ķ���
        class VNode{
            public:
                char data; // ������Ϣ
                ENode *firstEdge; // ָ���һ�������ö���Ļ�
        };

    // ˽�г�Ա
    private:
        int n;              // �ڵ���� 
        int e;              // �ߵĸ���
        VNode mVexs[len];
    
    public:
        Graph(){
            ENode *node1, *node2;
            n = 7; 
            e = 12;

            // ���ýڵ�ΪĬ����ֵ
            string nodes = "ABCDEFG";
            // ����ڵ�
            for(int i=0; i < n; i++){
                mVexs[i].data = nodes[i];
                mVexs[i].firstEdge = NULL;
            }

            // ���ñ�ΪĬ��ֵ
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
            
            // �ߵ�Ȩ��
            int weights[len] = {12, 16, 14, 10, 7, 3, 5, 6, 4, 2, 8, 9};
            
            //����ʼ���ڽӱ�ı�
            for(int i=0; i < e; i++){
                int start = get_Node_Index(edges[i][0]);
                int end = get_Node_Index(edges[i][1]);

                // ��ʼ�� node1
                node1 = new ENode();
                node1->vex = end;
                node1->weight = weights[i];
                node1->nextEdge = NULL;
                // �� node ��ӵ� srart ���������ĩβ
                if(mVexs[start].firstEdge == NULL){
                    mVexs[start].firstEdge = node1;
                }
                else{
                    linkLast(mVexs[start].firstEdge, node1);
                }

                // ��ʼ�� node2
                node2 = new ENode();
                node2->vex = start;
                node2->weight = weights[i];
                node2->nextEdge = NULL;
                // �� node ��ӵ� end ���������ĩβ
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
        
        // ���ض����±�
        int get_Node_Index(char number){
            for(int i=0; i < n; i++){
                if(number == mVexs[i].data){
                    return i;
                }
            }
            return -1; 
        }

        // ����ڽӱ�
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
        
        // ��ȡͼ�еı�
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

        // �Ա�����Ȩ�ش�С�������� 
        // �˴����á�ð������
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
        
        // ��ȡ�ڵ��'�յ�'
        int get_End(int vends[], int i){
            while(vends[i] != 0){
                i = vends[i];
            }
            return i;
        }

        // ��³˹�����㷨����������С������
        void kruskal(){
            int index = 0;
            EData *all_Edge; // ���ȫ���ı�
            
            int vends[len];    // ������С��������ÿ���ڵ�� '�յ�'
            memset(vends, 0, len);
            
            EData *ret;      // ��ſ�³˹����������С�������ı�
            ret = new EData[e-1];

            // ��ȡͼ�еı�
            all_Edge = get_Edge();

            // �Ա�����Ȩ�ش�С��������
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

            // ͳ�Ʋ���ӡ kruskal ��С����������Ϣ
            int length = 0;
            for(int i = 0; i < index; i++){
                length += ret[i].weight;
            }
            
            for(int i=0; i < index; i++){
                cout<<ret[i].start <<"-" << ret[i].end<<endl;
            }
            cout<<"��С�������ĳ���Ϊ: "<<length<<endl;
        }
};

int main(){
    Graph g;
    // ����ڽӱ�
    // g.print();

    g.kruskal();
    return 0;
}
