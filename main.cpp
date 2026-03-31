#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
    long long x, y;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].idx = i;
    }

    long long count = 0;

    // For each pair of points, check if they can form a valid rectangle
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            // Check if point i can be bottom-left and point j can be top-right
            if (points[i].x < points[j].x && points[i].y < points[j].y) {
                long long x1 = points[i].x;
                long long y1 = points[i].y;
                long long x2 = points[j].x;
                long long y2 = points[j].y;

                bool valid = true;

                // Check if any other point lies inside or on the boundary (except corners)
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;

                    long long x = points[k].x;
                    long long y = points[k].y;

                    // Check if point k is inside or on the boundary of the rectangle
                    if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    count++;
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}
