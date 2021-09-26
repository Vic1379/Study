#include<vector>

class FixedAllocator {
 public:
  FixedAllocator(size_t chunk_size, size_t page_size) {
    this->chunk_size = chunk_size;
    this->page_size = page_size;
    k = 1;
    new_page();
  }
  void* Allocate() {
    i = 0;
    while (i < page_size * k && !tf[i]) i++;
    if (i == page_size * k) {
      k++;
      new_page();
    }
    auto result = mas[i];
    tf[i] = false;
    return static_cast<void*>(result);
  }
  void Deallocate(void* ptr) {
    i = 0;
    while (i < page_size * k && tf[i]) i++;
    if (i != page_size * k) {
      auto node = static_cast<char*>(ptr);
      mas[i] = node;
      tf[i] = true;
    }
  }

 private:
  size_t chunk_size, page_size;
  std::vector<char*> mas;
  std::vector<bool> tf;
  int i, k;
  void new_page() {
    for (int i = 0; i < page_size; i++) {
      mas.push_back(new char[chunk_size]);
      tf.push_back(true);
    }
  }
};
