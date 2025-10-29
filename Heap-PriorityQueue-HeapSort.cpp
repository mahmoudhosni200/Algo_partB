// Mohamed Kamel Part

#include <iostream>
#include <vector>
using namespace std;

int left(int i) {
    return 2 * i + 1;
}
int right(int i) {
    return 2 * i + 2;
}
int parent(int i) {
    return (i - 1) / 2;
}

// 1. Heap Class
template<typename T>
class Heap {

    vector<T> elements;

    void maxHeapify(int i, int size) {
        int largest = i;
        if(left(i) <= size && elements[left(i)] > elements[largest]) {
            largest = left(i);
        }
        if(right(i) <= size && elements[right(i)] > elements[largest]) {
            largest = right(i);
        }
        if(largest != i) {
            swap(elements[i], elements[largest]);
            maxHeapify(largest, size);
        }
    }

    void buildMaxHeap() {
        int size = int(elements.size());
        for(int i = size / 2; i >= 0; i--) {
            maxHeapify(i, size - 1);
        }
    }

    void printHeap() {
        for(size_t i = 0; i < elements.size(); i++) {
            if constexpr (is_same<T, pair<int, string>>::value)
                cout << "(" << elements[i].second << "," << elements[i].first << ")";
            else
                cout << elements[i];
            if(i + 1 < elements.size()) cout << ", ";
        }
        cout << endl;
    }

public:
    void insert(T newValue) {
        elements.push_back(newValue);
        int i = int(elements.size()) - 1;
        while(i > 0 && elements[parent(i)] < elements[i]) {
            swap(elements[parent(i)], elements[i]);
            i = parent(i);
        }
        cout << "Heap after inserting ";
        if constexpr (is_same<T, pair<int, string>>::value)
            cout << "(" << newValue.second << "," << newValue.first << ")";
        else
            cout << newValue;
        cout << ": ";
        printHeap();
    }

    T extractMax() {
        if(elements.empty()) {
            cout << "Heap is empty, cannot extract max." << endl;
            return T();
        }
        int size = int(elements.size());
        T maxValue = elements[0];
        swap(elements[0], elements[size - 1]);
        elements.pop_back();
        size = int(elements.size());
        if(size > 0) maxHeapify(0, size - 1);

        cout << "Heap after extracting max ";
        if constexpr (is_same<T, pair<int, string>>::value)
            cout << "(" << maxValue.second << "," << maxValue.first << ")";
        else
            cout << maxValue;
        cout << ": ";
        printHeap();

        return maxValue;
    }

    T extractMin() {
        if(elements.empty()) {
            cout << "Heap is empty, cannot extract min." << endl;
            return T();
        }
        int minIndex = 0;
        for(int i = 1; i < elements.size(); i++) {
            if(elements[i] < elements[minIndex]) minIndex = i;
        }
        T minValue = elements[minIndex];
        swap(elements[minIndex], elements[elements.size() - 1]);
        elements.pop_back();
        if(!elements.empty()) buildMaxHeap();

        cout << "Heap after extracting min ";
        if constexpr (is_same<T, pair<int, string>>::value)
            cout << "(" << minValue.first << "," << minValue.second << ")";
        else
            cout << minValue;
        cout << ": ";
        printHeap();

        return minValue;
    }

    vector<T>& getArray() {
        return elements;
    }
};

//2. Priority Queue
template<typename dataType>
class PriorityQueue {

    Heap<pair<int, dataType>> heap;

public:
    void insert(dataType value, int priority) {
        heap.insert({priority, value});
    }

    dataType extractMax() {
        if(heap.getArray().empty()) {
            cout << "Priority Queue is empty, cannot extract max." << endl;
            return dataType();
        }
        return heap.extractMax().second;
    }
};

// 3. Heap Sort
template<typename dataType>
void heapSort(vector<dataType> &arr) {
    Heap<dataType> h;
    for(auto x : arr) h.insert(x);
    for(int i = arr.size() - 1; i >= 0; i--) {
        arr[i] = h.extractMax();
    }
}

int main() {
    Heap<int> heap;
    PriorityQueue<string> pqueue;
    vector<int> arr;

    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert into Heap\n";
        cout << "2. Extract max from Heap\n";
        cout << "3. Extract min from Heap\n";
        cout << "4. Insert into Priority Queue\n";
        cout << "5. Extract max from Priority Queue\n";
        cout << "6. Heap Sort\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int val;
                cout << "Value: ";
                cin >> val;
                heap.insert(val);
                break;
            }
            case 2: {
                heap.extractMax();
                break;
            }
            case 3: {
                heap.extractMin();
                break;
            }
            case 4: {
                string task;
                int prio;
                cout << "Task: "; cin >> task;
                cout << "Priority: "; cin >> prio;
                pqueue.insert(task, prio);
                break;
            }
            case 5: {
                pqueue.extractMax();
                break;
            }
            case 6: {
                int n;
                cout << "Number of elements: ";
                cin >> n;
                arr.clear();
                cout << "Enter elements: ";
                for(int i=0;i<n;i++){ int x; cin>>x; arr.push_back(x);}
                heapSort(arr);
                cout << "Sorted: ";
                for(size_t i = 0; i < arr.size(); i++) {
                    cout << arr[i];
                    if(i + 1 < arr.size()) cout << ", ";
                }
                cout << endl;
                break;
            }
        }
    } while(choice != 0);

    return 0;
}
