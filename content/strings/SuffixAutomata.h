/**
 * Author: idk
 * Date: 2025-09-05
 * License: Unknown
 * Source: cp-algos
 * Description: A DFA that accepts all suffixes. 
 * call the \texttt{link} of a node its parent
 * Accept states are all ancestors of \texttt{last}.
 * Time: O(n |\Sigma|)
 * Status: Barely tested, needs better description too
 */
#pragma once

const int alphasize = 26, alphastart = 'a';
struct SuffixAutomata {
	struct node {
		array<int, alphasize> next;
		int link, len;
		node(int link, int len) : link(link), len(len) {
			rep(i,0,alphasize) next[i]=-1;
		};
	};
	vector<node> st;
	int last;
	int make(int link, int len){
		st.emplace_back(link, len);
		return sz(st)-1;
	}
	int addChar(char cr){
		int c = cr - alphastart;
		int cur = make(0, st[last].len + 1);
		int p = last;
		for(; p != -1 && st[p].next[c] == -1; p=st[p].link) {
			st[p].next[c] = cur;
		}
		if(p!=-1){
			int q = st[p].next[c];
			if(st[p].len + 1 == st[q].len){
				st[cur].link = q;
			}else{
				int clone = make(st[q].link, st[p].len + 1);
				st[clone].next = st[q].next;
				st[q].link = st[cur].link = clone;
				for(; p != -1 && st[p].next[c] == q; p = st[p].link){
					st[p].next[c] = clone;
				}
			}
		}
		return last = cur;
	};
	SuffixAutomata(const string& s) : last(make(-1, 0)) {
		st.reserve(2*sz(s));
		for(char cr : s) addChar(cr);
	}
};
