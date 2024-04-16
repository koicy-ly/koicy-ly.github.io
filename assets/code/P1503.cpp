#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

template <typename Typex>
class Tree {
  struct TNode {
    Typex Key;
    unsigned size, cover;
    bool exist;
    TNode *LC, *RC;

    void _Pushup() {
      size = LC->size + RC->size + exist;
      cover = LC->cover + RC->cover + 1;
    }

    bool _Isbad() {
      return (LC->cover > cover * 0.8) || (RC->cover > cover * 0.8);
    }
  } * mempool, *tail, *null, *root, **bc;

  unsigned bc_top;

  TNode* _newNode(const Typex& Key) {
    TNode* p = bc_top ? bc[--bc_top] : tail++;
    p->LC = p->RC = null;
    p->size = p->cover = 1;
    p->exist = true;
    p->Key = Key;
    return p;
  }

  void _Travel(TNode* p, vector<TNode*>& x) {
    if (p == null)
      return;
    _Travel(p->LC, x);
    if (p->exist)
      x.push_back(p);
    else
      bc[bc_top++] = p;
    _Travel(p->RC, x);
  }

  TNode* _Divide(vector<TNode*>& x, const unsigned& l, const unsigned& r) {
    if (l >= r)
      return null;
    int mid = l + r >> 1;
    TNode* p = x[mid];
    p->LC = _Divide(x, l, mid);
    p->RC = _Divide(x, mid + 1, r);
    p->_Pushup();
    return p;
  }

  void _Rebuild(TNode*& p) {
    static vector<TNode*> x;
    x.clear();
    _Travel(p, x);
    p = _Divide(x, 0, x.size());
  }

  TNode** _Insert(TNode*& p, const Typex& Key) {
    if (p == null) {
      p = _newNode(Key);
      return &null;
    }
    p->size++;
    p->cover++;
    TNode** res =
        _Insert((Key < p->Key || !(p->Key < Key) ? p->LC : p->RC), Key);
    if (p->_Isbad())
      return &p;
    return res;
  }

  void _Remove(TNode*& p, const unsigned& k) {
    p->size--;
    unsigned offset = p->LC->size + p->exist;
    if (p->exist && offset == k)
      p->exist = false;
    else
      k <= offset ? _Remove(p->LC, k) : _Remove(p->RC, k - offset);
  }

 public:
  Tree(const unsigned& _TSize) : bc_top(0) {
    bc = new TNode*[_TSize];
    tail = mempool = new TNode[_TSize];
    null = tail++;
    null->LC = null->RC = null;
    null->cover = null->size = null->exist = 0;
    root = null;
  }

  void insert(const Typex& Key) {
    TNode** res = _Insert(root, Key);
    if (*res != null)
      _Rebuild(*res);
  }

  unsigned rank(const Typex& Key) {
    TNode* now = root;
    unsigned ans = 1;
    while (now != null)
      if (Key < now->Key)
        now = now->LC;
      else if (now->Key < Key) {
        ans += now->LC->size + now->exist;
        now = now->RC;
      } else
        now = now->LC;
    return ans;
  }

  const Typex* kth(unsigned Key) {
    TNode* now = root;
    while (now != null) {
      if (now->LC->size + 1 == Key && now->exist)
        return &now->Key;
      if (Key <= now->LC->size)
        now = now->LC;
      else {
        Key -= now->LC->size + now->exist;
        now = now->RC;
      }
    }
  }

  void remove(const Typex& k) {
    _Remove(root, rank(k));
    if (root->size < root->cover * 0.8)
      _Rebuild(root);
  }

  void remove(const Typex*& k) { remove(*k); }

  unsigned size() { return root->size; }
};

bool disable[50005];

int main() {
  Tree<int> tree(5000);
  tree.insert(0);
  stack<int> order;
  int n, m;
  scanf("%d %d
", &n, &m);
  tree.insert(n + 1);
  while (m--) {
    char op;
    string t;
    getline(cin, t);
    sscanf(t.c_str(), "%c", &op);
    if (op == 'D') {
      int x;
      sscanf(t.c_str(), "%c %d", &op, &x);
      tree.insert(x);
      disable[x] = true;
      order.push(x);
    } else if (op == 'R') {
      tree.remove(order.top());
      disable[order.top()] = false;
      order.pop();
    } else {
      int x;
      sscanf(t.c_str(), "%c %d", &op, &x);
      if (disable[x])
        puts("0");
      else
        printf("%d
",
               *tree.kth(tree.rank(x + 1)) - *tree.kth(tree.rank(x) - 1) - 1);
    }
  }
  return 0;
}