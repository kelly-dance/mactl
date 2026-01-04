/**
 * Author: Kelly Dance
 * Date: 2025-12-13
 * Description: The simplest hash map.
 */
#pragma once

namespace CheeseMap {
	typedef int T;
	const int D = 4;
	const int SIZE = 1<<20;
	const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	T vals[SIZE];
	array<int,D> tags[SIZE];
	int hsh(const array<int,D>& key){
		unsigned long long v = 0;
		rep(i,0,D){
			v*=676767677;
			v+=key[i];
		}
		return __builtin_bswap64(v*C)%SIZE;
	}
	bool has(const array<int,D>& key, int h=-1){
		if(h==-1) h=hsh(key);
		return tags[h]==key;
	}
	T get(const array<int,D>& key, int h=-1){
		if(h==-1) h=hsh(key);
		return vals[h];
	}
	T set(const array<int,D>& key, const T& v, int h=-1){
		if(h==-1) h=hsh(key);
		tags[h]=key;
		return vals[h]=v;
	}
};



