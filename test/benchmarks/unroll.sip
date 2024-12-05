main(n) {
    var c, i, j;
    c = 0;

    for(j : 1.. n) {
        for(i : 1..4) {
            c = c * 2;
        }
    }
    return c;
}
