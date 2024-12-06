add_two(x) {
  return x + 2;
}

main(n) {
  var i, s;
  s = 0;
  for(i : 0 .. n) {
    s = add_two(i);
    s = add_two(i);
    s = add_two(i);
    s = add_two(i);
    s = add_two(i);
  }
  return s;
}