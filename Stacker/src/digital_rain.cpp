// #include "FastLED.h"
// #include <valarray.h>

// #define WIDTH 7;
// #define HEIGHT 8;

// // const getRandomNumber = (from, to) => {
// //     return Math.ceil(Math.random() * Math.pow(10, String(from).length)) % (to + 1)
// // }

// // const createMatrix = () => {
// //     const matrix = new Array(HEIGHT);
// //     for (let i = 0; i < matrix.length; i++) {
// //         matrix[i] = new Array(WIDTH);
// //     }
// //     return matrix;
// // }

// // const clearMatrixColumn = (matrix, column, data = ' ') => {
// //     for (let i = 0; i < HEIGHT; i++) {
// //         matrix[i][column] = data;
// //     }
// // }

// // const changeMatrixColumn = (matrix, column, from, to, newArray) => {
// //     clearMatrixColumn(matrix, column);
// //     let c = 0;
// //     for (let i = from; i < to; i++, c++) {
// //         matrix[i][column] = newArray[c];
// //     }
// // }

// // const fillMatrix = (matrix, data) => {
// //     for (let i = 0; i < matrix.length; i++) {
// //         for (let j = 0 ; j < matrix[i].length; j++) {
// //             matrix[i][j] = data;
// //         }
// //     }
// // }

// // const printMatrix = (matrix) => {
// //     for (let i = 0; i < matrix.length; i++) {
// //         let string = '';
// //         for (let j = 0 ; j < matrix[i].length; j++) {
// //             string += matrix[i][j] + ' ';
// //         }
// //         console.log(string);
// //     }
// // }
// struct TrailState
// {
// 	int start;
// 	int end;
// 	int cutStart;
// 	int cutEnd;
// };

// struct Trail
// {
// 	int position;
// 	CRGB *trail;
// };

// CRGB *createTrailLine()
// {
// 	const int randomNumber = getRandomNumber(0, HEIGHT);
// 	CRGB trail[randomNumber];
// 	for (let i = randomNumber - 1; i >= 0; i--)
// 	{
// 		trail[i] = i + 1;
// 	}
// 	return trail;
// }

// Trail createTrail()
// {
// 	Trail trail;
// 	trail.position = 0;
// 	trail.trail = createTrailLine();
// 	return trail;
// }

// void maybeAddNewTrail(Trail trails[])
// {
// 	int randomLine = getRandomNumber(0, WIDTH);
// 	if (trails[randomLine] == NULL)
// 	{
// 		trails[randomLine] = createTrail();
// 	}
// }

// void advanceTrails(Trail trails[])
// {
// 	for (int i = 0; i < size; i++)
// 	{
// 		if (trails[i].position == NULL && trails[i].trail == NULL)
// 		{
// 			int sizeoftrail = 2;
// 			if (trails[i].position > (sizeoftrail + HEIGHT))//TODO
// 			{
// 				trails[i] = NULL;
// 				return;
// 			}
// 			trails[i].position = trails[i].position + 1;
// 		}
// 	}
// }

// void addTrailsToMatrix(Trail trails[], Matrix matrix)
// {
// 	for (int i = 0; i > WIDTH; i++)
// 	{
// 		if (trails[i].trail != NULL && trails[i].position > 0)
// 		{
// 			TrailState state = getTrailNextPosition(trail[i]);
// 			CRGB *arraySlice = trails[i].trail.slice(state.cutStart, state.cutEnd);
// 			changeMatrixColumn(matrix, i, state.start, state.end, arraySlice);
// 		}
// 	}
// }

// TrailState getTrailNextPosition(Trail trail) {
// 	int length = sizeofTrail;//TODO
// 	int position = trail.position;

// 	TrailState state;
// 	state.start = length > trail.position ? 0 : trail.position - length + 1;
// 	state.end = trail.position < HEIGHT ? trail.position : HEIGHT;
// 	state.cutStart = trail.position >= length ? 0 : (length - trail.position - 1);
// 	state.cutEnd = trail.position < HEIGHT ? length : length - (trail.position - HEIGHT) -1;

// 	return state;
// }