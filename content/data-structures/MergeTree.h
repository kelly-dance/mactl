/**
 * Author: Nathan George
 * License: CC0
 * Description: Segtree like structure that stores the sorted subarray
 * at each node to support queries that are fast on sorted data and can be combined with +.
 * Time: O(N \log N) construction, O(\log N) * O(f) per query.
 * Memory: O(N \log N).
 * Status: Tested on https://judge.yosupo.jp/problem/range_kth_smallest
 */
#pragma once

struct MergeTree {
	typedef int T;
	typedef int R;
	typedef int Q;
	static constexpr R zero = 0;
	typedef vector<T>::iterator iter;
	void f(iter a, int len, Q q, R& x) {
		x += lower_bound(a,a+len, q) - a;
	}
	int n; int h; vector<T> s;
	MergeTree(vector<T> const &a = {}) : n(sz(a)), h(33-__builtin_clz(n-1)), s(n*h) {
		iter e = copy(all(a), s.begin());
		for(int x = 1; x < n; x *= 2) {
			for (iter t = e-n; t+x<e; t+=2*x)
				merge(t, t+x, t+x, min(e, t+2*x), t+n);
			e+=n;
		}
	}
	R query(int b, int e, Q q) { // query [b, e)
		R x=zero;
		iter t = s.begin();
		for (int i = 1; b<e; i*=2, t+=n) {
			if (b&i) {f(t + b, i, q, x); b+=i;}
			if (e&i) {e-=i; f(t + e, i, q, x);}
		}
		return x;
	}
};
