// 1-indexed!
struct wavelet {
    int lo, hi;
    vector<int> b;
    wavelet *l = 0, *r = 0;
    wavelet(vector<int>::iterator pl, vector<int>::iterator pr, int x, int y) {
        lo = x, hi = y;
        if (lo == hi || pl >= pr) return;
        int mid = lo + (hi - lo) / 2;
        auto f = [mid](int x) {
            return x <= mid;
        };
        b.reserve(pr - pl + 1);
        b.push_back(0);
        for (auto it = pl; it != pr; it++)
            b.push_back(b.back() + f(*it));
        auto it = stable_partition(pl, pr, f);
        l = new wavelet(pl, it, lo, mid), r = new wavelet(it, pr, mid + 1, hi);
    }
    // retrieve the k_th minimal value in range [l, r]
    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        int le = b[l - 1], ri = b[r];
        if (ri - le >= k) return this->l->kth(le + 1, ri, k);
        return this->r->kth(l - le, r - ri, k - (ri - le));
    }
    // count values less than k in range [l, r]
    int clt(int l, int r, int k) {
        if (l > r || k <= lo) return 0;
        if (k > hi) return r - l + 1;
        int le = b[l - 1], ri = b[r];
        return this->l->clt(le + 1, ri, k) + this->r->clt(l - le, r - ri, k);
    }
    // count equal to k in range [l, r]
    int ce(int l, int r, int k) {
        if (k < lo || k > hi || l > r) return 0;
        if (lo == hi) return r - l + 1;
        int le = b[l - 1], ri = b[r];
        return this->l->ce(le + 1, ri, k) + this->r->ce(l - le, r - ri, k);
    }
    ~wavelet() { delete l, delete r; }
};
