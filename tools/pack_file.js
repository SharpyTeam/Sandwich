const fs = require('fs'),
    path = require('path');

if (process.argv.length < 5) {
    if (process.argv.length === 2) {
        console.info('Usage: node pack_file.js <input_file> <output_file>');
    }
    console.error("Not enough arguments!");
    console.info('Usage: node pack_file.js <input_file> <output_file>');
    process.exit(-1);
}

const inputFilePath = path.resolve(process.argv[2]);
const outputFilePath = path.resolve(process.argv[3]);
const variableName = process.argv[4].trim();

let inputFile = fs.openSync(inputFilePath, 'r');
let outputFile = fs.openSync(outputFilePath, 'w');

const fileLength = fs.fstatSync(inputFile).size;

console.log("Packing file '" + path.basename(inputFilePath) + "' to '" + path.basename(outputFilePath) + "'...");
let buffer = Buffer.alloc(1);

process.stdout.write("Starting...");

fs.writeSync(outputFile, 'const char ' + variableName + '[] = {');

for (let bytesWritten = 0; bytesWritten < fileLength; ++bytesWritten) {
    fs.readSync(inputFile, buffer, 0, 1, null);
    fs.writeSync(outputFile, '0x' + buffer.toString('hex') + ',');
    process.stdout.write("\rProcessed " + bytesWritten + " / " + fileLength + " bytes");
}
process.stdout.write("\rProcessed " + fileLength + " / " + fileLength + " bytes");

fs.writeSync(outputFile, '};\n');

console.log();
console.log("Done!");




