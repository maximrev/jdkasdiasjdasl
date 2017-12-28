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
	std::deque<double>PriceHistory;
};

class Analysis {
public:

	Analysis(int periodEMA, int periodSMA, int periodBearsEMA);
	void Analyse(double* &arr, double price, double low, double high);

protected:

	void CalcDMark(sSMA *highSMA, sSMA *lowSMA);
	void CalcSMA(double price, sSMA *SMA);
	void CalcEMA(double price, sEMA *EMA);
	void CalcBearsPower(double price, sEMA *EMA);
	void CalcBullsPower(double price, sEMA *EMA);
	void CalcForceIndex(double price, sEMA *EMA, sEMA *lastEMA);

private:

	double ForceIndex;
	double DMark;
	double BearsPower;
	double BullsPower;
	sSMA DMakhighSMA;
	sSMA DMaklowSMA;
	sSMA SMA;
	sEMA EMA;
	sEMA BearsEMA;
	sEMA BullsEMA;
	sEMA ApPriceEMA;
	sEMA lastApPriceEMA;

	double volume;
	double ApPrice;
	double low;
	double high;
	double lasthigh;
	double lastlow;
};