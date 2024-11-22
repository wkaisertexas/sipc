array_copy(a) {
  var b, i;
  b = [ #a of a[0] ];	
  for (i : 0 .. #a) {   
    b[i] = a[i];
  }
  return b;
}

main() {
  var a, b, x;
  a = [ 13, 7, -4, 14, 0 ];
  b = array_copy(a);
  if (a[1] != b[1]) error b[1];
  if (b[3] != 14) error b[3];
  return 0;
}
