main() {
  var i, s;

  s = 0;
  for (i : 0 .. 10) {
    s = s + i;
  } 
  if (s != 45) error s;

  for (i : 0 .. 10 by 2) {
    s = s + i;
  }
  if (s != 65) error s;

  return 0;
}
