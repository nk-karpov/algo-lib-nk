#ifndef TREE_NK
#define TREE_NK

#include <vector>

namespace nk {
	using namespace std;
	struct edge {
		 int s, t;
		 int cost;
		 edge(): s(-1), t(-1), cost(0) {}
		 edge(int s, int t, int cost): s(s), t(t), cost(cost) {}
	};

	struct tree {
		int n;
		vector<edge> edges;
		vector<int> prev;
		vector<int> q;
		vector<vector<int>> g;

		void add_edge(int s, int t) {	
			add_edge(s, t, 0);
		}
		void add_edge(int s, int t, int cost) {
			prev[t] = edges.size();
			g[s].push_back(edges.size());
			edges.push_back(edge(s, t, cost));
			g[t].push_back(edges.size());
			edges.push_back(edge(t, s, cost));
		}

		tree():n(0) {}

		tree(int n):n(n) {
			q.reserve(n);
			prev = vector<int>(n, -1);
			g = vector<vector<int>>(n, vector<int>());
		}

		void hang(int s, int pr = -1) {
			q.push_back(s);
			prev[s] = pr;
			for (auto ind : g[s]) {
				if ((ind ^ 1) == pr) continue;
				hang(edges[ind].t, ind);
			}
		}

		int up(int s) {
			if (prev[s] == -1) return -1;
			return edges[prev[s]].s;
		}
		/*
		void print(int s, int pr = -1) {
			eprintf("(");
			eprintf("%d", s);
			for (auto ind : g[s]) {
				if ((ind ^ 1) == pr) continue;
				print(edges[ind].t, ind);
			}
			eprintf(")");
			if (pr == -1) eprintf("\n");
		} */
	};
}
//nk

#endif
