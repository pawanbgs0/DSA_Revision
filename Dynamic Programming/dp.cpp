#include "dp.h"

int fibonacci(int num, vector<int> &dp)
{
    if (num <= 1)
        return num;

    if (dp[num] != -1)
        return dp[num];

    int prev = fibonacci(num - 1, dp);
    int prev2 = fibonacci(num - 2, dp);

    return dp[num] = prev + prev2;
}

int climb(int num, vector<int> &dp)
{
    if (num == 0 || num == 1)
        return 1;

    if (num < 0)
        return 0;

    if (dp[num] != -1)
        return dp[num];

    int one = climb(num - 1, dp);
    
    int two = climb(num - 2, dp);

    return dp[num] = one + two;
}

int frog_jump(int index, vector<int> &heights, vector<int> &dp)
{
    if (index == 0)
        return 0;

    if (dp[index] != -1)
        return dp[index];

    int one = frog_jump(index - 1, heights, dp) + abs(heights[index] - heights[index - 1]);

    int two = INT_MAX;
    if (index > 1)
        two = frog_jump(index - 2, heights, dp) + abs(heights[index] - heights[index - 2]);

    return dp[index] = min(one, two);
}


int subsquence_sum(int index, vector<int> arr, vector<int> &dp)
{
    if (index == 0)
        return arr[index];

    if (index < 0)
        return 0;

    if (dp[index] != -1)
        return dp[index];

    int pick = arr[index] + subsquence_sum(index - 2, arr, dp);
    int not_pick = subsquence_sum(index - 1, arr, dp);

    return dp[index] = max(pick, not_pick);
}

int subsquence_sumT(vector<int> arr)
{
    vector<int> dp(arr.size(), 0);

    dp[0] = arr[0];

    for (int i = 1; i < arr.size(); i++)
    {
        int pick = arr[i];
        if (i > 1)
            pick += dp[i - 2]; // to counter negative index as from above code

        int not_pick = dp[i - 1];

        dp[i] = max(pick, not_pick);
    }

    return dp[arr.size() - 1];
}

int ninja_training(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp)
{
    if (day == 0)
    {
        int maxi = INT_MIN;

        for (int task = 0; task < 3; task++)
        {
            if (task != last)
                maxi = max(maxi, points[day][task]);
        }
        return maxi;
    }

    int maxi = INT_MIN;

    for (int task = 0; task < 3; task++)
    {
        if (task != last)
        {
            int point = points[day][task] + ninja_training(day - 1, task, points, dp);

            maxi = max(maxi, point);
        }
    }

    return maxi;
}

int unique_paths(int rowIndex, int columnIndex, vector<vector<int>> &dp)
{
    if (rowIndex == 0 && columnIndex == 0)
        return 1;
    
    if (rowIndex < 0 || columnIndex < 0)
        return 0;

    if (dp[rowIndex][columnIndex] != -1)
        return dp[rowIndex][columnIndex];

    int top = unique_paths(rowIndex, columnIndex - 1, dp);
    int left = unique_paths(rowIndex - 1, columnIndex, dp);

    return dp[rowIndex][columnIndex] = top + left;
}

int unique_paths_II(int rowIndex, int columnIndex, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (rowIndex >= 0 && columnIndex >= 0 && grid[rowIndex][columnIndex] == 1)
        return 0;

    if (rowIndex == 0 && columnIndex == 0)
        return 1;
    
    if (rowIndex < 0 || columnIndex < 0)
        return 0;

    int top = unique_paths_II(rowIndex, columnIndex - 1, grid, dp);
    int left = unique_paths_II(rowIndex - 1, columnIndex, grid, dp);

    return left + top;
}

int min_path_sum(int rowIndex, int columnIndex, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (rowIndex < 0 || columnIndex < 0)
        return 214748364;
    
    if (rowIndex == 0 && columnIndex == 0)
        return grid[rowIndex][columnIndex];

    if (dp[rowIndex][columnIndex] != -1)
        return dp[rowIndex][columnIndex];

    int left = grid[rowIndex][columnIndex] + min_path_sum(rowIndex - 1, columnIndex, grid, dp);

    int top = grid[rowIndex][columnIndex] + min_path_sum(rowIndex, columnIndex - 1, grid, dp);

    return dp[rowIndex][columnIndex] = min(left, top);
}

int minimumTotal(int i, int j, int n, vector<vector<int>>& triangle, vector<vector<int>> &dp)
{
    if (i == n)
        return triangle[i][j];
    
    if (dp[i][j] != -1)
        return dp[i][j];

    int down = triangle[i][j] + minimumTotal(i + 1, j, n, triangle, dp);
    int diagonal = triangle[i][j] + minimumTotal(i+1, j+1, n, triangle, dp);

    return dp[i][j] = min(down, diagonal);
}

int maxMatrixPathSum(int columnIndex, int rowIndex, int rowSize, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    if (rowIndex < 0 || rowIndex > rowSize)
        return -1e8;

    if (columnIndex == 0)
        return matrix[columnIndex][rowIndex];

    int up = maxMatrixPathSum(columnIndex - 1, rowIndex, rowSize, matrix, dp);
    int dleft = maxMatrixPathSum(columnIndex - 1, rowIndex - 1, rowSize, matrix, dp);
    int dright = maxMatrixPathSum(columnIndex - 1, rowIndex - 1, rowSize, matrix, dp);

    return max(up, max(dleft, dright));
}


int cherryPickup(int i, int j1, int j2, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp)
{
    if (j1 < 0 || j2 < 0 || j1 > grid[0].size() - 1 || j2 > grid[0].size() -1)
        return -1e8;
    
    if (i == grid.size() - 1)
    {
        if (j1 == j2)
            return grid[i][j1]; // as only one will pick
        else
            return grid[i][j1] + grid[i][j2];
    }

    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int maxi = -1e8;

    for (int r1 = -1; r1 <= 1; r1++) // for each step of r1
    {
        for (int r2 = -1; r2 <= 1; r2++)  // there will be three steps of r2
        {
            if (j1 == j2)
                maxi = max(maxi, grid[i][j1] + cherryPickup(i + 1, j1 + r1, j2 + r2, grid, dp));
            else 
                maxi = max(maxi, grid[i][j1] + grid[i][j2] + cherryPickup(i + 1, j1 + r1, j2 + r2, grid, dp));
        }
    }
    return dp[i][j1][j2] = maxi;
}


bool hasValidSubset(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    if (target == 0)
        return true;

    if (index == 0)
        return arr[index] == target;

    if (dp[index][target] != -1)
        return dp[index][target];

    bool not_pick = hasValidSubset(index - 1, target, arr, dp);
    bool pick = false;
        if (arr[index] <= target)
            pick = hasValidSubset(index - 1, target - arr[index], arr, dp);
    
    return dp[index][target] = pick || not_pick;
}


bool canPartition(vector<int>& nums)
{
    int sum = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
    }

    if (sum % 2 != 0)
        return false;

    int target = sum / 2;
    vector<vector<int>> dp(nums.size(), vector<int>(target + 1, -1));

    return hasValidSubset(nums.size() - 1, target, nums, dp);
}