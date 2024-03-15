#include <stdio.h>
#include <math.h>
#define MAX 1000000.0
#define n 5

// Structure of a point in 2D plane
struct Point {
    int x, y;
};

// Function to find minimum of two double values
double min(double x, double y) {
    return (x <= y) ? x : y;
}

// Function to find distance between two points in a plane
double distance(struct Point p1, struct Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y));
}

// Function to find cost of a triangle
// The cost is considered as diagonal length
double cost(struct Point points[], int i, int j, int k) {
    struct Point p1 = points[i], p2 = points[j], p3 = points[k];
    return distance(p1, p2) + distance(p2, p3) + distance(p3, p1); //???
}

// A Dynamic programming based function to find minimum cost for convex polygon triangulation.
double mTCDP(struct Point points[]) {
    if (n < 3) {
        printf("There must be at least 3 points to form a triangle\n");
        return;
    }

   // Table to store results of subproblems
   // Table[i][j] stores cost of triangulation of points from i to j
   // The entry table[0][n-1] stores the final result.
    double table[n][n];

   // Fill table using above recursive formula.
   // Note that the table is filled in diagonal fashion i.e.,
   // from diagonal elements to table[0][n-1] which is the result.
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (j < i + 2)
                table[i][j] = 0.0;
            else
            {
                table[i][j] = MAX;
                for (int k = i + 1; k < j; k++)
                {
                    double val = table[i][k] + table[k][j] + cost(points, i, j, k);
                    if (table[i][j] > val)
                        table[i][j] = val;
                }
            }
        }
    }
    return table[0][n - 1];
}

int main()
{
    struct Point points[] = { {0, 0}, {1, 0}, {2, 1}, {1, 2}, {0, 2} };
    //int n = sizeof(points) / sizeof(points[0]);
    printf("%lf", mTCDP(points));
    return 0;
}


