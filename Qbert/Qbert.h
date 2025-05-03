#pragma once
class Qbert {
public:
	Qbert();

	Qbert(const Qbert&) = delete;
	Qbert& operator=(const Qbert&) = delete;
	Qbert(Qbert&&) = delete;
	Qbert& operator=(Qbert&&) = delete;
	~Qbert() = default;

private:

};

