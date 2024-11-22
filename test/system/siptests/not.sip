main() {
  var t, f, x;
  x = false;
  x = not x;

  if(x) {
    t = 1;
  } else {
    error 0;
  }

  x = not x;
  if(x) {
    f = 1;
    error 0;
  } else {
    f = 0;
  }

  return 0;
}
