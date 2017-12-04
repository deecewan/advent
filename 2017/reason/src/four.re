let dirname = switch [%bs.node __dirname] {
  | None => ""
  | Some(dir) => dir
};
let input_path = Node.Path.join([|dirname, "..", "..", "inputs", "four.txt"|]);
let input = Node.Fs.readFileSync(input_path, `utf8);

let has_duplicates = (row) => {
  row |> Array.map((i) => {
      Array.map((j) => {
         if (i === j) {
            1;
         } else {
           0;
         }
      }, row) |> Array.fold_left((acc, curr) => acc + curr, 0);
    }) |> Array.fold_left((acc, curr) => acc + curr, 0) > Array.length(row);
};

let test_has_duplicates = (string, expected) => {
  let result = string |> Js.String.split(" ") |> has_duplicates;
  Js.log("Expected string to be " ++ string_of_bool(expected) ++ ", got " ++ string_of_bool(!result) ++ ".");
};

test_has_duplicates("aa bb cc dd ee", true);
test_has_duplicates("aa bb cc dd aa", false);
test_has_duplicates("aa bb cc dd aaa", true);

let sort_strings = (row) => {
  row |> Array.map(word => {
    let split = word |> Js.String.split(""); 
    split |> Array.sort(Pervasives.compare);
    split |> Js.Array.join;
  });
};

input |> Js.String.split("\n")
  |> Array.map(Js.String.split(" "))
  /* uncommon the next line to solve part b */
  |> Array.map(sort_strings)
  |> Array.map(has_duplicates)
  |> Array.fold_left((acc, curr) => acc + (curr ? 0 : 1), 0)
  |> string_of_int
  |> s => Js.log("There are " ++ s ++ " valid passwords.");
