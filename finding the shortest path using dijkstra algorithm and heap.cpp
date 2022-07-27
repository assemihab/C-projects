#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;

struct Node
{
    char label;
    int cost;
};
class MinHeap
{
    //heap of nodes in form of array and it's size;
    Node* heap;
    int _size;
public:
    Node extractMin()
    {
        Node smallest=heap[0];
        heap[0]=heap[_size-1];
        _size--;
        minHeapify(0,_size);
        return smallest;

    }

    void buildMinHeap(Node*arr,int Size)
    {
        heap=arr;
        _size=Size;
        for(int i=(Size/2)-1;i>=0;i--)
        {
            minHeapify(i,_size);
        }
    }
    void minHeapify(int i, int n)
    {
        int smallest=i;
        int left=(i*2)+1;
        int right=(i*2)+2;

        //check if the element on the left smaller than parent
        if(left<n&&heap[left].cost<heap[smallest].cost)
            smallest=left;

        if(right<n&&heap[right].cost<heap[smallest].cost)
            smallest=right;
        if(smallest==i)
            return;
        Node temp=heap[i];
        heap[i]=heap[smallest];
        heap[smallest]=temp;
        minHeapify(smallest,n);
        //make a reverse heapify function
    }
    bool decreaseKey(char lab, int newCost)
    {
        int i;
        for(i=0;i<_size;i++)
        {
            if(heap[i].label==lab)
            {
                if(heap[i].cost>newCost)
                {
                    heap[i].cost=newCost;
                    break;
                }
                else
                    return false;

            }
        }
        while(i!=0&&heap[parent(i)].cost>heap[i].cost)
        {
            Node temp=heap[parent(i)];
            heap[parent(i)]=heap[i];
            heap[i]=temp;
            i=parent(i);
        }
        return true;
    }
    int parent(int i)
    {
            return (i-1)/2;

    }
    int getSize()
    {
        return _size;
    }
    bool inHeap(char lab)
    {
        for(int i=0;i<_size;i++)
            if(heap[i].label==lab)
                return true;
        return false;
    }
    void printHeap()
    {
        for(int i=0;i<_size;i++)
        {
            cout<<"\nThe "<<i<<" element of the heap label: "<<heap[i].label;
            cout<<"\nThe cost: "<<heap[i].cost;
        }
    }
    bool isEmpty()
    {
        if(_size==0)
            return true;
        else  return false;
    }

};

class WeightedGraph
{
    int **g;
    int nVertices;

public:
    int getNVertices()
    {
        return nVertices;
    }
    int getWeight(char row,char col)
    {
        return g[convertCharToInt(row)][convertCharToInt(col)];
    }
    int*returnNeighbors(int v)
    {
        int counter=0;
        for(int i=0;i<nVertices;i++)
        {
            if(g[v][i])
                counter++;
        }
        int arr[counter];
        int it=0;
        for(int i=0;i<nVertices;i++)
        {
            if(g[v][i])
            {
                arr[it]=i;
                it++;
            }
        }
        return arr;
    }
    int numNeighbors(int v)
    {
        int counter=0;
        for(int i=0;i<nVertices;i++)
        {
            if(g[v][i])
                counter++;
        }
        return counter;
    }
    int convertCharToInt(char k)
    {
        int j =int(k-97);
        return j;
    }
    char convertIntTochar(int j)
    {
        char c= j+97;
        return c;
    }
    void loadGraphFromFile(ifstream& ifile)
    {
int nEdges , weight;
    char v1,v2;
    ifile>>nVertices>>nEdges;

    g = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
        g[i] = new int[nVertices];
    for(int i=0;i<nVertices;i++)
        for(int j=0;j<nVertices;j++)
            g[i][j] = 0;

    for(int i=0;i<nEdges;i++)
    {
        ifile>>v1>>v2>>weight;
        g[convertCharToInt(v1)][convertCharToInt(v2)] = weight;
        //g[charToIndex(v2)][charToIndex(v1)] = weight;
    }
    /*for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
            cout<<g[i][j]<<"\t";
        cout<<endl;
    }*/

    }
    void dijkstra(char startVertex,char*prev,Node*distances)
    {
        bool visited[nVertices]={0};
        MinHeap minValues;
        prev[convertCharToInt(startVertex)]=startVertex;
        Node* arrNodes=new Node[nVertices];
        for(int i=0;i<nVertices;i++)
        {
            distances[i].label=convertIntTochar(i);
            if(i==convertCharToInt(startVertex))
                distances[i].cost=0;
            else
                distances[i].cost=INT_MAX;
        }
        for(int i=0;i<nVertices;i++)
        {
            arrNodes[i]=distances[i];
        }
        minValues.buildMinHeap(arrNodes,nVertices);
        int i=0;
        while(!minValues.isEmpty())
        {
            Node U=minValues.extractMin();
            visited[convertCharToInt(U.label)]=true;
            for(int j=0;j<nVertices;j++)
            {
                if(g[convertCharToInt(U.label)][j]!=0&&!visited[j])
                {

                    char a=convertIntTochar(j);
                    int newc=U.cost+g[U.label-97][j];
                    bool status=minValues.decreaseKey(a,newc);
                    if(status)
                    {
                        prev[j]= U.label;
                        distances[j].cost=U.cost+g[U.label-97][j];
                    }
                }
            }
            i++;
        }

    }
};

int main()
{
     WeightedGraph wg;
     ifstream ifile("graph.txt");
     wg.loadGraphFromFile(ifile);
     char* p;
     p = new char[wg.getNVertices()];
     Node* n;
     n=new Node[wg.getNVertices()];
     wg.dijkstra('g',p,n);
     cout<<endl<<"Node\tCost\tPrevious";
     for(int i=0;i<wg.getNVertices();i++)
     {
     cout<<endl<<n[i].label<<"\t"<<n[i].cost<<"\t"<<p[i];
     }
     ifile.close();

     return 0;
}
