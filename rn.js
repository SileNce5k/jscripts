if(process.argv.length < 3 || process.argv[2] == "--help"){
	console.log("Usage: node randomnumbers.js <how_many_digits_you_need>");
	process.exit(1);
}
const digits = process.argv[2];

let maxNumbers = 9;
let custom = false;
if(process.argv.length > 3){
	maxNumbers = process.argv[3]-1;
	custom = true;
}
let addNumber = false;
let number = 0;
if(process.argv.length > 4){
	number = process.argv[4]-1;
	number += 1;
	addNumber = true;
}

function g(digits){
	let m = [digits];
	for (let i = 0; i < digits; i++) {
		m[i] = Math.round(Math.random() * maxNumbers);
	}	
	let count = 0;
	for(let i = 0; i < m.length; i++){
		let x = 0;
		if(custom){
			x = 1;
		}
		
		if(addNumber){
			x += number;
		}
		let result = m[i]+x;
		if(count != 0)
			process.stdout.write(", ");
		//console.log(result);
		process.stdout.write(`${result}`)
		count += 1;
	}
	
	process.stdout.write("\n");
}
g(digits);