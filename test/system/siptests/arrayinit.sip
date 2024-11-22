main() {
  var x, y, z;
  y = 3;
  x = [y+3, 13, 42];
  if (x[0] != 6) error x[0];
  x = [7 of 9];
  if (x[4] != 9) error x[4];
  z = [5 of [5 of 5]];
  if (z[3][3] != 5) error z[3][3];
  z = [[1,2,3], [4,5,6], [7,8,9]];
  if (z[1][1] != 5) error z[1][1];
  return 0;
}
