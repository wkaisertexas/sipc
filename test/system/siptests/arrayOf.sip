main(){
    var x, y, z, j;

    x = [5 of 3];

    if (x[0] != 3) {
        error 0;
    }

    if(x[1] != 3) {
        error 0;
    }

    if(x[2] != 3) {
        error 0;
    }

    x[1] = 4;
    x[2] = 5;

    if (x[0] != 3) {
        error 0;
    }

    if(x[1] != 4) {
        error 0;
    }

    if(x[2] != 5) {
        error 0;
    }

    y = [5 of [5 of 3]];

    if (y[0][0] != 3) {
        error 0;
    }

    if(y[0][1] != 3) {
        error 0;
    }

    if(y[0][2] != 3) {
        error 0;
    }

    z = [5 of [5 of {a: 1, b: 2}]];

    if (z[0][0].a != 1) {
        error 0;
    }

    if (z[0][0].b != 2) {
        error 0;
    }

    j = [5 of [5 of false]];

    if (j[0][0] != false) {
        error 0;
    }

    return 0;
}