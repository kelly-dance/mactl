/**
 * Author: ChatGPT
 * Description: break 1..n into inclusive intervals based on the result of $\lfloor \frac{n}{i} \rfloor$.
 * Time: $O(\sqrt N)$
 */
#pragma once

vector<pair<ll,pair<ll,ll>>> sqrtIntervals(ll n){
  vector<pair<ll,pair<ll,ll>>> res;
  for(ll l=n/2+1, r=n, f=1;; r=l-1, f=n/r, l=n/(f+1)+1){
    res.push_back({f,{l,r}});
    if(l==1) return res;
  }
}

