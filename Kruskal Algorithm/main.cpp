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
void Kruskal_MST_Algorithm(Graph graph);
int find_least_path(Graph graph,vector<int> &visited);
int check_for_visited(int node, vector<int> &visited);
int check_for_visited(int i,int j, vector<int> &visited);
void print_cost(int cost);
void print_tree(int i, int j);


/// Main Entry point
int main()
{
    //Declare a graph object of Class graph
    Graph graph;

    //Generate a graph based on the provided data by the input file
    graph.generate_graph();

    //Print the generated graph to the user
    graph.print_graph();

    //Find the cost for MST and the tree using Kruskal Algorithm
    Kruskal_MST_Algorithm(graph);

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


void Kruskal_MST_Algorithm(Graph graph)
{
    /// Kruskal Minimum Spanning Tree Algorithm

    //Start from node zero and initialize cost to zero
    int cost = 0;

    //Create a vector to hold the visited nodes
    vector<int> visited;

    //start the Kruskal Algorithm
    while( visited.size() < graph.get_graph_size() )
    {
        //Create a Temporary variable to hold the return from find least function
        int temp;

        //Check the returned value is non zero
        if(temp = find_least_path(graph,visited))
        {
            //Accumulate the least cost found to the previous path cost
            cost += temp;
        }
        else
        {
            //There's no move from here
            //Print message to the user
            cout << "The tree of the MST using Kruskal Algorithm couldn't be completed  " << endl;
            cout << "The cost of the path and the tree so far:  " << endl;

            //Break the while loop and move to the next instruction
            break;
        }

    }

    //print the total cost
    print_cost(cost);

}


int find_least_path(Graph graph, vector<int> &visited)
{
    //Initialize least value to zero
    int least = 0;

    //Initialize variables to hold the path represented by nodes on the graph to zero
    int i_pos = 0, j_pos = 0;

    //Look for the least cost path without making loops
    for(int i=0, one_flag=0; (i< graph.get_graph_size())&&(!one_flag) ; i++)
    {
        for(int j=0, flag_visited=0; j<graph.get_graph_size() ; j++)
        {
            //Check there's a path between the two nodes
            if( graph.get_graph_xy(i,j) )
            {
                //check this node wasn't visited before
                if(check_for_visited(i,j,visited))
                {
                   //raise a flag
                    flag_visited = 1;
                    break;
                }

                //If the flag was raised, run the next Iteration
                if(flag_visited)
                {
                    flag_visited =0;
                    continue;
                }

                //This code is executed only if the found path doesn't cause a loop

                //We found the least possible path cost
                if(graph.get_graph_xy(i,j) == 1)
                {
                    //raise a flag
                    one_flag = 1;

                    //Add both nodes to visited vector
                    i_pos = i;
                    j_pos = j;

                    break;
                }

                //Compare the found value
                if(least)
                {
                    if((graph.get_graph_xy(i,j))< least)
                    {
                        //This means we found a non zero value less than the current least value
                        least = graph.get_graph_xy(i,j);

                         //store the position of both nodes
                        i_pos = i;
                        j_pos = j;
                    }
                }
                else
                {
                  //At the beginning, assign least to the first non zero value found
                  least = graph.get_graph_xy(i,j);

                  //store the position of both nodes
                    i_pos = i;
                    j_pos = j;

                }
            }
        }

    }

    //Add both nodes to visited vector and check they are unique
    if(!check_for_visited(i_pos,visited))
    {
        //This means this node doesn't exist in the visited
        visited.push_back(i_pos);
    }

    if(!check_for_visited(j_pos,visited))
    {
        //This means this node doesn't exist in the visited
        visited.push_back(j_pos);
    }


    //Print the chosen path
    print_tree(i_pos,j_pos);

    //Return the least value found
    return (graph.get_graph_xy(i_pos,j_pos));
}


int check_for_visited(int node, vector<int> &visited)
{
    //Initialize the flag to be zero
    int flag =0;

    //Search for the given node in the visited nodes
    for(int i=0; i<visited.size(); i++)
    {
        if(node == visited[i])
        {
            //raise the flag and return
            flag = 1;
            break;
        }
    }

   return flag;
}


int check_for_visited(int i,int j, vector<int> &visited)
{
    //Initialize the flag to be zero
    int flag =0;

    //Search for the first node in the visited nodes
    for(int k=0; (k< visited.size())&&(!flag) ;k++)
    {
        if(i == visited[k])
        {
            //This means the first node was found
            for(int p=0; p< visited.size() ;p++)
            {
                //Search the next node
                if(j == visited[p])
                {
                    //Both nodes were found
                    flag =1;
                    break;
                }
            }
        }
    }

   return flag;
}


void print_cost(int cost)
{
    //Print the cost for MST using Kruskal Algorithm
    cout << "\nThe Cost of the MST using Kruskal Algorithm is  " << cost << endl;
}


void print_tree(int i, int j)
{
    //Declare a flag at the beginning
    static int flag = 1;

    //Print the tree for MST using Kruskal Algorithm
    if(flag)
    {
        cout << "The tree of the MST using Kruskal Algorithm is  " << endl;

        //Reset the flag
        flag = 0;
    }

    //print the given path
    cout << "(" << i << "," << j << ")" << endl;

}


