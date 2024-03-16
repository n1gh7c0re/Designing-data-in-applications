#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 1000000.0
#define minimal(a, b) (((a)<(b))?(a):(b))
#define three_minimal(a, b, c) minimal(minimal(a, b), c)

// Structure of a point in 2D plane
struct Point {
    double x, y;
};

// Function to find maximum of two double values
double Max(double x, double y) {
    return (x >= y) ? x : y;
}

// Function to find distance between two points in a plane
double distance(struct Point p1, struct Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y));
}

// Function to find cost of a triangle
// The cost is considered as diagonal length
double cost(struct Point points[], int i, int j) {
    struct Point p1 = points[i], p2 = points[j];
    return distance(p1, p2); //?????
}

// A Dynamic programming based function to find minimum cost for convex polygon triangulation.
double** mTCDP(struct Point points[], int const n) {
   // Table to store results of subproblems
   // Table[i][j] stores cost of triangulation of points from i to j
   // The entry table[0][n-1] stores the final result.
    double** table = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        table[i] = (double*)malloc(sizeof(double) * n);
    }

   // Fill table using above recursive formula.
   // Note that the table is filled in diagonal fashion i.e.,
   // from diagonal elements to table[0][n-1] which is the result.
    //for (int i = 0; i < n; i++) {
    //    for (int j = i + 2; j < n; j++) {
    //        table[i][j] = MAX;
    //        table[i][j - 1] = MAX;
    //        table[i][j - 2] = MAX;
    //    }
    //}
    for (int gap = 0; gap < n; gap++) {
        for (int i = 0, j = gap; j < n; i++, j++) {
            if ((j - i) <= 2)
                table[i][j] = MAX;
            else {
                table[i][j] = MAX;
                for (int k = i + 1; k < j; k++) {
                    double minDiag = three_minimal(table[i][k], table[k][j], distance(points[k], points[j]));
                    if (table[i][j] > minDiag)
                        table[i][j] = minDiag; //??? cost(points, k, j)
                }
            }
        }
    }
    return table;
}

int main(void) {
    struct Point points[] = { {0, 0}, {0, 2}, {4, 2}, {2, 0} };
    int n = sizeof(points) / sizeof(points[0]);
    if (n < 3) {
        printf("There must be at least 3 points to form a triangle\n");
        return 1;
    }

    double** table = mTCDP(points, n);
    printf("The minimum length of the longest diagonal in the triangulation is: %lf", table[0][n - 1]);

    for (int i = 0; i < n; i++) {
        free(table[i]);
    }
    free(table);

    return 0;
}