main() {
  var t, f, x, y;
  t = true;
  f = false;
  if(t) {
    x = true;
  } else {
    error 0;
  }

  if(f) {
    error 0;
  } else {
    y = true;
  }

  return 0;
}
