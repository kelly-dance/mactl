/**
 * Author: Kelly Dance
 * Date: 2025-09-06
 * Source: based on https://codeforces.com/blog/entry/111399
 * Description: Convolve polynomials $A*B$ where $A[i],B[i]$
 *   depend on $C[i]$ where $C[k]=\sum_{i+j=k-1} A[i]B[j]$ 
 * Time: O(n \log^2 n)
 */
#pragma once

#include "./NumberTheoreticTransform.h"

// c[k] = sum_{i+j=k-1} a[i]b[j]
// !!! maybe need to index wonkily to make ^^^ true
// f(i, c[i]) -> {a[i], b[i]}
template<class F>
vl onlinefft(int n, ll ic, F f){
	vl a(n), b(n), c(n,0);
	c[0]=ic;
	auto upd = [&](int l1, int r1, int l2, int r2, int m, int r){
		vl res = conv({a.begin()+l1, a.begin()+r1}, {b.begin()+l2,b.begin()+r2});
		int s = l1+l2+1;
		rep(i,m-s,min(sz(res),r-s)) (c[i+s]+=res[i])%=mod;
	};
	auto solve = [&](auto& solve, int l, int r) -> void {
		if(l+1==r){
			auto res = f(l, c[l]);
			a[l] = res.F;
			b[l] = res.S;
		}else{
			int m = (l+r)/2;
			solve(solve, l, m);
			upd(l, m, 0, min(m, r-l), m, r);
			upd(0, min(l,r-l), l, m, m, r);
			solve(solve, m, r);
		}
	};
	solve(solve, 0, n);
	return b;
};
