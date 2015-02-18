#include "util.hpp"
#include <vector>
#include <string>

namespace nk {
	struct suffix_automaton {
		std::vector<state> st;
		int last;
		suffix_automaton() {
			st.push_back(state(0, -1));
			last = 0;
		}
		void extend(char c) {
			int p = last;
			last = st.size();
			st.push_back(state(st[p].len + 1, -1));
			while (p != -1 && st[p].next[c - 'a'] == -1) st[p].next[c - 'a'] = last;
			if (p == -1) {
				st[last].link = 0;
			} else {
				int q = st[p].next[c - 'a'];
				if (st[q].len == st[p].len + 1) {
					st[last].link = q;
				} else {
					int clone = st.size();
					st.push_back(state(st[p].len + 1, st[q].link));
					for (int i = 0; i < MAXK; i++) st[clone].next[i] = st[q].next[i];
					while (p != -1 && st[p].next[c - 'a'] == q) st[p].next[c - 'a'] = clone;
					st[last].link = st[q].link = clone;
				}
			}
		}
	};
}
