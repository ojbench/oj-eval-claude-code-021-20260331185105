#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<long long, long long>> points(n);
    map<long long, vector<long long>> byY; // Group points by y-coordinate

    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
        byY[points[i].second].push_back(points[i].first);
    }

    // Sort x-coordinates for each y-level
    for (auto& [y, xs] : byY) {
        sort(xs.begin(), xs.end());
    }

    long long count = 0;

    // Get all unique y-coordinates
    vector<long long> uniqueY;
    for (auto& [y, xs] : byY) {
        uniqueY.push_back(y);
    }

    int numY = uniqueY.size();

    // For each pair of y-coordinates as bottom and top of rectangle
    for (int yi = 0; yi < numY; yi++) {
        for (int yj = yi + 1; yj < numY; yj++) {
            long long y1 = uniqueY[yi];
            long long y2 = uniqueY[yj];

            vector<long long>& xs1 = byY[y1];
            vector<long long>& xs2 = byY[y2];

            // For each x at y1, try to pair with each x at y2
            for (long long x1 : xs1) {
                for (long long x2 : xs2) {
                    if (x1 >= x2) continue; // Must form a valid rectangle

                    bool valid = true;

                    // Check if any point is in the rectangle [x1, x2] × [y1, y2]
                    // excluding corners (x1, y1) and (x2, y2)
                    for (int yk = yi; yk <= yj && valid; yk++) {
                        long long y = uniqueY[yk];
                        vector<long long>& xs = byY[y];

                        // Find all x values in range [x1, x2]
                        auto it_start = lower_bound(xs.begin(), xs.end(), x1);
                        auto it_end = upper_bound(xs.begin(), xs.end(), x2);

                        for (auto it = it_start; it != it_end; ++it) {
                            long long x = *it;

                            // Check if this point invalidates the rectangle
                            if (x == x1 && y == y1) continue; // Bottom-left corner - OK
                            if (x == x2 && y == y2) continue; // Top-right corner - OK

                            // Any other point in the rectangle makes it invalid
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
    }

    cout << count << endl;

    return 0;
}
