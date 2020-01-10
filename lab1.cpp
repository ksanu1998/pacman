// CPP program to print the largest 
// connected component in a grid 
#include <iostream> 
#include <queue> 
#include <vector>
#include<stack>
using namespace std; 
/*
const int n = 5; 
const int m = 13; 
*/
//const int n = 9; 
//const int m = 13; 
int **input;
int **final_path;
//int result[n][m];
//int visited[n][m];
//int final_path[n][m];
//int final_path_DFS[n][m];
//int pacman[n][m];
int states_explored = 0;
// stores the count of cells in the largest 
// connected component 
int COUNT; 

struct Point 
{ 
    int x; 
    int y; 
}; 
  
// A Data Structure for queue used in BFS 
struct queueNode 
{ 
    Point pt;  // The cordinates of a cell 
    int dist;  // cell's distance of from the source
    queueNode* pptr; 
}; 
   
bool isValid(int row, int col, int n, int m) 
{ 
    // return true if row number and column number 
    // is in range 
    return (row >= 0) && (row < n) && 
           (col >= 0) && (col < m); 
} 
  
// These arrays are used to get row and column 
// numbers of 4 neighbours of a given cell 
int rowNum[] = {-1, 0, 0, 1}; 
int colNum[] = {0, -1, 1, 0}; 

int final_DFIS(int** mat, int n, int m, Point src, Point dest, int limit) 
{ 
    int depth = 1;
    states_explored=0;
    // check source and destination cell 
    // of the matrix have value 1 
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y]) 
        return -1; 
  
    bool visited[n][m]; 
    memset(visited, false, sizeof visited); 
    // Mark the source cell as visited 
    visited[src.x][src.y] = true; 
  
    // Create a queue for BFS 
    //vector <queueNode*> q; 
    stack <queueNode*> q; 
      
    // Distance of source cell is 0 
    queueNode* s = new queueNode;
    s->pt.x = src.x;
    s->pt.y = src.y;
    s->dist = 0;
    s->pptr = NULL;
    //q.push_back(s);  // Enqueue source cell 
    q.push(s);
    // Do a BFS starting from source cell 

    while (!q.empty() && (depth<=limit)) 
    { 
        states_explored++;
        //queueNode* curr = q.back(); 
        queueNode* curr = q.top(); 
        Point pt = curr->pt; 

        if (pt.x == dest.x && pt.y == dest.y) 
        {
            queueNode* root = curr;
            while(root->pptr!=NULL)
            {
                final_path[root->pt.x][root->pt.y]=1;
                root = root->pptr;
            }
            final_path[root->pt.x][root->pt.y]=1;
            return curr->dist; 
        }
  
        // Otherwise dequeue the front cell in the queue 
        // and enqueue its adjacent cells 
        //q.pop_back(); 
        q.pop(); 
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.x + rowNum[i]; 
            int col = pt.y + colNum[i]; 
              
            // if adjacent cell is valid, has path and 
            // not visited yet, enqueue it. 
            if (isValid(row, col, n, m) && mat[row][col] &&  
               !visited[row][col]) 
            { 
                // mark cell as visited and enqueue it 
                visited[row][col] = true; 
                queueNode* Adjcell = new queueNode;
                Adjcell->pt.x = row;
                Adjcell->pt.y = col;
                Adjcell->dist = curr->dist + 1;
                Adjcell->pptr = curr;
                //q.push_back(Adjcell); 
                q.push(Adjcell); 
            } 
        } 
        depth++;
    } 
  
    // Return -1 if destination cannot be reached 
    return -1; 
} 
int final_DFS(int** mat, int n, int m, Point src, Point dest) 
{ 
	states_explored=0;
    // check source and destination cell 
    // of the matrix have value 1 
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y]) 
        return -1; 
  
    bool visited[n][m]; 
    memset(visited, false, sizeof visited); 
    // Mark the source cell as visited 
    visited[src.x][src.y] = true; 
  
    // Create a queue for BFS 
    //vector <queueNode*> q; 
    stack <queueNode*> q; 
      
    // Distance of source cell is 0 
    queueNode* s = new queueNode;
    s->pt.x = src.x;
    s->pt.y = src.y;
    s->dist = 0;
    s->pptr = NULL;
   	//q.push_back(s);  // Enqueue source cell 
   	q.push(s);
    // Do a BFS starting from source cell 

    while (!q.empty()) 
    { 
    	states_explored++;
        //queueNode* curr = q.back(); 
        queueNode* curr = q.top(); 
        Point pt = curr->pt; 

        if (pt.x == dest.x && pt.y == dest.y) 
        {
        	queueNode* root = curr;
        	while(root->pptr!=NULL)
        	{
        		final_path[root->pt.x][root->pt.y]=1;
        		root = root->pptr;
        	}
        	final_path[root->pt.x][root->pt.y]=1;
            return curr->dist; 
        }
  
        // Otherwise dequeue the front cell in the queue 
        // and enqueue its adjacent cells 
        //q.pop_back(); 
        q.pop(); 
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.x + rowNum[i]; 
            int col = pt.y + colNum[i]; 
              
            // if adjacent cell is valid, has path and 
            // not visited yet, enqueue it. 
            if (isValid(row, col, n, m) && mat[row][col] &&  
               !visited[row][col]) 
            { 
                // mark cell as visited and enqueue it 
                visited[row][col] = true; 
                queueNode* Adjcell = new queueNode;
                Adjcell->pt.x = row;
                Adjcell->pt.y = col;
                Adjcell->dist = curr->dist + 1;
                Adjcell->pptr = curr;
                //q.push_back(Adjcell); 
                q.push(Adjcell); 
            } 
        } 
    } 
    // Return -1 if destination cannot be reached 
    return -1; 
} 

// function to find the shortest path between 
// a given source cell to a destination cell. 
int final_BFS(int** mat, int n, int m, Point src, Point dest) 
{ 
	states_explored=0;
    // check source and destination cell 
    // of the matrix have value 1 
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y]) 
        return -1; 
  
    bool visited[n][m]; 
    memset(visited, false, sizeof visited); 
    // Mark the source cell as visited 
    visited[src.x][src.y] = true; 
  	//cout<<"came 1"<<endl;
    // Create a queue for BFS 
    queue <queueNode*> q; 
      
    // Distance of source cell is 0 
    queueNode* s = new queueNode;
    s->pt.x = src.x;
    s->pt.y = src.y;
    s->dist = 0;
    s->pptr = NULL;
    q.push(s);  // Enqueue source cell 
    // Do a BFS starting from source cell 
	//cout<<"came 2"<<endl;
    while (!q.empty()) 
    { 
    	states_explored++;
        queueNode* curr = q.front(); 
        Point pt = curr->pt; 

        if (pt.x == dest.x && pt.y == dest.y) 
        {
        	queueNode* root = curr;
        	while(root->pptr!=NULL)
        	{
        		final_path[root->pt.x][root->pt.y]=1;
        		root = root->pptr;
        	}
        	final_path[root->pt.x][root->pt.y]=1;
            return curr->dist; 
        }
  
        // Otherwise dequeue the front cell in the queue 
        // and enqueue its adjacent cells 
        q.pop(); 
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = pt.x + rowNum[i]; 
            int col = pt.y + colNum[i]; 
              
            // if adjacent cell is valid, has path and 
            // not visited yet, enqueue it. 
            if (isValid(row, col, n, m) && mat[row][col] &&  
               !visited[row][col]) 
            { 
                // mark cell as visited and enqueue it 
                visited[row][col] = true; 
                queueNode* Adjcell = new queueNode;
                Adjcell->pt.x = row;
                Adjcell->pt.y = col;
                Adjcell->dist = curr->dist + 1;
                Adjcell->pptr = curr;
                q.push(Adjcell); 
            } 
        } 
    } 
  //cout<<"came 3"<<endl;
    // Return -1 if destination cannot be reached 
    return -1; 
} 

int main()
{ 	
    int mode;
    int n, m;
    int counter = 0;
    bool flag = true;
    int dest_x, dest_y;
    vector<string>store;
    vector<char>maze;
    cin>>mode;
    while (1) {
        string s;
        string l;
        if (flag == true) {
            l = "1";
            flag = false;
        }
        getline(cin, s);
        //cout<<s.size()<<endl;
        if ((s == "quit") || (s == "exit")) {
            exit(0);
        }
        //cout << "String: " << s << endl;
        //cout << "String Size: " << s.size() << endl;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (isblank(c)) {
                l += "1";
                store.push_back("1");
                maze.push_back(s[i]);
                //cout << "Found" << endl;
                //l.append("1", 1);
            }
            else if (c == '*') {
                l += "*";
                 store.push_back("*");
                 maze.push_back(s[i]);
                 dest_x = counter-1;
                 dest_y = i;
                //l.append("0", 1);
            }
            else if (c == '-'){
                l += "0";
                 store.push_back("0");
                 maze.push_back(s[i]);
            }
            else if (c == '|'){
                l += "0";
                 store.push_back("0");
                 maze.push_back(s[i]);
            }
            else
            {
            	l += "0";
                 store.push_back("0");
                 maze.push_back(s[i]);
            }
        } 
        	
        //cout << "Line Converted: " << l << endl;
        bool is_end = true;
        //bool break_while = false;
        for(int i = 0; i < s.size(); i++)
        {
            if(l[i]!='0')
            {
                is_end=false;
                break;
            }
        }
        //cout<<is_end<<" "<<counter<<endl;
        if(is_end && counter>1)
        {
            m = s.size();
            break;
        }
        counter++;
    }
    n = counter;
    input = new int *[m];
    final_path = new int *[m];
    store[0]="1";
    /*
    int temp1 = 0;
        for(int i=0;i<n;i++)
        {
        	for(int j=0;j<m;j++)
        	{
        		cout<<maze[temp1]<<" ";
        		temp1++;
        	}
        	cout<<endl;
        }
    */
    for(int i = 0; i <n; i++)
    {
    	input[i] = new int[m];
    }
    for(int i = 0; i <n; i++)
    {
    	final_path[i] = new int[m];
    }
    int feed = 0;
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<m;j++)
       {
            if(store[feed]=="1" || store[feed]=="*")
            {
            	//cout<<"came 0"<<endl;
                input[i][j]=1;
                //cout<<"came 00"<<endl;
            }
            else
            {
                input[i][j]=0;
            }
            feed++;
       }
    }
    /*
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<m;j++)
       {
            cout<<input[i][j]<<" ";
       }
       cout<<endl;
    }
    */
    input[0][0]=1;
    input[dest_x][dest_y]=1;
    //cout<<dest_x<<" "<<dest_y<<endl;
	Point source = {0, 0}; 
    /* Point dest = {4, 12}; */
    Point dest = {dest_x, dest_y};
    /*
    node* root = new node;
    root->x= 0;
    root->y=0;
    */
    //process source and destination
    int dist;
    if(mode == 0)
    {
    	dist = final_BFS(input, n, m, source, dest); 
    }
    else if(mode == 1)
    {
    	dist = final_DFS(input, n, m, source, dest); 
    }
    else if(mode == 2)
    {
        int limit = 1;
        while(true)
        {
            dist = final_DFIS(input, n, m, source, dest, limit);
            if(dist == -1)
            {
                limit++;
            }
            else
            {
                break;
            }
        }
    }
    //int dist = final_BFS(input, source, dest); 
    //int dist_DFS = final_DFS(input, source, dest); 
    cout/*<<"Number of states explored: "*/<<states_explored<<endl;
    if (dist != INT_MAX) 
        cout /* << "Length of path found: " */ << dist+1<<endl; 
    else
        cout /*<< "Shortest Path doesn't exist"*/<<-1<<endl; 
    
    int temp = 0; 
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    	{
    		if(final_path[i][j]==1)
    			cout<<0;
    		else
    			cout<<maze[temp];
    		temp++;
    	}
    	cout<<endl;
    }
    
	return 0; 
} 

