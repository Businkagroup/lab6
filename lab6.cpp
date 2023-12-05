#include <iostream>
#include <ctime>
#include <chrono>


// для удобства написания
using namespace std;
using namespace chrono;

// пузырьковая сортирвка 
// проходит по массиву и сравнивает каждый элемент с соседним
// если элемент больше последующего то они меняются местами
// использована функция swap из std

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// сортировка выбором
// проходимся по массиву и выбираем наименьший элемент
// помещаем его в начало
// проходимся еще раз
// ???
// profit
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge Sort 
// алгоритм сначала разбивает на маленькие кусочки массив 
// каждый из кусочков сортируем и сшиваем с другим
// снова сортируем и сшиваем
// итд пока не получим отсортированный массив изначальной длины

void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rightArr[j] = arr[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        }
        else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}
// быстрая сортировка
// На очередном шаге выбирается опорный элемент — им может быть любой элемент массива.
// Все остальные элементы массива сравниваются с опорным и те, которые меньше него, ставятся слева от него, а которые больше или равны — справа.
// Для двух получившихся блоков массива (меньше опорного, и больше либо равны опорному) 
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        int pivotIndex = i + 1;

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    //генератор случайных чисел
    // time(0) является случайным зерном
    srand(static_cast<unsigned>(time(0)));

    //объявляем массив  
    const int arraySize = 10000; 
    
    int myArray[arraySize];

    // заполняем рандомными значениями
    for (int i = 0; i < arraySize; ++i) {
        myArray[i] = rand();
    }


    // создаем копии массива чтоб не сортировать отсортированное
    // логичней бы было создавать новый массив для каждой сортировки, но это бы нарушило чистоту эксперимента
    int myArrayCopyBubble[arraySize];
    int myArrayCopySelection[arraySize];
    int myArrayCopyMerge[arraySize];
    int myArrayCopyQuick[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        myArrayCopyBubble[i] = myArray[i];
        myArrayCopySelection[i] = myArray[i];
        myArrayCopyMerge[i] = myArray[i];
        myArrayCopyQuick[i] = myArray[i];
    }

    // измеряем время за которое отработает пузырек
    // auto потому что я не понимаю какой тип данных вернется
    auto startBubble = high_resolution_clock::now();
    bubbleSort(myArrayCopyBubble, arraySize);
    auto stopBubble = high_resolution_clock::now();
    auto durationBubble = duration_cast
        <milliseconds>(stopBubble - startBubble);

    cout << "\n\nпузырек отработал за " << durationBubble.count() << " миллисекунд \n";

    // тут все то же самое
    auto startSelection = high_resolution_clock::now();
    selectionSort(myArrayCopySelection, arraySize);
    auto stopSelection = high_resolution_clock::now();
    auto durationSelection = duration_cast<milliseconds>(stopSelection - startSelection);

    cout << "выборочная сортировка отработала " << durationSelection.count() << " миллисекунд\n";

    
    auto startMerge = high_resolution_clock::now();
    mergeSort(myArrayCopyMerge, 0, arraySize - 1);
    auto stopMerge = high_resolution_clock::now();
    auto durationMerge = duration_cast<milliseconds>(stopMerge - startMerge);

    cout << "Merge Sort отработал за" << durationMerge.count() << " миллисекунд\n";

    auto startQuick = high_resolution_clock::now();
    quickSort(myArrayCopyQuick, 0, arraySize - 1);
    auto stopQuick = high_resolution_clock::now();
    auto durationQuick = duration_cast<milliseconds>(stopQuick - startQuick);

    cout << "быстрая сортировка отработала за " << durationQuick.count() << " миллисекунд\n";
    
    return 0;
}
