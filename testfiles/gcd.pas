(*******************************************
 * File: gcd.pas
 * A program to compute Greatest Common Divisor
 * 
 * Compile with the following command:
 * # fpc -MOBJFPC gcd.pas
 *******************************************)
program gcd;
var
    a, b: Integer;
    x, y, z: Integer;

// Function to compute the Greatest Common Divisor
function gcd(a: Integer; b: Integer): Integer;
begin
    if b = 0 then
        gcd := a;
    else
        gcd := gcd(b, a mod b);
end;

begin
    a := 10;
    b := 20;
    x := a;
    y := b;
    z := gcd(x, y);

    writeln(z);
end. 
