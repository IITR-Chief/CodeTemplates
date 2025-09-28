class DisjointSet {
public:
    vector<int> parent, size;

    // Constructor: initialize DSU for n nodes (0-based indexing)
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]);
    }

    // Union by size
    void unionBySize(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);

        if (pu == pv) return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};


//usecase
/*

int main() {
    DisjointSet dsu(7); // nodes 0 to 6

    dsu.unionBySize(0, 1);
    dsu.unionBySize(1, 2);
    dsu.unionBySize(3, 4);

    if (dsu.findParent(2) == dsu.findParent(6))
        cout << "Same component\n";
    else
        cout << "Different components\n";

    dsu.unionBySize(4, 5);
    dsu.unionBySize(5, 6);

    if (dsu.findParent(2) == dsu.findParent(6))
        cout << "Same component\n";
    else
        cout << "Different components\n";

    return 0;
}

*/
