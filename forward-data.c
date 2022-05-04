#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 65536 //�������� ���� ����
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP�Լ� ����
int original[MAX_SIZE];    //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];    //�� ���� �˰��򿡼� ����� ������ �迭
int n; //�������� ������ �޴� �������� ����
int sorted[MAX_SIZE];
clock_t start, finish, used_time = 0;    //���� �ð� ������ ���� ����

//���� ����
void bubble_sort(int list[], int n)
{
    int i, j, tmp;
    printf("���� ���� ��... ");
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], tmp);
    }
}

//���� ����
void selection_sort(int list[], int n)
{
    int i, j, least, tmp;

    printf("���� ���� ��... ");
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least]) least = j;
        SWAP(list[i], list[least], tmp);
    }
}

//�������� ���ؼ� ������ ������ ����Ϸ� ��.
void selection_sort_fd(int list[], int n)
{
    int i, j, least, tmp;

    printf("���� ��... ");
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least]) least = j;
        SWAP(list[i], list[least], tmp);
    }
}

//���� ����
void insertion_sort(int list[], int n)
{
    int i, j, key;
    printf("���� ���� ��... ");
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}

//������
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

//������
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
    printf("�� ���� �� ... ");
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

//������
int swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int list[], int n, int i) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;


    // ���� �ڽ� ��尡 �����ϸ鼭 �θ���� �� ��.
    if (leftChildNode < n && list[parentNode] < list[leftChildNode]) {
        parentNode = leftChildNode;
    }
    // ������ �ڽ� ��尡 �����ϸ鼭 �θ���� �� ��.
    if (rightChildNode < n && list[parentNode] < list[rightChildNode]) {
        parentNode = rightChildNode;
    }


    // ���� or ������ �ڽ� ��� �� �θ� ��庸�� ū ���� ������ ���
    if (i != parentNode) {
        swap(&list[parentNode], &list[i]);
        // �ʱ� �θ��尡 �������� ã�� ������ �������ϴ�.
        heapify(list, n, parentNode);
    }
}

void heap_sort(int list[], int n) {
    // �ִ� ��(Max Heap) ����
    printf("�� ���� ��...");
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(list, n, i);
    }

    // Root�� ��ġ�� �ִ밪�� ������ ���� �ٲ㰡�� Heap �籸��
    // Heap�� ũ�⸦ �ٿ����� ���� ū ���Ҹ� ���ʷ� �����ɴϴ�.
    for (int i = n - 1; i > 0; i--) {
        swap(&list[0], &list[i]);
        heapify(list, i, 0);
    }
}

//���� �迭�� �����ϴ� �Լ�
void CopyArr(void)
{
    int i;
    for (i = 0; i < n; i++)
        list[i] = original[i];
}

// ������ �����͸� ���Ҷ�� ���� �Լ�
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

//���� �ð��� ���� �� ����ϴ� �Լ�
void CalcTime(void)
{
    used_time = finish - start;
    printf("�Ϸ�!\n�ҿ� �ð� : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}

void main()
{
    int i;

    n = MAX_SIZE;
    for (i = 0; i < n; i++)
        original[i] = rand();

    printf("�������� ���� : %d\n\n", n);

    CopyArr();
    printf("\n");
    selection_sort_fd(list, n);
    printf("�Ϸ� !\n");
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
    printf("�� ���� ��... ");
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