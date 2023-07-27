#pragma once
class trap
{
private:
	bool active = false;
public:
	trap();
	bool is_active();
	void activate();
};

