#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

// ===== STATE =====
struct State {
    vector<pair<int, int>> boxes;
    pair<int, int> player;

    bool operator==(const State& o) const {
        return player == o.player && boxes == o.boxes;
    }
};

// ===== HASH =====
struct StateHash {
    size_t operator()(const State& s) const {
        size_t h = s.player.first * 1315423911u + s.player.second;
        for (auto& b : s.boxes)
            h ^= (b.first * 31 + b.second * 17);
        return h;
    }
};

// ===== SOLVER =====
class Solver {
public:
    vector<string> grid;
    int H, W;
    vector<pair<int, int>> goals;

    Solver(const string& level) {
        parse(level);
    }

    vector<State> solve() {

        struct Node {
            int f;
            State s;
        };

        struct Compare {
            bool operator()(const Node& a, const Node& b) const {
                return a.f > b.f;
            }
        };

        priority_queue<Node, vector<Node>, Compare> pq;
        unordered_map<State, int, StateHash> dist;
        unordered_map<State, State, StateHash> parent;

        // ===== METRICS =====
        size_t expanded = 0;
        size_t generated = 0;

        State start = initialState();
        dist[start] = 0;
        pq.push({ heuristic(start), start });

        while (!pq.empty()) {
            Node cur = pq.top(); pq.pop();
            expanded++;

            if (expanded % 1000 == 0) {
                cout << "Expanded: " << expanded << "\r";
            }

            if (isGoal(cur.s)) {
                cout << "\nExpanded states: " << expanded << "\n";
                cout << "Generated states: " << generated << "\n";
                cout << "Unique states: " << dist.size() << "\n\n";
                return build(cur.s, parent);
            }

            for (auto& nxt : expand(cur.s)) {
                generated++;

                if (deadlock(nxt)) continue;

                int g = dist[cur.s] + 1;

                if (!dist.count(nxt) || g < dist[nxt]) {
                    dist[nxt] = g;
                    parent[nxt] = cur.s;
                    pq.push({ g + heuristic(nxt), nxt });
                }
            }
        }

        cout << "\nExpanded states: " << expanded << "\n";
        cout << "Generated states: " << generated << "\n";
        cout << "Unique states: " << dist.size() << "\n\n";

        return {};
    }

    // ===== PRINT =====
    void printState(const State& s) {
        vector<string> out = grid;

        for (int y = 0;y < H;y++)
            for (int x = 0;x < W;x++) {
                if (out[y][x] == '@') out[y][x] = ' ';
                if (out[y][x] == '$') out[y][x] = ' ';
            }

        for (auto& b : s.boxes) {
            if (out[b.second][b.first] == '.')
                out[b.second][b.first] = '*';
            else
                out[b.second][b.first] = '$';
        }

        auto [px, py] = s.player;
        if (out[py][px] == '.')
            out[py][px] = '+';
        else
            out[py][px] = '@';

        for (auto& r : out)
            cout << r << "\n";
    }

private:

    void parse(const string& s) {
        stringstream ss(s);
        string line;
        while (getline(ss, line)) grid.push_back(line);

        H = grid.size();
        W = grid[0].size();

        for (int y = 0;y < H;y++)
            for (int x = 0;x < W;x++)
                if (grid[y][x] == '.')
                    goals.push_back({ x,y });
    }

    State initialState() {
        State s;
        for (int y = 0;y < H;y++)
            for (int x = 0;x < W;x++) {
                char c = grid[y][x];
                if (c == '@') s.player = { x,y };
                if (c == '$') s.boxes.push_back({ x,y });
            }
        sort(s.boxes.begin(), s.boxes.end());
        return s;
    }

    bool isGoal(const State& s) {
        for (auto& b : s.boxes)
            if (grid[b.second][b.first] != '.')
                return false;
        return true;
    }

    int heuristic(const State& s) {
        int total = 0;
        for (auto& b : s.boxes) {
            int best = 1e9;
            for (auto& g : goals) {
                int d = abs(b.first - g.first) + abs(b.second - g.second);
                best = min(best, d);
            }
            total += best;
        }
        return total;
    }

    vector<vector<bool>> reachable(const State& s) {
        vector<vector<bool>> vis(H, vector<bool>(W, false));
        queue<pair<int, int>> q;

        q.push(s.player);
        vis[s.player.second][s.player.first] = true;

        set<pair<int, int>> boxSet(s.boxes.begin(), s.boxes.end());

        int dx[4] = { 0,0,-1,1 };
        int dy[4] = { -1,1,0,0 };

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();

            for (int i = 0;i < 4;i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
                if (vis[ny][nx]) continue;

                if (grid[ny][nx] == '#') continue;
                if (boxSet.count({ nx,ny })) continue;

                vis[ny][nx] = true;
                q.push({ nx,ny });
            }
        }
        return vis;
    }

    vector<State> expand(const State& s) {
        vector<State> out;
        auto reach = reachable(s);

        set<pair<int, int>> boxSet(s.boxes.begin(), s.boxes.end());

        int dx[4] = { 0,0,-1,1 };
        int dy[4] = { -1,1,0,0 };

        for (auto& box : s.boxes) {
            int x = box.first, y = box.second;

            for (int d = 0;d < 4;d++) {
                int px = x - dx[d], py = y - dy[d];
                int tx = x + dx[d], ty = y + dy[d];

                if (px < 0 || py < 0 || tx < 0 || ty < 0 || px >= W || py >= H || tx >= W || ty >= H)
                    continue;

                if (!reach[py][px]) continue;
                if (grid[ty][tx] == '#' || boxSet.count({ tx,ty })) continue;

                State n = s;
                n.player = { x,y };

                for (auto& b : n.boxes)
                    if (b == box) { b = { tx,ty }; break; }

                sort(n.boxes.begin(), n.boxes.end());
                out.push_back(n);
            }
        }
        return out;
    }

    bool deadlock(const State& s) {
        for (auto& b : s.boxes) {
            if (grid[b.second][b.first] == '.') continue;

            bool L = grid[b.second][b.first - 1] == '#';
            bool R = grid[b.second][b.first + 1] == '#';
            bool U = grid[b.second - 1][b.first] == '#';
            bool D = grid[b.second + 1][b.first] == '#';

            if ((L || R) && (U || D)) return true;
        }
        return false;
    }

    vector<State> build(State goal,
        unordered_map<State, State, StateHash>& parent)
    {
        vector<State> path;
        while (parent.count(goal)) {
            path.push_back(goal);
            goal = parent[goal];
        }
        path.push_back(goal);
        reverse(path.begin(), path.end());
        return path;
    }
};

// ===== MAIN =====
int main() {
    std::string level = R"(#########
#..     #
###     #
#  $    #
#  $    #
# @    ##
#########)";

    Solver solver(level);
    auto sol = solver.solve();

    if (sol.empty()) {
        cout << "No solution\n";
        return 0;
    }

    cout << "Steps: " << sol.size() - 1 << "\n\n";

    int step = 0;
    for (const auto& s : sol) {
        cout << "Step " << step++ << ":\n";
        solver.printState(s);
        cout << "\n";
    }
}