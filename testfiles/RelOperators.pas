(*******************************************
 * File: RelOperators.pas
 * A test program for relational operators
 *******************************************)
program RelOperators;
var x, y: Integer;

begin
    {$ifdef RANDOM}
    Randomize;

    x := Random(100) + 1;
    y := Random(100) + 1;
    {$else}
    x := 4567;
    y := 33;
    {$endif}

    writeln('X = ', x, ' Y = ', y);

    // Greather than
    writeln('x > y: ', x > y);
    
    // Less than
    writeln('x < y: ', x < y);
    
    // Greather or Equal
    writeln('x >= y: ', x >= y);
    
    // Less or Equal
    writeln('x <= y: ', x <= y);
    
    // Not Equal
    writeln('x <> y: ', x <> y);
    
    // Equal
    writeln('x = y: ', x = y);
end.
(*** Expected output (non random) ***
X = 4567 Y = 33
x > y: TRUE
x < y: FALSE
x >= y: TRUE
x <= y: FALSE
x <> y: TRUE
x = y: FALSE
*)