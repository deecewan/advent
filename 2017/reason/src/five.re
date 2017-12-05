let dirname = switch [%bs.node __dirname] {
  | None => ""
  | Some(dir) => dir
};
let input_path = Node.Path.join([|dirname, "..", "..", "inputs", "five.txt"|]);
let input = Node.Fs.readFileSync(input_path, `utf8);

let rec traverse = (values, index, count) => {
  if (index < 0 || index >= Array.length(values)) {
    count
  } else {
    let next_step = Array.get(values, index);
    /* delta always = 1 for the first part */
    let delta = if (next_step >= 3) {
      -1
    } else {
      1
    };
    Array.set(values, index, next_step + delta);
    traverse(values, index + next_step, count + 1);
  }
};

let calculate = (value) => {
  let value = value 
    |> Js.String.split("\n")
    |> Array.map(int_of_string);

  Js.log(traverse(value, 0, 0));
};

calculate(input);

