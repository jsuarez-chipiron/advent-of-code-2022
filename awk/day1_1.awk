BEGIN {
    max = 0
    current = 0
}
{
    if ( $0 == "" ) {
        if ( current > max ) {
            max = current
        }
        current = 0
    } else {
        current += $0
    }
}
END {
    if ( current > max ) {
        max = current
    }
    print max
}
