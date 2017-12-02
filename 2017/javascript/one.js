import fs from 'fs';
import path from 'path';

const inputPath = path.join('..', 'inputs', 'one.txt');
const input = fs.readFileSync(inputPath, 'utf8');

function calc(input) {
    return Array.from(
        input[input.length - 1].concat(input)
    ).reduce((tally, num, i, x) => {
        if (i === 0) { return tally }
        if (num === x[i - 1]) { return tally + (num | 0) }
        return tally
    }, 0)
}

function calculate(string, step_calc) {
  const trimmed = string.trim();
  const step = step_calc(trimmed.length);
  return Array.from(trimmed).reduce((tally, num, i) => {
    if (num === trimmed[(i + step) % trimmed.length]) {
      return tally + (num | 0);
    }
    return tally;
  }, 0);
}

const partOneCalc = () => 1;
const partTwoCalc = length => length / 2;

function checkResult(expected, actual) {
  console.log(`Expected: ${expected}. Actual: ${actual}. \n\t${expected === actual ? 'PASS' : 'FAIL'}`)
}

console.log('Part One:');
checkResult(3, calculate('1122', partOneCalc));
checkResult(4, calculate('1111', partOneCalc));
checkResult(9, calculate('91212129', partOneCalc));
checkResult(0, calculate('1234', partOneCalc));
console.log(`Solution: ${calculate(input, partOneCalc)}`)

console.log('\nPart Two:');
checkResult(6, calculate('1212', partTwoCalc));
checkResult(0, calculate('1221', partTwoCalc));
checkResult(4, calculate('123425', partTwoCalc));
checkResult(12, calculate('123123', partTwoCalc));
checkResult(4, calculate('12131415', partTwoCalc));
console.log(`Solution: ${calculate(input, partTwoCalc)}`)
