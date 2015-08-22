#include "calculator.h"
#include <cstring>
#include <iostream>

using namespace std;

calculator::calculator() {
	init();
}

void calculator::init() {
	memset(op, 0, sizeof(op));
	memset(posfix_op, 0, sizeof(posfix_op));
	memset(posfix_num, 0, sizeof(posfix_num));
	len_op = len_num = len_pos = 0;
	have_ans = false;
}

bool calculator::parse(char input[]) {
	int length = strlen(input);
	int temp = 0;
	bool add_num = false;

	init();

	/* Parsing into posfix */
	/* Potential bugs: (-1) negative number */
	for (int i = 0; i < length; i++) {
		if (input[i] >= '0' && input[i] <= '9') {
			temp = temp * 10 + (input[i] - '0');
			add_num = true;
		}
		else {
			if (add_num) {
				posfix_num[len_pos++] = temp;
				temp = 0;
				add_num = false;
			}

			if (input[i] == '+' || input[i] == '-') {
				while (len_op > 0) {
					if (op[len_op - 1] == '*' || op[len_op - 1] == '/' || op[len_op - 1] == '+' || op[len_op - 1] == '-') {
						posfix_op[len_pos++] = op[len_op - 1];
						len_op--;
					}
					else break;
				}
				op[len_op++] = input[i];
			}
			else if (input[i] == '*' || input[i] == '/') {
				while (len_op > 0) {
					if (op[len_op - 1] == '*' || op[len_op - 1] == '/') {
						posfix_op[len_pos++] = op[len_op - 1];
						len_op--;
					}
					else break;
				}
				op[len_op++] = input[i];
			}
			else if (input[i] == '(') {
				op[len_op++] = input[i];
			}
			else if (input[i] == ')') {
				while (op[len_op - 1] != '(') {
					len_op--;
					posfix_op[len_pos++] = op[len_op];
					if (len_op == 0) {
						cout << "Unmatched Parenthesis" << endl;
						return false;
					}
				}
				len_op--;
			}
			else {
				cout << "Unrecognizable symbol" << endl;
				return false;
			}
		}
	}
	if (add_num) {
		posfix_num[len_pos++] = temp;
		add_num = false;
	}
	while (len_op > 0) {
		posfix_op[len_pos++] = op[len_op - 1];
		len_op--;
	}
	return true;
}

bool calculator::calc() {
	int stack[1024], top = 0;
	for (int i = 0; i < len_pos; i++) {
		if (posfix_op[i] == 0) {
			// put num to stack
			stack[top++] = posfix_num[i];
		}
		else {
			// pop num out, calc, and push back;
			top--;
			if (posfix_op[i] == '+') {
				stack[top - 1] += stack[top];
			}
			else if (posfix_op[i] == '-') {
				stack[top - 1] -= stack[top];
			}
			else if (posfix_op[i] == '*') {
				stack[top - 1] *= stack[top];
			}
			else if (posfix_op[i] == '/') {
				stack[top - 1] /= stack[top];
			}
			else {
				cout << "Undefined operator: " << posfix_op[i] << endl;
				return false;
			}
		}
	}
	if (top != 1) {
		cout << "stack size = " << top << endl;
		cout << "Calculation Error" << endl;
		return false;
	}
	ans = stack[0];
	have_ans = true;
	return true;
}

int calculator::get_ans() {
	return ans;
}