#ifndef CENTRE_NK
#define CENTRE_NK

#include "tree.hpp"

namespace nk {
	struct centre {
		int root;
		tree res;
		vector<int> f;
		vector<bool> v;
		const tree &t;
		centre(const tree &t):t(t) {
			res = tree(t.n);
			v = vector<bool>(t.n, 0);
			f = vector<int>(t.n);
			root = compose(0);
		}

		pair<int, int> get(int s, int fs, int pr = -1) {
			pair<int, int> res(fs - f[s], s);
			for (auto ind: t.g[s]) {
				if ((ind ^ 1) == pr) continue;
				if (!v[t.edges[ind].t]) res.first = max(res.first, f[t.edges[ind].t]);
			}
			for (auto ind : t.g[s]) {
				if ((ind ^ 1) == pr) continue;
				if (!v[t.edges[ind].t]) res = min(res, get(t.edges[ind].t, fs, ind));
			}
			return res;
		}

		int calc(int s, int pr = -1) {
			int &fu = f[s];
			fu = 1;
			for (auto ind : t.g[s]) {
				if ((ind ^ 1) == pr) continue;
				if (!v[t.edges[ind].t]) {
					fu += calc(t.edges[ind].t, ind);
				}
			}
			return fu;
		}

		int compose(int s) {
			calc(s, -1);
			pair<int, int> r = get(s, f[s]);
			v[r.second] = 1;
			for (auto ind : t.g[r.second]) {
				if (!v[t.edges[ind].t]) res.add_edge(r.second, compose(t.edges[ind].t));
			}
			return r.second;
		}
	};
}
//nk

#endif
