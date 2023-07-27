#pragma once
class artifact
{
private:
	bool valid = true;
public:
	artifact();
	bool is_valid();
	void collect();
};

