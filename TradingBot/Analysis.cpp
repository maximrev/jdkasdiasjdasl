#include "Analysis.h"

void Analysis::Analyse(double* &arr, double price, double low, double high) {
	this->lastlow = this->low;
	this->lasthigh = this->high;
	this->low = low;
	this->high = high;
}

void Analysis::CalcSMA(double price, sSMA *SMA) {
	SMA->sum += price;
	if (SMA->PriceHistory.size() == SMA->period) {
		SMA->sum -= SMA->PriceHistory.front();
		SMA->SMA = SMA->sum / (double)SMA->period;
		SMA->PriceHistory.pop_front();
		SMA->PriceHistory.push_back(price);
	}
	else {
		SMA->PriceHistory.push_back(price);
		SMA->SMA = SMA->sum / (double)SMA->PriceHistory.size();
	}
}

void Analysis::CalcEMA(double price, sEMA *EMA) {
	if (EMA->last) {
		EMA->EMA = (price - EMA->last)*EMA->mult + EMA->last;
		EMA->last = EMA->EMA;
	}
	else {
		EMA->last = price;
	}
}

void Analysis::CalcBearsPower(double price, sEMA *EMA) {
	CalcEMA(price, EMA);
	BearsPower = low - EMA->EMA;
}

void Analysis::CalcBullsPower(double price, sEMA *EMA) {
	CalcEMA(price, EMA);
	BullsPower = high - BullsEMA.EMA;
}

void Analysis::CalcDMark(sSMA *highSMA, sSMA *lowSMA) {
	if (high > lasthigh) {
		CalcSMA(high - lasthigh, highSMA);
	}
	else {
		CalcSMA(0, highSMA);
	}

	if(low < lastlow) {
		CalcSMA(high - lasthigh, lowSMA);
	}
	else {
		CalcSMA(0, lowSMA);
	}

	DMark = highSMA->SMA / (highSMA->SMA + lowSMA->SMA);
}

Analysis::Analysis(int periodEMA, int periodSMA, int periodBearsEMA) {
	this->SMA.sum = 0;
	this->EMA.period = periodEMA;
	this->SMA.period = periodSMA;
	this->BearsEMA.period = periodBearsEMA;
	this->EMA.mult = (double)2 / (double)(periodEMA + 1);
	this->BearsEMA.mult = (double)2 / (double)(periodBearsEMA + 1);
	this->lasthigh = 0;
	this->lastlow = 0;
}