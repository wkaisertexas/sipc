main(n) {
  var i, s;
  s = 0;
  for (i : 0 .. n * 2 by 2) {
    s = s + i;
  }
  return s;
}