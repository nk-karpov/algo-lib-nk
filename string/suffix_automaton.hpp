#include "util.hpp"

namespace nk {
	struct suffix_automaton {
		std::vector<state> st;
		int last;
		suffix_automaton() {
			st.push_back(state(0, -1));
			last = 0;
		}
		void extend(int c) {
			int p = last;
			last = st.size();
			st.push_back(state(st[p].len + 1, -1));
			while (p != -1 && st[p].next[c] == -1) {
				st[p].next[c] = last;
				p = st[p].link;
			}
			if (p == -1) {
				st[last].link = 0;
			} else {
				int q = st[p].next[c];
				if (st[q].len == st[p].len + 1) {
					st[last].link = q;
				} else {
					int clone = st.size();
					st.push_back(state(st[p].len + 1, st[q].link));
					for (int i = 0; i < MAXK; i++) st[clone].next[i] = st[q].next[i];
					while (p != -1 && st[p].next[c] == q) {
						st[p].next[c] = clone;
						p = st[p].link;
					}
					st[last].link = st[q].link = clone;
				}
			}
		}
	};
}
//nk
