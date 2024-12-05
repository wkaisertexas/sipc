main() {
  var x, y, z;
  x = 1;
  y = 8;
  z = 13;
  if (y < 8) error 8 - y;
  if (not (y <= 8)) error 8 - y;
  if (13 > z) error 13 - z;
  if (not (13 >= z)) error 13 - z;
  if (y+5 != z) error y+5-z;
  if (not (y+5 == z)) error y+5-z;
  return 0;
}
