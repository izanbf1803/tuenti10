string to_string(string s) 
{
    return '"' + s + '"';
}

string to_string(const char* s) 
{
    return to_string((string) s);
}

string to_string(bool b) 
{
    return (b ? "true" : "false");
}

string to_string(char ch) 
{
    return string("'")+ch+string("'");
}

template <typename A, typename B>
string to_string(pair<A, B> p) 
{
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <class InputIterator>
string to_string (InputIterator first, InputIterator last) 
{
    bool start = true;
    string res = "{";
    while (first!=last) {
        if (!start) {
            res += ", ";
        }
        start = false;
        res += to_string(*first);
        ++first;
    }
    res += "}";
    return res;
}

template <typename A> 
string to_string(A v) 
{
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template<typename A,size_t N>
string to_string(A(&v)[N])
{
    bool first = true;
    string res = "{";
    for (int i=0;i<N;i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}    

string to_string(const vector<bool>& v)
{
    string res;
    for (int i = 0; i < (int)v.size(); ++i) {
        res += char('0'+v[i]);
    }
    return res;
}

template<size_t N>
string to_string(const bitset<N>& v)
{
    string res;
    for (int i = 0; i < (int)v.size(); ++i) {
        res += char('0'+v[i]);
    }
    return res;
}

#define D(x) cerr << #x << " = " << to_string(x) << ", "
