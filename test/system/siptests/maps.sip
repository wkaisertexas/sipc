/* 
 * This is a higher-order function of type:
 *    ([\alpha1], (\alpha1) -> \alpha2) -> [\alpha2]
 */
map(a, f) {
  var m, i;
  m = [#a of f(a[0])];
  for (i : 0 .. #a) {            
    m[i] = f(a[i]);
  }
  return m;
}

ispositive(x) { return x > 0; }

main() {
  var a, b;
  a = [ 13, 7, -4, 14, 0 ];

  // The following statement should produce: [true, true, false, true, false]
  b = map(a, ispositive);

  if (not b[0]) error b[0];
  if (not b[1]) error b[1];
  if (b[2]) error b[2];
  if (not b[3]) error b[3];
  if (b[4]) error b[4];
  return 0;
}
