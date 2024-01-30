#pragma once
//monke arrays

/// <summary>
/// Chcecks is array/matrix is monge using brute force algorithm
/// </summary>
/// <returns>Returns true if yes, othwerwise false</returns>
template<class T=int>
bool is_monge(T** arr, const size_t& width, const size_t& height)
{
	if (width < 2 || height < 2)
		return false; //at least 2x2 array is required

	for (int x = 0; x < height-1; x++)
	{
		for (int y = 0; y < width-1; y++)
		{
			if (arr[x][y] + arr[x + 1][y + 1] > arr[x][y + 1] + arr[x + 1][y])
				return false;
		}
	}

	return true;
}
