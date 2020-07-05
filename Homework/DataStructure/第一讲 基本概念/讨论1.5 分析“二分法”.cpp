int find(List, X)
{
	begin = List起始元素的位置;
	end = List中间元素的位置;
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
