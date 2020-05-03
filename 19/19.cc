#include <bits/stdc++.h>
using namespace std;

#include "debug.h"

// const string FILE_ = "test";
const string FILE_ = "better_farm_systems_test_image";

using ll = long long;

vector<int> get_file_bytes(string filename) {
	ifstream input(filename, ios::binary);
    vector<char> bytes(
         (istreambuf_iterator<char>(input)),
         (istreambuf_iterator<char>()));
   	input.close();
   	vector<int> ibytes(bytes.size());
   	for (size_t i = 0; i < bytes.size(); ++i) {
   		ibytes[i] = int((unsigned char)bytes[i]);
   	}
   	return ibytes;
}

const ll P = 31; // polynomial hash base
const ll Pinv = 838709685; // P^-1 mod M
const ll M = 1e9 + 9; // polynomial hash modulus
vector<ll> preh; // prefix hash, preh[i] = hash[0...i-1], preh[0] = 0
vector<ll> minv; // Pinv^i

void precompute(const vector<int>& data) {
	int n = data.size();
	preh.assign(n+1, 0);
	preh[0] = 0;
	ll p_pow = 1;
	for (int i = 0; i < n; ++i) {
		preh[i+1] = (preh[i] + (data[i] + 1) * p_pow) % M;
		p_pow = (p_pow * P) % M;
	}
	minv.assign(n+1, 0);
	minv[0] = 1;
	for (int i = 1; i < n+1; ++i) {
		minv[i] = (minv[i-1] * Pinv) % M;
	}
}

ll hashv(int l, int r) {
	return ((preh[r+1] - preh[l] + M) * minv[l]) % M;
}

pair<int,int> find_coincidence_aprox(int n, int len) {
	for (int i = 0; i+len-1 < n; i += int(1e6)) {
		for (int j = i+1; j+len-1 < n; ++j) {
			ll hi = hashv(i, i+len-1);
			ll hj = hashv(j, j+len-1);
			if (hi == hj) return {i, j};
		}
	}
	return {-1, -1};
}

pair<int,int> find_coincidence(int n, int len) {
	for (int i = 0; i+len-1 < n; ++i) {
		for (int j = i+1; j+len-1 < n; ++j) {
			ll hi = hashv(i, i+len-1);
			ll hj = hashv(j, j+len-1);
			if (hi == hj) return {i, j};
		}
	}
	return {-1, -1};
}

int main() {
	// vector<int> v = get_file_bytes(FILE_);
	// int n = v.size();
	// vector<pair<int,int>> c;
	// c.emplace_back(v[0], 1);
	// for (int i = 1; i < n; ++i) {
	// 	if (v[i] == c.back().first) {
	// 		++c.back().second;
	// 	}
	// 	else {
	// 		c.emplace_back(v[i], 1);
	// 	}
	// }
	// cout << to_string(c) << endl;
	vector<int> data = get_file_bytes(FILE_);
	precompute(data);

	int n = data.size();

	int L = 1;
	int R = n;
	int len = 0;
	while (L <= R) {
		int M = (L+R)/2;
		D(M), D(L), D(R) << endl;
		pair<int,int> coinc = find_coincidence_aprox(n, M);
		if (coinc.first == -1) {
			R = M-1;
		}
		else {
			len = M;
			L = M+1;
		}
	}

	D(len), D(find_coincidence_aprox(n, len)) << endl;
}