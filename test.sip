main(n, x) {
    var i, c1, c2, c3;
    c1 = 1;
    c2 = 2;
    c3 = 3;
    for(i : 1..n) {
        if(x > 0) {
            c1 = c1 + i;
            c2 = c2 * i;
            c3 = c3 - i;
        } else {
            c1 = c1 * 2;
            c2 = c2 + 3;
            c3 = c3 / 2;
        }
    }
    return c1 + c2 + c3;
}