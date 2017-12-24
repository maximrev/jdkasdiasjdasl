#include "Analysis.h"

void Analysis::Analyse(double* &arr, double price, double low, double high) {

}

void Analysis::CalcSMA(double price) {
	SMA.sum += price;
	if (PriceHistory.size() == SMA.period) {
		SMA.sum -= PriceHistory.front();
		SMA.SMA = SMA.sum / (double)SMA.period;
		PriceHistory.pop_front();
		PriceHistory.push_back(price);
	}
	else {
		PriceHistory.push_back(price);
		SMA.SMA = SMA.sum / (double)PriceHistory.size();
	}
}

void Analysis::CalcEMA(double price) {
	if (EMA.last) {
		EMA.EMA = (price - EMA.last)*EMA.mult + EMA.last;
		EMA.last = EMA.EMA;
	}
	else {
		EMA.last = price;
	}
}

void Analysis::CalcBearsPower(double price) {
	if (BearsEMA.last) {
		BearsEMA.EMA = (price - BearsEMA.last)*BearsEMA.mult + BearsEMA.last;
		BearsEMA.last = BearsEMA.EMA;
	}
	else {
		BearsEMA.last = price;
	}
	BearsPower = low - BearsEMA.EMA;
}

void Analysis::CalcBullsPower(double price) {
	if (BullsEMA.last) {
		BullsEMA.EMA = (price - BullsEMA.last)*BullsEMA.mult + BullsEMA.last;
		BullsEMA.last = BullsEMA.EMA;
	}
	else {
		BullsEMA.last = price;
	}
	BullsPower = high - BullsEMA.EMA;
}

Analysis::Analysis(int periodEMA, int periodSMA, int periodBearsEMA) {
	this->SMA.sum = 0;
	this->EMA.period = periodEMA;
	this->SMA.period = periodSMA;
	this->BearsEMA.period = periodBearsEMA;
	this->EMA.mult = (double)2 / (double)(periodEMA + 1);
	this->BearsEMA.mult = (double)2 / (double)(periodBearsEMA + 1);
}