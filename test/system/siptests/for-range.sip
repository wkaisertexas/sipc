main() {
  var x, y;
  x = 0;
  y = 0;
  for(y : 1..3) {
    x = x + y;
  }

  if(x != 3) {
    error 0;
  }

  return x;
}
