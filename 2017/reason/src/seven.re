let dirname =
  switch [%bs.node __dirname] {
  | None => ""
  | Some(dir) => dir
  };

let input_path = Node.Path.join([|dirname, "..", "..", "inputs", "seven.txt"|]);
let input = Node.Fs.readFileSync(input_path, `utf8);

