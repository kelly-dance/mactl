/**
 * Author: Joseph Durie
 * Date: 2020-10-11
 * Description: Remember that idT and idU must be idempotent
 * Time: O(\log N)
 */
#pragma once

struct lztree {
	typedef ll T; T idT = {};
	typedef ll U; U idU = {};
	// combining segtree nodes a and b
	T f(T a, T b) { return a + b; }
	// applying updates a and b (in that order)
	U g(U b, U a) { return a + b; }
	// applying update b to segtree node a
	T h(U b, T a) { return a + b; }
	int n;
	vector<T> t;
	vector<U> d;
	lztree(int n) : n(n), t(2*n), d(n, idU) {}
	void calc(ll p) { t[p] = h(d[p], f(t[p * 2], t[p * 2 + 1])); }
	void apply(ll p, U v) {
		t[p] = h(v, t[p]);
		if(p < n) d[p] = g(v, d[p]);
	}
	void push(ll p) {
		p += n;
		for(int s = 19; s > 0; s--){
			ll i = p >> s;
			if(d[i] != idU) {
				apply(i * 2, d[i]);
				apply(i * 2 + 1, d[i]);
				d[i] = idU;
			}
		}
	}
	void modify(ll p, T v) {
		push(p);
		t[p += n] = v;
		while(p > 1) calc(p /= 2);
	}
	void modify(ll l, ll r, U v) {
		push(l), push(r - 1);
		bool cl = false, cr = false;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(cl) calc(l - 1);
			if(cr) calc(r);
			if(l & 1) apply(l++, v), cl = true;
			if(r & 1) apply(--r, v), cr = true;
		}
		for(--l; r; l /= 2, r /= 2) {
			if(cl) calc(l);
			if(cr) calc(r);
		}
	}
	T query(ll l, ll r) {
		push(l), push(r - 1);
		T resl = idT, resr = idT;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(l & 1) resl = f(resl, t[l++]);
			if(r & 1) resr = f(t[--r], resr);
		}
		return f(resl, resr);
	}
};
