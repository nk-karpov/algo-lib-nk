#include <cstring>

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
}
//nk
