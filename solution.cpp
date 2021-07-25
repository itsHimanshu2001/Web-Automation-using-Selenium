#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;             //10^9+7
const ll inf = 10e16;   //10^16
#define endl '\n'

#define MAX 4000010


ll lowest_prime_factor[MAX];

void init(){                            //this func stores the lowest prime factors for each number for ex: for multiples of 2 we store 2 and for multiples of 3 we store 3 so that 
	for(ll i=2; i<MAX; ++i){           //when 27 comes up lowest_prime_factor[27] = 3 and so on like this
		if(i&1){
			lowest_prime_factor[i] = i;
		}else{
			lowest_prime_factor[i] = 2;
		}
	}

	for(ll i=3; i*i<MAX; i+=2){
		if(lowest_prime_factor[i] == i){
			for(ll j=i*i; j<MAX; j+=2*i){
				if(lowest_prime_factor[j] == j){
					lowest_prime_factor[j] = i;
				}
			}
		}
	}
}

void helper(vector<pair<ll, ll>> &vec, ll i, ll val, vector<ll> &ans){
	if(i == vec.size()){
        
		ans.push_back(val);
		return;
	}

	for(ll cnt=0; cnt<=vec[i].second; ++cnt){  // we are running for no. of occurences of each prime factors (we first dont include the prime factor)  case where we get 1 as factor 
		helper(vec, i+1, val, ans);    //we called recursion for the next factor straight away 
		val *= vec[i].first;           // and now we updated the val(included the prime factor)
	}

}

vector<ll> factors(ll n){
	
	vector<pair<ll, ll>> vec;    //this will store each prime factors and their counts

	while(n != 1){ 
		ll cnt = 0, val = lowest_prime_factor[n];        
		while(lowest_prime_factor[n] == val){

			n /= val;
			++cnt;
		}
		vec.push_back({val, cnt});
	}
    
   
	
	vector<ll> ans;       
	helper(vec, 0, 1, ans);   //this func will give us all factors for n by traversing through vec

	

	return ans;
}

void solve(){
    ll k;
    cin>>k;
    vector<ll> ans = factors(4*k+1);   //from each k we got to know the last pairs follows 4k+1
    //observation from posn after last GCD pair at every posn of multiples of factors of 4k+1 we get the possible highest factor at that posn
    //for ex. [1,3,9,27] for 81 so from posn before 81 if we start at 27th multiples index we get 27 and same for other factors too but in the case 18th index...9 (highest possible factor) will be considered 
    ll sum = 4*k+1;  //already included the last term in the sum
    sort(ans.begin(),ans.end());
    ll size = ans.size();
    vector<ll> cnt(size);   //stores the count of each factor
    cnt[size-1] = 0; // last number 4*k+1 we dont consider this
    for(ll i = size-2;i>=0;i--){
        cnt[i] = (2*k -1)/ans[i];  //by dividing (total terms -1) by this number we will get the no. of index lies in this no's multiples
        for(ll j =i+1;j<size-1;j++){ //we will remove contribution from higher multiple indexes (already been taken care of by bigger factors)
            if(ans[j]%ans[i] == 0){  //only if the bigger factor is divisible by this smaller factor
                cnt[i] -= cnt[j];                 
            }
            
        }
        sum += (ll)cnt[i]*ans[i];
    }
    cout<<sum<<endl;
}








int main(){
ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    init();
    ll t;
    cin>>t;
    while(t--){
	solve();
	}
   return 0;
}