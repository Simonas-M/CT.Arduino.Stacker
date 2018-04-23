#include "FastLED.h"
#include "./my_defines.h"

struct TrailState
{
	int start;
	int end;
	int cutStart;
	int cutEnd;
};

struct Trail
{
	int position;
	CRGB *trail;
	unsigned int trailLength;
};

int getRandomNumber(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void advanceTrails(Trail *trails)
{
	for (int i = 0; i < LEDS_PER_ROW; i++)
	{
		if (trails[i].trail != NULL)
		{
			int trailSize = trails[i].trailLength;
			if (trails[i].position > trailSize + ROW_COUNT - 1)
			{
				free(trails[i].trail);
				trails[i].trail = NULL;
				return;
			}
			trails[i].position = trails[i].position + 1;
		}
	}
}

CRGB *createTrailLine(unsigned int trailLength)
{
	CRGB *trail = (CRGB *)malloc(trailLength * sizeof(CRGB));
	for (int i = trailLength - 1; i >= 0; i--)
	{
		trail[i] = CRGB::Aqua;
	}
	return trail;
}

Trail createTrail()
{
	int trailLength = getRandomNumber(1, ROW_COUNT);
	Trail trail;
	trail.position = 0;
	trail.trail = createTrailLine(trailLength);
	trail.trailLength = trailLength;
	return trail;
}

void maybeAddNewTrail(Trail trails[])
{
	int randomLine = getRandomNumber(0, LEDS_PER_ROW - 1);
	if (trails[randomLine].trail == NULL)
	{
		trails[randomLine] = createTrail();
	}
}

TrailState getTrailNextPosition(Trail trail)
{
	int length = trail.trailLength + 1;
	int position = trail.position;

	TrailState state;
	state.start = length > position ? 0 : position - length + 1;
	state.end = position < ROW_COUNT ? position : ROW_COUNT;
	state.cutStart = position >= length ? 0 : (length - position - 1);
	state.cutEnd = position < ROW_COUNT ? length : length - (position - ROW_COUNT) - 1;

	return state;
}

CRGB *getArraySlice(CRGB *array, int from, int to)
{
	const int size = to - from;
	CRGB *newArray = (CRGB *)malloc(size * sizeof(CRGB));
	for (int i = from; i > to; i++)
	{
		newArray[i] = array[i];
	}
	return newArray;
}