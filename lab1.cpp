// CPP program to print the largest 
// connected component in a grid 
#include <iostream> 
#include <queue> 
#include <vector>
#include<stack>
using namespace std; 

const int n = 5; 
const int m = 13; 

int result[n][m];
int visited[n][m];
int final_path[n][m];
int final_path_DFS[n][m];
int pacman[n][m];
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
   
bool isValid(int row, int col) 
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

int final_DFS(int mat[][m], Point src, Point dest) 
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
            if (isValid(row, col) && mat[row][col] &&  
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
int final_BFS(int mat[][m], Point src, Point dest) 
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
    queue <queueNode*> q; 
      
    // Distance of source cell is 0 
    queueNode* s = new queueNode;
    s->pt.x = src.x;
    s->pt.y = src.y;
    s->dist = 0;
    s->pptr = NULL;
    q.push(s);  // Enqueue source cell 
    // Do a BFS starting from source cell 

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
            if (isValid(row, col) && mat[row][col] &&  
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
  
    // Return -1 if destination cannot be reached 
    return -1; 
} 

int main() 
{ 	int mode;
	cin>>mode;
	int input[n][m] = { {1,0,0,0,0,0,0,0,0,0,0,0,0}, 
						{1,1,1,0,1,1,1,1,1,0,1,1,0}, 
						{0,1,1,0,1,1,0,1,1,0,1,1,0},  
						{0,1,1,1,1,1,0,1,1,1,1,1,0}, 
						{0,0,1,1,0,0,0,0,0,0,0,1,1}}; 

	// function to compute the largest 
	// connected component in the grid 
	//computeLargestConnectedGrid(input); 

	Point source = {0, 0}; 
    Point dest = {4, 12}; 
    /*
    node* root = new node;
    root->x= 0;
    root->y=0;
    */
    //process source and destination
    int dist;
    if(mode == 0)
    {
    	dist = final_BFS(input, source, dest); 
    }
    else if(mode == 1)
    {
    	dist = final_DFS(input, source, dest); 
    }
    //int dist = final_BFS(input, source, dest); 
    //int dist_DFS = final_DFS(input, source, dest); 
  
    if (dist != INT_MAX) 
        cout << "Length of path found: " << dist<<endl; 
    else
        cout << "Shortest Path doesn't exist"; 
    cout<<"Number of states explored: "<<states_explored<<endl;
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    	{
    		if(final_path[i][j]==1)
    			cout<<1<<" ";
    		else
    			cout<<0<<" ";
    	}
    	cout<<endl;
    }
	return 0; 
} 

