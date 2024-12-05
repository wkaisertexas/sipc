main() {
  var z;

  z = [[101,102], [103,104]];
  if (z[0][0] != 101) error z[0][0];
  if (z[0][1] != 102) error z[0][1];
  if (z[1][0] != 103) error z[1][0];
  if (z[1][1] != 104) error z[1][1];

  z = [[1,2,3], [4,5,6], [7,8,9]];
  if (z[0][0] != 1) error z[0][0];
  if (z[0][1] != 2) error z[0][1];
  if (z[0][2] != 3) error z[0][2];
  if (z[1][0] != 4) error z[1][0];
  if (z[1][1] != 5) error z[1][1];
  if (z[1][2] != 6) error z[1][2];
  if (z[2][0] != 7) error z[2][0];
  if (z[2][1] != 8) error z[2][1];
  if (z[2][2] != 9) error z[2][2];
  return 0;
}
