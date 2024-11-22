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

orodd(x,y) { output x; output y; return x or (y % 2 != 0); }            

main() {
  var a;
  a = [ 13, 7, -4, 14, 0 ];

  if (not fold(a, false, orodd)) error fold(a, false, orodd); 

  return 0;
}
