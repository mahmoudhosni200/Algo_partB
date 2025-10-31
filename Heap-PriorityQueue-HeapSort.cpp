// Mohamed Kamel Part

#include <iostream>
#include <vector>
#include <tuple>
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
            else if constexpr (is_same<T, tuple<int, int, string>>::value)
                cout << "(" << get<2>(elements[i]) << "," << get<0>(elements[i]) << ")";
            else
                cout << elements[i];
            if(i + 1 < elements.size()) cout << ", ";
        }
        cout << endl;
    }

public:
    void insert(T newValue, bool silent = false) {
        elements.push_back(newValue);
        int i = int(elements.size()) - 1;
        while(i > 0 && elements[parent(i)] < elements[i]) {
            swap(elements[parent(i)], elements[i]);
            i = parent(i);
        }

        if(!silent) {
            cout << "Heap after inserting ";
            if constexpr (is_same<T, pair<int, string>>::value)
                cout << "(" << newValue.second << "," << newValue.first << ")";
            else if constexpr (is_same<T, tuple<int, int, string>>::value)
                cout << "(" << get<2>(newValue) << "," << get<0>(newValue) << ")";
            else
                cout << newValue;
            cout << ": ";
            printHeap();
        }
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
        else if constexpr (is_same<T, tuple<int, int, string>>::value)
            cout << "(" << get<2>(maxValue) << "," << get<0>(maxValue) << ")";
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
            cout << "(" << minValue.second << "," << minValue.first << ")";
        else if constexpr (is_same<T, tuple<int, int, string>>::value)
            cout << "(" << get<2>(minValue) << "," << get<0>(minValue) << ")";
        else
            cout << minValue;
        cout << ": ";
        printHeap();

        return minValue;
    }

    vector<T>& getArray() {
        return elements;
    }

    bool empty() const {
        return elements.empty();
    }
};

// 2. Priority Queue
class PriorityQueue {

    Heap<tuple<int, int, string>> heap;
    int timestamp = 0;

public:
    void insert(const string& value, int priority) {
        heap.insert({priority, -timestamp++, value});
    }

    string extractMax() {
        if(heap.empty()) {
            cout << "Priority Queue is empty, cannot extract max." << endl;
            return "";
        }
        auto maxValue = heap.extractMax();
        return get<2>(maxValue);
    }
};

// 3. Automated Test
void runTests() {
    cout << "\n------- Testing Mode -------\n";

    cout << "\n[Heap Tests]\n";
    Heap<int> testHeap;
    vector<int> values = {10, 4, 15, 8, 20};
    for(int v : values) testHeap.insert(v);
    testHeap.extractMax();
    testHeap.extractMin();

    cout << "\n[PriorityQueue Tests]\n";
    PriorityQueue pq;
    pq.insert("TaskA", 3);
    pq.insert("TaskB", 5);
    pq.insert("TaskC", 5);
    pq.insert("TaskD", 2);
    pq.extractMax();
    pq.extractMax();
    pq.extractMax();
    pq.extractMax();
    pq.extractMax();

    cout << "\n[Heap Sort Test]\n";
    vector<int> arr = {9, 3, 7, 1, 8};
    Heap<int> tempHeap;
    for(int x : arr) tempHeap.insert(x, true);
    for(int i = arr.size() - 1; i >= 0; i--) {
        arr[i] = tempHeap.extractMax();
    }
    cout << "Sorted: ";
    for(size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if(i + 1 < arr.size()) cout << ", ";
    }
    cout << endl;

    cout << "\n---------- Tests Completed ----------\n";
}

// 4. Main
int main() {
    Heap<int> heap;
    PriorityQueue pqueue;
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
        cout << "7. Run Automated Tests\n";
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
                for(int i=0;i<n;i++){ int x; cin>>x; arr.push_back(x); }

                Heap<int> tempHeap;
                for(int x : arr) tempHeap.insert(x, true);

                for(int i = arr.size() - 1; i >= 0; i--) {
                    arr[i] = tempHeap.extractMax();
                }

                cout << "Sorted: ";
                for(size_t i = 0; i < arr.size(); i++) {
                    cout << arr[i];
                    if(i + 1 < arr.size()) cout << ", ";
                }
                cout << endl;
                break;
            }
            case 7: {
                runTests();
                break;
            }
        }
    } while(choice != 0);

    return 0;
}
