#include <iostream>
#include <vector>
using namespace std;

int strStr(string, string);
int removeElement(vector<int>&, int);

int main()
{
    vector<int> nums = {0,1,2,2,3,0,4};
    int k = removeElement(nums, 2);
    for(int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << endl;
    }
    return 0;
}

int strStr(string haystack, string needle) {
    size_t position = haystack.find(needle);
    return position;
    /*
        if(haystack.length() < needle.length())
        {
            return -1;
        }
        else if(haystack == needle)
        {
            return 0;
        }
        string sub;
        for(int i = 0; i < (haystack.length() - needle.length() + 1); i++)
        {
            sub = haystack.substr(i, needle.length());
            cout << sub << endl;
            if(sub == needle)
            {

                cout << sub << "==" << needle;
                return i;
            }
        }
        return -1;
        */
    }

int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            if(nums[i] == val)
            {
                
                nums.erase(nums.begin() + i);
                k++;
                i--;
            }
        }
        return k;
    }