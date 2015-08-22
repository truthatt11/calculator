#pragma once

class calculator {
public:
	calculator();
	bool parse(char[]);
	bool calc();
	int get_ans();

private:
	void init();
	char op[1024];
	char posfix_op[1024];
	int posfix_num[1024];
	int len_op, len_num, len_pos;
	bool have_ans;
	int ans;
};