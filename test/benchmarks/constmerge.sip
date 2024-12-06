

main(n) {
  var a, b, c, d, e, i, x, z, y;
  a = 1;
  b = 2;
  c = 3;
  d = 4;
  e = 5;
  x = 0;
  y = 3;
  z = 4;
  for(i : 0 .. n) {
    x = x + a + b + c + d + e + y + z;
    x = x + a + b + c + d + e + y + z;
    x = x + a + b + c + d + e + y + z;
    x = x + a + b + c + d + e + y + z;
  }
  return x;
}