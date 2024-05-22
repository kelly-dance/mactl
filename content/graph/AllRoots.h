/**
 * Author: Shashank Bhatt
 * License: CC0
 * Description: Applies a recurrence relation on a tree with every node as the root.
 * Modify operator+ to combine children into a single representation.
 * Modify the promote to combine a child representation with its parent (as well as parent's upward edge).
 * Time: O(N) Assuming merge/promote are O(1).
 * Memory: O(N) with bad constant factor.
 * Status: Tested on kattis:joiningnetwork and cses:1133
 */
#pragma once

struct ART {
	ll ans=0, kids=0;
	ART operator+(const ART& otr) const {}
	ART promote(int x, int e) const {
		// x=node index, e=edge index, e==-1 means x in root
		if(e==-1) return *this; // ex sum of distance from each node (unweighted)
		return {ans+kids+1,kids+1};
	}
};
template<class T>
struct AllRoots {
	int n;
	vector<vector<pii>> adj;
	vector<vector<T>> pre;
	vector<T> res;
	AllRoots(vector<pii>& el): n(sz(el)+1), adj(n), pre(n), res(n) {
		rep(i,0,n-1) {
			adj[el[i].F].pb({el[i].S,i});
			adj[el[i].S].pb({el[i].F,i});
		}
	}
	T down(int x, int p = -1) {
		int par_idx = -1;
		T val{};
		for(pii e:adj[x]) {
			if(e.F == p) par_idx = e.S;
			else val = val + down(e.F,x), pre[x].pb(val);
		}
		return val.promote(x,par_idx);
	}
	void up(int x, int p = -1) {
		reverse(all(adj[x]));
		for(pii e:adj[x]) {
			if(e.F == p) continue;
			if (sz(pre[x])) pre[x].pop_back();
			res[e.F] = (sz(pre[x]) ? res[x] + pre[x].back() : res[x]).promote(x,e.S);
			res[x] =  res[x] + (sz(pre[e.F]) ? pre[e.F].back() : T{}).promote(e.F,e.S);
			up(e.F, x);
		}
		res[x] = res[x].promote(x,-1);
	}
	static vector<T> calc(vector<pii>& el) {
		AllRoots ar(el);
		ar.down(0); ar.up(0);
		return ar.res;
	}
};
