add_two(x) {
  return x + 2;
}

main(a) {
  var x, i;

  x = 0;
  i = 0;
  while(i < 1000000000) {
    x = add_two(a);
    i = i + 1;
  }
  
  return x;
}