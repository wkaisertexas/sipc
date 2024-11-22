main() {
  var t, f, x;
  x = 1;
  x = -x;

  if(x == -1) {
    t = 1;
  } else {
    error 0;
  }

  x = -x;
  if(x == 1) {
    f = 1;
  } else {
    f = 0;
    error 0;
  }

  return 0;
}
