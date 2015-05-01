#ifndef NK_MCMF
#define NK_MCMF
#include <algorithm>
#include <cassert>
#include <vector>
#include <queue>
#include <cmath>


#define eprintf(...) fprintf(stderr, __VA_ARGS__)


namespace nk {
	namespace mcmf {
		using t_f = long double;
		using t_w = long double;
		const t_w INF = 1. / 0.;

		struct edge {
			int s, t;
			t_f c, f;
			t_w w;
			edge() {}
			edge(int s, int t, t_f c, t_f f, t_w w): s(s), t(t), c(c), f(f), w(w) {}
		};

		struct graph {
			int n;
			std::vector<std::vector<int>> adj;
			std::vector<edge> edges;
			graph(int n): n(n) {
				adj.resize(n);
			}
			void add_edge(int s, int t, t_f c, t_w w) {
				adj[s].push_back(edges.size());
				edges.push_back(edge(s, t, c, 0, w));
				adj[t].push_back(edges.size());
				edges.push_back(edge(t, s, 0, 0, -w));
			}
		};

		void sp_3(graph &g, int s, std::vector<t_w> &d, std::vector<t_w> &ph, std::vector<int> &p) {
			std::queue<int> pq;
			std::vector<bool> v(g.n, 0);
			pq.push(s);
			d[s] = 0;
			v[s] = 1;
			while (!pq.empty()) {
				s = pq.front();
				pq.pop();
				v[s] = 0;
				for (auto id : g.adj[s]) {
					const edge &e = g.edges[id];
					if (e.c - e.f > 0 && d[e.t] + ph[e.t] > d[e.s] + ph[e.s] + e.w) {
						d[e.t] = ph[e.s] + d[e.s] - ph[e.t] + e.w;
						if (!v[e.t]) pq.push(e.t);
						v[e.t] = 1;
						p[e.t] = id;
					}
				}
			}
		}

		void sp_1(graph &g, int s, std::vector<t_w> &d, std::vector<t_w> &ph, std::vector<int> &p) {
			std::fill(p.begin(), p.end(), -1);
			std::fill(d.begin(), d.end(), INF);
			std::priority_queue<std::pair<t_w, int> > pq;
			d[s] = 0;
			pq.push(std::make_pair(-d[s], s));
			while (!pq.empty()) {
				auto cur = pq.top();
				pq.pop();
				s = cur.second;
				if (d[s] != -cur.first) continue;
				for (auto id : g.adj[s]) {
					const edge &e = g.edges[id];
					if (e.c - e.f > 0 && d[e.t] + ph[e.t] > d[e.s] + ph[e.s] + e.w) {
						d[e.t] = d[e.s] + ph[e.s] - ph[e.t] + e.w;
						p[e.t] = id;
						pq.push(std::make_pair(-d[e.t], e.t));
					}
				}
			}
		}

		void sp_2(graph &g, int s, std::vector<t_w> &d, std::vector<t_w> &ph, std::vector<int> &p) {
			std::fill(p.begin(), p.end(), -1);
			std::fill(d.begin(), d.end(), INF);
			std::vector<bool> v(g.n, false);
			d[s] = 0;
			while (1) {
				int ind = -1;
				for (int i = 0; i < g.n; ++i) {
					if (!v[i] && (ind == -1 || d[ind] > d[i])) ind = i;
				}
				if (ind == -1) break;
				s = ind;
				v[s] = true;
				for (auto id : g.adj[s]) {
					const edge &e = g.edges[id];
					if (e.c - e.f > 0 && d[e.t] + ph[e.t] > d[e.s] + ph[e.s] + e.w) {
						d[e.t] = d[e.s] + ph[e.s] + e.w - ph[e.t];
						p[e.t] = id;
					}
				}
			}
		}

		void mcmf(graph &g, int s, int t, t_f L, t_f &f, t_w &w) {
			w = 0;
			f = 0;
			std::vector<t_w> ph(g.n, 0);
			std::vector<int> p(g.n, -1);
			std::vector<t_w> d(g.n, INF);
			sp_2(g, s, d, ph, p);
			while (1) {
				sp_2(g, s, d, ph, p);
				if (p[t] == -1) break;
				int v = t;
				t_f vf = L - f;
				while (p[v] != -1) {
					const edge &e = g.edges[p[v]];
					vf = std::min(vf, e.c - e.f);
					v = e.s;
				}
				assert(vf > 0);
				f += vf;
				v = t;
				while (p[v] != -1) {
					edge &e = g.edges[p[v]];
					edge &er = g.edges[p[v] ^ 1];
					w += e.w * vf;
					e.f += vf;
					er.f -= vf;
					v = e.s;
				}
				for (int i = 0; i < g.n; i++) ph[i] += d[i];
				if (f == L) break;
			}
		}

		void compose(graph &g, int s, int t, std::vector<int> &p) {
			if (s == t) return;
			for (auto id : g.adj[s]) {
				const edge &e = g.edges[id];
				if (e.f > 0) {
					p[e.t] = id;
					return compose(g, e.t, t, p);
				}
			}
		}
	}
}
//end nk

#endif NK_LIB_MCMF
