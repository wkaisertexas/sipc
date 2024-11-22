// in-place insertion sort for array of integers
sort(a) {
  var i, j, k, break;
  for (i : 1 .. #a) {
    k = a[i];                    // array indexing
    j = i - 1;

    /* SIP's logical operators do not use short-circuit evaluation
     * so this more complex logic is required.
     */
    break = false;
    while (j >= 0 and not break) {
      if (a[j] > k) { 
        a[j+1] = a[j];
        j--;       
      } else {
        break = true;
      }
    }

    a[j+1] = k;
  } 
  return a;
}

array_median(a) {
  var s;
  s = sort(a);    
  return s[#s/2]; 
}

main() {
  var a, m;
  a = [ 13, 7, -4, 14, 0 ];
  m = array_median(a);
  if (m != 7) error m;
  return 0;
}
