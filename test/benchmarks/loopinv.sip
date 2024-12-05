main(x) {
    var c, i, j;
    c = 0;
    i = 0;
    while(i < 1000000000) {
        j = 10 * x + 5 * 10 * 4 + x + 12 + x + x + 12 + 34 + x + x + (x + x - x + x + x + 12);
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        j = j + x;
        c = c + j;
        i++;
    }
    return c;
}