main() {
  var t, f;
  t = true;
  f = false;
  if(not (t and t)) {
    error 0;
  }

  if(t and f) {
    error 0;
  }

  if(f and f) {
    error 0;
  }

  if(not (t or f)) {
    error 0;
  }

  if(not (t or t)) {
    error 0;
  }

  if(f or f) {
    error 0;
  }

  return 0;
}
