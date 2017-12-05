/*
  No code required for this one.
  Input was 265149.

  The square root of that is 514.9. The next 'last square' of the 
  sequence is 515 - there are 515 places along each axis of the board.
  That means there is (515 / 2) - .5 = 257 distance between my location and the
  centre of the board. I am (515^2 - 265149) squares away from the centre
  along the edge. So, the result is (257 + 257), which would get me from 515^2
  to the middle, minus the distance I am already toward the middle (76).
  514 - 76 = 438.

  Below, I've written some code that is correct for *my* input. It's not a 
  general solution.

  The next part was a sequence called 'Square spiral of sums of selected preceding terms'
  which is available on OEIS (https://oeis.org/A141481). This had my solution as the 58th
  term, 266, 330. Work smarter, not harder.
 */

let next_larger_square = (input) => {
  input |> float_of_int |> Js.Math.sqrt |> Js.Math.ceil
};

/* turns out if you leave this as an int, it will floor automatically */
let steps_to_center = (square_size: int) => square_size / 2;

let steps_back_from_edge = (bigger_square: int, input: int) => {
  let bigger_square_float = bigger_square |> float_of_int;
  let input_float = input |> float_of_int;

  let result = (bigger_square_float ** 2.) -. input_float;
  result |> int_of_float;
};

let value = 265149;

let print_result = (result) => Js.log("Total steps: " ++ string_of_int(result));

let calculate = (input) => {
  Js.log("Result for input " ++ string_of_int(input) ++ ":");
  let larger_square = next_larger_square(input);
  let steps_back = steps_back_from_edge(larger_square, input);
  let steps_from_center = steps_to_center(larger_square);
  if (steps_from_center < steps_back) {
    print_result(steps_back);
  } else {
    print_result((steps_to_center(larger_square) * 2) - steps_back);
  }
};

calculate(value);
calculate(325489);
