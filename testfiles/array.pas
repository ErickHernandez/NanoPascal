program array1;
var
    a: array[1 .. 5] of Integer;
    i, x: Integer;
begin
    a[1] := 10;
    a[2] := 20;
    a[3] := 30;
    a[4] := 40;
    a[5] := 50;

    writeln(a[1], ' ',a[2], ' ',a[3], ' ',a[4], ' ',a[5]);
    x := a[1];
    a[1] := a[2];
    a[2] := x;
    writeln(a[1], ' ',a[2], ' ',a[3], ' ',a[4], ' ',a[5]);
end.
