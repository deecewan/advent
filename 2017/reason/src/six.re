let dirname =
  switch [%bs.node __dirname] {
  | None => ""
  | Some(dir) => dir
  };

let input_path = Node.Path.join([|dirname, "..", "..", "inputs", "six.txt"|]);

let input = Node.Fs.readFileSync(input_path, `utf8);

let get_current_max = (arr) =>
  arr
  |> Array.fold_left(
       (acc, curr) => {
         let (highest, index_of_lowest, index) = acc;
         let (highest, index_of_lowest) =
           if (curr > highest) {
             (curr, index)
           } else {
             (highest, index_of_lowest)
           };
         (highest, index_of_lowest, index + 1)
       },
       (Pervasives.min_int, 0, 0)
     );

let rec distribute = (arr, index, count) =>
  if (count === 0) {
    arr
  } else {
    let index = (index + 1) mod Array.length(arr);
    let item = arr[index];
    arr[index] = item + 1;
    distribute(arr, index, count - 1)
  };

let as_string = (value) => value |> Js.Array.joinWith(" ");

let rec move_through_first = (value, distributions) => {
  let (highest, index, _) = get_current_max(value);
  value[index] = 0;
  let next_value = distribute(value, index, highest);
  let stringed = next_value |> as_string;
  if (List.exists((x) => x === stringed, distributions)) {
    List.length(distributions) + 1
  } else {
    let distributions = distributions @ [next_value |> as_string];
    move_through_first(next_value, distributions)
  }
};

let rec move_through_second = (value, distributions, count) => {
  let (highest, index, _) = get_current_max(value);
  value[index] = 0;
  let next_value = distribute(value, index, highest);
  let stringed = next_value |> as_string;

  let x = List.filter((x) => x === stringed, distributions) |> List.length;
  let distributions = distributions @ [next_value |> as_string];

  if (x > 1) {
    count
  } else if (x > 0) {
    move_through_second(value,distributions, count + 1);
  } else {
    move_through_second(value, distributions, 0);
  }
};

let calculate = (value) => {
  let value = value |> Js.String.split("\t") |> Array.map(int_of_string);
  Js.log(move_through_first(value, []));
  Js.log(move_through_second(value, [], 0))
};

let test = "0\t2\t7\t0";

Js.log("Test output:");

calculate(test);

Js.log("Actual Output:");

calculate(input);
