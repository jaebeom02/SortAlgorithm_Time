#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 131072 //데이터의 개수 지정
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP함수 설정
int original[MAX_SIZE];    //랜덤함수로 만든 데이터를 저장할 원본 배열
int list[MAX_SIZE];    //각 정렬 알고리즘에서 사용할 데이터 배열
int n; //데이터의 개수를 받는 전역변수 설정
int sorted[MAX_SIZE];
clock_t start, finish, used_time = 0;    //실행 시간 측정을 위한 변수

//버블 정렬
void bubble_sort(int list[], int n)
{
    int i, j, tmp;
    printf("버블 정렬 중... ");
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], tmp);
    }
}

//선택 정렬
void selection_sort(int list[], int n)
{
    int i, j, least, tmp;

    printf("선택 정렬 중... ");
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least]) least = j;
        SWAP(list[i], list[least], tmp);
    }
}

////선택정렬 택해서 정방향 데이터 출력하려 함.(초창기)
//void selection_sort_fd(int list[], int n)
//{
//    int i, j, least, tmp;
//
//    printf("정렬 중... ");
//    for (i = 0; i < n - 1; i++)
//    {
//        least = i;
//        for (j = i + 1; j < n; j++)
//            if (list[j] < list[least]) least = j;
//        SWAP(list[i], list[least], tmp);
//    }
//}

//삽입 정렬
void insertion_sort(int list[], int n)
{
    int i, j, key;
    printf("삽입 정렬 중... ");
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}

//퀵정렬
int partition(int list[], int left, int right)
{
    int pivot = list[left], tmp, low = left, high = right + 1;

    do
    {
        do
            low++;
        while (low <= right && list[low] < pivot);

        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], tmp);
    } while (low < high);

    SWAP(list[left], list[high], tmp);
    return high;
}
void quick_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

//쉘정렬
inc_insertion_sort(int list[], int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
            list[j + gap] = list[j];
        list[j + gap] = key;
    }
}

void shell_sort(int list[], int n)
{
    int i, gap;
    printf("쉘 정렬 중 ... ");
    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++)
        {
            inc_insertion_sort(list, i, n - 1, gap);
        }
    }
}

//힙정렬
int swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int list[], int n, int i) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;


    // 왼쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (leftChildNode < n && list[parentNode] < list[leftChildNode]) {
        parentNode = leftChildNode;
    }
    // 오른쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (rightChildNode < n && list[parentNode] < list[rightChildNode]) {
        parentNode = rightChildNode;
    }


    // 왼쪽 or 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재한 경우
    if (i != parentNode) {
        swap(&list[parentNode], &list[i]);
        // 초기 부모노드가 제자지를 찾을 때까지 내려갑니다.
        heapify(list, n, parentNode);
    }
}

void heap_sort(int list[], int n) {
    // 최대 힙(Max Heap) 구성
    printf("힙 정렬 중...");
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(list, n, i);
    }

    // Root에 위치한 최대값을 마지막 노드와 바꿔가며 Heap 재구성
    // Heap의 크기를 줄여가며 값이 큰 원소를 차례로 가져옵니다.
    for (int i = n - 1; i > 0; i--) {
        swap(&list[0], &list[i]);
        heapify(list, i, 0);
    }
}

//힙정렬을 택해서 출력하려함.
int swap2(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify2(int list[], int n, int i) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;


    // 왼쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (leftChildNode < n && list[parentNode] < list[leftChildNode]) {
        parentNode = leftChildNode;
    }
    // 오른쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (rightChildNode < n && list[parentNode] < list[rightChildNode]) {
        parentNode = rightChildNode;
    }


    // 왼쪽 or 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재한 경우
    if (i != parentNode) {
        swap2(&list[parentNode], &list[i]);
        // 초기 부모노드가 제자지를 찾을 때까지 내려갑니다.
        heapify2(list, n, parentNode);
    }
}

void heap_sort2(int list[], int n) {
    // 최대 힙(Max Heap) 구성
    printf("정렬 중... ");
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify2(list, n, i);
    }

    // Root에 위치한 최대값을 마지막 노드와 바꿔가며 Heap 재구성
    // Heap의 크기를 줄여가며 값이 큰 원소를 차례로 가져옵니다.
    for (int i = n - 1; i > 0; i--) {
        swap2(&list[0], &list[i]);
        heapify2(list, i, 0);
    }
}

//원본 배열을 복사하는 함수
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        list[i] = original[i];
}

// 정방향 데이터를 구할라고 만든 함수
void ForwardArr(void)
{
    int i;
    for (i = 0; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            sorted[i] = list[j];
        }
    }
    sorted[i] = list[i];
}

//실행 시간을 측정 및 출력하는 함수
void CalcTime(void)
{
    used_time = finish - start;
    printf("완료!\n소요 시간 : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}

void main()
{
    int i;

    n = MAX_SIZE;
    for (i = 0; i < n; i++)
        original[i] = rand();

    printf("데이터의 개수 : %d\n\n", n);

    CopyArr();
    printf("\n");
    heap_sort2(list, n);
    printf("완료 !\n");
    printf("\n");

    ForwardArr();
    start = clock();
    bubble_sort(sorted, n);
    finish = clock();
    CalcTime();

    ForwardArr();
    start = clock();
    selection_sort(sorted, n);
    finish = clock();
    CalcTime();

    ForwardArr();
    start = clock();
    insertion_sort(sorted, n);
    finish = clock();
    CalcTime();

    ForwardArr();
    start = clock();
    printf("퀵 정렬 중... ");
    quick_sort(sorted, 0, n);
    finish = clock();
    CalcTime();

    ForwardArr();
    start = clock();
    shell_sort(sorted, n);
    finish = clock();
    CalcTime();

    ForwardArr();
    start = clock();
    heap_sort(sorted, n);
    finish = clock();
    CalcTime();
}