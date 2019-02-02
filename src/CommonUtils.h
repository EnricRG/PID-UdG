#ifndef COMMONUTILS_H
#define COMMONUTILS_H

//pre: n is at least the length of src
template<class T>
static T* getCopyOfArray(const T* src, int n) {
	T * copy = new T[n];
	for (int i = 0; i < n; i++) { copy[i] = src[i]; }
	return copy;
}

//pre: 0 terminated array
static int intArraySum(const int * int_arr)
{
	int index = 0;
	int acum = 0;
	while (int_arr[index] != 0) {
		acum += int_arr[index];
		index++;
	}
	return acum;
}

static int nElements(const int* int_arr) {
	int index = 0;
	while (int_arr[index] != 0) {
		index++;
	}
	return index + 1;
}

#endif