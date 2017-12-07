const fs = require('fs');
const path = require('path');

const content = fs.readFileSync(path.join('..', 'inputs', 'seven.txt'), 'utf8');

const data = {};

const rows = content.trim().split('\n');

const res = rows
    .map(row => row.match(/([^ ]+) \((\d+)\)( -> (.*$))?/))
    .map(([, name, weight, , children]) => ({
        name,
        weight: parseInt(weight, 10),
        children: children ? children.split(', ') : [],
    }))

const findRoot = (child) => {
    const name = child.name;
    const item = res.find(row => row.children.includes(name));
    if (item) {
        return findRoot(item);
    }
    return child;
};

const root = findRoot(res[0]);
console.log('The root is', root.name);

const map = res
    .map(x => ({ [x.name]: x }))
    .reduce((acc, curr) => ({ ...acc, ...curr }), {});

const sum = (arr) => arr.reduce((acc, curr) => acc + curr);

const calculateWeight = (item) => {
    const itemWeight = item.weight;
    const children = item.children.map(x => map[x]);
    return itemWeight + children.map(calculateWeight).reduce((acc, curr) => acc + curr, 0);
}

res.forEach(item => {
    const total = calculateWeight(item);
    map[item.name].total = total;
});

const validate = (item) => {
    const childWeights = item.children.map(x => map[x].total);

    if (sum(childWeights) / childWeights.length === childWeights[0]) {
        return item;
    }

    // go into that one
    const oddOneOut = childWeights.find(x => childWeights.filter(y => x === y).length === 1);
    const res = validate(map[item.children.find(x => map[x].total === oddOneOut)]);

    if (typeof res === 'number') {
        return res;
    }

    const diff = oddOneOut - childWeights.find(x => childWeights.filter(y => x === y).length !== 1);

    return res.weight - diff;
};

console.log(`Bad weight should be: ${validate(map[root.name])}`);
