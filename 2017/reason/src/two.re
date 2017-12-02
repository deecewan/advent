let dirname = switch [%bs.node __dirname] {
  | None => ""
  | Some(dir) => dir
};
let input_path = Node.Path.join([|dirname, "..", "..", "inputs", "two.txt"|]);
let input = Node.Fs.readFileSync(input_path, `utf8);

let example = "5\t1\t9\t5\n7\t5\t3\n2\t4\t6\t8";
let example_answer = 18;

let calculate = (string) => {

  let rows = Js.String.split("\n", string);

  rows
    |> Array.map(Js.String.split("\t"))
    |> Array.map(Array.map(int_of_string))
    |> Array.map((c) => {
      c |> Array.sort(Pervasives.compare);
      c;
    })
    |> Array.map((c) => {
        let first = Array.get(c, 0);
        let last = Array.get(c, Array.length(c) - 1);
        last - first
      })
    |> Array.fold_left((acc, curr) => acc + curr, 0);
};

Js.log("EXAMPLE: Expected: " ++ string_of_int(example_answer) ++ ". Actual: " ++ string_of_int(calculate(example)) ++ ".");
Js.log("Part One output: " ++ string_of_int(calculate(input)) ++ ".");

let calculate_part_two = (string) => {
  let rows = Js.String.split("\n", string);

  rows
    |> Array.map(Js.String.split("\t"))
    |> Array.map(Array.map(float_of_string))
    |> Array.map((c) => {
        Array.mapi((i, x) => {
          Array.mapi((j, z) => {
            if (i === j) {
              0.
            } else {
              x /. z
            }
          }, c) |> Array.to_list;
        }, c) |> Array.to_list |> List.concat;
      })
    |> Array.map(List.filter(x => x > 0. && Js.Math.round(x) === x))
    |> Array.to_list
    |> List.flatten
    |> List.fold_left((acc, curr) => acc +. curr, 0.)
};

let second_example = "5\t9\t2\t8\n9\t4\t7\t3\n3\t8\t6\t5";
let second_answer = 9;

Js.log("EXAMPLE: Expected: " ++ string_of_int(second_answer) ++ ". Actual: " ++ string_of_float(calculate_part_two(second_example)) ++ ".");
Js.log("Part two output: " ++ string_of_float(calculate_part_two(input)) ++ ".");
