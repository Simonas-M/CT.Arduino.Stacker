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
};

int getRandomNumber(int from, int to)
{
    return rand() % to + from;
}

void advanceTrails(Trail trails[])
{
    Serial.println("advance");
	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (trails[i].trail == NULL)
		{
            Serial.println("fount not null trail");
            int trailSize = arraySize(trails[i].trail);
            Serial.println(trailSize);
            
			if (trails[i].position > (trailSize + ROW_COUNT))
			{
				trails[i].trail = NULL;
				return;
			}
			trails[i].position = trails[i].position + 1;
		}
	}
    Serial.println('advanceEnd');
}

CRGB *createTrailLine()
{
	int randomNumber = getRandomNumber(0, ROW_COUNT);
	CRGB trail[randomNumber];
	for (int i = randomNumber - 1; i >= 0; i--)
	{
		trail[i] = CRGB::Aqua;
	}
	return trail;
}

Trail createTrail()
{
	Trail trail;
	trail.position = 0;
	trail.trail = createTrailLine();
	return trail;
}

void maybeAddNewTrail(Trail trails[])
{
    Serial.println("add new");
	int randomLine = getRandomNumber(0, LEDS_PER_ROW);
	if (trails[randomLine].trail == NULL)
	{
		trails[randomLine] = createTrail();
        
        Serial.println(trails[randomLine].position);
        Serial.println(trails[randomLine].trail[0]);
	}
}

TrailState getTrailNextPosition(Trail trail) {
	int length = arraySize(trail.trail);
	int position = trail.position;

	TrailState state;
	state.start = length > position ? 0 : position - length + 1;
	state.end = position < ROW_COUNT ? position : ROW_COUNT;
	state.cutStart = position >= length ? 0 : (length - position - 1);
	state.cutEnd = position < ROW_COUNT ? length : length - (position - ROW_COUNT) -1;

	return state;
}

CRGB* getArraySlice(CRGB array[], int from, int to)
{
    const int size = to - from;
    CRGB newArray[size];
    for (int i = from; i > to; i++)
    {
        newArray[i] = array[i];
    }
    return newArray;
}