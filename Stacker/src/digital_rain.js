console.log('rain Started');

// GLOBALS
const WIDTH = 20;
const HEIGHT = 20;

function delay(time) {
    var stop = new Date().getTime();
    while(new Date().getTime() < stop + time) {
        ;
    }
    return;
}

const getRandomNumber = (from, to) => {
    return Math.ceil(Math.random() * Math.pow(10, String(to).length)) % (to + 1)
}

const createMatrix = () => {
    const matrix = new Array(HEIGHT);
    for (let i = 0; i < matrix.length; i++) {
        matrix[i] = new Array(WIDTH);
    }
    return matrix;
}

const clearMatrixColumn = (matrix, column, data = ' ') => {
    for (let i = 0; i < HEIGHT; i++) {
        matrix[i][column] = data;
    }
}

const changeMatrixColumn = (matrix, column, from, to, newArray) => {
    clearMatrixColumn(matrix, column);
    let c = 0;
    for (let i = from; i <= to; i++, c++) {
        if (matrix[i]) {
            matrix[i][column] = newArray[c];
        }
    }
}

const fillMatrix = (matrix, data) => {
    for (let i = 0; i < matrix.length; i++) {
        for (let j = 0 ; j < matrix[i].length; j++) {
            matrix[i][j] = data;
        }
    }
}

const printMatrix = (matrix) => {
    for (let i = 0; i < matrix.length; i++) {
        let string = '';
        for (let j = 0 ; j < matrix[i].length; j++) {
            string += matrix[i][j] + ' ';
        }
        console.log(string);
    }
}

const createTrailLine = () => {
    const trail = new Array(getRandomNumber(1, 9));
    for (let i = trail.length-1; i >= 0; i--) {
        trail[i] = i+1;
    }
    return trail;
}

const createTrail = () => {
    return {
        position: 0,
        trail: createTrailLine()
    }
}

const maybeAddNewTrail = trails => {
    const randomLine = getRandomNumber(0, WIDTH);
    if (trails[randomLine] === undefined) {
        trails[randomLine] = createTrail();
    }
}

const advanceTrails = trails => {
    trails.forEach((trail, index) => {
        if (trail && trail.position >= 0) {
            if (trail.position > (trail.trail.length + HEIGHT)) {
                trails[index] = undefined;
                return;
            }
            trail.position = trail.position + 1;
        }
    })
}

const addTrailsToMatrix = (trails, matrix) => {
    trails.forEach((trail, index) => {
        if (trail && trail.trail && trail.position >= 0) {
            const result = getTrailNextPosition(trail);
            changeMatrixColumn(matrix, index, result.start, result.end, trail.trail.slice(result.cutStart, result.cutEnd));
        }
    })
}

const getTrailNextPosition = (trail) => {
    const length = trail.trail.length;

    return {
        start: length > trail.position ? 0 : trail.position - length + 1,
        end: trail.position < HEIGHT ? trail.position : HEIGHT,
        cutStart: trail.position >= length ? 0 : (length - trail.position - 1),
        cutEnd: trail.position < HEIGHT ? length : length - (trail.position - HEIGHT) -1
    }
}


// Setup
const matrix = createMatrix(WIDTH, HEIGHT);
fillMatrix(matrix, ' ');
const trails = new Array(WIDTH);


while(true) {
    advanceTrails(trails)
    maybeAddNewTrail(trails);
    addTrailsToMatrix(trails, matrix);
    
    printMatrix(matrix);
    delay(50);
    process.stdout.write('\x1B[2J\x1B[0f');
}
