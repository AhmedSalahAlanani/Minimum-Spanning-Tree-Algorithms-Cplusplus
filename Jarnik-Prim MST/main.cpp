#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;


/// Classes
class Graph
{
    public:
        //Class Functions
        void generate_graph(void);
        void print_graph(void);
        int get_graph_xy(int x, int y);
        int get_graph_size(void);


    private:
       //2-D array of int to represent values of undirected paths
       int **graph;
       int graph_size;

};


///  Function Prototypes
void Jarnik_Prim_MST_Algorithm(Graph graph);
int choose_next_node(Graph graph, vector<int> const visited, int graph_size);
void print_cost(int cost);
void print_tree(vector<int> const visited);



/// Main Entry point
int main()
{
    //Declare a graph object of Class graph
    Graph graph;

    //Generate a graph based on the provided data by the input file
    graph.generate_graph();

    //Print the generated graph to the user
    graph.print_graph();

    //Find the cost for MST and the tree using Jarnik-Prim Algorithm
    Jarnik_Prim_MST_Algorithm(graph);

    return 0;
}


///Functions Implementation
void Graph::generate_graph(void)
{
    //Read input from file "data.txt"
    ifstream datafile("data.txt");
    istream_iterator<int> start(datafile), end;
    vector<int> data(start,end);

    //Read the first number in the file as the size of graph
    graph_size = data[0];

    //Create the 2D graph in heap, and Set the size of the graph to be (size X size) matrix
    graph = new int*[graph_size];

    for(int i=0; i<graph_size; i++)
    {
        graph[i] = new int[graph_size];
    }

    //Initialize all paths to zeros
    for(int i = 0; i<graph_size; i++)
    {
        for(int j = 0; j<graph_size; j++)
        {
            graph[i][j] = 0;
        }
    }

    //Place the path cost between nodes according to data in the graph
    for(int i = 0; i<(data.size()-3); )
    {
        //Fill the remaining Elements
        graph[data[++i]][data[++i]] = data[++i];
    }

}


void Graph::print_graph(void)
{
    //Print message to the User
    cout << "The generated graph is : \n"  << endl;
    for(int i = 0; i<graph_size; i++)
    {
        for(int j = 0; j<graph_size; j++)
        {
            cout << graph[i][j] << " " ;
        }
        cout << "\n" << endl;
    }

}


int Graph::get_graph_xy(int x, int y)
{
    return (graph[x][y]);
}


int Graph::get_graph_size(void)
{
    return graph_size;
}


void Jarnik_Prim_MST_Algorithm(Graph graph)
{
    /// Jarnik_Prim Minimum Spanning Tree Algorithm

    //Start from node zero and initialize cost to zero
    int cost = 0, current_pos = 0, next_pos = 0;

    //Get the graph size
    int graph_size = graph.get_graph_size();

    //Create a vector to hold the visited nodes
    vector<int> visited;

    //Add the chosen node to the visited vector
    visited.push_back(next_pos);

    //start the MST Algorithm
    while( visited.size() < graph_size)
    {
        //Look for the least cost path
        next_pos = choose_next_node(graph,visited,graph_size);

        if(next_pos)
        {
            //Add the chosen node to the visited vector
            visited.push_back(next_pos);

            //Add the cost of the chosen path
            cost += graph.get_graph_xy(current_pos,next_pos);

            //Move to the chosen node
            current_pos = next_pos;
        }
        else
        {
            //There's no move from here
            //Print message to the user
            cout << "The tree of the MST using Jarnik-Prim Algorithm couldn't be completed  " << endl;
            cout << "The cost of the path and the tree so far:  " << endl;

            //Break the while loop and move to the next instruction
            break;
        }
    }

    //print the total cost
    print_cost(cost);

    //print visited
    print_tree(visited);

}


int choose_next_node(Graph graph, vector<int> const visited, int graph_size)
{
    //Initialize to zero
    int least = 0;

    //Initialize the position of least cost node to zero
    int least_pos = 0;

    //Look for path from the open nodes found
    for(int i=0;i< visited.size(); i++)
    {
        for(int j=0, flag_visited=0; j<graph_size; j++)
        {
            //Check there's a path between the two nodes
            if( graph.get_graph_xy(visited[i],j) )
            {
                //check this node wasn't visited before
                for(int k=0; k< visited.size() ;k++)
                {
                    if(j== visited[k])
                    {
                        //raise a flag
                        flag_visited = 1;
                        break;
                    }
                }

                if(flag_visited)
                {
                    flag_visited =0;
                    continue;
                }

                //This code is executed only if the found node wasn't visited before

                //Compare the found value
                if(least)
                {
                    if((graph.get_graph_xy(visited[i],j))< least)
                    {
                        //This means we found a non zero value less than the current least value
                        least = graph.get_graph_xy(visited[i],j);

                        //Store the position of least cost
                        least_pos = j;
                    }
                }
                else
                {
                  //At the beginning, assign least to the first non zero value found
                  least = graph.get_graph_xy(visited[i],j);

                  //Store the position of least cost
                  least_pos = j;
                }
            }
        }

    }

    //Return the found node, otherwise return zero
    return least_pos;
}


void print_cost(int cost)
{
    //Print the cost for MST using Jarnik-Prim Algorithm
    cout << "The Cost of the MST using Jarnik-Prim Algorithm is  " << cost << endl;
}


void print_tree(vector<int> const visited)
{
    //Print the tree for MST using Jarnik-Prim Algorithm
    cout << "The tree of the MST using Jarnik-Prim Algorithm is  " << endl;

     for(int i=0;i< visited.size(); i++)
    {
        cout << visited[i] << " " ;
    }

    //Print empty line at the end
    cout << " " << endl;
}


