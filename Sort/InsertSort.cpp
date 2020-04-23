void InsertSort(int Data[], int Lenght)
{
    for(int i = 1; i < Lenght; i++)
    {
        int j, Target = Data[i];
        for(j = i - 1; j >= 0 && Data[j] > Target; j--)
        {
            Data[j + 1] = Data[j];
        }
        Data[j + 1] = Target;
    }
}
