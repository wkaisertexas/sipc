/*
 * This function requires an extension to type inference referred
 * to as "let polymorphism".  This is not implemented in the sipc 
 * compiler, so to compile this program use the "-dt" option to
 * disable type checking.  
 */

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

// new operators, e.g., or, mod, and not equals
orodd(x,y) { return x or (y % 2 != 0); }            

main() {
  var a;
  a = [ 13, 7, -4, 14, 0 ];

  // The following statement would produce: "30"
  if (fold(a, 0, sum) != 30) error fold(a, 0, sum); 

  // The following statement would produce: "true"
  if (not fold(a, false, orodd)) error fold(a, false, orodd); 

  return 0;
}
