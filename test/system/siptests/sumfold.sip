/* 
 * This is a higher-order function of type:
 *    ([\alpha1], \alpha2, (\alpha2, \alpha1) -> \alpha2) -> \alpha2
 */
fold(a, i, f) {
  var s, e;
  s = i;
  for (e : a) {                 // iterator-style for loop  
    s = f(s,e);                  
  }
  return s;
}

sum(x,y) { return x + y; }

main() {
  var a;
  a = [ 13, 7, -4, 14, 0 ];

  // The following statement would produce: "30"
  if (fold(a, 0, sum) != 30) error fold(a, 0, sum); 

  return 0;
}
