/**
 * Author: Shashank Bhatt & Kelly Dance
 * License: CC0
 * Source: Adapted from https://cses.fi/paste/17afc28084d1ac7755778e/
 * Description: Applies a recurrence relation on a tree with every node as the root.
 * Modify the merge function to combine children into a single representation.
 * Modify the promote function to combine a child representation with its parent.
 * Time: O(N) Assuming merge/promote are O(1).
 * Status: Tested on kattis:joiningnetwork and cses:1133
 */
#pragma once

typedef pair<ll,ll> T;
struct AllRoots {
	int n;
	vector<vi> adj;
	vector<vector<T>> pre, suf;
	const T unit = {0, 0};
	AllRoots(int n) : n(n), adj(n), pre(n), suf(n) {}
	// !!!
	T merge(const T& v1, const T& v2) {
		return {v1.F + v2.F, v1.S + v2.S};
	}
	T promote(const T& v1) {
		return {v1.F + v1.S, v1.S + 1};
	}
	T get(int x, int i = 0){
		return promote(merge(pre[x][i], suf[x][i+1]));
	};
	void addEdge(int u, int v){
		adj[u].pb(v);
		adj[v].pb(u);
	}
	T down(int x, int p = -1) {
		for(auto& c : adj[x]) if(c == p) swap(c, adj[x][0]);
		for(int i = adj[x].size()-1; i > -(p<0); --i)
			suf[x][i] = merge(down(adj[x][i], x), suf[x][i+1]);
		return get(x);
	}
	void up(int x, int p = -1) {
		rep(i, p != -1, adj[x].size()) {
			pre[x][i+1] = merge(pre[x][i], get(adj[x][i]));
			pre[adj[x][i]][1] = get(x, i);
			up(adj[x][i], x);
		}
	}
	vector<T> calc(int root = 0) {
		rep(i,0,n) {
			pre[i].assign(adj[i].size() + 1, unit);
			suf[i].assign(adj[i].size() + 1, unit);
		}
		down(root);
		if(sz(adj[root]))
			pre[root][1] = get(adj[root][0]);
		up(root);
		vector<T> res(n);
		rep(i,0,n) res[i] = promote(pre[i].back());
		return res;
	}
};