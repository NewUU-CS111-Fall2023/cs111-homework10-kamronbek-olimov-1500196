#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF);
    dist[k] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        int u = pq.top().second;
        int uDist = pq.top().first;
        pq.pop();

        if (uDist > dist[u]) {
            continue;  // Skip if we have already found a shorter path
        }

        for (const auto& edge : times) {
            int v = edge[1];
            int w = edge[2];

            if (edge[0] == u && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    int maxTime = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) {
            return -1;  // Some nodes are not reachable
        }
        maxTime = max(maxTime, dist[i]);
    }

    return maxTime;
}

int main() {
    // Sample input
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4;
    int k = 2;

    // Calculate the minimum time for all nodes to receive the signal
    int result = networkDelayTime(times, n, k);

    // Output the result
    cout << "Minimum time: " << result << endl;

    return 0;
}
