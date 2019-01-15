class FixedAllocator {
 public:
  FixedAllocator(size_t chunk_size, size_t page_size) {
    this->chunk_size = chunk_size;
    this->page_size = page_size;
  }
  void* Allocate() {
    if (free == nullptr) newM();
    auto result = free;
    free = free->next;
    return static_cast<void*>(result);
  }
  void Deallocate(void* ptr) {
    if (free == nullptr) return;
    auto node = static_cast<Chunk*>(ptr);
    node->next = free;
    free = node;
  }

 private:
  size_t chunk_size, page_size;
  struct Chunk {
    char buf;
    Chunk* next = nullptr;
  };
  Chunk* free = nullptr;
  void newM() {
    for (int i = 1; i < page_size; i++) {
      Chunk* q = new Chunk();
      q->buf = static_cast<char>(chunk_size);
      q->next = free;
      free = q;
    }
  }
};
