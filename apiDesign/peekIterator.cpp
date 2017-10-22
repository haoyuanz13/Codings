class Iterator {
  struct Data;
  Data* data;

public:
  Iterator(const vector<int>& nums);
  Iterator(const Iterator& iter);
  virtual ~Iterator();

  // Returns the next element in the iteration.
  int next();
  // Returns true if the iteration has more elements.
  bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
  int peekone;
  Iterator* its;

  PeekingIterator(const vector<int>& nums) : Iterator(nums) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
    its = new Iterator(nums);
    if (its->hasNext())
      peekone = its->next();
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() {
    return peekone;
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    int res = peekone;
    peekone = (its->hasNext())? its->next() : 0;
    return res;
  }

  bool hasNext() const {
    return (peekone != 0);
  }
};