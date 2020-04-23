void SelectionSort(int DataSet[], int Lenght)
{
    for(int i = 0; i < Lenght; i++)
    {
        int MinIdx = i;
        for(int j = i; j < Lenght; j++)
        {
            if(DataSet[i] > DataSet[j])
            {
                MinIdx = j;
            }
        }
        int Temp = DataSet[MinIdx];
        DataSet[MinIdx] = DataSet[i];
        DataSet[i] = Temp;
    }
}
