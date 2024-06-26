#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip> // untuk membuat tabel lebih rapi

using namespace std;
namespace plt = matplotlibcpp;

// Algoritma Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]); // Tukar elemen jika salah urutan
            }
        }
    }
}

// Algoritma Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Geser elemen ke kanan untuk memberi ruang ke key
            j = j - 1;
        }
        arr[j + 1] = key; // Menempatkan key di posisi yang benar
    }
}

// Algoritma Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j; // Menemukan elemen terkecil
            }
        }
        swap(arr[min_idx], arr[i]); // Menukar elemen terkecil dengan elemen pertama yang belum diurutkan
    }
}

// Fungsi merge untuk Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    // Isi array sementara L dan R
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Gabungkan dua array sementara kembali ke arr
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy elemen yang tersisa dari L, jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy elemen yang tersisa dari R, jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Algoritma Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m); // Urutkan bagian kiri
        mergeSort(arr, m + 1, r); // Urutkan bagian kanan
        merge(arr, l, m, r); // Gabungkan kedua bagian yang sudah diurutkan
    }
}

// Fungsi partition untuk Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pilih pivot sebagai elemen terakhir
    int i = (low - 1); // Indeks elemen yang lebih kecil
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]); // Tukar elemen lebih kecil dengan elemen yang lebih besar
        }
    }
    swap(arr[i + 1], arr[high]); // Pindahkan pivot ke posisi yang tepat
    return (i + 1); // Kembalikan indeks pivot
}

// Algoritma Quick Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Dapatkan indeks pivot
        quickSort(arr, low, pi - 1); // Urutkan bagian kiri pivot
        quickSort(arr, pi + 1, high); // Urutkan bagian kanan pivot
    }
}

// Fungsi untuk menghasilkan data
void generateData(vector<int>& arr, int N, string type) {
    arr.clear(); // Kosongkan array
    for (int i = 0; i < N; i++)
        arr.push_back(rand() % 100); // Isi array dengan angka acak

    // Atur tipe data
    if (type == "terbalik") {
        sort(arr.begin(), arr.end());
        reverse(arr.begin(), arr.end()); // Balik urutan
    }
    else if (type == "terurut") {
        sort(arr.begin(), arr.end()); // Urutkan
    }
}

// Fungsi untuk mencetak hasil waktu eksekusi dalam bentuk tabel
void printResults(const string& algName, const string& complexity, vector<long long>& times) {
    cout << "| " << setw(15) << algName << " | " << setw(12) << complexity << " |";
    for (long long time : times) {
        cout << setw(7) << time << " |"; // Cetak waktu eksekusi
    }
    cout << endl;
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000}; // Ukuran data yang akan diuji
    vector<string> types = {"acak", "terbalik", "terurut"}; // Jenis data yang akan diuji
    vector<void(*)(vector<int>&)> simpleAlgorithms = {bubbleSort, insertionSort, selectionSort}; // Algoritma pengurutan sederhana
    vector<string> simpleAlgNames = {"Bubble Sort", "Insertion Sort", "Selection Sort"}; // Nama algoritma pengurutan sederhana
    vector<string> simpleComplexities = {"O(n^2)", "O(n^2)", "O(n^2)"}; // Kompleksitas waktu algoritma pengurutan sederhana
    vector<string> complexAlgNames = {"Merge Sort", "Quick Sort"}; // Nama algoritma pengurutan kompleks
    vector<string> complexComplexities = {"O(n log n)", "O(n log n)"}; // Kompleksitas waktu algoritma pengurutan kompleks

    // Untuk setiap tipe data
    for (string type : types) {
        cout << "Data type: " << type << endl;
        cout << "+------------------+---------------+--------+--------+--------+--------+---------+" << endl;
        cout << "|     Algoritma    |  Kompleksitas | N=10   | N=100  | N=500  | N=1000 | N=10000 |" << endl;
        cout << "+------------------+---------------+--------+--------+--------+--------+---------+" << endl;

        // Uji algoritma sederhana
        for (size_t i = 0; i < simpleAlgorithms.size(); i++) {
            vector<long long> times;
            for (int N : sizes) {
                vector<int> data;
                generateData(data, N, type); // Buat data berdasarkan tipe

                auto start = chrono::high_resolution_clock::now(); // Catat waktu mulai
                simpleAlgorithms[i](data); // Jalankan algoritma
                auto end = chrono::high_resolution_clock::now(); // Catat waktu selesai
                long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count(); // Hitung durasi eksekusi
                times.push_back(duration); // Simpan durasi
            }
            printResults(simpleAlgNames[i], simpleComplexities[i], times); // Cetak hasil
        }

        // Uji algoritma kompleks
        for (size_t i = 0; i < complexAlgNames.size(); i++) {
            vector<long long> times;
            for (int N : sizes) {
                vector<int> data;
                generateData(data, N, type); // Buat data berdasarkan tipe

                auto start = chrono::high_resolution_clock::now(); // Catat waktu mulai
                if (i == 0) {
                    mergeSort(data, 0, data.size() - 1); // Jalankan merge sort
                } else if (i == 1) {
                    quickSort(data, 0, data.size() - 1); // Jalankan quick sort
                }
                auto end = chrono::high_resolution_clock::now(); // Catat waktu selesai
                long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count(); // Hitung durasi eksekusi
                times.push_back(duration); // Simpan durasi
            }
            printResults(complexAlgNames[i], complexComplexities[i], times); // Cetak hasil
        }
        cout << "+------------------+---------------+--------+--------+--------+--------+---------+\n" << endl;
    }

    return 0;
}
