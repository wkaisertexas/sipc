

main(n) {
  var a, b, c, d, e, i, x;
  a = 1;
  b = 2;
  c = 3;
  d = 4;
  e = 5;
  x = 0;
  for(i : 0 .. n) {
    x = x + a + b + c + d + e;
  }
  return x;
}