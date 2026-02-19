/**
 * Author: Kelly Dance
 * Date: 2026-02-18
 * Description: smol[k] is the smallest prime factor of k
 */
#pragma once

static const vi smol = []{
	const int LIM = 1e7+10;
	vi smol(LIM); iota(all(smol), 0);
	for(int i = 2; i < LIM; i++) {
		if(smol[i] == i) for(ll j = (ll)i*i; j < LIM; j += i) {
			smol[j] = min(smol[j], i);
		}
	}
	return smol;
}();
