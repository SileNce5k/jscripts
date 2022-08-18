// Clean up txt file that is created by copying foobar2k songs and pasting into notepad. (Basically just removing '[]' and everything in between :))
// First arg is path to file

const fs = require('fs');
const path = require('path');


function argHandler(args){
	let pathToTextFile = "";
	switch (args[2]) {
		case "--help":
		case "-h":
		case undefined:
			printHelp();
			break;
		default:
			pathToTextFile = args[2];
			break; 
	}
	return pathToTextFile;
}

function printHelp(){
	const helpText = `Usage:\n\tnode cleanuptxtfile.js <path_to_text_file>\n`;
	process.stdout.write(helpText);
	process.exit(0);
}

function fileNotFound(pathToTextFile) {
	console.log(`FILE NOT FOUND: ${pathToTextFile}\n`);
	process.exit(404);
}

function cleanFile(pathToTextFile) {
	let file = fs.readFileSync(pathToTextFile).toString();
	const regex = /(\[)(.*)(\])/gm;
	file = file.replace(regex, "");
	let newPath = `CLEANED_${path.basename(pathToTextFile)}`;
	fs.writeFileSync(newPath, file);
	console.log(`\nWrote new file to ${newPath}`);
}

let pathToTextFile = argHandler(process.argv);

fs.existsSync(pathToTextFile) ? cleanFile(pathToTextFile) : fileNotFound(pathToTextFile);