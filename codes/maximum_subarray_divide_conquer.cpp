// find the maximum subarray using divide and conquer 
// empty array is not allowed
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int NEGINF = -1000000;
char TESTFILE[] = "../tests/maximum_subarray_divide_conquer.txt";
char SOLUTION[] = "../tests/solution_maximum_subarray_divide_conquer.txt";

struct result{
	int left;
	int right;
	int sum;
};

// find max subarray that crossing the midpoint
result cross_max(vector<int> &nums, int low, int mid, int high){
	int left_sum = NEGINF;
	int right_sum = NEGINF;
	int sum = 0;
	int max_left;
	int max_right;
	for (int i = mid; i >= low; i--){
		sum += nums.at(i);
		if (sum > left_sum){
			left_sum = sum;
			max_left = i;
		}
	}
	sum = 0;
	for (int j = mid+1; j <= high; j++){
		sum += nums.at(j);
		if (sum > right_sum){
			right_sum = sum;
			max_right = j;
		}
	}
	result ret = {max_left, max_right, left_sum + right_sum};
	return ret;
}

// divide and conquer
result max_subarray(vector<int> &nums, int low, int high){
	if (low == high){
		result ret = {low, high, nums.at(low)};
		return ret;
	}
	else {
		int mid = (low + high) >> 1;
		result left_res = max_subarray(nums, low, mid);
		result right_res = max_subarray(nums, mid+1, high);
		result mid_res = cross_max(nums, low, mid, high);
		if ((left_res.sum >= right_res.sum) && (left_res.sum >= mid_res.sum)){
			result ret = {left_res.left, left_res.right, left_res.sum};
			return ret;
		}
		else if ((right_res.sum >= left_res.sum) && (right_res.sum >= mid_res.sum)){
			result ret = {right_res.left, right_res.right, right_res.sum};
			return ret;
		}
		else {
			result ret = {mid_res.left, mid_res.right, mid_res.sum};
			return ret;
		}
	}
}


int solve(vector<int> &nums){
	int low = 0;
	int high = nums.size()-1;
	result ret = max_subarray(nums, low, high);
	return ret.sum;
}


void test(char test[], char answer[]){
	ifstream ftest;
	ifstream fanswer;
	ftest.open(test);
	fanswer.open(answer);
	int num_test;
	int len_array;
	int incorrect = 0;
	ftest >> num_test;
	for (int j = 0; j < num_test; j++){
		ftest >> len_array;
		vector<int> nums;
		for (int i = 0; i < len_array; i++){
			int in;
			ftest >> in;
			nums.push_back(in);
		}
		int solution;
		fanswer >> solution;
		int output = solve(nums);
		if (solution != output){
			cout << "output: " << output << " solution: " << solution << " FAILED!\n";
			incorrect += 1;
		}
		else {
			cout << "output: " << output << " solution: " << solution << "\n";
		}
	}
	ftest.close();
	fanswer.close();
	cout << "PASSED " << num_test - incorrect << "/" << num_test << " TESTS\n";
}

int main(){
	test(TESTFILE, SOLUTION);
	return 0;
}