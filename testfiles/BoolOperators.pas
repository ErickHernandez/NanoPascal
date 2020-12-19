(*******************************************
 * File: BoolOperators.pas
 * A test program for boolean operators
 * 
 * Compile with the following command:
 * # fpc -MOBJFPC BoolOperators.pas
 *******************************************)
program BoolOperators;
var x, y: Integer;

begin
    {$ifdef RANDOM}
    Randomize;

    x := Random(100) + 1;
    y := Random(100) + 1;
    {$else}
    x := 10;
    y := 20;
    {$endif}

    writeln('X = ', x, ' Y = ', y);

    // And
    writeln('x = 10 and y = 20: ', (x = 10) and (y = 20));
    
    // or
    writeln('x = 10 or y = 30: ', (x = 10) or (y = 20));
    
    // Greather or Equal
    writeln('not x >= y: ', not (x >= y));
end.
(*** Expected output (non random) ***
X = 10 Y = 20
x = 10 and y = 20: TRUE
x = 10 or y = 30: TRUE
not x >= y: TRUE
*)