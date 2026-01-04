/**
 * Author: Kelly Dance
 * Date: 2025-09-06
 * Source: Based on cp-algos
 * Description: Find the inverse FPS
 * Time: O(n \log n)
 */
#pragma once

#include "../number-theory/euclid.h"
#include "./NumberTheoreticTransform.h"

vl polyinv(const vl& a){
	vl q={inv(a[0])};
	for(int z = 2; z<sz(a)*2; z*=2){
		vl qa = conv(q, {a.begin(), a.begin() + min(z, sz(a))});
		(qa[0]+=mod-2)%=mod;
		q=conv(q, qa);
		q.resize(z);
		for(ll& x : q) x=(mod-x)%mod;
	}
	q.resize(sz(a));
	return q;
}
