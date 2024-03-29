#include <Windows.h>

#include "CHRTimer.h"

CHRTimer::CHRTimer() {
	this->Reset();

	LARGE_INTEGER tempTime;
	QueryPerformanceFrequency(&tempTime);

	this->m_frequency = static_cast<unsigned long long>(tempTime.QuadPart);
	this->m_ResetNumberOfSamples(DEFAULTNUMBEROFSAMPLES);
	this->m_bFirstSampleTaken = false;

	return;
}

CHRTimer::~CHRTimer() {
	return;
}

void CHRTimer::Start(void) {
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);
	this->m_startTime = static_cast<unsigned long long>(tempTime.QuadPart);
	this->m_bIsRunning = true;
}

void CHRTimer::Stop(void) {
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);
	this->m_stopTime = static_cast<unsigned long long>(tempTime.QuadPart);
	this->UpdateLongDuration();
	this->m_bIsRunning = false;
}

void CHRTimer::Reset(bool bStopTimerToo /*= false*/) {
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);
	this->m_elapsedTime = 0;
	this->m_startTime = this->m_startTime = static_cast<unsigned long long>(tempTime.QuadPart);
	this->m_stopTime = this->m_startTime;

	this->ResetLongDuration();

	if (bStopTimerToo) {
		this->m_bIsRunning = false;
	}

	return;
}

void CHRTimer::ResetAndStart(void) {
	this->Reset();
	this->Start();
	return;
}

float CHRTimer::GetElapsedSeconds(bool bAndResetTimer /*= false*/) {
	// Update current time
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);

	if (this->m_bIsRunning) {
		this->m_stopTime = static_cast<unsigned long long>(tempTime.QuadPart);
	}

	// Calculate elapsed time
	this->m_elapsedTime = this->m_stopTime - this->m_startTime;
	float elapsedTimeSec = static_cast<float>(this->m_elapsedTime) / static_cast<float>(this->m_frequency);

	if (bAndResetTimer) {
		this->Reset(false);
	}

	// Update the long duration timer
	if (this->m_bIsRunning) {
		this->m_AppendLondDurationTimer(elapsedTimeSec);
	}

	return elapsedTimeSec;
}

void CHRTimer::SetNumberOfAverageSamples(unsigned int numSamples) {
	this->m_ResetNumberOfSamples(numSamples);
	return;
}

float CHRTimer::GetElapsedSecondsAverage(bool bAndResetTimer /*= false*/) {
	float curSample = this->GetElapsedSeconds(bAndResetTimer);

	if (this->m_vecLastXSamples.empty()) {
		return 0.0f;
	}

	this->m_vecLastXSamples[this->m_nextSampleIndex] = curSample;

	this->m_nextSampleIndex++;
	if (this->m_nextSampleIndex >= this->m_vecLastXSamples.size()) {
		this->m_nextSampleIndex = 0;
	}

	float sumSamples = 0.0f;
	for (int index = 0; index != this->m_numberOfSamples; index++) {
		sumSamples += this->m_vecLastXSamples[index];
	}

	return sumSamples / static_cast<float>(this->m_numberOfSamples);
}

void CHRTimer::m_ResetNumberOfSamples(unsigned int newNumberOfSamples) {
	// Create a new vector of samples and pre-load it with the average of the old vector

	// Save old average
	float oldAverage = this->GetElapsedSecondsAverage(true);

	this->m_numberOfSamples = newNumberOfSamples;

	this->m_vecLastXSamples.clear();
	this->m_vecLastXSamples.reserve(this->m_numberOfSamples);

	for (int index = 0; index != this->m_numberOfSamples; index++) {
		this->m_vecLastXSamples.push_back(oldAverage);
	}
	// Start at the beginning of the sample vector
	this->m_nextSampleIndex = 0;

	return;
}

unsigned long long CHRTimer::GetFrequency(void) {
	return this->m_frequency;
}


void CHRTimer::m_AppendLondDurationTimer(float deltaSeconds) {
	this->m_dLongDurationTotalSeconds += deltaSeconds;
	return;
}

void CHRTimer::UpdateLongDuration(void) {
	// GetElapsedSeconds() updates m_elapsedTime;
	float deltaTime = this->GetElapsedSeconds();
	this->m_AppendLondDurationTimer(deltaTime);
	return;
}

void CHRTimer::getLongDurationValues(float &seconds, float &minutes) {
	double dSeconds = this->m_dLongDurationTotalSeconds;
	double dMinutes = 0.0f;
	if (this->m_dLongDurationTotalSeconds >= 60.0) {
		dMinutes = dSeconds / 60.0;
		dSeconds -= (dMinutes * 60.0f);
	}
	seconds = static_cast<float>(dSeconds);
	minutes = static_cast<float>(dMinutes);
	return;
}

float CHRTimer::get_fLondDurationTotalSeconds(void) {
	return static_cast<float>(this->m_dLongDurationTotalSeconds);
}

double CHRTimer::get_dLondDurationTotalSeconds(void) {
	return this->m_dLongDurationTotalSeconds;
}

void CHRTimer::ResetLongDuration(void) {
	this->m_dLongDurationTotalSeconds = 0.0;
	return;
}