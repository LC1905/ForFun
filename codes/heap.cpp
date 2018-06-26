// an implementation of max-heap and min-heap and priority queue

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

struct mheap{
	vector<int> heap;
	char mode[3];
	int length;
	int heapsize;
};

int parent(int i){
	return (int)(i/2);
}

int left(int i){
	return 2*i;
}

int right(int i){
	return 2*i+1;
}

void show_heap(struct mheap* h){
	for (int i = 0; i < h->heapsize; i++){
		cout << h->heap[i] << " ";
	}
	cout << "\n";
}

void exchange(struct mheap* h, int i1, int i2){
	int temp = h->heap[i1];
	h->heap[i1] = h->heap[i2];
	h->heap[i2] = temp;
}

// complexity O(log n)
void max_heapify(struct mheap* h, int i){  
	int l = left(i);
	int r = right(i);
	int largest = i;
	if (l < h->heapsize && h->heap[l] > h->heap[largest]){
		largest = l;
	}
	if (r < h->heapsize && h->heap[r] > h->heap[largest]){
		largest = r;
	}
	if (largest != i){
		exchange(h, largest, i);
		max_heapify(h, largest);
	}
}

// complexity O(log n)
void min_heapify(struct mheap* h, int i){  
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < h->heapsize && h->heap[l] < h->heap[smallest]){
		smallest = l;
	}
	if (r < h->heapsize && h->heap[r] < h->heap[smallest]){
		smallest = r;
	}
	if (smallest != i){
		exchange(h, smallest, i);
		min_heapify(h, smallest);
	}
}

// complexity O(n)
struct mheap* build_heap(vector<int> v, int length, char mode[]){
	struct mheap* h = new mheap();
	h->heap = v;
	h->length = length;
	h->heapsize = length;
	strcpy(h->mode, mode);
	int height = (int)(log2(length));
	if (strcmp(h->mode, "max") == 0){
		for (int i = pow(2.0, height) - 2; i >= 0; i--){
			max_heapify(h, i);
		}
	}
	else if (strcmp(h->mode, "min") == 0){
		for (int i = pow(2.0, height) - 2; i >= 0; i--){
			min_heapify(h, i);
		}
	}
	return h;
}

// complexity O(nlogn)
struct mheap* heapsort(vector<int> v, int length, char mode[]){
	struct mheap* h = build_heap(v, length, mode);
	show_heap(h);
	vector<int> ret;
	for (int i = length-1; i >= 0; i--){
		exchange(h, 0, i);
		h->heapsize -= 1;
		if (strcmp(h->mode, "max") == 0){
			max_heapify(h, 0);
		}
		else if (strcmp(h->mode, "min") == 0){
			min_heapify(h, 0);
		}
	}
	h->heapsize = length;
	return h;
}
int main(){
	vector<int> v = {4, 1, 2, 5, 3};
	struct mheap* h = heapsort(v, v.size(), (char*)"min");
	show_heap(h);
}