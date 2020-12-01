
const int base = 10000, width = 4;
struct bigint : vector<int> {
    bigint(int x = 0) {
        while(x) pb(x%base), x /= base;
    }
    void trim() {
        while(size() && back() == 0) pop_back();
    }
    bigint operator+=(const bigint &b) {
        int carry = 0;
        if(b.size() > size()) resize(b.size());
        //debug(size()), debug(b.size());
        for(int i = 0; i < size(); i++) {
            at(i) += (i<b.size() ? b[i] : 0) + carry;
            carry = at(i) / base;
            at(i) %= base;
        }
        while(carry) pb(carry%base), carry /= base;
        trim();
        return *this;
    }
    bigint operator+(const bigint &b) const {
        bigint c = *this;
        c += b;
        return c;
    }
    bigint operator*(const bigint &b) {
        bigint c;
        c.resize(size()+b.size()+1);
        for(int i = 0; i < size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                c[i+j] += at(i)*b[j];
                c[i+j+1] += c[i+j] / base;
                c[i+j] %= base;
            }
        }
        for(int carry = 0; c.size() && c.back() >= base; c.pb(0)) {
            c.back() += carry;
            carry = c.back() / base;
            c.back() %= base;
        }
        trim();
        return c;
    }
    friend ostream& operator<<(ostream &O, bigint x) {
        if(x.empty()) return O << 0;
        reverse(x.begin(), x.end());
        O << x[0];
        for(int i = 1; i < x.size(); i++) {
            //O << '\'';
            if(x[i] == 0) {
                for(int k = 0; k < width; k++) O << 0;
            }else {
                int p = 1;
                for(int k = 0; k < width; k++) {
                    if(x[i] < p) O << 0;
                    p *= 10;
                }
                O << x[i];
            }
        }
        return O;
    }
}
