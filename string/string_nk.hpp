#include <vector>
#include <string>

namespace nk {
	static const int MAXK = 26;
	struct state {
		int len;
		int link;
		int next[MAXK];
		state(int len, int link):len(len), link(link) {
			memset(next, -1, sizeof next);
		}
	};

	struct palindrome_trie {
		int last;
		std::vector<state> st;
		palindrome_trie() {
			st.push_back(state(-1, -1));
			st.push_back(state(-1, 0));
			st.push_back(state(0, 1));
			last = 2;
			for (int i = 0; i < MAXK; i++) st[0].next[i] = 2;
		}
		void extend(const std::string &str, int ind) {
			while (ind - st[last].len - 1 < 0 || str[ind - st[last].len - 1] != str[ind]) last = st[last].link;
			int q = last;
			if (st[q].next[str[ind] - 'a'] == -1) {
				st[q].next[str[ind] - 'a'] = st.size(); 
				st.push_back(state(st[q].len + 2, -1));
			}
			last = st[q].next[str[ind] - 'a'];
			q = st[q].link;
			while (ind - st[q].len - 1 < 0 || str[ind - st[q].len - 1] != str[ind]) q = st[q].link;
			st[last].link = st[q].next[str[ind] - 'a'];
		}
	};
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
//nk
