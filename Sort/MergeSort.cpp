#include <stdio.h>
#include <stdlib.h>

void MergeSort(int DataSet[], int StartIndex, int EndIndex);
void Merge(int DataSet[], int StartIndex, int MiddleIndex, int EndIndex);


void MergeSort(int DataSet[], int StartIndex, int EndIndex)
{
    if(StartIndex > EndIndex) return;
    
    int MiddleIndex = (StartIndex + EndIndex) / 2; // 절반으로 나누기 위해 중간 값 찾기
    
    MergeSort(DataSet, StartIndex, MiddleIndex); // 시작 ~ 중간
    MergeSort(DataSet, MiddleIndex + 1, EndIndex); // 중간+1 ~ 끝
    
    Merge(DataSet, StartIndex, MiddleIndex, EndIndex); // 다시 합치기
}

void Merge(int DataSet[], int StartIndex, int MiddleIndex, int EndIndex)
{
    int Length = EndIndex - StartIndex + 1;
    int* Destination = (int*) malloc(sizeof(int) * Length); // 현재 데이터 집합 크기만큼 임시 배열 만들기
    
    int LeftIndex = StartIndex;         // 왼쪽 배열의 시작은 시작 인덱스
    int RightIndex = MiddleIndex + 1;   // 오른쪽 배열의 시작은 중간 인덱스 + 1
    int DestIndex = 0;
    
    while(LeftIndex <= MiddleIndex && RightIndex <= EndIndex)
    {
        if(DataSet[LeftIndex] < DataSet[RightIndex]) // 왼쪽 배열의 값이 더 작으면
        {
            Destination[DestIndex] = DataSet[LeftIndex]; // 왼쪽 배열의 데이터부터 넣어준다
            LeftIndex++;
        }
        else                                         // 오른쪽 배열의 값이 더 작으면
        {
            Destination[DestIndex] = DataSet[RightIndex]; // 오른쪽 배열의 데이터부터 넣어준다
            RightIndex++;
        }
        DestIndex++;
    }
    
    while(LeftIndex <= MiddleIndex) // 오른쪽 배열이 먼저 끝나서, 왼쪽 배열 데이터가 남은 경우
    {
        Destination[DestIndex++] = DataSet[LeftIndex++];
    }
    
    while(RightIndex <= EndIndex) // 왼쪽 배열이 먼저 끝나서, 오른쪽 배열 데이터가 남은 경우
    {
        Destination[DestIndex++] = DataSet[RightIndex++];
    }
    
    DestIndex = 0;
    for(int i = StartIndex; i <= EndIndex; i++)
    {
        DataSet[i] = Destination[DestIndex++]; // 기존 배열에 정렬된 데이터를 넣어준다.
    }
    
    free(Destination);
}

int main(void)
{
    int DataSet[] = { 334, 6, 4, 2, 3, 1, 5, 117, 12, 34 };
    int Length = sizeof DataSet / sizeof DataSet[0];
    
    MergeSort(DataSet, 0, Length-1);
    
    for(int i = 0; i < Length; i++)
    {
        printf("%d ", DataSet[i]);
    }
    return 0;
}
