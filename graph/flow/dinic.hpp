#include <vector>
#include <queue>

using vi = std::vector<int>;

namespace nk {
	struct edge {
		int s, t;
		int cap, flow;
		edge(int s, int t, int cap):s(s), t(t), cap(cap), flow(0) {}
		edge() {}
	};
	using ve = std::vector<edge>;
	
	struct graph {
		int n, m;
		ve edges;
		std::vector<vi> g;

		graph(int n, int m = 0):n(n), m(m) {
			g.resize(n);
			edges.reserve(m);
		}

		void add_edge(int s, int t, int cap) {
			g[s].push_back((int)edges.size());
			edges.push_back(edge(s, t, cap));
			g[t].push_back((int)edges.size());
			edges.push_back(edge(t, s, 0));
		}

	};
	
	struct dinic {
		vi dist;
		vi p;
		vi c;

		int bfs(int s, int t, int l, graph &g) {
			std::fill(dist.begin(), dist.end(), g.n);
			std::fill(p.begin(), p.end(), -1);
			std::queue<int> pq;
			dist[s] = 0;
			pq.push(s);
			while (!pq.empty()) {
				auto u = pq.front();
				pq.pop();
				if (dist[t] != g.n) continue;
				for (auto ind : g.g[u]) {
					edge &e = g.edges[ind];
					if (e.cap - e.flow >= l && dist[e.t] > dist[e.s] + 1) {
						dist[e.t] = dist[e.s] + 1;
						p[e.t] = ind;
						pq.push(e.t);
					}
				}
			}
			std::fill(c.begin(), c.end(), 0);
			return dist[t] != g.n;
		}

		int dfs(int s, int t, int l, int flow, graph &g) {
			if (s == t) return flow;
			for(;c[s] < (int)g.g[s].size(); c[s]++) {
				edge &e = g.edges[g.g[s][c[s]]];
				edge &re = g.edges[g.g[s][c[s]] ^ 1];
				if (e.cap - e.flow >= l && dist[e.t] == dist[e.s] + 1) {
					int add = dfs(e.t, t, l, std::min(flow, e.cap - e.flow), g);
					if (add > 0) {
						e.flow += add;
						re.flow -= add;
						return add;
					}
				}
			}
			return 0;
		}

		int run(int s, int t, graph &g) {
			const static int INF = (int)1e9;
			int res = 0;
			dist.resize(g.n);
			p.resize(g.n);
			c.resize(g.n);
			int L = 100;
			while (L) {
				while (bfs(s, t, L, g)) {
					while (1) {
						auto add = dfs(s, t, L, INF, g);
						if (add == 0) break;
						res += add;
					}
				}
				L >>= 1;
			}
			return res;
		}
	};
}
//nk
