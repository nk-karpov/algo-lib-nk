#ifndef LCA_NK
#define LCA_NK

#include "tree.hpp"
namespace nk {
	struct lca {
		int k;
		vector<vector<int>> p;
		vector<int> h;
		lca() {}
		lca(const tree &t) {
			k = 0;
			h = vector<int>(t.n);
			while ((1 << k) <= t.n) k++;
			p = vector<vector<int>>(t.n, vector<int>(k, -1));
			for (auto s : t.q) {
				if (t.prev[s] == -1) {
					p[s][0] = s;
					h[s] = 0;
				} else {
					h[s] = h[t.edges[t.prev[s]].s] + 1;
					p[s][0] = t.edges[t.prev[s]].s;
				}
			}
			for (int lvl = 1; lvl < k; lvl++) {
				for (int i = 0; i < t.n; i++) {
					p[i][lvl] = p[p[i][lvl - 1]][lvl - 1];
				}
			}
		}

		int get(int a, int b) {
			if (h[a] > h[b]) swap(a, b);
			for (int lvl = k - 1; lvl >= 0; lvl--) {
				if (h[b] - (1 << lvl) >= h[a]) b = p[b][lvl];
			}
			if (a == b) return a;
			for (int lvl = k - 1; lvl >= 0; lvl--) {
				if (p[a][lvl] != p[b][lvl]) {
					a = p[a][lvl];
					b = p[b][lvl];
				}	
			}
			return p[a][0];
		}
	};
}
//nk

#endif
