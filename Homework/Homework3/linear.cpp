// Return true if the somePredicate function returns false for at
// least one of the array elements, false otherwise.
bool anyFalse(const double a[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    if (!somePredicate(a[n-1]))
    {
        return true;
    }
    else
    {
        return anyFalse(a, n-1);
    }
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else
    {
        if (!somePredicate(a[n-1]))
        {
            return countFalse(a, n-1) + 1;
        }
        else
        {
            return countFalse(a, n - 1);
        }
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    if (somePredicate(a[n-1]))
    {
        if (firstTrue(a, n-1) == -1)
        {
            return n-1;
        }
    }
    return firstTrue(a, n-1);
}

// Return the subscript of the largest element in the array (i.e.,
// return the smallest subscript m such that a[m] >= a[k] for all
// k such that k >= 0 and k < n).  If there is no such subscript,
// return -1.
int locateMax(const double a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    if (n == 1)
    {
        return 0;
    }
    else
    {
        if (a[n-1] > a[locateMax(a, n-1)])
        {
            return n-1;
        }
        else
        {
            return locateMax(a, n-1);
        }
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
    {
        return true;
    }
    if (n1 <= 0)
    {
        return false;
    }
    if (a1[n1-1] == a2[n2-1])
    {
        return contains(a1, n1-1, a2, n2-1);
    }
    else
    {
        return contains(a1, n1-1, a2, n2);
    }
}
