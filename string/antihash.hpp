#ifndef ANTIHASH_NK
#define ANTIHASH_NK

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

namespace nk {
	typedef __int128_t ll;

	inline ll add(ll a, ll b, ll p) {
		assert(a >= 0 && b >= 0);
		if ((a += b) >= p) a -= p;	
		return a;
	}

	inline ll mult(ll a, ll b, ll p) {
		ll res = 0;
		while (b) {
			if (b & 1) res = add(res, a, p);
			a = add(a, a, p);
			b >>= 1;
		}
		return res;
	}

	namespace antihash {

		struct h {
			ll x;
			int f, s;
			h() {}
			h(ll x, int f, int s): x(x), f(f), s(s) {}
		};

		bool operator <(const h &a, const h &b) {
			if (a.x != b.x) return a.x < b.x;
			if (a.f != b.f) return a.f < b.f;
			return a.s < b.s;
		}

		void go(int lvl, int ind, int flag, std::vector<std::vector<h>> &table, std::string &s, std::string &t) {
			if (ind == -1) return;
			if (lvl == 0) {
				int xx = table[lvl][ind].f;
				s[xx] = 'b';
				t[xx] = 'a';
				if (!flag) std::swap(s[xx], t[xx]);
				return ;
			}
			go(lvl - 1, table[lvl][ind].f, flag, table, s, t);
			go(lvl - 1, table[lvl][ind].s, flag ^ 1, table, s, t);
		}

		int build_test(ll p, ll q, int n, std::string &s, std::string &t) {
			static const int k = 18;
			assert(p < q);
			s = std::string(n, 'a');
			t = std::string(n, 'a');
			std::vector<std::vector<h>> table;
			table.push_back(std::vector<h>());
			table[0].resize(n);
			ll c = 1;
			for (int i = 0; i < n; i++) {
				table[0][i] = h(c, n - i - 1, n - i - 1);
				c = mult(c, p, q);
			}
			for (int lvl = 0; 1; lvl++) {
				sort(table[lvl].begin(), table[lvl].end());
				if ((int)table[lvl].size() < k) {
					std::vector<std::pair<ll, int>> t0;
					int nn = table[lvl].size();
					int n0 = nn / 2;
					int n1 = nn - n0;
					for (int mask = 0; mask < (1 << n0); mask++) {
						if (mask == 0) continue;
						ll sum = 0;
						for (int j = 0; j < n0; j++) {
							if (mask & (1 << j)) sum = add(sum , table[lvl][j].x, q);
						}
						t0.push_back(std::make_pair(sum, mask));
						if (sum == 0) {
							for (int j = 0; j < n0; j++) {
								if (mask & (1 << j)) go(lvl, j, 0, table, s, t);
							}
							return 1;
						}
					}
					sort(t0.begin(), t0.end());
					for (int mask = 0; mask < (1 << n1); mask++) {
						if (mask == 0) continue;
						ll sum = 0;
						for (int j = 0; j < n1; j++) {
							if (mask & (1 << j)) sum = add(sum , table[lvl][j + n0].x, q);
						}
						if (sum == 0) {
							for (int j = 0; j < n1; j++) {
								if (mask & (1 << j)) go(lvl, j + n0, 0, table, s, t);
							}
							return 1;
						}
						auto ind = lower_bound(t0.begin(), t0.end(), std::make_pair(q - sum, -1));
						if (ind != t0.end() && ind->first + sum == q) {
							for (int j = 0; j < n0; j++) {
								if (ind->second & (1 << j)) go(lvl, j, 0, table, s, t);
							}
							for (int j = 0; j < n1; j++) {
								if (mask & (1 << j)) go(lvl, j + n0, 0, table, s, t);
							}
							return 1;
						}
					}
					return 0;
				}
				if (table[lvl][0].x == 0) {
					go(lvl, 0, 0, table, s, t);
					return 1;
				}
				table.push_back(std::vector<h>((table[lvl].size() + 1) / 2));
				for (int i = 0; 2 * i + 1 < (int)table[lvl].size(); i++) {
					table[lvl + 1][i] = h(add(table[lvl][2 * i].x, q - table[lvl][2 * i + 1].x, q), 2 * i, 2 * i + 1);
				}
				if (table[lvl].size() & 1) {
					table[lvl + 1].back() = h(table[lvl].back().x, table[lvl].size() - 1, -1);
				}
			}
		}
	}
	//antihash
}
//nk
#endif
