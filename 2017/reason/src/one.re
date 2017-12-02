let x = "1122";
let x_ans = 3;
let y = "1111";
let y_ans = 4;
let z = "91212129";
let z_ans = 9;
let w = "1234";
let w_ans = 0;

let input = Node.Fs.readFileSync("./one_input.txt", `utf8);

let prepare_string = (string) => {
  let trimmed = String.trim(string);
  let first = Char.escaped(
    String.get(
      trimmed,
      String.length(trimmed) - 1
  	)
  );
  String.concat("", [first, string]);
};

let rec calculate = (string, i, tally) => {
  if (i === String.length(string)) {
    tally;
  } else {
    let a = String.get(string, i - 1);
    let b = String.get(string, i);
    if (a === b) {
      let num = Int32.to_int(Int32.of_string(String.make(1, a)));
      calculate(string, i + 1, tally + num);
    } else {
      calculate(string, i + 1, tally) 
    }
  }
};


Js.log(calculate(prepare_string(x), 1, 0));
Js.log(calculate(prepare_string(y), 1, 0));
Js.log(calculate(prepare_string(z), 1, 0));
Js.log(calculate(prepare_string(w), 1, 0));
Js.log(calculate(prepare_string(input), 1, 0));
