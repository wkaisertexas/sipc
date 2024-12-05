
main() {
  var a, b;
  a = [ 13, 7, -4, 14, 0 ];

  b = [ #a of a[0] ];	

  if (a[3] != 14) error a[3];
  if (b[3] != 13) error b[3];

  return 0;
}
