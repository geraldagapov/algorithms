#include <iostream>
#include <vector>
#include <cassert>
#include <functional>

// __IMPLEMENTATION_START__
template<typename Value>
class SegmentTree {
 public:
  using Join = std::function<Value(const Value&, const Value&)>;

  SegmentTree(int size, const Join& join) {
    tree_.resize(size * 4);
    size_ = size;
    join_ = join;
  }

  void Assign(int pos, const Value& value) {
    Update(pos, value, 0, 0, size_ - 1);
  }

  Value Sum(int l, int r) {
    return Sum(l, r, 0, 0, size_ - 1);
  }

 private:
  SegmentTree() {}  // deleted

  void Update(int pos, const Value& value, int v, int l, int r) {
    assert(0 <= l && l <= r && r < size_);
    if (l == r) {
      assert(l == pos);
      tree_[v] = value;
      return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
      Update(pos, value, 2 * v + 1, l, mid);
    } else {
      Update(pos, value, 2 * v + 2, mid + 1, r);
    }
    tree_[v] = join(tree_[2 * v + 1], tree_[2 * v + 2]);
  }

  Value Sum(int ql, int qr, int v, int l, int r) {
    assert(0 <= l && l <= ql && ql <= qr && qr <= r && r < size_);
    if (ql == l && qr == r) {
      return tree_[v];
    }
    int mid = (l + r) / 2;
    if (qr <= mid) return Sum(ql, qr, 2 * v + 1, l, mid);
    if (ql >= mid + 1) return Sum(ql, qr, 2 * v + 2, mid + 1, r);
    return join(Sum(ql, mid, 2 * v + 1, l, mid),
                Sum(mid + 1, qr, 2 * v + 2, mid + 1, r));
  }

  int size_;
  std::vector<Value> tree_;
  Join join_;
};
// __IMPLEMENTATION_END__

int main() {
  return 0;
}
