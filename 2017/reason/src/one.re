let dirname = switch [%bs.node __dirname] {
  | None => ""
  | Some(dir) => dir
};
let input_path = Node.Path.join([|dirname, "..", "..", "inputs", "one.txt"|]);
let input = Node.Fs.readFileSync(input_path, `utf8);

let inverse_captcha = (string, step_calc) => {
  let string = String.trim(string);
  let length = String.length(string);
  let next_char = (i) => (i + step_calc(length)) mod length; 
  let rec op = (i, tally) => {
    if (i === length) {
      tally;
    } else {
      let this_char = String.get(string, i);
      let assoc_char = String.get(string, next_char(i));
      if (this_char === assoc_char) {
        let num = Int32.to_int(Int32.of_string(Char.escaped(this_char)));
        op(i + 1, tally + num);
      } else {
        op(i + 1, tally);
      }
    }
  };

  op(0, 0);
};

let check_solution = (expected, actual) => {
  Js.log("Expected: " ++ string_of_int(expected) ++ ". Actual: " ++ string_of_int(actual) ++ ".");
  if (expected === actual) {
    Js.log("\tPASS");
  } else {
    Js.log("\tFAIL");
  }
};

let part_one_step = (_) => 1;
let part_two_step = (length) => length / 2;

Js.log("Part One:");
check_solution(3, inverse_captcha("1122", part_one_step));
check_solution(4, inverse_captcha("1111", part_one_step));
check_solution(9, inverse_captcha("91212129", part_one_step));
check_solution(0, inverse_captcha("1234", part_one_step));
Js.log("Solution: " ++ string_of_int(inverse_captcha(input, part_one_step)));

Js.log("\nPart Two:");
check_solution(6, inverse_captcha("1212", part_two_step));
check_solution(0, inverse_captcha("1221", part_two_step));
check_solution(4, inverse_captcha("123425", part_two_step));
check_solution(12, inverse_captcha("123123", part_two_step));
check_solution(4, inverse_captcha("12131415", part_two_step));
check_solution(4, inverse_captcha("12131415", part_two_step));
Js.log("Solution: " ++ string_of_int(inverse_captcha(input, part_two_step)));
