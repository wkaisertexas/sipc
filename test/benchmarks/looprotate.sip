main(n) {
    var c, i, j, k;
    c = [(n + 4) * (n + 4) + 4 of 1];

    for(k : 1 .. 100) {
        for(j : 1.. n) {
            for(i : 1 .. n) {
                c[j + i * n] = c[j + i * n] + 1;
            }
        }
    }

    return c[1];
}
