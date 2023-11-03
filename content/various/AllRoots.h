/**
 * Author: Shashank Bhatt & Kelly Dance
 * License: CC0
 * Source: Adapted from https://cses.fi/paste/17afc28084d1ac7755778e/
 * Description: Applies a recurrence relation on a tree with every node as the root.
 * Modify operator+ to combine children into a single representation.
 * Modify the promote to combine a child representation with its parent (as well as parent's upward edge).
 * Time: O(N) Assuming merge/promote are O(1).
 * Memory: O(N) with bad constant factor.
 * Status: Tested on kattis:joiningnetwork and cses:1133
 */
#pragma once

vi ews;
vector<pii> el;

struct ART {
	ll ans = 0;
	ll size = 0;
	ART operator+(const ART& otr) const {
		return {ans + otr.ans, size + otr.size};
	}
	ART promote(int x, int e) const { // x=node index, e=edge index
		return {ans + (size + 1) * ews[e], size + 1};
	}
};
template<class T>
struct AllRoots {
	int n;
	vector<vector<pii>> adj;
	vector<vector<T>> pre, suf;
	AllRoots(vector<pii>& el) : n(sz(el)+1), adj(sz(el)+1), pre(sz(el)+1), suf(sz(el)+1) {
		rep(i,0,n-1){
			adj[el[i].F].pb({el[i].S,i});
			adj[el[i].S].pb({el[i].F,i});
		}
		rep(i,0,n) {
			pre[i].resize(adj[i].size() + 1);
			suf[i].resize(adj[i].size() + 1);
		}
	}
	T get(int x, int i = 0){
		T& v = suf[x][i+1];
		if(i) v = pre[x][i] + v; 
		return v.promote(x, adj[x][i].S);
	};
	T down(int x, int p = -1) {
		for(auto& c : adj[x]) if(c.F == p) swap(c, adj[x][0]);
		for(int i = adj[x].size()-1; i > -(p<0); --i)
			suf[x][i] = down(adj[x][i].F, x) + suf[x][i+1];
		return get(x);
	}
	void up(int x, int p = -1) {
		rep(i, p != -1, adj[x].size()) {
			pre[x][i+1] = pre[x][i] + get(adj[x][i].F);
			pre[adj[x][i].F][1] = get(x, i);
			up(adj[x][i].F, x);
		}
	}
	static vector<T> calc(vector<pii>& el) {
		AllRoots ar(el);
		ar.down(0);
		ar.up(0);
		vector<T> res(ar.n);
		rep(i,0,ar.n) res[i] = ar.pre[i].back(); // optional promote here.
		return res;
	}
};

int example() {
	// sum of distances to all nodes in weighted tree
	int n;cin>>n;
	ews.resize(n-1);
	el.resize(n-1);
	rep(i,0,n-1){
		cin>>el[i].F>>el[i].S>>ews[i];
		el[i].F--;
		el[i].S--;
	}
	auto res = AllRoots<ART>::calc(el);
	rep(i,0,n)cout<<res[i].ans<<' ';
	cout<<endl;
}
