#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
int num[4];
struct Elem {
    pair<int, int> score;
    string expression;
    Elem(int x) {
        this->score = mp(x, 1);
        this->expression = to_string(x);
    }
    Elem(int x, int y) {
        this->score = mp(x, y);
        this->expression = to_string(x) + '/' + to_string(y);
    }
    Elem operator+(const Elem &other) const {
        Elem newElem(this->score.fi * other.score.se + this->score.se * other.score.fi, this->score.se * other.score.se);
        newElem.expression = '(' + this->expression + '+' + other.expression + ')';
        return newElem;
    }
    Elem operator-(const Elem &other) const {
        Elem newElem(this->score.fi * other.score.se - this->score.se * other.score.fi, this->score.se * other.score.se);
        newElem.expression = '(' + this->expression + '-' + other.expression + ')';
        return newElem;
    }
    Elem operator*(const Elem &other) const {
        Elem newElem(this->score.fi * other.score.fi, this->score.se * other.score.se);
        newElem.expression = '(' + this->expression + '*' + other.expression + ')';
        return newElem;
    }
    Elem operator/(const Elem &other) const {
        Elem newElem(this->score.fi * other.score.se, this->score.se * other.score.fi);
        newElem.expression = '(' + this->expression + '/' + other.expression + ')';
        return newElem;
    }
    void Simplify() {
        int GCD = __gcd(this->score.fi, this->score.se);
        this->score = mp(this->score.fi / GCD, this->score.se / GCD);
    }
} ;
bool dfs(vector<Elem> cur);
bool getNewElems(vector<Elem> source, int pos1, int pos2, char op)
{
    vector<Elem> target;
    for (int i = 0; i < (int)source.size(); ++i) {
        if (i == pos1 || i == pos2)
            continue;
        target.pb(source[i]);
    }

    Elem newElem(1, 1);
    switch (op) {
        case '+':
            newElem = source[pos1] + source[pos2];
            break;
        case '-':
            newElem = source[pos1] - source[pos2];
            break;
        case '*':
            newElem = source[pos1] * source[pos2];
            break;
        case '/':
            if (source[pos2].score.fi != 0) {
                newElem = source[pos1] / source[pos2];
            } else {
                return false;
            }
            break;
    }

    target.pb(newElem);
    return dfs(target);
}
bool dfs(vector<Elem> cur)
{
    if ((int)cur.size() == 1) {
        cur[0].Simplify();
        if (cur[0].score.fi == 24 && cur[0].score.se == 1) {
            cout << cur[0].expression;
            return true;
        }
        return false;
    }

    vector<Elem> newElems;

    for (int i = 0; i < (int)cur.size(); ++i) {
        for (int j = 0; j < (int)cur.size(); ++j) {
            if (i == j)
                continue;
            if (getNewElems(cur, i, j, '+'))
                return true;
            if (getNewElems(cur, i, j, '-'))
                return true;
            if (getNewElems(cur, i, j, '*'))
                return true;
            if (getNewElems(cur, i, j, '/'))
                return true;
        }
    }

    return false;
}
int main()
{
    vector<Elem> elems;
    for (int i = 1; i <= 4; ++i) {
        int num;
        cin >> num;
        elems.push_back(Elem(num));
    }
    if (!dfs(elems))
        puts("");
    return 0;
}