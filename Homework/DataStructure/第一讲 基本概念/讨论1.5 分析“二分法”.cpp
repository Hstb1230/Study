int find(List, X)
{
	begin = List��ʼԪ�ص�λ��;
	end = List�м�Ԫ�ص�λ��;
	while(begin <= end)
	{
		mid = (end + begin) / 2;
		if(List[mid] == X)
		    return mid;
		else if(List[mid] <= X)
			begin = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}
