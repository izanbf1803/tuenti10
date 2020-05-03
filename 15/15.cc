#include <bits/stdc++.h>
using namespace std;

using ul = unsigned long;

struct DNA {
    list<pair<size_t,int>> bytes;
    size_t size;
    DNA() {}
    DNA(size_t size_) {
        bytes = list<pair<size_t,int>>();
        size = size_;
    }
};

const ul POLYNOMIAL = 0xEDB88320;
const string DIR = "animals";
const ul LAST_7_BITS = 0x7f;
const size_t PRECOMP_STEP = 10000;

ul crc_table[256];
ul* precomp;
map<string,DNA> dnas;

// https://stackoverflow.com/questions/26049150/calculate-a-32-bit-crc-lookup-table-in-c-c
void make_crc_table() {
    ul remainder;
    unsigned char b = 0;
    do {
        remainder = b;
        for (ul bit = 8; bit > 0; --bit) {
            if (remainder & 1)
                remainder = (remainder >> 1) ^ POLYNOMIAL;
            else
                remainder = (remainder >> 1);
        }
        crc_table[(size_t)b] = remainder;
    } while(0 != ++b);
}

ul step_zero(ul crc) {
    return crc_table[crc&0xff] ^ (crc>>8);
}

ul steps_zeros_naive(ul crc, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        crc = step_zero(crc);
    }
    return crc;
}

ul steps_zeros(ul crc, size_t n) {
    while (n > 0) {
        if (n >= PRECOMP_STEP and (crc & LAST_7_BITS) == 0) {
            crc = precomp[crc>>7];
            n -= PRECOMP_STEP;
        }
        else {
            crc = step_zero(crc);
            --n;
        }
    }
    return crc;
}


ul gen_crc(list<pair<size_t,int>> bytes, size_t size) {
    ul crc = 0xfffffffful;

    size_t i = 0;
    for (auto p : bytes) {
        size_t pos = p.first;
        ul byte = p.second;

        if (i < pos) {
            crc = steps_zeros(crc, pos-i);
            i = pos;
        }

        crc = crc_table[byte^(crc&0xff)] ^ (crc>>8);
        ++i;
    }

    crc = steps_zeros(crc, size-i);

    return ~crc;
}

string crc_hex(ul n) {
    string res;
    for (int i = 0; i < 8; ++i) {
        char c = n%16;
        if (c < 10)
            c = char(c + '0');
        else
            c = char(c - 10 + 'a');
        n /= 16;
        res.push_back(c);
    }
    reverse(res.begin(), res.end());
    return res;
}

void insert(DNA& dna, size_t pos, int byte) {
    auto it = dna.bytes.begin();

    while (it != dna.bytes.end() and it->first < pos) {
        ++it;
    }

    dna.bytes.insert(it, {pos, byte});

    while (it != dna.bytes.end()) {
        ++it->first;
        ++it;
    }

    ++dna.size;
}

inline ul gen_crc(const DNA& dna) { return gen_crc(dna.bytes, dna.size); }


int main() {
    make_crc_table();

    precomp = new ul[1<<25];

    ul crc = 0;
    do {
        if ((crc & LAST_7_BITS) == 0) {
            precomp[crc>>7] = steps_zeros_naive(crc, PRECOMP_STEP);
        }

        ++crc;
    } while (crc != 0);

    string name;
    long long size;
    ifstream fin("file_sizes.txt");
    while (fin >> name >> size) {
        dnas[name] = DNA((size_t)size);
    }
    fin.close();
    
    int m;
    while (cin >> name >> m) {
        DNA& dna = dnas[name];
        cout << name << " " << 0 << ": " << crc_hex(gen_crc(dna)) << endl;
        for (int i = 0; i < m; ++i) {
            long long pos;
            int val;
            cin >> pos >> val;
            insert(dna, (size_t)pos, val);
            cout << name << " " << i+1 << ": " << crc_hex(gen_crc(dna)) << endl;
        }
    }
}