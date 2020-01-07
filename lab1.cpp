// CPP program to print the largest 
// connected component in a grid 
#include <iostream> 
#include <queue> 
#include <vector>
using namespace std; 

const int n = 5; 
const int m = 13; 
struct node
{
	int x;
	int y;
	node* pptr;
	node* nptr;
};
// stores information about which cell 
// are already visited in a particular BFS 
vector<int>x_path;
vector<int>y_path;
// result stores the final result grid 
int result[n][m];
int visited[n][m];
int final_path[n][m];
int pacman[n][m];
int states_explored = 0;
// stores the count of cells in the largest 
// connected component 
int COUNT; 

// Function checks if a cell is valid i.e it 
// is inside the grid and equal to the key 
/*
bool is_valid(int x, int y, int key, int input[n][m]) 
{ 
	if (x < n && y < m && x >= 0 && y >= 0) { 
		if (visited[x][y] == false && input[x][y] == key) 
			return true; 
		else
			return false; 
	} 
	else
		return false; 
} 
*/
//To store matrix cell cordinates 
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
}; 
  
// check whether given cell (row, col) is a valid 
// cell or not. 
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


// function to find the shortest path between 
// a given source cell to a destination cell. 
int final_BFS(int mat[][m], Point src, Point dest, node* root) 
{ 
    // check source and destination cell 
    // of the matrix have value 1 
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y]) 
        return -1; 
  
    bool visited[n][m]; 
    memset(visited, false, sizeof visited); 
      
    // Mark the source cell as visited 
    visited[src.x][src.y] = true; 
  
    // Create a queue for BFS 
    queue <queueNode> q; 
      
    // Distance of source cell is 0 
    queueNode s = {src, 0}; 
    q.push(s);  // Enqueue source cell 
  	root->pptr = NULL;
    // Do a BFS starting from source cell 

    while (!q.empty()) 
    { 
    	states_explored++;
        queueNode curr = q.front(); 
        Point pt = curr.pt; 
        //final_path[pt.x][pt.y]=1;
        // If we have reached the destination cell, 
        // we are done 
        if (pt.x == dest.x && pt.y == dest.y) 
        {
        	while(root->pptr!=NULL)
        	{
        		final_path[root->x][root->y]=1;
        		root = root->pptr;
        	}
        	final_path[root->x][root->y]=1;
            return curr.dist; 
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
                queueNode Adjcell = { {row, col}, 
                                      curr.dist + 1 }; 
                node* temp = new node;
                temp->x=row;
                temp->y=col;
                temp->pptr=root;
                root->nptr = temp;
                root = root->nptr;
                q.push(Adjcell); 
            } 
        } 
    } 
  
    // Return -1 if destination cannot be reached 
    return -1; 
} 

// BFS to find all cells in 
// connection with key = input[i][j] 
/*
void BFS(int x, int y, int i, int j, int input[n][m]) 
{ 
	// terminating case for BFS 
	if (x != y)
		return; 
	visited[i][j] = 1; 
	COUNT++; 

	// x_move and y_move arrays 
	// are the possible movements 
	// in x or y direction 
	
	int x_move[] = { 0, 0, 1, -1 }; 
	int y_move[] = { 1, -1, 0, 0 }; 
	

	// checks all four points connected with input[i][j] 
	for (int u = 0; u < 4; u++) 
		if (is_valid(i + y_move[u], j + x_move[u], x, input)) 
			BFS(x, y, i + y_move[u], j + x_move[u], input); 
} 
*/
// called every time before a BFS 
// so that visited array is reset to zero 
/*
void reset_visited() 
{ 
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			visited[i][j] = 0; 
} 

// If a larger connected component 
// is found this function is called 
// to store information about that component. 
void reset_result(int key, int input[n][m]) 
{ 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < m; j++) { 
			if (visited[i][j] && input[i][j] == key) 
				result[i][j] = visited[i][j]; 
			else
				result[i][j] = 0; 
		} 
	} 
} 
// function to print the result 
void print_result(int res) 
{ 
	cout << "The largest connected "
		<< "component of the grid is :" << res << "\n"; 

	// prints the largest component 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < m; j++) { 
			if (result[i][j]) 
				cout << result[i][j] << " "; 
			else
				cout << ". "; 
		} 
		cout << "\n"; 
	} 
} 

// function to calculate the largest connected 
// component 

void computeLargestConnectedGrid(int input[n][m]) 
{ 
	int current_max = INT_MIN; 

	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < m; j++) { 
			reset_visited(); 
			COUNT = 0; 

			// checking cell to the right 
			if (j + 1 < m) 
				BFS(input[i][j], input[i][j + 1], i, j, input); 

			// updating result 
			if (COUNT >= current_max) { 
				current_max = COUNT; 
				reset_result(input[i][j], input); 
			} 
			reset_visited(); 
			COUNT = 0; 

			// checking cell downwards 
			if (i + 1 < n) 
				BFS(input[i][j], input[i + 1][j], i, j, input); 

			// updating result 
			if (COUNT >= current_max) { 
				current_max = COUNT; 
				reset_result(input[i][j], input); 
			} 
		} 
	} 
	print_result(current_max); 
} 
*/
// Drivers Code 
int main() 
{ 
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
    node* root = new node;
    root->x= 0;
    root->y=0;
    int dist = final_BFS(input, source, dest, root); 
  
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

