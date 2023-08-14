
#include<iostream>
using namespace std;

const int rows = 5; 
const int cols = 6;

string path[rows][cols]; //array to store the paths(row came from and row at)
int costs[rows][cols]={0}; //create cost array so each time get cost of different index can store it in this for memoization

int cost(int i, int j){ 
    int weight[rows][cols]={ //assign values to weight array
        {3,4,1,2,8,6},
        {6,1,8,2,7,4},
        {5,9,3,9,9,5}, 
        {8,4,1,3,2,6}, 
        {3,7,2,8,6,4}};
    if (costs[i][j] != 0) return costs[i][j]; //if theres a non zero value in costs array means already found it
    if(j==0) { //check base case if its at column 0
        costs[i][0]=weight[i][0]; //then the value of the cost is value in column 0
        return weight[i][0];
    }
   
    int row_above; 
    int row_below;
    if(i==0) row_above=4; // if row is 0, row above is 4 since goes out of bounds
    else row_above=(i-1); 
    if(i==4) row_below=0; //if row is 4, row below is 0 since goes out of bounds 
    else row_below=(i+1);
    
    // recursive call 
    int directions[3]; //create directions array so it is easier to find min and allow you to know which direction coming from
    int left=0, up=1, down=2; 
    directions[left]=weight[i][j]+cost(i,j-1); //initiliaze lefts cost to be the weight plus the cost to the left(not worried about highest or lowest row out of bounds)
    directions[up]=weight[i][j]+cost(row_above,j-1); 
    directions[down]=weight[i][j]+cost(row_below,j-1); 
    int min = directions[0]; //initialize minimum cost direction to be 0(left) to start
    for (int i=1; i<=2; i++){ //loop to find the value of the direction with the least cost (shortest path) 
        if (directions[i] < min) {
            min=directions[i];
        }
    }

    int row_from; //create a variable to keep track of what row it came from in the path array
    if(min==directions[left]) row_from=i; //based on which direction was the minimum declare which row it came from
    else if(min==directions[up]) row_from=row_above;
    else if (min==directions[down]) row_from=row_below;
    for(int i=0; i<rows; i++){
        path[i][0]=to_string(i); //for the first column initialize each row to be the row it is currently at(since thats the row it came from)
    }

    string boxbefore=path[row_from][j-1]; //initialize the box before to be the box path array that is in the row you came from and the column above
    string row_at=to_string(i); //convert the row at to be a string so can easily append to it later
    string a=boxbefore.append(row_at); //append the row at to the box befores contents so you can store this in the path array
    path[i][j]=a; 
    costs[i][j]=min; //store minimum in the costs array 
    return min; 
}

int main(){
    int ex[rows]; //create exit array for last column to get the shortest path out of each cell on the right 
    for(int i=0; i<rows; i++) ex[i]=cost(i,cols-1); 
    int min=ex[0];
    for(int i=0; i<rows; i++) {
        if(ex[i]<min) min=ex[i]; //find the minimum cost of the last column
    }
    cout<< "the sortest path is of length " << min << endl; 
    for(int c=0; c<rows; c++){
       for(int d=0; d<cols; d++){
            cout << path[c][d] << " ";
       }
       cout<<endl;
    }
    cout << endl;
    for(int a=0; a<rows; a++){
        for(int b=0; b<cols; b++){  
            cout<< costs[a][b] << " ";
       }
       cout << endl;
    }
    int min_row=0;
    for(int i=0; i<rows; i++){ //find the row with the smallest cost in the last column of the cost array since that will be where the path taken ends 
        if(costs[i][cols-1]<costs[min_row][cols-1]) min_row=i;
    }
    cout << "from row ";
    for(int l=0; l<cols; l++){ //print out the rows of the path taken by going through the value stored in the path array at minimum row (lowest cost)
        cout << path[min_row][cols-1].at(l);
            if (l<(cols-1)){
                cout << " to row ";
            }
    }
    cout << endl;
}