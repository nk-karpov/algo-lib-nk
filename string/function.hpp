#include "util.hpp"

namespace nk {
	vi border(const std::string &str) {
		vi p(str.size());
		if (!str.empty()) p[0] = -1;
		for (int i = 1; i < (int)str.size(); i++) {
			int k = p[i - 1];
			while (k >= 0 && str[i] != str[k + 1]) k = p[k];
			if (str[i] == str[k + 1]) k++;
			p[i] = k;
		}
		return p;
	}
	int get_border(const std::string &s, const vi &p, int k, char c) {
		while (k >= 0 && (k + 1 == (int)s.size() || c != s[k + 1])) k = p[k];
		if (c == s[k + 1]) k++;
		return k;
	}
	vi z(const std::string &str) {
		vi z(str.size(), 0);
		int k = 1;
		for (int i = 1; i < (int)str.size(); i++) {
			z[i] = std::max(std::min(z[k] + k - i, z[i - k]), 0);
			while (str[z[i]] == str[z[i] + i]) z[i]++;
			if (z[i] + i > k + z[k]) k = i;
		}
		return z;
	}
}

