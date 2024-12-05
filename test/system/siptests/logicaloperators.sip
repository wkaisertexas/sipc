main() {
  var x, y, z;
  x = true;
  y = false;
  z = true;
  if (not x) error -1;
  if (not (y or z)) error -1;
  if (not (x and z)) error -1;
  return 0;
}
