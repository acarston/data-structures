#include <algorithm>
#include <iostream>
#include <fstream>

template <typename T>
class Heap {
    private:
        T* heap = nullptr;
        int size = 0;
        bool ascending = true;

        bool reverse(const bool condition) const {
            if (this->ascending) return condition;
            else return !condition;
        }
    
        void move_down(const int i, const int size) {
            const int I_LEFT = 2 * i + 1;
            const int I_RIGHT = 2 * i + 2;
            if (I_LEFT >= size) return;

            int iLarger = I_LEFT;
            if (I_RIGHT < size) iLarger = reverse(heap[I_LEFT] > heap[I_RIGHT]) ? I_LEFT : I_RIGHT;

            if (reverse(heap[i] > heap[iLarger])) return;
            std::swap(heap[i], heap[iLarger]);
            move_down(iLarger, size);
        }

        void heapify() { for (int i = this->size / 2 - 1; i >= 0; --i) move_down(i, this->size); }

    public:
        Heap(T* heap, const int size, const bool ascending = true) : heap(heap), size(size), ascending(ascending) {};

        void sort() {
            heapify();
            for (int size = this->size - 1; size > 0; --size) {
                std::swap(heap[0], heap[size]);
                move_down(0, size);
            }
        }

        void output() const {
            for (int i = 0; i < this->size; ++i) std::cout << heap[i] << " ";
            std::cout << std::endl;
        }

        void output(std::ofstream& fout) const { for (int i = 0; i < this->size; ++i) fout << heap[i] << "\n"; }
};