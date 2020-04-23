void BubbleSort(int DataSet[], int Lenght)
{
    int temp = 0;
    for(int i = 0; i < Lenght; i++)
    {
        for(int j = 1; j < Lenght - i; j++)
        {
            if(DataSet[j-1] > DataSet[j])
            {
                temp = DataSet[j-1];
                DataSet[j-1] = DataSet[j];
                DataSet[j] = temp;
            }
        }
    }
}
