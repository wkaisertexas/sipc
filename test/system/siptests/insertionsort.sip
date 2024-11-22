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

copy(a) {
  var b, i;
  b = [ #a of 0 ];	// computed array initialization
  for (i : 0 .. #a) {   
    b[i] = a[i];
  }
  return b;
}

main() {
  var a, b, x;
  var e;
  a = [ 13, 7, -4, 14, 0 ];
  b = copy(a);
  a[2] = 2;
  a[4] = 3;
  if (sort(b)[0] != -4) error sort(b)[0];
  if (sort(b)[1] != 0) error sort(b)[1];
  if (sort(b)[2] != 7) error sort(b)[2];
  if (sort(b)[3] != 13) error sort(b)[3];
  if (sort(b)[4] != 14) error sort(b)[4];
  if (sort(a)[0] != 2) error sort(a)[0];
  if (sort(a)[1] != 3) error sort(a)[1];
  if (sort(a)[2] != 7) error sort(a)[2];
  if (sort(a)[3] != 13) error sort(a)[3];
  if (sort(a)[4] != 14) error sort(a)[4];
  return 0;
}
