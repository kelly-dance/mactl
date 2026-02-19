/**
 * Author: Kelly Dance
 * Date: 2025-09-07
 * Source: based on cp-algos
 * Description: log and exp of FPS
 * Time: O(n \log n)
 */
#pragma once

#include "./PolyInverse.h"

vl polylog(const vl& a){
	assert(a[0]==1);
	if(sz(a)==1) return {0};
	vl ap(sz(a)-1);
	rep(i,0,sz(a)-1) ap[i]=(a[i+1]*(i+1))%mod;
	vl r = conv(ap, polyinv(a));
	r.resize(sz(a)-1);
	r.insert(r.begin(), 0);
	rep(i,1,sz(a)) r[i]=(r[i]*inv(i))%mod;
	return r;
}

vl polyexp(const vl& p){
	assert(p[0]==0);
	vl q = {1};
	for(int z = 1; z < sz(p)*2; z*=2){
		vl lq = polylog(q);
		vl o{p.begin(), min(p.end(), p.begin()+2*z)};
		o[0]=(o[0]+1)%mod;
		rep(i,0,min(sz(o),sz(lq)))o[i]=(o[i]-lq[i]+mod)%mod;
		q=conv(q, o);
		q.resize(2*z);
	}
	q.resize(sz(p));
	return q;
}
