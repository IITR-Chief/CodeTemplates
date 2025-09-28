class LazySegTree {
    public:
    vector<int> st, lazy; // segment tree + lazy array

    LazySegTree(int n) {
        st.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    // Build function
    void build(int idx, int l, int r, vector<int> &arr) {
        if (l == r) {
            st[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2*idx+1, l, mid, arr);
        build(2*idx+2, mid+1, r, arr);
        st[idx] = st[2*idx+1] + st[2*idx+2];
    }

    // Propagate pending updates
    void pushDown(int idx, int l, int r) {
        if (lazy[idx] != 0) {
            st[idx] += (r - l + 1) * lazy[idx]; // apply lazy value

            if (l != r) { // not a leaf
                lazy[2*idx+1] += lazy[idx];
                lazy[2*idx+2] += lazy[idx];
            }
            lazy[idx] = 0; // clear lazy value
        }
    }

    // Range update: add val to [ql, qr]
    void updateRange(int idx, int l, int r, int ql, int qr, int val) {
        pushDown(idx, l, r);

        // No overlap
        if (r < ql || l > qr) return;

        // Complete overlap
        if (ql <= l && r <= qr) {
            lazy[idx] += val;
            pushDown(idx, l, r);
            return;
        }

        // Partial overlap
        int mid = (l + r) / 2;
        update(2*idx+1, l, mid, ql, qr, val);
        update(2*idx+2, mid+1, r, ql, qr, val);
        st[idx] = st[2*idx+1] + st[2*idx+2];
    }

    // Range query: sum of [ql, qr]
    int query(int idx, int l, int r, int ql, int qr) {
        pushDown(idx, l, r);

        // No overlap
        if (r < ql || l > qr) return 0;

        // Complete overlap
        if (ql <= l && r <= qr) return st[idx];

        // Partial overlap
        int mid = (l + r) / 2;
        return query(2*idx+1, l, mid, ql, qr) +
               query(2*idx+2, mid+1, r, ql, qr);
    }
};
