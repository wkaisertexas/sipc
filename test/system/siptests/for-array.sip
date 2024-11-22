main() {
  var x, y, z;
  x = [1, 2, 3];
  z = 0;
  for(y : x) {
    z = z + y;
  }

  if(z != 6) {
    error 0;
  }

  return z;
}
