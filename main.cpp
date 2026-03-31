#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<long long, long long>> points(n);
    map<long long, vector<long long>> byX; // points grouped by x-coordinate

    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
        byX[points[i].first].push_back(points[i].second);
    }

    // Sort y-coordinates for each x
    for (auto& [x, ys] : byX) {
        sort(ys.begin(), ys.end());
    }

    long long count = 0;

    // Get all unique x-coordinates
    vector<long long> uniqueX;
    for (auto& [x, ys] : byX) {
        uniqueX.push_back(x);
    }

    int numX = uniqueX.size();

    // For each pair of x-coordinates (left and right edges)
    for (int xi = 0; xi < numX; xi++) {
        for (int xj = xi + 1; xj < numX; xj++) {
            long long x1 = uniqueX[xi];
            long long x2 = uniqueX[xj];

            // Find valid pairs of y-coordinates
            vector<long long>& ys1 = byX[x1];
            vector<long long>& ys2 = byX[x2];

            for (long long y1 : ys1) {
                for (long long y2 : ys2) {
                    if (y1 >= y2) continue;

                    // Check if rectangle [x1,x2] × [y1,y2] has any other points
                    bool valid = true;

                    // Check all x-coordinates in the range
                    for (int xk = xi; xk <= xj && valid; xk++) {
                        long long x = uniqueX[xk];
                        vector<long long>& ys = byX[x];

                        // Find points in y-range [y1, y2]
                        auto it_start = lower_bound(ys.begin(), ys.end(), y1);
                        auto it_end = upper_bound(ys.begin(), ys.end(), y2);

                        for (auto it = it_start; it != it_end && valid; ++it) {
                            long long y = *it;

                            // Skip the two corners
                            if (x == x1 && y == y1) continue;
                            if (x == x2 && y == y2) continue;

                            // Found another point in the rectangle
                            valid = false;
                        }
                    }

                    if (valid) {
                        count++;
                    }
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}
