main() {
  var t, f, x;
  x = 1;
  x++;
  x--;

  if(x == 1) {
    t = 1;
  } else {
    error 0;
  }

  t--;
  t++;
  t--;

  if(t == 0){
    f = 0;
  } else {
    f = 1;
    error 0;
  }

  return 0;
}
