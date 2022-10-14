// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <typename T>
class stack {
public:
	stack(const size_t cap = 0) : capacity(cap) {
		data = new T[cap];
	}

	stack(const stack& copy): size(copy.size), capacity(copy.capacity) {
		data = new T[capacity];
		for (size_t i = 0; i < size; ++i)
			data[i] = copy.data[i];
	}

	unsigned int get_capacity() const {
		return capacity;
	}

	~stack() {
		delete[] data;
	}

	void clear() {
		delete[] data;
		data = new T[capacity];
		size = 0;
	}
	
	void push(const T& value) {
		if (capacity == 0) {
			data = new T[1];
			capacity = 1;
		}

		if (size == capacity) {
			T* new_data = new T[capacity * 2];
			for (size_t i = 0; i < capacity; ++i)
				new_data[i] = data[i];
			delete[] data;
			data = new_data;
			capacity *= 2;
		}

		data[size++] = value;
	}

	bool empty() {
		return size == 0;
	}

	T pop() {
		if (empty())
			throw std::exception("stack is empty");
		T value = data[size-1];
		size--;
		return value;
	}

	T& top() {
		if (empty())
			throw std::exception("stack is empty");
		return data[size - 1];
	}

private:
	T* data;
	size_t size = 0;
	size_t capacity;
};
