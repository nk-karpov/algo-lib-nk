#include "util.hpp"

namespace nk {
	using vi = std::vector<int>;
	struct suffix_array {
		vi p, lcp;
		suffix_array(const std::string &str) {
			int n = (int)str.size();
			vi cnt(std::max(n, MAXK) + 1, 0);
			vi c(n, 0), cd(n, 0), pn(n, 0);
			lcp.resize(n);
			p.resize(n);
			for (int i = 0; i < n; i++) p[i] = i;
			p.resize(n);
			int cn = MAXK;
			for (int i = 0; i < n; i++) c[i] = str[i] - 'a';
			for (int k = -1; pow2(k) <= n; k++) {
				std::fill(cnt.begin(), cnt.begin() + cn, 0);
				for (int i = 0; i < n; i++) {
					cnt[c[i]]++;
					pn[i] = (p[i] - pow2(k) + n) % n;
				}
				for (int i = 0; i < cn; i++) cnt[i + 1] += cnt[i];
				for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
				cn = 1;
				cd[p[0]] = cn - 1;
				for (int i = 1; i < n; i++) {
					int ave1 = (p[i - 1] + pow2(k) + n) % n; 
					int ave2 = (p[i] + pow2(k) + n) % n;
					cn += c[p[i -1]] != c[p[i]] || c[ave1] != c[ave2];
					cd[p[i]] = cn - 1;
				}
				std::copy(cd.begin(), cd.end(), c.begin());
				if (cn == n && k != -1) break;
			}
			std::fill(cnt.begin(), cnt.begin() + cn, 0);
			std::copy(p.begin(), p.end(), pn.begin());
			for (int i = 0; i < n; i++) cnt[c[i]]++;
			for (int i = 0; i < cn; i++) cnt[i + 1] += cnt[i];
			for (int i = 0; i < n; i++) p[--cnt[c[i]]] = i;
			for (int i = 0; i < n; i++) pn[p[i]] = i;
			for (int i = 0, cur = 0; i < n; i++) {
				int t = pn[i] + 1;
				if (t == n) {
					lcp[t - 1] = cur = 0;
				} else {
					int j = p[t];
					while (cur < n && str[(i + cur) % n] == str[(j + cur) % n]) cur++;
					lcp[t - 1] = cur;
					cur = std::max(0, cur - 1);
				}
			}
		}
	};
}
//nk
