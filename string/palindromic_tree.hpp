#include "util.hpp"
#include <vector>
#include <string>

namespace nk {
	struct palindromic_tree {
		int last;
		std::vector<state> st;
		palindromic_tree() {
			st.push_back(state(-1, -1));
			st.push_back(state(-1, 0));
			st.push_back(state(0, 1));
			last = 2;
			for (int i = 0; i < MAXK; i++) st[0].next[i] = 2;
		}
		void extend(const std::string &str, int ind) {
			while (ind - st[last].len - 1 < 0 || str[ind - st[last].len - 1] != str[ind]) 
				last = st[last].link;
			int q = last;
			if (st[q].next[str[ind] - 'a'] == -1) {
				st[q].next[str[ind] - 'a'] = st.size(); 
				st.push_back(state(st[q].len + 2, -1));
			}
			last = st[q].next[str[ind] - 'a'];
			q = st[q].link;
			while (ind - st[q].len - 1 < 0 || str[ind - st[q].len - 1] != str[ind]) 
				q = st[q].link;
			st[last].link = st[q].next[str[ind] - 'a'];
		}
	};
}
//nk
