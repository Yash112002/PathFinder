#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vector<int>>
#define rep(i, a, b) for (int i = a; i < b; i++)
const int N = 1e3 + 2;
//***************************showing all the available destination in a particular location***********************************************
void BFS(int n, int m, vvi &edges, vector<string> &location_name)
{
    bool vis[N] = {0};
    vi v[N];
    rep(i, 0, m)
    {
        int x = edges[i][0];
        int y = edges[i][1];
        v[x].push_back(y);
        v[y].push_back(x);
    }
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << "||" << location_name[node] << "||   ";
        vi ::iterator it;
        for (it = v[node].begin(); it != v[node].end(); it++)
        {
            if (!vis[*it])
            {
                q.push(*it);
                vis[*it] = 1;
            }
        }
    }
}
//****************************************************************************************************************************************

// ****************************************choice 1***************************************************************************************
// Infinite value for array
const int INF = 1e7;
int dis[N][N];
int Next[N][N];
int cost = 0;
void initialise(int V, vector<vector<int>> &graph)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            dis[i][j] = graph[i][j];

            // No edge between node
            // i and j
            if (graph[i][j] == INF)
                Next[i][j] = -1;
            else
                Next[i][j] = j;
        }
    }
}
vector<int> constructPath(int u, int v)
{
    // If there's no path between
    // node u and v, simply return
    // an empty array
    if (Next[u][v] == -1)
        return {};

    // Storing the path in a vector
    vector<int> path = {u};
    while (u != v)
    {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}
void floydWarshall(int V)
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                // We cannot travel through
                // edge that doesn't exist
                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;

                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
}
void printPath(vector<int> &path, vector<string> &location_name)
{
    int n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << location_name[path[i]] << " ---> ";
    cout << location_name[path[n - 1]] << endl;
}
int calculate_cost(vi &path, vvi &graph)
{
    rep(i, 0, path.size() - 1)
    {
        int a, b;
        a = path[i];
        b = path[i + 1];
        cost += graph[a][b];
    }
    return cost;
}
void shortest_path_to_dest(int n, int m, vvi &edges, int src, int dest, vector<string> &location_name)
{
    cost = 0;
    if (src == dest)
    {
        cout << "\n**you are on ur destination location!\n"
             << endl;
        return;
    }
    vvi graph(n, vi(n, INF));
    rep(i, 0, m)
    {
        int u, v, w;
        u = edges[i][0];
        v = edges[i][1];
        w = edges[i][2];
        graph[u][v] = w;
        graph[v][u] = w;
    }
    // Function to initialise the
    // distance and Next array
    initialise(n, graph);
    // Calling Floyd Warshall Algorithm,
    // this will update the shortest
    // distance as well as Next array
    floydWarshall(n);
    vector<int> path;
    // Path from node src to dest
    cout << "\n**Shortest path from " << src << " to " << dest << " : \n"
         << endl;
    path = constructPath(src, dest);
    printPath(path, location_name);
    int cost = calculate_cost(path, graph);
    cout << "\n**total distance travel : " << cost << "\n"
         << endl;
}
// ***************************************************************************************************************************************

//************************************************************choice 3********************************************************************
list<int> *adj;

void printAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index, vector<string> &location_name)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
        for (int i = 0; i < path_index - 1; i++)
            cout << location_name[path[i]] << " ---> ";
        cout << location_name[path[path_index - 1]] << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index, location_name);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}
void print_all_path(int src, int dest, int n, vector<string> &location_name)
{
    bool *vis = new bool[n];
    int *path = new int[n];
    int path_index = 0;
    for (int i = 0; i < n; i++)
    {
        vis[i] = false;
    }
    printAllPathsUtil(src, dest, vis, path, path_index, location_name);
}
void print_all_path_to_dest_node(int n, int m, vvi &edges, int src, int dest, vector<string> &location_name)
{
    adj = new list<int>[n];
    rep(i, 0, m)
    {
        int u, v;
        u = edges[i][0];
        v = edges[i][1];
        adj[u].push_back(v); // Add v to u’s list.
        adj[v].push_back(u); // Add v to u’s list.
    }
    print_all_path(src, dest, n, location_name);
}

//******************************************choice 2**************************************************************************************

void primsMST(int n, int m, int src, vvi &edges, vector<string> &location_name)
{
    vvi g[N];
    cost = 0;
    vi dist(N), parent(N), vis(N);
    const int INF = 1e9;
    rep(i, 0, n)
    {
        dist[i] = INF;
    }
    rep(i, 0, m)
    {
        int u, v, w;
        u = edges[i][0];
        v = edges[i][1];
        w = edges[i][2];
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    set<vi> s;
    dist[src] = 0;
    s.insert({0, src});
    //{wt,vertex}
    int i = 0;
    while (!s.empty())
    {
        auto x = *(s.begin());
        s.erase(x);
        vis[x[1]] = true;
        int u = parent[x[1]];
        int v = x[1];
        int w = x[0];
        if (i != 0)
            cout << "\n**from " << location_name[u] << " ---> " << location_name[v] << " by distance " << w << " KM" << endl;
        cost += w;
        for (auto it : g[x[1]])
        {
            if (vis[it[0]])
            {
                continue;
            }
            if (dist[it[0]] > it[1])
            {
                s.erase({dist[it[0]], it[0]});
                dist[it[0]] = it[1];
                s.insert({dist[it[0]], it[0]});
                parent[it[0]] = x[1];
            }
        }
        i++;
    }
    cout << "\n**Minimun total distance covered will be : " << cost << "\n"
         << endl;
}

//***********************************************register/login***************************************************************************
void Register_Login()
{
    cout << "\n\n*********************Welcome to Path Finder*********************\n" // greeting
         << endl;
    // registering or login for the students or the teacher
    int choice, n = 1;
    string name, password,
        inName, inPassword,
        registerName, registerPassword;

    while (n == 1) // running the code untill it will login or register successfully
    {
        cout << "1.Register\n2.Login\n3.terminate\n"
             << "Enter Choice(1 for register, 2 for login, 3 for terminate): ";
        cin >> choice;
        if (choice == 1)
        {
            ofstream g("Login_credentials.txt", std::fstream::app); // creating a file for storing the data of logincredential for the future refernce
            fflush(stdin);
            // pushing all the data in the text file accordingly to register
            cout << "\n\n"
                 << "New Username: ";
            getline(cin, registerName);
            cout << "New Password: ";
            getline(cin, registerPassword);
            g << registerName;
            g << '\n';
            g << registerPassword;
            g << '\n';
            cout << "Successfully Registered!!, Now Please Login" << endl;
            g.close();
        }
        else if (choice == 2)
        {
            while (1)
            {
                ifstream f("Login_credentials.txt");
                fflush(stdin);
                // taking the input for the login credentials
                cout << "\n\n"
                     << "Enter Username: ";
                getline(cin, inName);
                cout << "Enter Password: ";
                getline(cin, inPassword);
                // after taking the input checking with the lohin credentials available in the text file, if it matches will continue the program else repeat asking login or register
                while (!f.eof())
                {
                    // checking line by line
                    getline(f, name, '\n');
                    getline(f, password, '\n');
                    if (inName == name && inPassword == password)
                    {
                        n = 2;
                        break;
                    }
                }
                if (n == 2)
                {
                    cout << "Login Successful\n"
                         << "Welcome, " << inName;
                    break;
                }
                cout << "Incorrect Credentials, please try again" << endl;
                // closing the opened file
                f.close();
            }
        }
        else if (choice == 3)
        {
            exit(0);
        }
        else
        {
            cout << "invalid input!\n";
        }
        cout << "\n\n\n\n";
    }
}
//****************************************************************************************************************************************

//***************************************************driver code**************************************************************************
int main()
{
    Register_Login();
    int n, m, choice, src, dest, petrol, petrol_pump;
    vector<vector<int>> edges(N);
    vector<string> location_name;
    cout << "\n**For now, We have only few locations which are following :\n"
         << endl;
    while (1)
    {
        cout << ">>Choose your current location :\n";
        cout << "\n1.Kirari\n2.Adhyapak Nagar\n3.Najafgarh\n4.North Delhi\n5.terminate the program\n(enter locations as e.g. 1 for location A)\n";
        cout << "\n>>Enter the Choice : ";
        cin >> choice;
        if (choice == 1)
        {
            n = 5, m = 6;
            edges = {{0, 1, 11}, {1, 2, 3}, {1, 3, 1}, {2, 3, 4}, {3, 4, 5}, {4, 0, 8}};
            location_name = {"0.Qamaruddin Nagar", "1.Nangloi", "2.Miyanwali", "3.Mundka", "4.Petrol Pump"};
            petrol_pump = 4;
        }
        else if (choice == 2)
        {
            n = 6, m = 9;
            edges = {{0, 1, 1}, {1, 2, 4}, {2, 3, 7}, {3, 4, 2}, {4, 5, 8}, {5, 0, 11}, {0, 4, 9}, {1, 5, 2}, {2, 5, 6}};
            location_name = {"0.Prem Nagar", "1.Pooth kalan", "2.Begum Pur", "3.Petrol Pump", "4.Kanjhawala", "5.Madan Pur"};
            petrol_pump = 3;
        }
        else if (choice == 3)
        {
            n = 8, m = 10;
            edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 8}, {3, 4, 4}, {4, 5, 6}, {0, 5, 3}, {5, 6, 9}, {2, 6, 2}, {2, 7, 5}, {7, 4, 4}};
            location_name = {"0.Daulat Pur", "1.Bawana", "2.Rithala", "3.NSP", "4.Rohini sect 21", "5.Shabad dairy", "6.rohini sect 23", "7.Petrol Pump"};
            petrol_pump = 7;
        }
        else if (choice == 4)
        {
            n = 5, m = 6;
            edges = {{0, 1, 7}, {1, 2, 9}, {2, 3, 2}, {3, 0, 3}, {4, 3, 1}, {1, 4, 5}};
            location_name = {"0.Peera Garhi", "1.Pachim Vihar", "2.Petrol Pump", "3.Indralok", "4.Keshav Puram"};
            petrol_pump = 2;
        }
        else if (choice == 5)
        {
            cout << "\n******************Thanks for using our service********************\n";
            exit(0);
        }
        else
        {
            cout << "\nSorry!!!, no such location availalble right now...\nkindly choose from the options...\n"
                 << endl;
            continue;
        }
        cout << "\n\n**We have different destinations in location with their pincode, which are following :\n\n"
             << endl;
        BFS(n, m, edges, location_name);
        break;
    }
    cout << "\n\nWe have different functionality in this location which are following :\n\n";
    char ch = 'y';
    while (ch == 'y' || ch == 'Y')
    {
        cout << "\n1.shortest path to a partricular node\n2.shortest path to the all nodes of the graph\n3.show all paths to destination node\n4.limited petrol\n5.nearest petrol pump\n6.multiple location with priority\n7.previous data\n8.terminate\n(enter the choice in numbers e.g 1 for choice 1)\n";
        cout << "\n>>enter the choice : ";
        cin >> choice;
        if (choice == 8)
        {
            cout << "\n****************Thanks for using our service******************\n";
            exit(0);
        }
        cout << "\n>>enter the your initial pos : ";
        cin >> src;
        if (src > n - 1)
        {
            cout << "\ninvalid initial position!\n"
                 << endl;
            continue;
        }
        if (choice == 1)
        {
            cout << "\n**You choose option 1...\n";
            cout << "\n>>enter the destination : ";
            cin >> dest;
            if (dest > n - 1)
            {
                cout << "\ninvalid destination position!\n"
                     << endl;
                continue;
            }
            cout << "\n**the travelling path for your destination is following : \n"
                 << endl;
            shortest_path_to_dest(n, m, edges, src, dest, location_name);
        }
        else if (choice == 2)
        {
            cout << "\nYou choose option 2...\n";
            cout << "\n**Shortest path to all the nodes are : \n"
                 << endl;
            primsMST(n, m, src, edges, location_name);
        }
        else if (choice == 3)
        {
            cout << "\nYou choose option 3...\n";
            cout << "\n>>enter the destination : ";
            cin >> dest;
            if (dest > n - 1)
            {
                cout << "\ninvalid destination position!\n"
                     << endl;
                continue;
            }
            cout << "\n**All available path from initial position to the final position : \n"
                 << endl;
            print_all_path_to_dest_node(n, m, edges, src, dest, location_name);
        }
        else if (choice == 4)
        {
            cout << "\nYou choose option 4...\n";
            cout << "\n>>enter the destination : ";
            cin >> dest;
            if (dest > n - 1)
            {
                cout << "\ninvalid destination position!\n"
                     << endl;
                continue;
            }
            cout << "\n>>enter the amount of petrol : ";
            cin >> petrol;
            int dis = petrol * 5;
            shortest_path_to_dest(n, m, edges, src, dest, location_name);
            if (cost > dis)
            {
                cout << "\nno path available to travel the path according to ur need!!!";
            }
        }
        else if (choice == 5)
        {
            cout << "\nYou choose option 5...\n"
                 << endl;
            cout << "\nnearest petrol pump from ur location is : \n"
                 << endl;
            shortest_path_to_dest(n, m, edges, src, petrol_pump, location_name);
        }
        else if (choice == 6)
        {
            cout << "\nYou choose option 6...\n";
            while (ch == 'y' || ch == 'Y')
            {
                cout << "\n>>enter the destination from your current location : ";
                cin >> dest;
                if (dest > n - 1 || src > n - 1)
                {
                    cout << "\ninvalid destination or initial position!!!\n"
                         << endl;
                }
                else
                {
                    // cout << "\nshortest path to the dest is : ";
                    shortest_path_to_dest(n, m, edges, src, dest, location_name);
                    src = dest;
                }
                cout << "\n>>Do you want to continue in this location : (enter y or Y for continue or any other key for termination)\n";
                cin >> ch;
            }
        }
        else if (choice == 7)
        {
            cout << "\nprevious data";
        }
        else
        {
            cout << "Sorry!, no funcyionality matches with ur input...";
        }
        cout << "\n>>Do you want to continue the program : (enter y or Y for continue or any other key for termination) : ";
        cin >> ch;
    }
    return 0;
}