main(x) {
    var c, i;
    c = 0;
    for(i : 1..1000000000) {
        c = c + x;
    }
    return c;
}