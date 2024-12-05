autovectorize(x, y, z, n) {
    var i;
    for(i : 0 .. n){
        x[i] = y[i] + z[i];
    }
    return 0;
}

main(n) {
    var x, y, z, i, j, k;

    x = [1 of n];
    y = [2 of n];
    z = [3 of n];

    for(i: 0 .. n){
        for(i : 0 .. n){
            x[i] = y[i] + z[i];
        }
    }

    return 0;
}