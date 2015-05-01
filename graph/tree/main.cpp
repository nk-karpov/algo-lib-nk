#include "tree.hpp"
#include "lca.hpp"
#include "centre.hpp"
#include <cstdio>

using namespace std;

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

nk::tree ct;
nk::tree t;
nk::lca lca;

const int INF = (int)1e9 + 123;
const int maxn = (int)1e5 + 123;

long long d[maxn];

long long distt(int a, int b) {
	return d[a] + d[b] - 2 * d[lca.get(a, b)];
}

vector<pair<int, pair<int, int> > > st[maxn];


#define sz(c) (int)(c).size()

void update(int s, int dx, int cx, int q) {
	int ss = s;
	while (ss != -1) {
		int du = dx - distt(s, ss);
		if (du >= 0) {
			while (st[ss][sz(st[ss]) - 1].first <= du) st[ss].pop_back(); 
			st[ss].push_back(make_pair(du, make_pair(cx, q)));
		}
		ss = ct.up(ss);
	}
}

int get(int s) {
	int cur = 0;
	int t = -1;
	int ss = s;
	while (ss != -1) {
		long long du = distt(s, ss);
		int left = 0;
		int right = sz(st[ss]);
		while (left + 1 < right) {
			int ave = (left + right) >> 1;
			if (st[ss][ave].first < du) {
				right = ave;
			} else {
				left = ave;
			}
		}
		if (st[ss][left].second.second > t) {
			t = st[ss][left].second.second;
			cur = st[ss][left].second.first;
		}
		ss = ct.up(ss);
	}
	return cur;
}


int main() {
	int n;
	scanf("%d", &n);
	nk::tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		a--, b--;
		t.add_edge(a, b, w);
	}
	t.hang(0);
	for (auto x : t.q) {
		int pr = t.prev[x];
		if (pr == -1) {
			d[x] = 0;
		} else {
			d[x] = d[t.up(x)] + t.edges[pr].cost;
		}
	}
	lca = nk::lca(t);
	nk::centre temp(t);
	ct = temp.res;
	//t.print(0);
	//ct.print(temp.root);
	for (int i = 0; i < n; i++) {
		st[i].push_back(make_pair(INF, make_pair(0, -1)));
	}
	int Q;
	scanf("%d", &Q);
	for (int it = 0; it < Q; it++) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int vx, dx, cx;
			scanf("%d%d%d", &vx, &dx, &cx);
			vx--;
			update(vx, dx, cx, it);
		} else {
			int x;
			scanf("%d", &x);
			x--;
			printf("%d\n", get(x));
		}
	}
}
