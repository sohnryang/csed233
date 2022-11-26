#include <iostream>
#include <string>
using namespace std;

class sortAlg {

public:
  sortAlg();

  int arr_size;
  int *arr;

  void printArray(ofstream &);
  int partition(ofstream &fout, int left, int right);
  void quickSort(ofstream &, int left, int right);

  void mergeSort(ofstream &, int left, int right);
  void merge(int left, int mid, int right);
};
