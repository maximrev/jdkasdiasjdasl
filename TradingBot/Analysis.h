#pragma once

#include <deque>

struct sEMA {
	double mult;
	double last;
	int period;
	double EMA;
};

struct sSMA {
	double sum;
	int period;
	double SMA;
};

class Analysis {
public:

	Analysis(int periodEMA, int periodSMA, int periodBearsEMA);
	void Analyse(double* &arr, double price, double low, double high);

protected:

	void CalcSMA(double price);
	void CalcEMA(double price);
	void CalcBearsPower(double price);
	void CalcBullsPower(double price);

private:

	double BearsPower;
	double BullsPower;
	sSMA SMA;
	sEMA EMA;
	sEMA BearsEMA;
	sEMA BullsEMA;

	std::deque<double>PriceHistory;
	double low;
	double high;
};