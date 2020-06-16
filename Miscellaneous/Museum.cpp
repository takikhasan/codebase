/* error() function: */
int DEBUG_LINE = 0;
#define error(args...) { cout << "[DEBUG] Line " << DEBUG_LINE++ << ": "; string _s = #args; err(_s, 0, args); }
void err(const string &name, int in) {}
template<typename T, typename... Args>
void err(const string &name, int in, T a, Args... args) {
    if (name[in] == ' ') in++; string curr_name;
    while (in < SZ(name) && name[in] != ',') {
        if (name[in] == 34 || name[in] == 39) {
            curr_name.pb(name[in]);
            char c = name[in++];
            while (name[in] != c) curr_name.pb(name[in++]);
        }
        curr_name.pb(name[in++]);
    }
    if (curr_name.back() == ' ') curr_name.pop_back();
	OUT(curr_name), OUT(" = "), OUT(a), OUT((sizeof...(args) ? ", " : "\n"));
	err(name, ++in, args...);
}


/* error() function */
template<typename T1, typename T2>
inline ostream& operator<<(ostream& os, pair<T1, T2> p) { os << "{" << p.first << ", " << p.second << "}"; return os; }
template<typename T>
inline ostream& operator<<(ostream& os, vector<T>& a) { os << "["; for (int i = 0; i < (int)a.size(); i++) { if (i) os << ", "; os << a[i]; } os << "]"; return os; }


#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cout << *it << " = " << a << endl;
	err(++it, args...);
}
