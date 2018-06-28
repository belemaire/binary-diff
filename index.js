const bsdiff = require('./build/Release/bsdiff.node');
module.exports = (bufA, bufB) => bsdiff.diff(bufA, bufA.length, bufB, bufB.length)