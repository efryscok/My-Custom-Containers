#pragma once

#include <vector>

class CHRTimer {
public:
	CHRTimer();
	virtual ~CHRTimer();
	void Start(void);
	void Stop(void);
	void Reset(bool bStopTimerToo = false);
	void ResetAndStart(void);

	// This will 'reset' the regular (short duration) timer and update the long duration
	float GetElapsedSeconds(bool bAndResetTimer = false);

	void SetNumberOfAverageSamples(unsigned int numSamples);
	float GetElapsedSecondsAverage(bool bAndResetTimer = false);

	unsigned long long GetFrequency(void);

	void ResetLongDuration(void);

	// Updates the long duration (and resets the 'short' or regular duration timer)
	void UpdateLongDuration(void);
	float get_fLondDurationTotalSeconds(void);
	double get_dLondDurationTotalSeconds(void);
	void getLongDurationValues(float &seconds, float &minutes);
private:
	unsigned long long m_elapsedTime;
	unsigned long long m_startTime;
	unsigned long long m_stopTime;
	unsigned long long m_frequency;

	void m_AppendLondDurationTimer(float deltaTime);
	double m_dLongDurationTotalSeconds;

	void m_ResetNumberOfSamples(unsigned int newNumberOfSamples);
	std::vector< float > m_vecLastXSamples;
	unsigned int m_nextSampleIndex;
	unsigned int m_numberOfSamples;
	static const unsigned int DEFAULTNUMBEROFSAMPLES = 60;
	bool m_bFirstSampleTaken;

	bool m_bIsRunning;
};
