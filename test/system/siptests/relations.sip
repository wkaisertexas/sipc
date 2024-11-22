main() {
  var x, y;
  x = 1;
  y = 2;
  if(not (x < y)) {
    error 0;
  } 

  if(not (x <= x)) {
    error 0;
  }

  if(not (x <= y)) {
    error 0;
  }

  if(not (y > x)) {
    error 0;
  }

  if(not (y >= x)) {
    error 0;
  }


  if(not (y >= y)) {
    error 0;
  }
  return 0;
}
