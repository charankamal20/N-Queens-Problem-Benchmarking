#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<vector<int> > result;

void printGridSolution(int N, vector<vector<int> > v)
{
    fstream file;
    string fileName;
    fileName = "results/solution";
    fileName.append(to_string(N));
    fileName.append(".txt");

    file.open(fileName, ios::out);

    file << "\nSolution for " << N << " Queens is: ";
    file << "\nTotal Solutions: " << result.size();
    
    for (auto solution : v) {
        file << endl;
        file << "[";
        for (auto it : solution)
            file << it << " ";
        file << "]";
        file << endl;
        for (int i = 0; i < N; i++)    {
            for ( int j = 0; j<N ;j++)   {
                if(solution[i] - 1 == j)  {
                    file << "Q";
                }
                else    {
                    file << ".";
                }
            }
            file << endl;
        }
    }

    file.close();
} 

bool isSafe(vector<vector<int> > board,
            int row, int col)
{
    int i, j;
    int N = board.size();
 
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
 
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;
 
    return true;
}
 

bool solveNQUtil(vector<vector<int> >& board, int col)
{

    int N = board.size();
    if (col == N) {
        vector<int> v;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 1)
                    v.push_back(j + 1);
            }
        }
        result.push_back(v);
        return true;
    }
 
    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            res = solveNQUtil(board, col + 1) || res;
 
            board[i][col] = 0; // BACKTRACK
        }
    }
 
    return res;
}
 
vector<vector<int> > nQueen(int n)
{
    result.clear();
    vector<vector<int> > board(n, vector<int>(n, 0));
 
    if (solveNQUtil(board, 0) == false) {
        return {};
    }
 
    sort(result.begin(), result.end());
    return result;
}
 
// Driver Code
int main()
{
    // sleep(5);
    cout << "Finding solutions to n queens, output stored in result.txt file";
    fstream file;
    
    time_t now = time(0); // get current dat/time with respect to system  
    char* dt = ctime(&now); // convert it into string  

    std::cout << "Current Local Date and time: " << dt << std::endl; // print local date and time

    std::cout << "This is N queens program:\nBelow you will find the system specifications:\n";
    
    system("neofetch | grep 'Memory\\|OS\\|Kernel\\|CPU'");
    // sleep(20);

    std::cout << "\nStarting N queens benchmarking\n";
    std::cout << std::string(60,'-');

    for ( int i = 4; i < INT_MAX; i++)  {
        int n = i;
        cout << "\nFor " << n << " Queens\n";
        auto start = high_resolution_clock::now();
        vector<vector<int> > v = nQueen(n);
        auto end = high_resolution_clock::now();
        double time_taken = duration_cast<nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        int solutions = v.size();
        // for (auto ar : v) {
            // cout << "[";
            // for (auto it : ar)
            //     cout << it << " ";
            // cout << "]";
            // cout << endl;
        // }
        cout << "\nTime taken by program is : " << fixed
            << time_taken << setprecision(9);
        printGridSolution(n, v);
        cout << "\nNo of solutions: " << solutions;
        std::cout << "\nCPU Core Temperatures:\n ";
        system("sensors | grep Core");
        // sleep(10);
        cout << string(60,'-');
        cout << '\n';
    }  
    return 0;
}